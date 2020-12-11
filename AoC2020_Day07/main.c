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
} vertex_t;

int top = -1;

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

void push(int stack[], int item)
{
    stack[++top] = item;
}

int pop(int stack[])
{
    return stack[top--];
}

int peek(int stack[])
{
    return stack[top];
}

bool isStackEmpty()
{
    return top == -1;
}

void addEdge(int length, int adjMatrix[][length], int start, int end)
{
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1;
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
    return bsearch(name, vertexList, vertexCount, sizeof(vertex_t), cmp_key_vertex)-vertexList;
}

void labelVertices(FILE * input, vertex_t vertexList[], int length)
{
    for(int i = 0; i < length; i++)
    {
        vertexList[i].label.vertexVal = i;
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
        printf("%d: %s\n", vertexVal, desc);
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
    char currCh = '\n'; // welcome back

    for(int i = 0; i < length; i++)
    {
        fscanf("%s %s contains", heldFirstWord, heldSecondWord);
        // TODO convert to desc, grab index
        // int getVertexId(const char * name, vertex_t vertexList, int vertexCount)
        convertToDesc(heldFullDesc, heldFirstWord, heldSecondWord); 
        heldInx = getVertexId(heldFullDesc, vertexList, length);
        while(fscanf(input, " %*d %s %s", compFirstWord, compSecondWord) == 2)
        {
            convertToDesc(heldCompDesc, compFirstWord, compSecondWord); 
            compInx = getVertexId(heldCompDesc, vertexList, length);
           // convert to desc, grab index, add edge 
        }
        // consumes remainder
        // reset
    }
}


int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r"); 
    int vertexCount = nlCount(input);
    int adjMatrix[vertexCount][vertexCount];
    int stack[vertexCount];
    vertex_t vertexList[vertexCount];
    
    readLabels(input, vertexList, vertexCount);
    qsort(vertexList, vertexCount, sizeof(vertex_t), cmp_vertex_t);
    labelVertices(input, vertexList, vertexCount);
    printVertexList(vertexList, vertexCount);
    
    nl;
    return 0;
}
