
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

#include"include/priority.h"
#include"include/stringhelp.h"
#include"include/candidate.h"


struct candidatePair {
    struct candidate *localCandidate;
    struct candidate *remoteCandidate;
    uint64_t pair_priority;
};


int paircmp(const void *p1, const void *p2)
{
    uint64_t y1 = ((const struct candidatePair*)p1)->pair_priority;
    uint64_t y2 = ((const struct candidatePair*)p2)->pair_priority;
    if(y1>y2) return -1;
    if(y1<y2) return 1;

    return 0;
}


void printCandidatePair(struct candidatePair *pair) {
    if(pair->localCandidate->ipType == IPv4)
        printf("\x1B[31m");
    else
        printf("\x1B[34m");
    printf("Loc: ");
    printCandidate(pair->localCandidate);
    printf(" Rem: ");
    printCandidate(pair->remoteCandidate);
    printf("(%llu)\n", pair->pair_priority);
    printf("\x1B[30m");
}

void printChecklist(struct candidatePair *pair_list, uint32_t num){
    int i;
    for(i=0;i<num;i++){
        printf("(%i) ", i);
        printCandidatePair(&pair_list[i]);
    }
}
                   


int parseLocalCandidateFile(struct candidate *candidateList, int listLen,
                            struct PriorityTable *pTable,
                            char *filename)
{
    FILE *input_file;
    char line[80];
    char cand_type[10];
    char addr_type[10];
    char component_type[10];
    uint32_t numberOfCandidates = 0;

    input_file = fopen(filename, "r");
    
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
                                               pTable,
                                               0,
                                               stringToCandidateType(cand_type,10),
                                               stringToIpAddrType(addr_type, 10),
                                               stringToComponentId(component_type, 10));

        }
    }
    
    fclose(input_file);

    return numberOfCandidates;
}


int parseRemoteCandidateFile(struct candidate *candidateList, int listLen,
                             char *filename)
{
    FILE *input_file;
    char line[80];
    char cand_type[10];
    char addr_type[10];
    char component_type[10];
    uint32_t priority;
    uint32_t numberOfCandidates = 0;

    input_file = fopen(filename, "r");
    
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
            sscanf(line, "%s %s %s %u", cand_type, addr_type, component_type, &priority);

            //printf("%s, %s, %s, %u \n", cand_type, addr_type, component_type, priority);
            
            numberOfCandidates = addCandidate( candidateList, numberOfCandidates,
                                               NULL,
                                               priority,
                                               stringToCandidateType(cand_type,10),
                                               stringToIpAddrType(addr_type, 10),
                                               stringToComponentId(component_type, 10));
            
        }
    }
    
    fclose(input_file);

    return numberOfCandidates;
}

int formChecklist(struct candidatePair *checklist, int numChecklist,
                  struct candidate *localCandidates, int numLocalCand,
                  struct candidate *remoteCandidates, int numRemoteCand)
{
    int i=0,j=0,idx=0;
    //Pair em up
    for(i=0;i<numLocalCand;i++){
        for(j=0;j<numRemoteCand;j++){
            //same component and addr type
            if(localCandidates[i].ipType == remoteCandidates[j].ipType &&
               localCandidates[i].componentId == remoteCandidates[j].componentId){
                checklist[idx].localCandidate = &localCandidates[i];
                checklist[idx].remoteCandidate = &remoteCandidates[j];
                checklist[idx].pair_priority = ICELIB_pairPriority(localCandidates[i].priority, 
                                                                   remoteCandidates[j].priority);
                idx++;
            }
        }
    }
    

    return idx;
}

int main (int argc, char **argv)
{
    const uint32_t list_len = 100;
    const uint32_t checkListLen = list_len * list_len;
    struct candidate localCandidateList[list_len];
    struct candidate remoteCandidateList[list_len];
    uint32_t numberOfLocalCandidates = 0;
    uint32_t numberOfRemoteCandidates = 0;
    uint32_t numberOfCandPairs =0;
    
    struct candidatePair checkList[checkListLen];
    
    
    struct PriorityTable pTable;
    memset (&pTable, 0, sizeof(pTable));
    pTable.IPv6_start_priority = 60000;
    pTable.IPv4_start_priority = 59000;
        
    pTable.maxInRow = atoi(argv[1]);
    
    numberOfLocalCandidates = parseLocalCandidateFile(localCandidateList, list_len,
                                                      &pTable,
                                                      argv[2]);
    
    qsort(localCandidateList, numberOfLocalCandidates, sizeof(*localCandidateList), candcmp);

    printf("********** Local Candidates (sorted) *********\n");
    printCandidatelist(localCandidateList, numberOfLocalCandidates);

    if(argv[3] != NULL){
        numberOfRemoteCandidates =parseRemoteCandidateFile(remoteCandidateList, list_len,
                                                           argv[3]);
        printf("********** Remote Candidates *********\n");    
        printCandidatelist(remoteCandidateList, numberOfRemoteCandidates);
 
        numberOfCandPairs = formChecklist(checkList, checkListLen,
                                          localCandidateList, numberOfLocalCandidates,
                                          remoteCandidateList, numberOfRemoteCandidates);
           
        qsort(checkList, numberOfCandPairs, sizeof(struct candidatePair), paircmp);

        printf(" ********** CheckList *********\n");
        printChecklist(checkList, numberOfCandPairs);
    }
    
    return 0;
}

