#include <stdio.h>
#include <stdlib.h>

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
    int xPos = 0; // x position of ferry
    int yPos = 0; // y position of ferry
    int theta = 0; // current degree facing of ferry
    int manhattanDistance = 0; // distance of ferry from origin (abs value of x diff + abs value of y diff)
        
    while(fscanf(input, "%c%d\n", &currCh, &value) == 2)
    {
        //printf("%c%d\n", currCh, value);
        switch(currCh)
        {
            case 'N': // if we're facing north, increase y position by value
                yPos += value;
                printf("Move north by %d\n", value);
                break;
            case 'S': // if we're facing south, decrease y position by value
                yPos -= value;
                printf("Move south by %d\n", value);
                break;
            case 'E': // if we're facing east, increase x position by value
                xPos += value;
                printf("Move east by %d\n", value);
                break;
            case 'W': // if we're facing west, decrease x position by value
                xPos -= value;
                printf("Move west by %d\n", value);
                break;
            case 'L': // increase theta by value (ferry facing in degrees)
                theta += value;
                if(theta < 0) theta += 360;
                if(theta > 360) theta -= 360;
                printf("Ferry now facing %d degrees\n", theta);
                break;
            case 'R': // decrease theta by value (ferry facing in degrees)
                theta -= value;
                if(theta < 0) theta += 360;
                if(theta > 360) theta -= 360;
                printf("Ferry now facing %d degrees\n", theta);
                break;
            case 'F':
                switch(theta)
                {
                case 0:
                    xPos += value; // ferry moves east by value
                    printf("Move east by %d\n", value);
                    break;
                case 90:
                    yPos += value; // ferry moves north by value
                    printf("Move north by %d\n", value);
                    break;
                case 180:
                    xPos -= value; // ferry moves west by value
                    printf("Move south by %d\n", value);
                    break;
                case 270:
                    yPos -= value; // ferry moves south by value
                    printf("Move west by %d\n", value);
                    break;
                }        
                break;
             
        }
    }
    manhattanDistance = abs(xPos) + abs(yPos); // calculate manhattan distance from origin
    printf("Manhattan Distance from origin is: %d\n", manhattanDistance);

    return 0;
}
