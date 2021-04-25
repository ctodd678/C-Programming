#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Double_Array{
  double **array;
  int rowsize;
  int colsize;
};

struct Double_Array *  double_array(int,int);

double rand_double(double , double);
void print_array(struct Double_Array*);
void randomize_array(struct Double_Array*, double, double);
void swap_rows(struct Double_Array* , int , int);
void swap_columns(struct Double_Array* ptr , int , int);
void free_array(struct Double_Array* ptr);


int main(){

  srand ( time(NULL) ); //FOR RANDOM NUMBERS

  double a , b;
  int row , col;
  int r1 , r2 , c1 , c2;

  struct Double_Array *doubleArrayPtr;



  printf("\n--------------------------------------");
  printf("\n            Question 1"                );
  printf("\n--------------------------------------");

  //INPUT VALUES
  a = 0.0;
  b = 100.0;
  row = 6;
  col = 9;


  //INITIALIZE 2D ARRAY INSIDE OF Double_Array STRUCT
  printf("\n\nRunning double_array...");
  doubleArrayPtr = double_array(row , col);
  printf("\nDone!");

  //RANDOMLY INITIALIZE 2D ARRAY INSIDE OF Double_Array STRUCT
  printf("\n\nRandomly initializing array in Double_Array struct...");
  randomize_array(doubleArrayPtr , a , b);
  printf("\nDone!");


  //PRINTING ORIGINAL 2D ARRAY
  printf("\n\nPrinting array from Double_Array struct...");
  print_array(doubleArrayPtr);
  printf("\nDone!");


  //RANDOMLY SWAPPING ROWS
  printf("\n\nRandomly picking and swapping two rows from array...");

  r1 = rand() % 6;
  r2 = rand() % 6;
  while(r1 == r2){ //LOOP UNTIL 2 DIFFERENT NUMBERS
    r2=rand() % 6;
  }

  //SWAP ROWS
  swap_rows(doubleArrayPtr , r1 , r2);
  printf("\nDone!");


  //PRINTNG 2D ARRAY AFTER ROWS WERE SWAPPED
  printf("\n\nRows swapped were: %d & %d" , r1 + 1 , r2 + 1);
  printf("\nPrinting array after rows were swapped...");
  print_array(doubleArrayPtr);
  printf("\nDone!");


  //RANDOMLY SWAPPING COLUMNS
  printf("\n\nRandomly picking and swapping two columns from array...");
  c1 = rand() % 6;
  c2 = rand() % 6;
  while(c1 == c2){ //LOOP UNTIL 2 DIFFERENT NUMBERS
    c2 = rand() %6;
  }
  printf("\nDone!");

  //PRINTNG 2D ARRAY AFTER COLUMNS WERE SWAPPED
  printf("\n\nColumns swapped were: %d & %d" , c1 + 1, c2 + 1);
  swap_columns(doubleArrayPtr , c1 , c2);
  printf("\nPrinting array after columns were swapped...");
  print_array(doubleArrayPtr);
  printf("\nDone!");

  //FREEING MEMORY
  free_array(doubleArrayPtr);


  printf("\n\n\n");

  return 0;
}

double rand_double(double a, double b){
  double temp;

  if(a>b){
    return ((double) rand() / (double) RAND_MAX) * (b-a) + a;
  }
  else if(b>a){
    temp = a;
    a = b;
    b = temp;
    return ((double) rand() / (double)  RAND_MAX) * (b-a) + a;
  }

  printf("\nERROR");
  return 0;
}

struct Double_Array * double_array(int row, int col){

  int i, j;

  struct Double_Array *ptr;

  ptr = (struct Double_Array*) malloc(sizeof(struct Double_Array));
  ptr->array = (double**) malloc(sizeof(*ptr->array) * 6);


  for(i = 0; i < 6; i++){
    ptr->array[i] = (double*) malloc(sizeof(ptr->array) * 9);
  }

    ptr->colsize = 9;
    ptr->rowsize = 6;

  return ptr;
}

void randomize_array(struct Double_Array * doubleArrayPtr, double a, double b){

  int i, j;

  //RANDOMLY INITIALIZE ROWS
  //RANDOMLY INITIALIZE COLUMNS
  for(i = 0; i < 6; i++){
    for(j = 0; j < 9; j++){
      doubleArrayPtr->array[i][j] = rand_double(a , b);
    }
  }
}

void print_array(struct Double_Array* ptr){

  int i , j;

  //Nested for loops to print 2D array.
  printf("\n");
  for(i = 0; i < 6; i++){
    for(j = 0; j < 9; j++){
      if(ptr->array[i][j] < 9.999){
        printf(" ");
      }
      printf("%.1lf" , ptr->array[i][j]);
      printf("    ");
    }
    printf("\n");
  }
}

void swap_rows(struct Double_Array* ptr , int r1 , int r2){

    int i;

    for (i = 0; i < ptr->rowsize; i++){
      double temp;
      temp = ptr->array[r2][i];
      ptr->array[r2][i] = ptr->array[r1][i];
      ptr->array[r1][i] = temp;
    }
}

void swap_columns(struct Double_Array* ptr , int c1 , int c2){

    int i;

    for (i = 0; i < ptr->rowsize; i++){
      double temp;
      temp = ptr->array[i][c2];
      ptr->array[i][c2] = ptr->array[i][c1];
      ptr->array[i][c1] = temp;
    }

}

void free_array(struct Double_Array* ptr){

  int i;
  for(i = 0; i < 6; i++){
    free(ptr->array[i]);
  }
  free(ptr->array);
  free(ptr);

}
