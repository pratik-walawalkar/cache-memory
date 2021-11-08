#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define FILENAME "input_problem_1.txt"

#define MAXROWS 100
#define MAXCOLS 500

//char memBlockAddress[MAXROWS];
//char cache[8][8];

//char listOfCondons[MAXWORDS][MAXCOLS];
//char codonsStart[] = "AUG";
//char codonsEnd[MAXROWS][MAXCOLS] = {"UAA", "UAG", "UGA"};

int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};

void printInputs(int numTestCases, int numAccesses, char memBlockAddress[MAXROWS]){
    printf("%d \n", numTestCases);
    printf("%d\n",numAccesses);
    for (int i = 0; i < numAccesses; i++) {
        printf("%d ", memBlockAddress[i]); 
    }
    printf("\n");
}

int bestScheme(int hitCount[4]){
    int index = 0;
    int maxHits = hitCount[index];
    
    for(int i=0; i<4; i++){
        if(hitCount[i] > maxHits){
            maxHits = (int)hitCount[i];
            index = i;
        }
    }
    return index;
}

void displayOutput(int caseNum, int hitCount[4], int missCount[4]){
    printf("\nTest case %d: \n", caseNum);
    for(int i=0; i<4; i++){
        printf("%d-way set associative hits: %d misses: %d\n", (int)pow(2, i), hitCount[i], missCount[i]);
    }
    printf("\nBest scheme: %d-way set associative\n", (int)pow(2, bestScheme(hitCount)));
}

void clearCache(int numBlocks, char cache[8][8], int numSets){
    for(int set=0; set<numSets; set++){
        for(int block=0; block<numBlocks; block++){
            cache[set][block] = 0;
        }
    }
}

bool hit(int numBlocks, char cache[8][8], int setIndex, int memBlockAddress){
    for(int k=0; k<numBlocks;k++){
        if(cache[setIndex][k] == memBlockAddress){
            return true;
        }
    }
    return false;
}

void addToCache(int numBlocks, char cache[8][8], int setIndex, int memBlockAddress){
    for(int k=numBlocks; k>=0;k--){
        if(k==0){
            cache[setIndex][k] = memBlockAddress;
        }
        else{
            cache[setIndex][k] = cache[setIndex][k-1];
        } 
    }
}

void totalHitsMiss(char memBlockAddress[], int numAccesses, int caseNum){
    int numSets, index;
    int hitCount[4] = {0, 0, 0, 0};
    int missCount[4] = {0, 0, 0, 0};
    int numBlocks[] = {1, 2, 4, 8};

    for(int i=0; i<4; i++){
        numSets = 8/numBlocks[i];
        char cache[8][8];        
        clearCache(numBlocks[i], cache, numSets);

        //char cache[numSets][numBlocks[i]];
        // printf("numSets:%d numBlocks:%d \n", numSets, numBlocks[i]);
        for(int j=0; j<numAccesses; j++){
            index = (memBlockAddress[j])%(numSets);

            if(hit(numBlocks[i], cache, index, memBlockAddress[j])){
                hitCount[i]++;
            }
            else{
                addToCache(numBlocks[i], cache, index, memBlockAddress[j]);
                missCount[i]++;
            }
        }
        //printf("Hit: %d | Miss: %d \n", hitCount, missCount);
    }
    displayOutput(caseNum, hitCount, missCount);
}

int main()
{
	freopen("input_problem_4.txt", "r", stdin);
    int numTestCases, numAccesses;

// 1. Input number of test cases
	scanf("%d", &numTestCases);

// 2. Iterate through number of test cases
	for (int i = 0; i < numTestCases; i++) {

// 3. Input number of Accesses
	    scanf("%d", &numAccesses);

        char memBlockAddress[numAccesses];
// 4. Input memory block address to the grid
		for (int i = 0; i < numAccesses; i++) {
		    scanf(" %d", &memBlockAddress[i]); // Note: there should be a space before %c to skip spaces and newlines
		}
        //printInputs(numTestCases, numAccesses, memBlockAddress);
        totalHitsMiss(memBlockAddress, numAccesses, i);

    }


}