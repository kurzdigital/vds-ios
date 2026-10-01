#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// The statuses follow the validation policy of ICAO Doc 9303-13,
// Appendix D.
typedef NS_ENUM(NSInteger, VDSVerificationStatus) {
    // The signature is valid, the certificate is trusted and it is
    // valid at the time of verification.
    VDSVerificationStatusValid,
    // The signature is valid and the certificate is trusted, but the
    // certificate or a CSCA of its chain is not valid at the time of
    // verification.
    VDSVerificationStatusExpiredCertificate,
    // No given certificate or key verifies the signature, and none of
    // them is the one the seal references.
    VDSVerificationStatusUnknownCertificate,
    // The signature is valid, but the certificate embedded in the seal
    // neither chains to a given CSCA nor is a given certificate.
    VDSVerificationStatusUntrustedCertificate,
    // The signature does not match the certificate the seal references
    // or embeds, or the embedded certificate cannot be read.
    VDSVerificationStatusInvalidSignature,
    // The seal carries no signature.
    VDSVerificationStatusUnsigned
};

__attribute__((visibility("default")))
@interface VDSVerification : NSObject

@property (nonatomic, assign) VDSVerificationStatus status;
// DER encoding of the certificate the signature was checked with.
// Empty if no certificate verified it or a public key was used.
@property (nonatomic, copy) NSData *certificate;

- (instancetype)initWithStatus:(VDSVerificationStatus)status
                   certificate:(NSData *)certificate;

@end

// Paths to the files a seal is verified against. Files that cannot be
// read or hold unexpected data are skipped.
__attribute__((visibility("default")))
@interface VDSTrustMaterial : NSObject

// Signer certificates, trusted as they are. X.509 (DER, or PEM with any
// number of certificates) or CMS files like .ml and .p7b.
@property (nonatomic, copy) NSArray<NSString *> *certificates;
// CMS files with CSCA certificates. A certificate embedded in a seal is
// trusted if it chains to one of them.
@property (nonatomic, copy) NSArray<NSString *> *cms;
// Public keys (PEM or DER) for seals that are signed with a bare key.
@property (nonatomic, copy) NSArray<NSString *> *publicKeys;

- (instancetype)initWithCertificates:(NSArray<NSString *> *)certificates
                                 cms:(NSArray<NSString *> *)cms
                          publicKeys:(NSArray<NSString *> *)publicKeys;

@end

NS_ASSUME_NONNULL_END
