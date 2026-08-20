import UIKit
import AVFoundation
import VDS
import ZXingCpp

class ExampleViewController: UIViewController {
    let captureSession = AVCaptureSession()
    lazy var preview = AVCaptureVideoPreviewLayer(session: captureSession)
    let queue = DispatchQueue(label: "com.kurzdigital.ios.vdsexample")
    let barcodeReader = ZXIBarcodeReader()
    let processingLock = DispatchSemaphore(value: 1)
    @MainActor
    var isPresentingAlert = false

    override func viewDidLoad() {
        super.viewDidLoad()

        self.preview.videoGravity = AVLayerVideoGravity.resizeAspectFill
        self.preview.frame = self.view.layer.bounds
        self.view.layer.addSublayer(self.preview)

        self.requestAccess {
            let discoverySession = AVCaptureDevice.DiscoverySession(
                deviceTypes: [
                    .builtInTripleCamera,
                    .builtInDualWideCamera,
                    .builtInDualCamera,
                    .builtInWideAngleCamera
                ],
                mediaType: .video,
                position: .back)

            let device = discoverySession.devices.first!
            let cameraInput = try! AVCaptureDeviceInput(device: device)
            self.captureSession.beginConfiguration()
            self.captureSession.addInput(cameraInput)
            let videoDataOutput = AVCaptureVideoDataOutput()
            videoDataOutput.setSampleBufferDelegate(self, queue: self.queue)
            videoDataOutput.videoSettings = [kCVPixelBufferPixelFormatTypeKey as String: kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange]
            videoDataOutput.alwaysDiscardsLateVideoFrames = true
            self.captureSession.addOutput(videoDataOutput)
            self.captureSession.commitConfiguration()
            DispatchQueue.global(qos: .background).async {
                self.captureSession.startRunning()
            }
        }
    }
}

extension ExampleViewController {
    func requestAccess(_ completion: @escaping () -> Void) {
        if AVCaptureDevice.authorizationStatus(for: AVMediaType.video) == .notDetermined {
            AVCaptureDevice.requestAccess(for: .video) { _ in
                completion()
            }
        } else {
            completion()
        }
    }

    private func showDialog(_ message: String) {
        DispatchQueue.main.async { [weak self] in
            guard let self else { return }

            guard !self.isPresentingAlert else {
                self.processingLock.signal()
                return
            }

            self.isPresentingAlert = true

            let alert = UIAlertController(
                title: "Decoded",
                message: message,
                preferredStyle: .alert
            )

            alert.addAction(UIAlertAction(title: "OK", style: .default) { [weak self] _ in
                self?.isPresentingAlert = false
                self?.processingLock.signal()
            })

            guard self.view.window != nil else {
                self.isPresentingAlert = false
                self.processingLock.signal()
                return
            }

            self.present(alert, animated: true)
        }
    }
}

extension ExampleViewController: AVCaptureVideoDataOutputSampleBufferDelegate {
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        guard self.processingLock.wait(timeout: DispatchTime.now()) == .success else {
            // The previous image is still processed, drop the new one to prevent too much pressure
            return
        }

        let imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer)!

        guard let result = try? barcodeReader.read(imageBuffer).first else {
            self.processingLock.signal()
            return
        }

        if let idbResult = IDBDecoder.decode(result.text) {
            showDialog(getIDBSummary(idbResult: idbResult))
        } else if let vdsResult = VDSDecoder.decode(result.bytes) {
            showDialog(getVDSSummary(vdsResult: vdsResult))
        } else if let vdsNcResult = VDSNCDecoder.decode(result.text) {
            showDialog(getVDSNCSummary(vdsNcResult: vdsNcResult))
        } else if let doc2dResult = Doc2DDecoder.decode(result.text) ?? Doc2DDecoder.decodeBytes(result.bytes) {
            showDialog(getDoc2DSummary(doc2dResult: doc2dResult))
        } else if let checkAtResult = CheckATDecoder.decode(result.text) {
            showDialog(getCheckATSummary(checkAtResult: checkAtResult))
        } else if let beSealResult = BESealDecoder.decode(result.text) {
            showDialog(getBESealSummary(beSealResult: beSealResult))
        } else {
            self.processingLock.signal()
        }
    }
}

private func getIDBSummary(idbResult: IDBResult) -> String {
    var out = """
Signed: \(idbResult.isSigned)
Zipped: \(idbResult.isZipped)
Messages:
\(formatFeatures(idbResult.features))
"""

    var verificationResult: String
    let masterListPath = Bundle.main.path(forResource: "csca-2026-07-24-04-00-30", ofType: "ml") ?? ""
    switch idbResult.verify(masterListPath) {
    case .signatureInvalid:
        verificationResult = "Signature invalid"
    case .signatureValid:
        verificationResult = "Signature valid"
    case .signatureUnsigned:
        verificationResult = "Barcode is unsigned"
    @unknown default:
        verificationResult = "Unknown verification result"
    }
    out += "\nVerification: " + verificationResult

    return out
}

private func getVDSSummary(vdsResult: VDSResult) -> String {
    var features = "Name: \(vdsResult.name)\n" +
        formatFeatures(vdsResult.features)

    features += "\nVerified: "
    if let certificate = verify(vdsResult: vdsResult) {
        features += "true (\(certificate))"
    } else {
        features += "false"
    }
    features += "\n"

    return features
}

