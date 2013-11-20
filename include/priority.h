
#include<stdio.h>
#include<stdint.h>


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
