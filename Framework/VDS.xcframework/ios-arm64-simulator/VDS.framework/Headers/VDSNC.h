#import <Foundation/Foundation.h>

#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VDSNCVerificationResult) {
    VDSNCVerificationResultSignatureInvalid,
    VDSNCVerificationResultSignatureValidCertificateUnknown,
    VDSNCVerificationResultSignatureValidCertificateVerified
};

__attribute__((visibility("default")))
@interface VDSNCHeader : NSObject

@property (nonatomic, copy) NSString *issuingCountry;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, assign) NSInteger version;

- (instancetype)initWithIssuingCountry:(NSString *)issuingCountry
                                  type:(NSString *)type
                               version:(NSInteger)version;

@end

__attribute__((visibility("default")))
@interface VDSNC : NSObject

@property (nonatomic, strong) VDSNCHeader *header;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy) NSData *sha256;
@property (nonatomic, copy) NSData *signature;
@property (nonatomic, copy) NSData *certificate;
@property (nonatomic, copy) NSString *name;

- (instancetype)initWithHeader:(VDSNCHeader *)header
                      features:(NSArray<VDSFeature *> *)features
                        sha256:(NSData *)sha256
                     signature:(NSData *)signature
                   certificate:(NSData *)certificate
                          name:(NSString *)name;

- (VDSNCVerificationResult)verify:(NSString *)cmsFilePath;

- (VDSNCVerificationResult)verify:(NSString *)cmsFilePath
                               now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
