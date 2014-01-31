

#include <stdint.h>

#include "include/candidate.h"
#include "include/stringhelp.h"



uint32_t addCandidate( struct candidate *candidateList, 
                       uint32_t numberOfCandidates, 
                       struct PriorityTable *pTable,
                       uint32_t priority,
                       ICE_CANDIDATE_TYPE candType,
                       IpType ipType,
                       uint32_t componentId){
    
    uint32_t local_pri = 0;
    if(priority == 0){
        local_pri = ICELIB_calculatePriority(candType, 
                                             componentId, 
                                             ICELIB_calculateLocalPreference(pTable,
                                                                             candType,
                                                                         ipType));
    }else{
        local_pri = priority;
    }
    candidateList[numberOfCandidates].priority = local_pri;
    candidateList[numberOfCandidates].ipType = ipType;
    candidateList[numberOfCandidates].type = candType;
    candidateList[numberOfCandidates].componentId = componentId;
    return ++numberOfCandidates;
}


void printCandidate(struct candidate *cand) {
    if(cand->ipType == IPv4)
        printf("\x1B[31m");
    else
        printf("\x1B[34m");
    if(cand->type == ICE_CAND_TYPE_HOST) printf("HOST  ");
    if(cand->type == ICE_CAND_TYPE_SRFLX) printf("SRFLX ");
    if(cand->type == ICE_CAND_TYPE_RELAY) printf("RELAY ");


    if(cand->ipType == NONE){
        printf("Empty");
        return;
    }
    if(cand->ipType == IPv4) printf("IPv4 ");
    if(cand->ipType == IPv6) printf("IPv6 ");
    printf("(%i) ", cand->componentId);
    printf("Priority: %u", cand->priority);
    printf("\x1B[30m");
}


void printCandidatelist(struct candidate *cand_list, uint32_t num){
    int i;
    for(i=0;i<num;i++){
        printf("(%i) ", i+1);
        if(i<9) printf(" ");
        printCandidate(&cand_list[i]);
        printf("\n");
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
