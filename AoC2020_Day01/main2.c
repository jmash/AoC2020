#include <stdio.h>

int main(int argc, const char *argv[])
{
  FILE * input = fopen("./input.txt", "r");
  int heldInt1 = 0;
  int heldInt2 = 0;
  int newlineCount = 0;
  int product = 1;
  int sumCounter = 0;
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
          heldInt1 = expenses[i];
          for(int j = i+1; j < newlineCount; j++)
          {
              heldInt2 = expenses[j];
              for(int k = j+1; k < newlineCount; k++)
              {
                  sumCounter++;
                  //printf("%d + %d + %d\n", heldInt1, heldInt2, expenses[k]);
                  if((heldInt1 + heldInt2 + expenses[k]) == 2020)
                  {
                      product = heldInt1 * heldInt2 * expenses[k];
                  }
              }
          }
      }
  } 
  else
  {
      printf("Ya done goofed, ya big idjit. That file is empty.\n");
      return 1;
  }

  printf("Product is: %d\n", product);
  printf("number of sums is %d\n", sumCounter);
  fclose(input);
  return 0;
}