private func getVDSNCSummary(vdsNcResult: VDSNC) -> String {
    var out = """
Name: \(vdsNcResult.name)
Features:
\(formatFeatures(vdsNcResult.features))
"""

    let masterListPath = Bundle.main.path(forResource: "csca-2026-07-24-04-00-30", ofType: "ml") ?? ""
    switch vdsNcResult.verify(masterListPath) {
    case .signatureInvalid:
        out += "\nVerification: Signature invalid"
    case .signatureValidCertificateUnknown:
        out += "\nVerification: Signature valid (certificate unknown)"
    case .signatureValidCertificateVerified:
        out += "\nVerification: Signature valid (certificate verified)"
    @unknown default:
        out += "\nVerification: Unknown verification result"
    }

    return out
}

private func getDoc2DSummary(doc2dResult: Doc2DResult) -> String {
    let h = doc2dResult.header
    var out = """
Version: \(h.version)
Authority: \(h.authorityIdentifier)
Certificate: \(h.certificateReference)
Document type: \(h.documentType)
Perimeter: \(h.perimeter)
Features:
\(formatFeatures(doc2dResult.features))
"""

    if let annex = doc2dResult.annex, !annex.isEmpty {
        out += "Annex:\n\(formatFeatures(annex))"
    }

    out += "\nVerified: "
    if let certificate = verifyDoc2D(doc2dResult: doc2dResult) {
        out += "true (\(certificate))"
    } else {
        out += "false"
    }
    out += "\n"

    return out
}

private func getCheckATSummary(checkAtResult: CheckATResult) -> String {
    var out = """
Certificate: \(checkAtResult.certificateId)
Features:
\(formatFeatures(checkAtResult.features))
"""

    // The public keys are rotated every three months and published at
    // https://api.check-at.gv.at/api/v2/certificates.
    if let publicKey = loadFile(forResource: checkAtResult.certificateId, ofType: "pem") {
        out += "\nVerified: \(checkAtResult.verify(publicKey))"
    } else {
        out += "\nVerified: no public key for \(checkAtResult.certificateId)"
    }
    out += "\n"

    return out
}

private func getBESealSummary(beSealResult: BESealResult) -> String {
    // There is no verification because the certificate the seal
    // references with its keyId is not publicly available.
    return """
Version: \(beSealResult.version)
Algorithm: \(beSealResult.algorithm)
Key ID: \(beSealResult.keyId.map { String(format: "%02X", $0) }.joined())
Features:
\(formatFeatures(beSealResult.features))
"""
}

private func verifyDoc2D(doc2dResult: Doc2DResult) -> String? {
    for fileName in certificates {
        guard let data = loadFile(name: fileName) else {
            continue
        }
        if doc2dResult.verify(data) {
            return fileName
        }
    }
    return nil
}

private func formatFeatures(_ features: [VDSFeature], indent: String = "") -> String {
    var output = ""
    for feature in features {
        let name = feature.name.isEmpty ? "tag:\(feature.tag)" : feature.name
        if let children = feature.children, !children.isEmpty {
            output += "\(indent)\(name):\n"
            output += formatFeatures(children, indent: indent + "  ")
            continue
        }

        output += "\(indent)\(name): "
        if let mrzInfo = feature.value as? VDSMRZInfo {
            output += """
documentCode: \(mrzInfo.documentCode)
issuingState: \(mrzInfo.issuingState)
primaryIdentifier: \(mrzInfo.primaryIdentifier)
secondaryIdentifier: \(mrzInfo.secondaryIdentifier)
nationality: \(mrzInfo.nationality)
documentNumber: \(mrzInfo.documentNumber)
dateOfBirth: \(mrzInfo.dateOfBirth)
sex: \(mrzInfo.sex)
dateOfExpiry: \(mrzInfo.dateOfExpiry)
optionalData1: \(mrzInfo.optionalData1)
optionalData2: \(mrzInfo.optionalData2)
errors: \(mrzInfo.errors.count)

"""
        } else if let value = feature.value {
            output += "\(value)\n"
        } else {
            output += "nil\n"
        }
    }

    return output
}

private func verify(vdsResult: VDSResult) -> String? {
    for fileName in certificates {
        guard let data = loadFile(name: fileName) else {
            continue
        }
        if vdsResult.verify(data) {
            return fileName
        }
    }
    return nil
}

private let certificates: [String] = [
    "doc2d_test.crt",
    "ETD.crt",
    "IndonesiaKtp.crt",
    "KDS_EasyCard_VDS.crt",
    "KDS_ETD.crt",
    "KDS_TAXSTAMPS.crt",
    "KDS_TEST_VACC.crt",
    "KDS_VEHICLE_VIGNETTE.crt",
    "SchoolAccess.crt",
    "sealgen_UTTS5B.crt"
]

private func loadFile(name: String) -> Data? {
    let components = name.split(separator: ".")
    return loadFile(forResource: String(components[0]), ofType: String(components[1]))
}

private func loadFile(forResource: String, ofType: String) -> Data? {
    guard let filePath = Bundle.main.path(forResource: forResource, ofType: ofType) else {
        print("File not found")
        return nil
    }
    do {
        return try Data(contentsOf: URL(fileURLWithPath: filePath))
    } catch {
        print("Error loading file \(filePath): \(error)")
        return nil
    }
}
