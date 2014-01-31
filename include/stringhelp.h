
#include<stdint.h>
#include<string.h>
#include "priority.h"

#ifndef STRINGHELP_H
#define STRINGHELP_H

ICE_CANDIDATE_TYPE stringToCandidateType(const char *s, int len);
IpType stringToIPAddrype(const char *s, int len);
IpType stringToIpAddrType(const char *s, int len);
uint32_t stringToComponentId(const char *s, int len);
#endif
