
#include<stdio.h>
#include<stdint.h>

#ifndef PRIORITY_H
#define PRIORITY_H

typedef enum {
    NONE,
    IPv4,
    IPv6
}IpType;



struct CandTypePriorityTable{
    uint32_t IPv6_lpriority;
    uint32_t IPv4_lpriority;
    uint32_t IPv6_nInRow;
    uint32_t IPv4_nInRow;
};

struct PriorityTable{
    struct CandTypePriorityTable hostPri;
    struct CandTypePriorityTable rflxPri;
    struct CandTypePriorityTable relayPri;
    uint32_t maxInRow;
};


typedef enum {
    ICE_CAND_TYPE_NONE,
    ICE_CAND_TYPE_HOST,
    ICE_CAND_TYPE_SRFLX,
    ICE_CAND_TYPE_RELAY,
    ICE_CAND_TYPE_PRFLX
} ICE_CANDIDATE_TYPE;

#if !defined(max)
#define max(a, b)       ((a) > (b) ? (a) : (b))
#define min(a, b)       ((a) < (b) ? (a) : (b))
#endif

#define ICELIB_LOCAL_TYPEPREF   126
#define ICELIB_PEERREF_TYPEREF  110
#define ICELIB_REFLEX_TYPEREF   100
#define ICELIB_RELAY_TYPEREF    0




uint64_t ICELIB_pairPriority(uint32_t G, uint32_t D);
uint32_t ICELIB_calculatePriority(ICE_CANDIDATE_TYPE type, uint16_t compid, uint16_t local_pref);
uint16_t ICELIB_calculateLocalPreference(struct PriorityTable *priTbl,
                                         ICE_CANDIDATE_TYPE type,
                                         IpType addrType);
#endif
