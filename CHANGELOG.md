# Changelog

## 2.1.0
* Revert split IPO name into two fields

## 2.0.1
* Fix exported symbols of iOS wrapper

## 2.0.0
* Decode all proprietary formats into one collective type
* Add vds::decodeSeal() to detect the format of a barcode
* Unify verification across the proprietary formats

Breaking: `doc2d::Doc2D`, `checkat::CheckAT` and `beseal::BESeal` are
replaced by `vds::Seal`, and `Doc2DDecoder`, `CheckAtDecoder` and
`BeSealDecoder` by `SealDecoder` on Android and iOS. What used to be a
header per format is a list of named metadata features now. See
[README_SEAL.md](README_SEAL.md).

## 1.3.2
* Support International Police Organization ID Cards

## 1.3.1
* Decode the Indonesia KTP fields as the generator writes them now
* Support IDB dates of three and four bytes
* Fix decoding C40 triples whose packed value ends in a zero byte

## 1.3.0
* Support Austrian ID QR Code format
* Support DataMatrix code on Belgian passports

## 1.2.8
* Preserve already DER-encoded ECDSA signatures

## 1.2.7
* Replace timelocal() with mktime() for portability

## 1.2.6
* Add support for 2D-Doc format

## 1.2.5
* Fix parsing VDS version 4
* Support Romania QR Code format

## 1.2.4
* Update CSCA MasterList
* Add another IDB profile

## 1.2.3
* Verify expired VDS sample too
* Fix building with gcc
* Update CSCA MasterList

## 1.2.2
* Improve iOS wrapper

## 1.2.1
* Add face image to IDB profiles

## 1.2.0
* Support IDB format
* Support VDS version 4+
* Support verification dates
* Unify document features across VDS, VDS-NC and IDB
* Include ObjC sources in XCFramework
* Use 16 KB ELF alignment for Android library
* Fix translating timestamps on Android

## 1.1.3
* Simplify VDS-NC data structure

## 1.1.2
* Improve iOS VDS-NC data types

## 1.1.1
* Prefix VDS-NC ICAO data types

## 1.1.0
* Return VDS-NC in proper objects
* Add iOS wrapper and example

## 1.0.6
* Return document number including version part for Swiss driver licenses
* Update CSCA MasterList

## 1.0.5
* Remove support for incomplete MRZs on Swiss driver licenses

## 1.0.4
* Also return invalid MRZs including error information
* Update CSCA MasterList

## 1.0.3
* Support another MRZ format of Swiss driver licenses

## 1.0.2
* Return Swiss driver licenses blank number and language
* Update CSCA MasterList

## 1.0.1
* Use our own fork of the OpenSSL-CMake wrapper
* Make Date in Android VDS header non-nullable
* Update CSCA MasterList
