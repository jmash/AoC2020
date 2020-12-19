#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} coord_pos_t;

void swapPositions(int * a, int * b)
{
    int temp = *(b);
    *(b) = *(a);
    *(a) = temp;
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Error: no input file.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error: can't read input file.\n");
        return 1;
    }
    // real meat 'n taters begins here
    char currCh; // welcome back Currch :D missed you from yesterday <3
    int value = 0; // value associated with each instruction (each Currch ;))
    coord_pos_t ferry; // initialize ferry position
    coord_pos_t waypoint; // initialize waypoint position
    ferry.x = 0; // ferry position set to origin
    ferry.y = 0;
    waypoint.x = 10; // waypoint position offset from origin
    waypoint.y = 1;
    int theta = 0; // current degree facing of ferry
    int manhattanDistance = 0; // distance of ferry from origin (abs value of x diff + abs value of y diff)
        
    while(fscanf(input, "%c%d\n", &currCh, &value) == 2)
    {
        switch(currCh)
        {
            case 'N': // if we're facing north, increase waypoint y position by value
                waypoint.y += value;
                break;
            case 'S': // if we're facing south, decrease waypoint y position by value
                waypoint.y -= value;
                break;
            case 'E': // if we're facing east, increase waypoint x position by value
                waypoint.x += value;
                break;
            case 'W': // if we're facing west, decrease waypoint x position by value
                waypoint.x -= value;
                break;
            case 'L':
                theta = value;
                switch(theta)
                {
                    case 90: 
                        swapPositions(&waypoint.x, &waypoint.y);
                        waypoint.x *= -1;
                        break;
                    case 180:
                        waypoint.x *= -1;
                        waypoint.y *= -1;
                        break;
                    case 270:
                        swapPositions(&waypoint.x, &waypoint.y);
                        waypoint.y *= -1;
                        break;
                }
                break;
            case 'R':
                theta = value;
                switch(theta)
                {
                    case 90:
                        swapPositions(&waypoint.x, &waypoint.y);
                        waypoint.y *= -1;
                        break;
                    case 180:
                        waypoint.x *= -1;
                        waypoint.y *= -1;
                        break;
                    case 270:
                        swapPositions(&waypoint.x, &waypoint.y);
                        waypoint.x *= -1;
                        break;
                }
                break;
            case 'F':
                ferry.x += value*waypoint.x;
                ferry.y += value*waypoint.y;
                break; 
        }
    }
    manhattanDistance = abs(ferry.x) + abs(ferry.y); // calculate manhattan distance from origin
    printf("Manhattan Distance from origin is: %d\n", manhattanDistance);

    return 0;
}
