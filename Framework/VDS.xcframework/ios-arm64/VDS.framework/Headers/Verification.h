#ifndef Verification_h
#define Verification_h

#import "VDSVerification.h"

#include <vds/verify.h>

NS_ASSUME_NONNULL_BEGIN

namespace vds {
TrustMaterial toTrustMaterial(VDSTrustMaterial * _Nullable);
VDSVerification *toVerification(const Verification &);
VDSVerification *toVerification(VerificationStatus);
};

NS_ASSUME_NONNULL_END

#endif
