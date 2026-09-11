# VDS/VDS-NC/IDB for iOS

Parse and verify:

* [Visible Digital Seals][vds]
* [ICAO VDS-NC (Non-Constrained)][vdsnc]
* [ICAO Datastructure for Barcode][idb]

The proprietary formats below all decode into one collective type:

* [2D-Doc][doc2d]
* [CHECK-AT (Austrian identity card)][checkat]
* [Belgian Digital Seal][beseal] (parsing only)

## Example App

The folder `Example` contains a minimal functional demo app.

Remember to set your Team in the `Signing & Capabilities` settings for the
Target `Example` in this project, when building for an iOS device.

## Framework Installation

Add this framework to your Xcode project:

1. Open your project in Xcode.
2. Navigate to `File > Add Package Dependencies`.
3. Enter the repository URL: `https://github.com/kurzdigital/vds-ios` and add the package.

## Usage

Here is a simple example:

```swift
import VDS

if let idbResult = IDBDecoder.decode(text) {
	…
} else if let vdsResult = VDSDecoder.decode(bytes) {
	…
} else if let vdsNcResult = VDSNCDecoder.decode(text) {
	…
} else if let sealResult = SealDecoder.decode(text) ?? SealDecoder.decodeBytes(bytes) {
	…
}
```

2D-Doc, CHECK-AT and the Belgian Digital Seal all decode into one
`SealResult`. A new proprietary format is added in the native library.
As long as it is verified with a certificate or a public key, nothing in
this wrapper or in your app has to change for it. A format that needs
another kind of trust material adds a `SealTrustRequirement`, which a
`switch` over it has to handle.

`sealResult.format` says which format it is, `SealFormatDoc2D` for
example. Note that `VDSDecoder` has to be tried first because a binary
2D-Doc borrows the VDS header.

What used to be the header of the individual formats is in
`sealResult.metadata`, an array of `VDSFeature` just like
`sealResult.features`, so both can be rendered without knowing the
format. Features that are not covered by the signature, like the 2D-Doc
annex, are in `sealResult.unsignedFeatures`.

The seal says what kind of trust material it needs:

```swift
switch sealResult.trustRequirement {
case .certificate:
	// sealResult.keyIdentifier names the certificate.
	_ = sealResult.verify(certificate) == .valid
case .publicKey:
	// sealResult.keyIdentifier names the public key. For CHECK-AT the
	// keys are rotated every three months and published at
	// https://api.check-at.gv.at/api/v2/certificates.
	_ = sealResult.verify(publicKey) == .valid
case SealTrustRequirement.none:
	// The seal cannot be verified. This is the case for the Belgian
	// Digital Seal, whose certificate is not publicly available.
	break
@unknown default:
	break
}
```

## Changelog

[Changelog](CHANGELOG.md)

## License

[LICENSE](LICENSE)

## Support

If you encounter any issues or have any questions, we encourage you to open
an issue in the GitHub issue tracker.

[vds]: https://visibledigitalseal.org/
[vdsnc]: https://www.icao.int/Security/FAL/TRIP/PublishingImages/Pages/Publications/Guidelines%20-%20VDS%20for%20Travel-Related%20Public%20Health%20Proofs.pdf
[idb]: https://www.icao.int/sites/default/files/TRIP/Publications/ICAO-TR-ICAO-Datastructure-for-Barcode.pdf
[doc2d]: https://fr.wikipedia.org/wiki/2D-Doc
[checkat]: https://github.com/Yepoleb/idcard-qr
[beseal]: https://www.consilium.europa.eu/prado/en/BEL-AO-11001/index.html
