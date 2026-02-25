#import <Foundation/Foundation.h>

#import "IDBHeader.h"
#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, IDBVerificationResult) {
    IDBVerificationResultSignatureInvalid,
    IDBVerificationResultSignatureValid,
    IDBVerificationResultSignatureUnsigned
};

__attribute__((visibility("default")))
@interface IDBResult : NSObject

@property (nonatomic, strong) IDBHeader *header;
@property (nonatomic, assign) bool isSigned;
@property (nonatomic, assign) bool isZipped;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy) NSData *certificate;
@property (nonatomic, copy) NSData *signature;
@property (nonatomic, copy) NSData *sha256;
@property (nonatomic, copy) NSString *raw;
@property (nonatomic, copy, nullable) NSString *profiles;

- (instancetype)initWithHeader:(IDBHeader *)header
                      isSigned:(bool)isSigned
                      isZipped:(bool)isZipped
                      features:(NSArray<VDSFeature *> *)features
                   certificate:(NSData *)certificate
                     signature:(NSData *)signature
                        sha256:(NSData *)sha256
                           raw:(NSString *)raw;

- (instancetype)initWithHeader:(IDBHeader *)header
                      isSigned:(bool)isSigned
                      isZipped:(bool)isZipped
                      features:(NSArray<VDSFeature *> *)features
                   certificate:(NSData *)certificate
                     signature:(NSData *)signature
                        sha256:(NSData *)sha256
                           raw:(NSString *)raw
                      profiles:(nullable NSString *)profiles;

- (IDBVerificationResult)verify:(NSString *)masterListPath;

- (IDBVerificationResult)verify:(NSString *)masterListPath
                             now:(nullable NSDate *)now;

- (IDBVerificationResult)verifyWithCertificateData:(NSData *)certificate;

- (IDBVerificationResult)verifyWithCertificateData:(NSData *)certificate
                                               now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
