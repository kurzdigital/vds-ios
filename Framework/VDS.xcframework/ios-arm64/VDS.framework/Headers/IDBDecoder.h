#import <Foundation/Foundation.h>

#import "IDBResult.h"

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default")))
@interface IDBDecoder : NSObject

+ (nullable IDBResult *)decode:(NSString *)string;

+ (nullable IDBResult *)decode:(NSString *)string
                  withProfiles:(nullable NSString *)profiles;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                            masterListPath:(NSString *)masterListPath;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                            masterListPath:(NSString *)masterListPath
                                       now:(nullable NSDate *)now;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                            masterListPath:(NSString *)masterListPath
                                  profiles:(nullable NSString *)profiles;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                            masterListPath:(NSString *)masterListPath
                                  profiles:(nullable NSString *)profiles
                                       now:(nullable NSDate *)now;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                           certificateData:(NSData *)certificate;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                           certificateData:(NSData *)certificate
                                       now:(nullable NSDate *)now;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                           certificateData:(NSData *)certificate
                                  profiles:(nullable NSString *)profiles;

+ (IDBVerificationResult)verifyWithBarcode:(NSString *)barcode
                           certificateData:(NSData *)certificate
                                  profiles:(nullable NSString *)profiles
                                       now:(nullable NSDate *)now;

@end

NS_ASSUME_NONNULL_END
