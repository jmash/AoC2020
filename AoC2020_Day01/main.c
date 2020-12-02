#include <stdio.h>

int main(int argc, const char *argv[])
{
  FILE * input = fopen("./input.txt", "r");
  int heldInt = 0;
  int newlineCount = 0;
  int product = 1;
  char currCh;
  
  if(input)
  {
      while((currCh = fgetc(input)) != EOF)
      {
          if(currCh == '\n') newlineCount++;
      }

      fseek(input, 0, SEEK_SET);
      printf("%d\n", newlineCount);
      int expenses[newlineCount];

      for(int i = 0; i < newlineCount; i++)
      {
          fscanf(input, "%d\n", &expenses[i]);
      }

      for(int i = 0; i < newlineCount; i++)
      {
          heldInt = expenses[i];
          for(int j = i+1; j < newlineCount; j++)
          {
              if((heldInt + expenses[j]) == 2020)
              {
                product = heldInt * expenses[j]; 
              }
              //printf("%d + %d\n", heldInt, expenses[j]); 
          }
      }
  } 
  else
  {
      printf("Ya done goofed, ya big idjit. That file is empty.\n");
      return 1;
  }

  printf("Product is: %d\n", product);
  return 0;
}
