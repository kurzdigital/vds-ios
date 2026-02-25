#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MRZError) {
    ErrorDocumentCode,
    ErrorIssuingState,
    ErrorDocumentNumber,
    ErrorDocumentNumberCheckDigit,
    ErrorOptionalData1,
    ErrorDateOfBirth,
    ErrorDateOfBirthCheckDigit,
    ErrorSex,
    ErrorDateOfExpiry,
    ErrorDateOfExpiryCheckDigit,
    ErrorNationality,
    ErrorOptionalData2,
    ErrorPersonalNumber,
    ErrorPersonalNumberCheckDigit,
    ErrorCombinedCheckDigit,
    ErrorVisa,
    ErrorNoVisa,
    ErrorNotFrance,
    ErrorDepartmentOfIssuance,
    ErrorOfficeOfIssuance,
    ErrorYearOfIssuance,
    ErrorMonthOfIssuance,
    ErrorIdentifiers,
    ErrorCsumDocumentNumber,
    ErrorCsumDateOfBirth,
    ErrorCsumDateOfExpiry,
    ErrorCsumPersonalNumber,
    ErrorCsumCombined,
    ErrorSwissBlankNumber,
    ErrorSwissLanguage,
    ErrorSwissVersion,
    ErrorSwissFiller,
    ErrorUndefined
};

/**
 VDSMRZInfo represents the Machine Readable Zone (MRZ) information of a document.
 */
__attribute__((visibility("default")))
@interface VDSMRZInfo : NSObject

/**
 The document code.
 */
@property (nonatomic, strong) NSString *documentCode;

/**
 The issuing state of the document.
 */
@property (nonatomic, strong) NSString *issuingState;

/**
 The primary identifier (surname) of the document holder.
 */
@property (nonatomic, strong) NSString *primaryIdentifier;

/**
 The secondary identifier (given name) of the document holder.
 */
@property (nonatomic, strong) NSString *secondaryIdentifier;

/**
 The nationality of the document holder.
 */
@property (nonatomic, strong) NSString *nationality;

/**
 The document number.
 */
@property (nonatomic, strong) NSString *documentNumber;

/**
 The date of birth of the document holder.
 */
@property (nonatomic, strong) NSString *dateOfBirth;

/**
 The sex of the document holder.
 */
@property (nonatomic, strong) NSString *sex;

/**
 The date of expiry of the document.
 */
@property (nonatomic, strong) NSString *dateOfExpiry;

/**
 Optional data first line (TD1).
 */
@property (nonatomic, strong) NSString *optionalData1;

/**
 Optional data second line (TD1/TD2/MRVA/MRVB).
 */
@property (nonatomic, strong) NSString *optionalData2;

/**
 List of errors in the MRZ.
 */
@property (nonatomic, strong) NSArray<NSNumber *> *errors;

/**
 Initializes a new VDSMRZInfo instance with the specified parameters.

 @param documentCode The document code.
 @param issuingState The issuing state of the document.
 @param primaryIdentifier The primary identifier (surname) of the document holder.
 @param secondaryIdentifier The secondary identifier (given name) of the document holder.
 @param nationality The nationality of the document holder.
 @param documentNumber The document number.
 @param dateOfBirth The date of birth of the document holder.
 @param sex The sex of the document holder.
 @param dateOfExpiry The date of expiry of the document.
 @param optionalData1 Optional data first line (TD1).
 @param optionalData2 Optional data second line (TD1/TD2/MRVA/MRVB).
 @param errors List of errors.
 @return A new VDSMRZInfo instance.
 */
- (instancetype)init:(NSString *)documentCode
        issuingState:(NSString *)issuingState
   primaryIdentifier:(NSString *)primaryIdentifier
 secondaryIdentifier:(NSString *)secondaryIdentifier
         nationality:(NSString *)nationality
      documentNumber:(NSString *)documentNumber
         dateOfBirth:(NSString *)dateOfBirth
                 sex:(NSString *)sex
        dateOfExpiry:(NSString *)dateOfExpiry
       optionalData1:(NSString *)optionalData1
       optionalData2:(NSString *)optionalData2
              errors:(NSArray<NSNumber *> *)errors;

- (BOOL)valid;

- (NSDictionary<NSString *, id> *)toJSON;

@end

NS_ASSUME_NONNULL_END
