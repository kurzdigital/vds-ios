#ifndef Common_h
#define Common_h

#import <Foundation/Foundation.h>

#include <array>
#include <string>
#include <vector>

NS_ASSUME_NONNULL_BEGIN

namespace vds {
NSString *stringToNSString(const std::string &);
NSDate *timeToNSDate(time_t);
time_t dateToTime(NSDate * _Nullable);
NSData *vectorToNSData(const std::vector<unsigned char> &);
NSData *arrayToNSData(const unsigned char *, size_t);
};

NS_ASSUME_NONNULL_END

#endif
