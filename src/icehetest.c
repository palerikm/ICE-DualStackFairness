
#include <stdlib.h>

#include"include/priority.h"

typedef enum {
    NONE,
    IPv4,
    IPv6
}IpType;

struct candidatePair {
    IpType ipType;
    uint64_t pair_priority;
};

struct prefTable {
    uint32_t pref;
    uint32_t nUsed;
};

int paircmp(const void *p1, const void *p2)
{
    uint64_t y1 = ((const struct candidatePair*)p1)->pair_priority;
    uint64_t y2 = ((const struct candidatePair*)p2)->pair_priority;
    if(y1>y2) return 1;
    if(y1<y2) return -1;

    return 0;
}


void printCandidatePair(struct candidatePair *pair) {
    if(pair->ipType == NONE){
        printf("Empty\n");
        return;
    }
 if(pair->ipType == IPv4) printf("IPv4 ");
    if(pair->ipType == IPv6) printf("IPv6 ");
    printf("Priority: %llu\n", pair->pair_priority); 
}

void printChecklist(struct candidatePair *pair_list, uint32_t num){
    int i;
    for(i=0;i<num;i++){
        printf("(%i) ", i);
        printCandidatePair(&pair_list[i]);
    }
}

void fillPrefTable( struct prefTable *prefT, uint32_t num, uint32_t numCand){
    uint32_t i;
    uint32_t start = 65534;

    for(i=0;i<num;i++){
        prefT[i].pref = start-i*numCand;
        prefT[i].nUsed = 0;
    }
}

void addCandidate( struct prefTable *prefT, uint32_t prefSize, 
                   struct candidatePair *pair, uint32_t pairSize, uint32_t idx,
                   uint32_t remote_pri,
                   ICE_CANDIDATE_TYPE candType,
                   IpType ipType,
                   uint32_t blah){
    
    uint32_t local_pri = 0;

    if(ipType == IPv6 ){
        local_pri = ICELIB_calculatePriority(candType, 
                                             blah, 
                                             prefT[0].pref);
        prefT[0].nUsed++;
        if( prefT[0].nUsed > 2){
            prefT[0].pref = prefT[1].pref -1;
            prefT[0].nUsed = 0;
        }
    }

    if(ipType == IPv4 ){
        local_pri = ICELIB_calculatePriority(candType, 
                                             blah, 
                                             prefT[1].pref);
        prefT[1].nUsed++;
        if(prefT[1].nUsed > 2){
            prefT[1].pref = prefT[1].pref - 101;
            prefT[1].nUsed = 0;
        }
    }


    pair[idx].pair_priority = ICELIB_pairPriority( local_pri, remote_pri);
    pair[idx].ipType = ipType;
}
                   

int main()
{
    const uint32_t list_len = 10;
    struct candidatePair candPair[list_len];
    //struct candidatePair *checlist = candPair;
    struct prefTable prefT[2];
    uint32_t remote_ipv6 = 2122633471;
        
        
    fillPrefTable( prefT, 2, 100);
        
    addCandidate( prefT, 2, 
                  candPair, list_len, 0,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv4,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 1,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv6,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 2,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv6,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 3,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv6,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 4,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv6,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 5,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv6,
                  1);
    
    addCandidate( prefT, 2, 
                  candPair, list_len, 6,
                  remote_ipv6,
                  ICE_CAND_TYPE_HOST,
                  IPv4,
                  1);
    
    
    qsort(candPair, 7, sizeof(*candPair), paircmp);
    
    printChecklist(candPair, list_len);
}

