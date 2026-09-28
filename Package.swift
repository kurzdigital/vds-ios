// swift-tools-version: 5.8

import PackageDescription

let package = Package(
    name: "VDS",
    platforms: [
        .iOS(.v15)
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
