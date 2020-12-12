#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define nl printf("\n")

typedef struct
{
    char desc[50];
    int vertexVal;
} label_t;

typedef struct
{
    label_t label;
    bool visited;
    bool foundtarget;
    int numBags;
} vertex_t;

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

void addEdge(int length, int adjMatrix[][length], int start, int end, int weight)
{
    adjMatrix[start][end] = weight;
    //adjMatrix[end][start] = 1;
}

int nlCount(FILE * input)
{
    char currCh;
    int nlCount = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') nlCount++;
    }

    rewindFile(input);
    return nlCount;
}

int cmp_vertex_t(const void *a, const void *b)
{
    return strcmp(((const vertex_t*)a)->label.desc, ((const vertex_t*)b)->label.desc);    
}

int cmp_key_vertex(const void * key, const void * vert)
{
    return strcmp((const char *)key, ((const vertex_t*)vert)->label.desc);    
}

int getVertexId(const char * name, vertex_t vertexList[], int vertexCount)
{
    return (vertex_t *)bsearch(name, vertexList, vertexCount, sizeof(vertex_t), cmp_key_vertex)-vertexList;
}

void labelVertices(FILE * input, vertex_t vertexList[], int length)
{
    for(int i = 0; i < length; i++)
    {
        vertexList[i].label.vertexVal = i;
        vertexList[i].visited = false;
        vertexList[i].foundtarget = false;
    }
}

void readLabels(FILE * input, vertex_t vertexList[], int length)
{
    char firstWord[50];
    char secondWord[50];
    for(int i = 0; i < length; i++)
    {
        char * desc = vertexList[i].label.desc;
        fscanf(input, "%s %s %*[^\n]", firstWord, secondWord);
        strcpy(firstWord, strcat(firstWord, " "));
        strcpy(desc, strcat(firstWord, secondWord));
    }
    rewindFile(input);
}

void printVertexList(vertex_t vertexList[], int length)
{
    for(int i = 0; i < length; i++)
    {
        int vertexVal = vertexList[i].label.vertexVal;
        char * desc = vertexList[i].label.desc;
        //printf("%d: %s\n", vertexVal, desc);
    }
}

void convertToDesc(char * dest, char * word1, char * word2)
{
    strcpy(word1, strcat(word1, " "));
    strcpy(dest, strcat(word1, word2));
}

/*
 * loop->
 *    compare first two words
 *    get index, hold it
 *    enounter a number
 *    get two words, compare to index
 *    add node
 *    enounter a number
 *    get two words, compare to index
 *    add node
 *      ...
 *    hit nl
 *    ^
*/

void printNumBags(int length, vertex_t vertexList[])
{
    for(int i = 0; i < length; i++)
    {
        printf("%d\n", vertexList[i].numBags);
    }
}

void initializeNumBags(int length, vertex_t vertexList[])
{
    for(int i = 0; i < length; i++)
    {
        vertexList[i].numBags = 0;
    }
}

void populateAdjMatrix(FILE * input, int length, vertex_t vertexList[], int adjMatrix[][length])
{
    char heldFirstWord[50];
    char heldSecondWord[50];
    char heldFullDesc[50];
    char compFirstWord[50];
    char compSecondWord[50];
    char heldCompDesc[50];
    int heldInx = 0;
    int compInx = 0;
    int weight = 0;
    char numBagsCh[10];
    char currCh = '\n'; // welcome back

    for(int i = 0; i < length; i++)
    {
        fscanf(input, " %s %s bags contain ", heldFirstWord, heldSecondWord);
        convertToDesc(heldFullDesc, heldFirstWord, heldSecondWord); 
        heldInx = getVertexId(heldFullDesc, vertexList, length);

        while(fscanf(input, " %[no0123456789] %s %s bag%*[,|s,|.]", numBagsCh, compFirstWord, compSecondWord) == 3)
        {
            convertToDesc(heldCompDesc, compFirstWord, compSecondWord); 
            compInx = getVertexId(heldCompDesc, vertexList, length);
            if((compInx < 0) || (strcmp(compFirstWord, "other bags.") == 0)) 
                break;
            weight = atoi(numBagsCh);
            addEdge(length, adjMatrix, heldInx, compInx, weight);
        }
    }
}


void printMatrix(int length, int adjMatrix[][length])
{
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < length; j++)
        {
            printf("[%d]", adjMatrix[i][j]);
        }
        nl;
    }
}
/*
  procedure DFS(G, v) is
    label v as discovered
    for all directed edges from v to w that are in G.adjacentEdges(v) do
        if vertex w is not labeled as discovered then
            recursively call DFS(G, w)
*/

int depthFirstSearch(int length, int adjMatrix[][length], int vertexIndex, vertex_t vertexList[], int * solCountPtr) 
{
    vertexList[vertexIndex].visited = true;
    vertexList[vertexIndex].numBags = 1;

    for(int w = 0; w < length; w++)
    {
        if(adjMatrix[vertexIndex][w])
        {
            //printf("Thinking about %s\n", vertexList[w].label.desc);
            if(!vertexList[w].visited)
            {
                //printf("Visiting: %s\n", vertexList[w].label.desc);
                depthFirstSearch(length, adjMatrix, w, vertexList, solCountPtr);
            }
            vertexList[vertexIndex].numBags += adjMatrix[vertexIndex][w]*vertexList[w].numBags;
        }
    }
    return vertexList[vertexIndex].numBags;
}

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./input.txt", "r"); 
    int vertexCount = nlCount(input);
    int adjMatrix[vertexCount][vertexCount];
    int stack[vertexCount];
    int solCount = 1;
    int * solCountPtr = &solCount;
    vertex_t vertexList[vertexCount];
    
    readLabels(input, vertexList, vertexCount);
    qsort(vertexList, vertexCount, sizeof(vertex_t), cmp_vertex_t);
    memset(adjMatrix, 0, sizeof(int)*vertexCount*vertexCount);
    initializeNumBags(vertexCount, vertexList);
    labelVertices(input, vertexList, vertexCount);
    populateAdjMatrix(input, vertexCount, vertexList, adjMatrix);
    //printMatrix(vertexCount, adjMatrix);
    // for test this returns 7
    int shinyVertex = getVertexId("shiny gold", vertexList, vertexCount);
    printf("%d\n", depthFirstSearch(vertexCount, adjMatrix, shinyVertex, vertexList, solCountPtr)-1);
    nl;
    return 0;
}
