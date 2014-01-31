
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
#include"include/candidate.h"


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
                                               stringToCandidateType(cand_type,10),
                                               stringToIpAddrType(addr_type, 10),
                                               stringToComponentId(component_type, 10));

        }
    }
    
    fclose(input_file);

    return numberOfCandidates;
}

int main (int argc, char **argv)
{
    const uint32_t list_len = 100;
    struct candidate candidateList[list_len];
    uint32_t numberOfCandidates = 0;
    
    
    struct PriorityTable pTable;
    memset (&pTable, 0, sizeof(pTable));
    pTable.IPv6_start_priority = 60000;
    pTable.IPv4_start_priority = 59000;
        
    pTable.maxInRow = atoi(argv[1]);
    
    numberOfCandidates = parseLocalCandidateFile(candidateList, list_len,
                                                 &pTable,
                                                 argv[2]);
    
    qsort(candidateList, numberOfCandidates, sizeof(*candidateList), candcmp);

    printCandidatelist(candidateList, numberOfCandidates);
    
    return 0;
}

