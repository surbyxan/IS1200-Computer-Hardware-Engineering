
#include <stdio.h>
#include <stdlib.h>
#define COLUMNS 6

//the sieve part is partly written by Anja Gullbrand. the rest is written by malin andreasson
//Prime checker
int is_prime(int n){
  if (n == 0 || n == 1 ){
    return 0;
  }

  for (int i = 2; i < n; i++){
    if((n % i) == 0){
      return 0;
    }
  }
  return 1;
}

//printing numbers
void print_number(int n){
   printf("%10d ", n);
}

// Sieves method
void print_sieves(int n){

  int* array = malloc(n*sizeof(int));
  int size = n;

   for(int i = 2; i < n; i++){
    array[i] = 1;
  }

  for(int i = 2; i*i < n; i++){
    if(array[i] != 0){
      for(int j = i*i; j < n; j += i){
        array[j] = 0;
      }
    }
  }

//mean_sieves
  int primcnt = 0;
  int primsm = 0;
  for (int i = 2; i < n; i++)
  {
    if (array[i] != 0)
    {
      primcnt++;
      primsm += i;
    }  
  }
 //calculating mean value
 int meansiv = (primsm / primcnt);
print_number(meansiv);


 /* // print numbers
  int column = 0;
  for (int i = 2; i < n; i++){
      if (array[i] != 0){
        print_number(i);
        column++;
      }
      if (column == COLUMNS)
      {
        printf("\n");
        column = 0; 
      }   
  }*/
  free(array);
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}