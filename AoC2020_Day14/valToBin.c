#include <stdio.h>
#include <stdint.h>

void valueToBinary(int64_t value, char * binaryArray, size_t arrayLength)
{
    int64_t x = value;
    for(size_t i = 0; i < arrayLength; i++)
    {
        binaryArray[arrayLength-i-1] = (x/((1ULL) << i)) % 2;
    }
}

int main()
{
    char binaryArray[36];

    valueToBinary(50, binaryArray, 36);

    for(size_t i = 0; i < 36; i++)
    {
        printf("%d", binaryArray[i]);
    }

    

    return 0;

}
