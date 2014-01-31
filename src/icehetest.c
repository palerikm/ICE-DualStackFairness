
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include"include/priority.h"
#include"include/stringhelp.h"

struct candidate {
    ICE_CANDIDATE_TYPE type;
    IpType ipType;
    uint32_t priority;
    uint32_t componentId;
};

struct candidatePair {
    struct candidate local_candidate;
    struct candidate remote_candidate;
    uint64_t pair_priority;
};


int paircmp(const void *p1, const void *p2)
{
    uint64_t y1 = ((const struct candidatePair*)p1)->pair_priority;
    uint64_t y2 = ((const struct candidatePair*)p2)->pair_priority;
    if(y1>y2) return 1;
    if(y1<y2) return -1;

    return 0;
}

int candcmp(const void *p1, const void *p2)
{
    uint32_t y1 = ((const struct candidate*)p1)->priority;
    uint32_t y2 = ((const struct candidate*)p2)->priority;
    if(y1>y2) return -1;
    if(y1<y2) return 1;

    return 0;
}


void printCandidatePair(struct candidatePair *pair) {
    if(pair->local_candidate.ipType == NONE){
        printf("Empty\n");
        return;
    }
    if(pair->local_candidate.ipType == IPv4) printf("IPv4 ");
    if(pair->local_candidate.ipType == IPv6) printf("IPv6 ");
    printf("Priority: %llu\n", pair->pair_priority); 
}

void printChecklist(struct candidatePair *pair_list, uint32_t num){
    int i;
    for(i=0;i<num;i++){
        printf("(%i) ", i);
        printCandidatePair(&pair_list[i]);
    }
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
                   




int main (int argc, char **argv)
{
    int c;
    char *input = argv[1];
    FILE *input_file;
    char line[80];
    char cand_type[10];
    char addr_type[10];
    char component_type[10];
    const uint32_t list_len = 100;
    struct candidate candidateList[list_len];
    uint32_t numberOfCandidates = 0;
    //struct prefTable prefT[2];
    
        
        
    //fillPrefTable( prefT, 2, 100);
    
    struct PriorityTable pTable;
    pTable.hostPri.IPv6_lpriority = 60000;
    pTable.hostPri.IPv4_lpriority = 50000;
    pTable.hostPri.IPv6_nInRow = 0;
    pTable.hostPri.IPv4_nInRow = 0;
    
    pTable.rflxPri.IPv6_lpriority = 60000;
    pTable.rflxPri.IPv4_lpriority = 50000;
    pTable.rflxPri.IPv6_nInRow = 0;
    pTable.rflxPri.IPv4_nInRow = 0;
    
    pTable.relayPri.IPv6_lpriority = 60000;
    pTable.relayPri.IPv4_lpriority = 50000;
    pTable.relayPri.IPv6_nInRow = 0;
    pTable.relayPri.IPv4_nInRow = 0;
    
    pTable.maxInRow = 2;
    

    input_file = fopen(input, "r");
    
    if (input_file == 0)
    {
        //fopen returns 0, the NULL pointer, on failure
        perror("Canot open input file\n");
        exit(-1);
    }
    else
    {
                
        while (fgets(line, 80, input_file) != NULL )
        {
            sscanf(line, "%s %s %s", cand_type, addr_type, component_type);

            //printf("%s, %s, %s \n", cand_type, addr_type, component_type);

            numberOfCandidates = addCandidate( candidateList, numberOfCandidates,
                                               &pTable, 
                                               stringToCandidateType(cand_type,10),
                                               stringToIpAddrType(addr_type, 10),
                                               stringToComponentId(component_type, 10));

        }
    }
    
    fclose(input_file);
    
    qsort(candidateList, numberOfCandidates, sizeof(*candidateList), candcmp);

    printCandidatelist(candidateList, numberOfCandidates);
    
    return 0;
    


    /*
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
    */
}

