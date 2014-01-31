
#include "include/priority.h"

#ifndef CANDIDATE_H
#define CANDIDATE_H

struct candidate {
    ICE_CANDIDATE_TYPE type;
    IpType ipType;
    uint32_t priority;
    uint32_t componentId;
};



uint32_t addCandidate( struct candidate *candidateList, 
                       uint32_t numberOfCandidates, 
                       struct PriorityTable *pTable, 
                       ICE_CANDIDATE_TYPE candType,
                       IpType ipType,
                       uint32_t componentId);

void printCandidate(struct candidate *cand);

void printCandidatelist(struct candidate *cand_list, uint32_t num);

int candcmp(const void *p1, const void *p2);


#endif
