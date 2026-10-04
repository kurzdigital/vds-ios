#import <Foundation/Foundation.h>

#import "VDSHeader.h"
#import "VDSFeature.h"
#import "VDSVerification.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSResult : NSObject

@property (nonatomic, strong) VDSHeader *header;
@property (nonatomic, strong) NSArray<VDSFeature *> *features;
// SHA-256 of the signed data. The signature is not always made over this
// hash; verification uses `digest`.
@property (nonatomic, strong) NSData *sha256;
// Hash of the signed data that the signature was made over. Its
// algorithm depends on the length of the key.
@property (nonatomic, strong) NSData *digest;
@property (nonatomic, strong) NSData *signature;
@property (nonatomic, copy) NSString *name;

// Sets `digest` to `sha256`, which only fits a seal with a 256-bit key.
- (instancetype)initWithHeader:(VDSHeader *)header
                      features:(NSArray<VDSFeature *> *)features
                        sha256:(NSData *)sha256
                     signature:(NSData *)signature
                          name:(NSString *)name;

- (instancetype)initWithHeader:(VDSHeader *)header
                      features:(NSArray<VDSFeature *> *)features
                        sha256:(NSData *)sha256
                        digest:(NSData *)digest
                     signature:(NSData *)signature
                          name:(NSString *)name;

- (BOOL)verify:(NSData *)certificate;

- (BOOL)verify:(NSData *)certificate
            now:(nullable NSDate *)now;

- (VDSVerification *)verifyWithTrustMaterial:(VDSTrustMaterial *)trust;

- (VDSVerification *)verifyWithTrustMaterial:(VDSTrustMaterial *)trust
                                         now:(NSDate *)now;

@end

NS_ASSUME_NONNULL_END
