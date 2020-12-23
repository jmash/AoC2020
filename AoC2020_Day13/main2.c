#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

// NOTES FOR PART TWO:
// -first line in input file is no longer relevant
// -Current idea for algorithm:
//   * keep track of id numbers + x's (the x's are now relevant)
//   * pair up coprime numbers, not skipping pairs (in other words, [1][2], [2][3], [3][4], etc)
//   * all integer pairs are guaranteed coprime, so calculating gcd is not useful (gcd
//     is guaranteed to be 1 in all cases)
//   * get the larger of the two values, and add it to itself. continuously add the smaller
//     of the two numbers to itself and check for a difference of 1 + [inbetween x's] between the two numbers
//     on each pass.
//   * the first instance of a difference of 1 + [number of inbetween x's] will kill the loop
//     and move on to the next coprime pair. if there are x's inbetween, count them up and apply
//     them to the difference check for the next pair.
// -^^^ Turns out that would take a long, long time to compute. Better idea is extended Euclidean algorithm
//     applied to linear diophantine equations.

// T mod 13 + 1 mod 13 = 0 mod 13 T mod 13 = 12
// (T + 0) mod 7 = 0  <=> T mod  7 =  0 : first constraint
// (T + 1) mod 13 = 0 <=> T mod 13 = 12 : second constraint
// (T + 4) mod 59 = 0 <=> T mod 59 = 55 : third constraint
// (T + 6) mod 31 = 0 <=> T mod 31 = 25 : fourth constraint
// (T + 7) mod 19 = 0 <=> T mod 19 = 12 : fifth constraint
//
// x = 0 mod 7
// x = 12 mod 13
// x = 55 mod 59
// x = 25 mod 31
// x = 12 mod 19
//
// 7x - 13y = 1
// 7x = 1 mod 13
//
/*

 
 CHINESE REMAINDER THEOREM

 Extended Euclidean Algorithm Pseudo-Code:
 (int64_t will be required for BIG ANSWER)

function extended_gcd(a, b)
    s <- 0;    old_s <- 1
    t <- 1;    old_t <- 0
    r <- b;    old_r <- a
    while r ≠ 0
        quotient <- old_r div r
        (old_r, r) <- (r, old_r - quotient * r)
        (old_s, s) <- (s, old_s - quotient * s)
        (old_t, t) <- (t, old_t - quotient * t)       
    output "Bézout coefficients:", (old_s, old_t)
    output "greatest common divisor:", old_r
    output "quotients by the gcd:", (t, s) 
 
 */


typedef struct
{
    int busId;
    int skips;
} bus_skip_t;

typedef struct
{
    int64_t a;
    int64_t b;
} bezout_coeff_t;

// simpler way to get the modular inverse from the extended euclidean;
// it doesn't bother computing the part that ISN'T the modular inverse.
// stole it (with permission) from Steve (thanks Steve)
int64_t mod_inv(int64_t a, int64_t n)
{
	int64_t t = 0, newt = 1, r = n, newr = a;
	while (newr != 0)
	{
		int64_t q = r / newr;
		int64_t nt = newt; newt = t - q * newt; t = nt;
		int64_t nr = newr; newr = r - q * newr; r = nr;
	}
	if (r > 1) return -1;
	if (t < 0) t += n;
	return t;
}

// shamelessly translated from the Python code at https://brilliant.org/wiki/extended-euclidean-algorithm/
// because I'm a CHUMP (and not cooler than Steve :(  )
// (THIS WOULD HAVE WORKED, HAD I BEEN MORE EAGLE-EYED REGARDING OVERFLOW)
/*
bezout_coeff_t extendedGCD(int64_t a, int64_t b)
{
    bezout_coeff_t bc;
    int64_t x = 0;
    int64_t y = 1;
    int64_t u = 1;
    int64_t v = 0;
    int64_t r = b;
    int64_t ob = b;
    int64_t m, n;
    int64_t q; //quotient
    while(r != 0)
    {
        q = b / a;
        r = b % a;
        m = x-u*q;
        n = y-v*q;
        b = a; a = r; x = u;
        y = v; u = m; v = n; 
    }

    if(x < 0)
        x += ob;
    bc.a = x;
    bc.b = y;
    return bc;
}
*/

// does what it says on the tin. takes in a file pointer
// and counts the ids in the second line of the file.
int countBusIdsInFile(FILE * input)
{
    int numIds = 0;
    char currCh; // VIV (very important variable)

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == ',') numIds++;
    }
    numIds++;

    rewind(input);

    return numIds;
}

// Does exactly what you think it does.
void printBusses(bus_skip_t * busses, int numIds)
{
    for(int i = 0; i < numIds; i++)
    {
        printf("Bus ID 1: %d\n", busses[i].busId);
        printf("Number of skips: %d\n", busses[i].skips);
    }
}

// Prints a basic array of integers
void printIntArray(int * array, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("[%d]", array[i]);
    }
    printf("\n");
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
    
    char currCh; // to the rescue?
    int busIdAmount = countBusIdsInFile(input); // get the number of busses

    int busIdArray[busIdAmount];

    // eat the first, now irrelevant, number in the file
    int numDump;
    fscanf(input, "%d\n", &numDump);
    
    int currBusInx = 0; // current bus index; if a number is encountered in the scan, increase it
    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%d,", &busIdArray[currBusInx]);
            currBusInx++;
        }
        if(currCh == 'x')
        {
            busIdArray[currBusInx] = 0; // put in a zero to indicate skips
            currBusInx++;
            fgetc(input); // munch the comma
        }
    }

    // find the number of busses with actual ids (the ones that are used in the
    // modual equations)
    int busSkipsAmount = 0;
    for(int i = 0; i < busIdAmount; i++)
    {
        if(busIdArray[i] != 0)
        {
            busSkipsAmount++;
        }
    }

    // initialize busSkips array
    bus_skip_t busSkips[busSkipsAmount];

    // get busIds and associated skips in busSkips array
    int busSkipsInx = 0;
    int totalSkips = 0;
    for(int i = 0; i < busIdAmount; i++)
    {
        if(busIdArray[i] != 0)
        {
            busSkips[busSkipsInx].busId = busIdArray[i]; 
            busSkips[busSkipsInx].skips = totalSkips;
            busSkipsInx++;
            totalSkips++;
        } else
        {
            totalSkips++;
        }
    }

    printBusses(busSkips, busSkipsAmount);

    // get 'n' value (the product of all the 'B' (bus id) values)
    int64_t n = 1;
    for(int i = 0; i < busSkipsAmount; i++)
    {
        n *= busSkips[i].busId;
        printf("n: %ld\n", n);
    }

    int64_t solution = 0;
    // for each bus,
    for(int i = 0; i < busSkipsAmount; i++)
    {
        // band-aid fix to make sure that A is 0 in the first
        // instance; otherwise it would be B mod B rather than
        // 0 mod B as it should be
        int64_t A;
        if(busSkips[i].skips == 0)
        {
            A = 0;
        } else
        {
            A = (busSkips[i].busId - busSkips[i].skips) % busSkips[i].busId;  
        }

        int64_t B = busSkips[i].busId;

        int64_t nHat = n / B;

        int64_t inv = mod_inv(nHat, B);

        solution += (A * inv * nHat); 
    }
    solution %= n;
    printf("%ld\n", solution);
    
    fclose(input); // was forgetting to do this constantly XD will have to go back and fix that in
                   // almost all previous days

    return 0;
}
