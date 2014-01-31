
#include<stdlib.h>
#include "../include/priority.h"


uint64_t ICELIB_pairPriority(uint32_t G, uint32_t D)
{

    uint64_t  f1 = min(G, D);
    uint64_t  f2 = max(G, D);
    uint64_t  f3 = G > D ? 1 : 0;

    return (f1 << 32) | (f2 * 2) | f3;

}


uint16_t ICELIB_calculateLocalPreference(struct PriorityTable *inPriTbl,
                                         ICE_CANDIDATE_TYPE type,
                                         IpType addrType)
{
    uint16_t retVal = 0;

    uint16_t IPv6_startPri = inPriTbl->IPv6_start_priority;
    uint16_t IPv4_startPri = inPriTbl->IPv4_start_priority;
    uint16_t priDiff = abs(IPv6_startPri-IPv4_startPri);
    struct CandTypePriorityTable *priTbl;

    switch(type){
    case ICE_CAND_TYPE_NONE:
    case ICE_CAND_TYPE_PRFLX:
        break;
    case ICE_CAND_TYPE_HOST:
        priTbl = &inPriTbl->hostPri;
        break;
    case ICE_CAND_TYPE_RELAY:
        priTbl = &inPriTbl->relayPri;
        break;
    case ICE_CAND_TYPE_SRFLX:
        priTbl = &inPriTbl->rflxPri;
        break;
    }
    if(addrType == IPv6) {
        retVal = IPv6_startPri - (priDiff*2*(priTbl->IPv6_nInRow/inPriTbl->maxInRow));
        priTbl->IPv6_nInRow++;   
    }
    else {
        retVal = IPv4_startPri - (priDiff*2*(priTbl->IPv4_nInRow/inPriTbl->maxInRow));
        priTbl->IPv4_nInRow++;   
    }

    return retVal;
}

uint32_t ICELIB_calculatePriority(ICE_CANDIDATE_TYPE type, 
                                  uint16_t compid, 
                                  uint16_t local_pref)
{
    uint32_t typepref = 0;
    uint32_t typeprefs[] = { 0,
                             ICELIB_LOCAL_TYPEPREF,
                             ICELIB_REFLEX_TYPEREF,
                             ICELIB_RELAY_TYPEREF,
                             ICELIB_PEERREF_TYPEREF
                           };

    typepref = (0xff000000 & (typeprefs[type] << 24));

    return (typepref | local_pref<<8 | ((256 - compid) & 0xff));
}
