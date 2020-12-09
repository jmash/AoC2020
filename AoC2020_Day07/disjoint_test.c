#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SET_MAX 10

//Disjoint Set implementation
//implementation analyzed from https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
/*
  My understanding is that this will create the initial array
  that describes the set. There will be two arrays, one for the
  numbers that describe the set (the keys for each node, I suppose)
  along with an array that describes the size for each node.
*/
void initialize(int Arr[], int size[], int N)
{
  for(int i = 0; i < N; i++)
  {
    Arr[i] = i;
    size[i] = 1;
  }
}

// finding root of an element in log_2(N) time
int root_log_2(int Arr[], int i)
{
    while(Arr[i] != i) //chase parent of current element until it reaches root.
    {
      i = Arr[i];
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
    if(root_log_2(Arr, A) == root_log_2(Arr, B) )       //if A and B have same root, means they are connected.
      return true;
    else
      return false;
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
  printf("\n");
}

void print_two_arrays(int arr1[], int arr2[], int N)
{
  for(int i = 0; i < N; i++)
  {
    printf("%d ", arr1[i]);
  }
  printf("\n");
  for(int i = 0; i < N; i++)
  {
    printf("%d ", arr2[i]);
  }
  printf("\n");
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

  initialize(set, size, SET_MAX);
  print_two_arrays(set, size, SET_MAX);

  return 0;
}
