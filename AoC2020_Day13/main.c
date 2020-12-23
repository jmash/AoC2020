#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
  NOTES:

  Take earliest time departure (value in first line) and modulo to each of the bus IDs, then subtract result from bus ID to
  get the time units needed to wait for the next bus. Save the time-to-wait and the bus ID in an array of structs, then
  qsort the structs by the time-to-wait. The first struct in the sorted array will have shortest wait time, so take that value, multiply it by
  the bus ID, and get the answer
*/

typedef struct
{
    int busId;
    int timeToWait;
} bus_t;

// be kind, rewind. (used to reset the file buffer back to the
// beginning)
void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

// comparator function for qsort (comparing Time To Wait)
int compareTimeToWait(const void * a, const void * b)
{
    bus_t * busA = (bus_t *) a;
    bus_t * busB = (bus_t *) b;

    return (busA->timeToWait - busB->timeToWait);
}

// does what it says on the tin. takes in a file pointer
// and counts the ids in the second line of the file.
int countIdsInFile(FILE * input)
{
    int numIds = 0;
    char currCh; // VIV (very important variable)

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'x') numIds--;
        if(currCh == ',') numIds++;
    }

    rewindFile(input);

    return numIds;
}

// Does exactly what you think it does.
void printBusses(bus_t * busses, int numIds)
{
    for(int i = 0; i < numIds; i++)
    {
        printf("Bus ID: %d\n", busses[i].busId);
        printf("Time to Wait: %d\n", busses[i].timeToWait);
    }
}

// calculate Time To Wait for each bus in the bus array.
// the Time To Wait is the bus ID minus the remainder of
// the division between the earliest time stamp and the current busId.
void calculateTimeToWait(bus_t * busses, int earliestTimestamp, int numIds)
{
    for(int i = 0; i < numIds; i++)
    {
        busses[i].timeToWait = busses[i].busId - (earliestTimestamp % busses[i].busId);
    }
}

int main(int argc, const char *argv[])
{
    if(argc < 2) 
    {
        printf("Error: no input file specified.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error: could not read input file.\n");
        return 1;
    }

    int earliestTimestamp = 0; // first line in the file
    int numIds = 0;            // the number of commas in the second line of the file
                               // (indicative of size of bus_t array)
    numIds = countIdsInFile(input) + 1; // number of ids in file (corresponds to number of commas)

    bus_t busses[numIds]; // create array of bus types that is numIds size large

    fscanf(input, "%d\n", &earliestTimestamp);  // get first number on first line of file (earliest timestamp)
    
    char currCh; // to the rescue?
    int currBusInx = 0; // current bus index; if a number is encountered in the scan,
                        // put the number back and the use fscanf to take the number in
    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input); // put number back into buffer so fscanf can take in the full number
            fscanf(input, "%d,", &busses[currBusInx].busId); // assign the number to the corresponding index in busses array
            currBusInx++;
        }
    }

    // calculate the time to wait for each bus
    calculateTimeToWait(busses, earliestTimestamp, numIds); 
    // use qsort so that the smallest time to wait will be the first struct in the array.
    qsort(busses, numIds, sizeof(bus_t), compareTimeToWait);

    // the solution will be busId * timeToWait of first bus in array
    int solution = busses[0].busId * busses[0].timeToWait;

    // display the beautiful solution <3
    printf("Solution is %d\n", solution);
    
    fclose(input); // was forgetting to do this constantly XD will have to go back and fix that in
                   // almost all previous days

    return 0;
}
