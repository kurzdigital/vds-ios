#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, Doc2DEncoding) {
    Doc2DEncodingC40,
    Doc2DEncodingBinary,
    Doc2DEncodingMixed
};

__attribute__((visibility("default")))
@interface Doc2DHeader : NSObject

@property (nonatomic, assign) uint8_t version;
@property (nonatomic, assign) Doc2DEncoding encoding;
@property (nonatomic, copy) NSString *authorityIdentifier;
@property (nonatomic, copy) NSString *certificateReference;
@property (nonatomic, strong, nullable) NSDate *documentIssueDate;
@property (nonatomic, strong, nullable) NSDate *signatureCreationDate;
@property (nonatomic, copy) NSString *documentType;
@property (nonatomic, copy) NSString *perimeter;
@property (nonatomic, copy) NSString *issuerCountry;

- (instancetype)initWithVersion:(uint8_t)version
                       encoding:(Doc2DEncoding)encoding
            authorityIdentifier:(NSString *)authorityIdentifier
            certificateReference:(NSString *)certificateReference
              documentIssueDate:(nullable NSDate *)documentIssueDate
          signatureCreationDate:(nullable NSDate *)signatureCreationDate
                   documentType:(NSString *)documentType
                      perimeter:(NSString *)perimeter
                  issuerCountry:(NSString *)issuerCountry;

@end

NS_ASSUME_NONNULL_END
