
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


    

    
    //printf("CURRENT IPv6 pri: %u\n",priTbl->IPv6_lpriority); 
    //printf("CURRENT IPv4 pri: %u\n",priTbl->IPv4_lpriority); 
        


    //Do we need to adjust the pri values
    if(priTbl->IPv6_nInRow >= inPriTbl->maxInRow ){
        priTbl->IPv6_lpriority = priTbl->IPv6_lpriority - 20000;
        
        printf("####  Adjusting IPv6 #####\n");
        printf("IPv6 pri: %u\n",priTbl->IPv6_lpriority); 
        printf("IPv4 pri: %u\n",priTbl->IPv4_lpriority); 

        priTbl->IPv6_nInRow = 0;
        priTbl->IPv4_nInRow = 0;
    }
    if(priTbl->IPv4_nInRow >= inPriTbl->maxInRow){
        priTbl->IPv4_lpriority = priTbl->IPv4_lpriority - 20000;
                
        printf("####  Adjusting IPv4 #####\n");
        printf("New IPv4 pri: %u\n",priTbl->IPv4_lpriority);
        printf("Old IPv6 pri: %u\n",priTbl->IPv6_lpriority); 
        priTbl->IPv4_nInRow = 0;
        priTbl->IPv6_nInRow = 0;
    }
    
    printf("Adding: ");
    if(addrType == IPv6) {
        retVal = priTbl->IPv6_lpriority;
        priTbl->IPv6_nInRow++;   
         printf("IPv6\n");
    }
    else {
        retVal = priTbl->IPv4_lpriority; 
        priTbl->IPv4_nInRow++;   
        printf("IPv4\n");
        
    }
 
    printf("Returning: %i\n", retVal);

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
