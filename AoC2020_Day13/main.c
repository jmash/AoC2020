#include <stdio.h>

/*
  NOTES:

  Take earliest time departure (value in first line) and modulo to each of the bus IDs, then subtract result from bus ID to
  get the time units needed to wait for the next bus. Save the time-to-wait and the bus ID in an array of structs, then
  qsort the structs. The first struct in the sorted array will have shortest wait time, so take that value, multiply it by
  the bus ID, and get the answer
*/

int main(int argc, const char *argv[])
{
    return 0;
}
