
#include "include/stringhelp.h"


ICE_CANDIDATE_TYPE stringToCandidateType(const char *s, int len)
{
    if(strncmp(s, "HOST", len) == 0)
        return ICE_CAND_TYPE_HOST;
    if(strncmp(s, "RFLX", len) == 0)
        return ICE_CAND_TYPE_SRFLX;
    if(strncmp(s, "RELAY", len) == 0)
        return ICE_CAND_TYPE_RELAY;

    return ICE_CAND_TYPE_NONE;
}


IpType stringToIPAddrype(const char *s, int len)
{
    if(strncmp(s, "IPv4", len) == 0)
        return IPv4;
    if(strncmp(s, "IPv6", len) == 0)
        return IPv6;
    
    return NONE;
}

IpType stringToIpAddrType(const char *s, int len)
{
    if(strncmp(s, "IPv4", len) == 0)
        return IPv4;
    if(strncmp(s, "IPv6", len) == 0)
        return IPv6;
    
    return NONE;
}

uint32_t stringToComponentId(const char *s, int len)
{
    if(strncmp(s, "RTP", len) == 0)
        return 1;
    if(strncmp(s, "RTCP", len) == 0)
        return 2;
    
    return NONE;
}
