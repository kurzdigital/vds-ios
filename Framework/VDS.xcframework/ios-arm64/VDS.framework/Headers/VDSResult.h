#import <Foundation/Foundation.h>

#import "VDSHeader.h"
#import "VDSFeature.h"
#import "VDSVerification.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface VDSResult : NSObject

@property (nonatomic, strong) VDSHeader *header;
@property (nonatomic, strong) NSArray<VDSFeature *> *features;
// Hash of the signed data that the signature was made over. Its
// algorithm depends on the length of the key.
@property (nonatomic, strong) NSData *digest;
@property (nonatomic, strong) NSData *signature;
@property (nonatomic, copy) NSString *name;

- (instancetype)initWithHeader:(VDSHeader *)header
                      features:(NSArray<VDSFeature *> *)features
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
