// swift-tools-version: 5.8

import PackageDescription

let package = Package(
    name: "VDS",
    platforms: [
        .iOS(.v14)
    ],
    products: [
        .library(
            name: "VDS",
            targets: ["VDS"])
    ],
    targets: [
        .binaryTarget(
            name: "VDS",
            path: "Framework/VDS.xcframework")
    ]
)
