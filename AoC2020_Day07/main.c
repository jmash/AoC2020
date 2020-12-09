#include <stdio.h>
#include <stdlib.h>

/*

[0] light red bags contain 1 [2] bright white bag, 2 [3] muted yellow bags.
[1] dark orange bags contain 3 [2] bright white bags, [3] 4 muted yellow bags.
[2] bright white bags contain 1 [4] shiny gold bag.
[3] muted yellow bags contain 2 [4] shiny gold bags, 9 [7] faded blue bags.
-----
[4] shiny gold bags contain 1 [5] dark olive bag, 2 [6] vibrant plum bags.
[5] dark olive bags contain 3 [7] faded blue bags, 4 [8] dotted black bags.
[6] vibrant plum bags contain 5 [7] faded blue bags, 6 [8] dotted black bags.
[7] faded blue bags contain no other bags.
[8] dotted black bags contain no other bags.

(0)
size: 1 1 1 1 1 1 1 1 1
      0 1 2 3 4 5 6 7 8
inx:  0 1 2 3 4 5 6 7 8
      0 1 2 3 4 5 6 7 8

union(2, 1)



size: 1 1 1 1 1 1 1 1 1
      0 1 2 3 4 5 6 7 8
inx:  0 1 2 3 4 5 6 7 8
      0 1 2 3 4 5 6 7 8

*/

int main(int argc, const char *argv[])
{
    printf("Hello World\n");
    return 0;
}
