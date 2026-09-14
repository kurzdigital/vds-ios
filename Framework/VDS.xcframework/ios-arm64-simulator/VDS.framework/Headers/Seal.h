#import <Foundation/Foundation.h>

#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

// The framework is built with hidden visibility, so the string constants
// have to be exported explicitly like the classes are.
#define VDS_EXPORT extern __attribute__((visibility("default")))

// What kind of trust material verify() requires. Lets a caller supply
// the right input without knowing the format.
typedef NS_ENUM(NSInteger, SealTrustRequirement) {
    SealTrustRequirementNone,
    SealTrustRequirementCertificate,
    SealTrustRequirementPublicKey
};

typedef NS_ENUM(NSInteger, SealVerification) {
    SealVerificationUnsupported,
    SealVerificationInvalid,
    SealVerificationValid
};

// A format is a string so a new one cannot break a switch over the
// known ones.
VDS_EXPORT NSString * const SealFormatDoc2D;
VDS_EXPORT NSString * const SealFormatCheckAT;
VDS_EXPORT NSString * const SealFormatBESeal;

// Metadata names shared between formats. A format sets what it has.
VDS_EXPORT NSString * const SealMetaVersion;
VDS_EXPORT NSString * const SealMetaAlgorithm;
VDS_EXPORT NSString * const SealMetaIssuer;
VDS_EXPORT NSString * const SealMetaIssuerCountry;
VDS_EXPORT NSString * const SealMetaCertificateReference;
VDS_EXPORT NSString * const SealMetaDocumentType;
VDS_EXPORT NSString * const SealMetaDocumentIssueDate;
VDS_EXPORT NSString * const SealMetaSignatureCreationDate;

// One type for all proprietary seal formats. What used to be a per
// format header is a list of named metadata features here.
__attribute__((visibility("default")))
@interface SealResult : NSObject

@property (nonatomic, copy) NSString *format;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSArray<VDSFeature *> *metadata;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy) NSArray<VDSFeature *> *unsignedFeatures;
@property (nonatomic, copy) NSString *keyIdentifier;
@property (nonatomic) SealTrustRequirement trustRequirement;
@property (nonatomic, copy) NSData *signedData;
@property (nonatomic, copy) NSData *digest;
@property (nonatomic, copy) NSData *signature;

- (instancetype)initWithFormat:(NSString *)format
                          name:(NSString *)name
                      metadata:(NSArray<VDSFeature *> *)metadata
                      features:(NSArray<VDSFeature *> *)features
              unsignedFeatures:(NSArray<VDSFeature *> *)unsignedFeatures
                 keyIdentifier:(NSString *)keyIdentifier
              trustRequirement:(SealTrustRequirement)trustRequirement
                    signedData:(NSData *)signedData
                        digest:(NSData *)digest
                     signature:(NSData *)signature;

- (SealVerification)verify:(NSData *)trust;

- (SealVerification)verify:(NSData *)trust
                       now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
