#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define nl printf("\n")

typedef struct
{
    int label;
    bool visited;
} vertex_t;

int top = -1;

void push(int item)
{
    stack[++top] = item;
}

int pop()
{
    return stack[top--];
}

int peek()
{
    return stack[top];
}

bool isStackEmpty()
{
    return top == -1;
}

void addEdge(int adjMatrix[][], int start, int end)
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

    return nlCount;
}

void labelVertices(FILE * input, vertex_t vertexList[], int length)
{
    for(int i = 0; i < length; i++)
    {
        vertexList[i].label = i;
    }
}


void printVertexList(vertex_t vertexList[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%d\n", vertexList[i].label);
    }
}

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r"); 
    char currCh; // friend :)
    int vertexCount = nlCount(input);
    int adjMatrix[vertexCount][vertexCount];
    int stack[vertexCount];
    vertex_t vertexList[vertexCount];
    
    labelVertices(input, vertexList, vertexCount);
    printVertexList(vertexList, vertexCount);
    
    nl;
    return 0;
}
