#import <Foundation/Foundation.h>

#import "VDSFeature.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface CheckATResult : NSObject

@property (nonatomic, copy) NSString *certificateId;
@property (nonatomic, copy) NSArray<VDSFeature *> *features;
@property (nonatomic, copy) NSData *sha256;
@property (nonatomic, copy) NSData *signature;
@property (nonatomic, copy) NSData *derSignature;

- (instancetype)initWithCertificateId:(NSString *)certificateId
                             features:(NSArray<VDSFeature *> *)features
                               sha256:(NSData *)sha256
                            signature:(NSData *)signature
                         derSignature:(NSData *)derSignature;

- (BOOL)verify:(NSData *)publicKey;

@end

NS_ASSUME_NONNULL_END
