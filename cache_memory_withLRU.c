#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXROWS 100
#define MAXCOLS 500
char cache[8][8];                               // Grid to store cache blocks

int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};

// Prints the input variables for debugging purpose
void printInputs(int numTestCases, int numAccesses, char memBlockAddress[MAXROWS]){
    printf("%d \n", numTestCases);
    printf("%d\n",numAccesses);
    for (int i = 0; i < numAccesses; i++) {
        printf("%d ", memBlockAddress[i]); 
    }
    printf("\n");
}

// Findes the best scheme for every case by finding maximum number of hits by a cache
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

// Finds the index of the least resently used block in a set
int leastRecentlyUsed_index(char countLRU[8]){
    int index = 0;
    int minCount = countLRU[index];
    
    for(int i=0; i<4; i++){
        if(countLRU[i] < minCount){
            minCount = (int)countLRU[i];
            index = i;
        }
    }
    return index;

}

// Displays the output in the given format
void displayOutput(int caseNum, int hitCount[4], int missCount[4]){
    printf("\nTest case %d: \n", caseNum);
    for(int i=0; i<4; i++){
        printf("%d-way set associative hits: %d misses: %d\n", (int)pow(2, i), hitCount[i], missCount[i]);
    }
    printf("\nBest scheme: %d-way set associative\n", (int)pow(2, bestScheme(hitCount)));
}

// Clears the cache after every type of cache memory
void clearCache(int numBlocks, char cache[8][8], int numSets){
    for(int set=0; set<numSets; set++){
        for(int block=0; block<numBlocks; block++){
            cache[set][block] = 0;
        }
    }
}

// returns True if it is a hit
bool hit(int numBlocks, char cache[8][8], int setIndex, int memBlockAddress, char countLRU[8][8]){
    for(int k=0; k<numBlocks;k++){
        if(cache[setIndex][k] == memBlockAddress){
            return true;
        }
    }
    return false;
}

// Find and return the index of the block in the set after a hit
int hitIndex(int numBlocks, char cache[8][8], int setIndex, int memBlockAddress){
    for(int k=0; k<numBlocks;k++){
        if(cache[setIndex][k] == memBlockAddress){
            return k;
        }
    }
    return NULL;
}    

// Add new memory address to cache after a miss - currently redundant function
void addToCache(int numBlocks, char cache[8][8], int setIndex, int indexLRU, int memBlockAddress){
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
    int numSets, setIndex, blockIndex, indexLRU;
    int hitCount[4] = {0, 0, 0, 0};                     // Keeps a track of number of hits
    int missCount[4] = {0, 0, 0, 0};                    // Keeps a track of number of misses
    int numBlocks[] = {1, 2, 4, 8};                     // Number of blocks in 4 different types of cache
    // Iterate for all 4 types of cache memory
    for(int i=0; i<4; i++){
        numSets = 8/numBlocks[i];                       // Find the number of sets in the block
        char countLRU[8][8];                            // Keep a track of LRU block
        clearCache(numBlocks[i], cache, numSets);       // clear Cache
        clearCache(numBlocks[i], countLRU, numSets);    // clear LRU Counter
        //char cache[numSets][numBlocks[i]];
        // printf("numSets:%d numBlocks:%d \n", numSets, numBlocks[i]);
        for(int j=0; j<numAccesses; j++){                   // Iterate of all given addresses
            setIndex = (memBlockAddress[j])%(numSets);      // Find the setIndex  

            if(hit(numBlocks[i], cache, setIndex, memBlockAddress[j], countLRU)){           // Check if it is a hit
                blockIndex = hitIndex(numBlocks[i], cache, setIndex, memBlockAddress[j]);   // Find the index of Hit block
                countLRU[setIndex][blockIndex]++;                                           // Increment LRU counter
                hitCount[i]++;                                                              // Increment number of Hits
            }
            else{
                indexLRU = leastRecentlyUsed_index(countLRU[setIndex]); // Find the LRU index
                cache[setIndex][indexLRU] = memBlockAddress[j];         // Add to cache
                countLRU[setIndex][indexLRU] = 0;                       // Reset the counter for the block
                missCount[i]++;                                         // increment the number of misses
            }
        }
        //printf("Hit: %d | Miss: %d \n", hitCount, missCount);
    }
    displayOutput(caseNum, hitCount, missCount);                        // Display the output in the given format
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