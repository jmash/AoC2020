#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SET_MAX 10
#define nl printf("\n");

//Disjoint Set implementation
//implementation analyzed from https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
/*
  My understanding is that this will create the initial array
  that describes the set. There will be two arrays, one for the
  numbers that describe the set (the keys for each node, I suppose)
  along with an array that describes the size for each node.
*/
void initialize(int Arr[], int N)
{
  for(int i = 0; i < N; i++)
  {
    Arr[i] = i;
  }
}

// finding root of an element in log_2(N) time
int root_log_2(int Arr[], int i)
{
    while(Arr[i] != i) //chase parent of current element until it reaches root.
    {
      i = Arr[i];
      printf("Arr[%d] = %d\n", Arr[i], i);
    }
    return i;
}

// finding root of an element in log * N time (recursive log)
int root_log_2_rec (int Arr[], int i)
{
  while(Arr[i] != i)
  {
    Arr[i] = Arr[Arr[i]]; 
    i = Arr[i]; 
  }
  return i;
}

bool find(int Arr[], int A, int B)
{
    if(root_log_2(Arr, A) == root_log_2(Arr, B))       //if A and B have same root, means they are connected.
    {
      return true;
    }
    else
      return false;
}

void set_union(int Arr[], int A, int B)
{
    int root_A = root_log_2(Arr, A);
    int root_B = root_log_2(Arr, B);
    Arr[ root_A ] = root_B ;
}

void weighted_union(int Arr[], int size[], int A, int B)
{
    int root_A = root_log_2(Arr, A);
    int root_B = root_log_2(Arr, B);
    if(size[root_A] < size[root_B])
    {
      Arr[root_A] = Arr[root_B];
      size[root_B] += size[root_A];
    }
    else
    {
      Arr[root_B] = Arr[root_A];
      size[root_A] += size[root_B];
    }
}

void print_array(int arr[], int N)
{
  for(int i = 0; i < N; i++)
  {
    printf("%d ", arr[i]);
  }
  nl;
}

void print_two_arrays(int arr1[], int arr2[], int N)
{
  for(int i = 0; i < N; i++)
  {
    printf("%d ", arr1[i]);
  }
  nl;
  for(int i = 0; i < N; i++)
  {
    printf("%d ", arr2[i]);
  }
  nl;
}

int main()
{
  //let's create a driver and trace the process of
  //creating a tree, setting unions, and tracing the
  //tree to find the parent node.

  // there will be 10 nodes in our tree, labeled 0 to 9
  int set[SET_MAX];
  // these correspond to the size of each node in the above set
  // (every element should be initialized to 1, because every
  // node should initially be 1).
  int size[SET_MAX]; 
  int inx[SET_MAX] = {0,1,2,3,4,5,6,7,8,9};

  initialize(set, SET_MAX);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 0, 2);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 0, 3);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 1, 2);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 1, 3);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 2, 4);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 3, 4);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 3, 7);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 4, 5);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 4, 6);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 5, 7);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 5, 8);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 6, 7);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  set_union(set, 6, 8);
  print_two_arrays(size, inx, SET_MAX);
  nl;
  
  root_log_2(set, 4);
  return 0;
}
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
*/
