

#include <stdint.h>

#include "include/candidate.h"
#include "include/stringhelp.h"



uint32_t addCandidate( struct candidate *candidateList, 
                       uint32_t numberOfCandidates, 
                       struct PriorityTable *pTable, 
                       ICE_CANDIDATE_TYPE candType,
                       IpType ipType,
                       uint32_t componentId){
    
    uint32_t local_pri = 0;
    local_pri = ICELIB_calculatePriority(candType, 
                                         componentId, 
                                         ICELIB_calculateLocalPreference(pTable,
                                                                         candType,
                                                                         ipType));
    
    candidateList[numberOfCandidates].priority = local_pri;
    candidateList[numberOfCandidates].ipType = ipType;
    candidateList[numberOfCandidates].type = candType;
    candidateList[numberOfCandidates].componentId = componentId;
    return ++numberOfCandidates;
}


void printCandidate(struct candidate *cand) {
    if(cand->type == ICE_CAND_TYPE_HOST) printf("HOST  ");
    if(cand->type == ICE_CAND_TYPE_SRFLX) printf("SRFLX ");
    if(cand->type == ICE_CAND_TYPE_RELAY) printf("RELAY ");


    if(cand->ipType == NONE){
        printf("Empty\n");
        return;
    }
    if(cand->ipType == IPv4) printf("IPv4 ");
    if(cand->ipType == IPv6) printf("IPv6 ");
    printf("(%i) ", cand->componentId);
    printf("Priority: %u\n", cand->priority); 
}


void printCandidatelist(struct candidate *cand_list, uint32_t num){
    int i;
    for(i=0;i<num;i++){
        printf("(%i) ", i+1);
        if(i<9) printf(" ");
        printCandidate(&cand_list[i]);
    }
}


int candcmp(const void *p1, const void *p2)
{
    uint32_t y1 = ((const struct candidate*)p1)->priority;
    uint32_t y2 = ((const struct candidate*)p2)->priority;
    if(y1>y2) return -1;
    if(y1<y2) return 1;

    return 0;
}
