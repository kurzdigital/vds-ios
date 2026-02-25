# VDS/VDS-NC/IDB for iOS

Parse and verify:

* [Visible Digital Seals][vds]
* [ICAO VDS-NC (Non-Constrained)][vdsnc]
* [ICAO Datastructure for Barcode][idb]

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
