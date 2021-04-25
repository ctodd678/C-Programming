#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCT DECLARTION
struct Double_Array{
  double **array;
  int rowsize;
  int colsize;
};

//FUNCTION HEADERS
struct Double_Array * shallow_copy(struct Double_Array * );
struct Double_Array * deep_copy(struct Double_Array * );
struct Double_Array * double_array();
void print_struct(struct Double_Array *, char *);
void print_array(struct Double_Array* ptr);
void randomize_array(struct Double_Array * doubleArrayPtr, double a, double b);
double rand_double(double a, double b);

int main(){

  //DECLARATIONS
  struct Double_Array *a1;
  struct Double_Array *a2;
  struct Double_Array *a_shallow;
  struct Double_Array *a_deep;
  struct Double_Array *b1;
  char *h_a1, *h_a2, *h_ashallow, *h_adeep, *h_b1;
  double a , b;
  int i;

  h_a1       = "\nThe structure pointed to by a1 is:";
  h_a2       = "\nThe structure pointed to by a2 is:";
  h_ashallow = "\nThe structure pointed to by a_shallow is:";
  h_adeep    = "\nThe structure pointed to by a_deep is:";
  h_b1         = "\nThe structure pointed to by b1 is:";


  a = 0.0;
  b = 10.0;

  //QUESTION 2a
  printf("\n--------------------------------------");
  printf("\n            Question 2a"               );
  printf("\n--------------------------------------");

  //INITALIZE AND RANDOMIZE a1
  a1 = double_array();
  randomize_array(a1 , a , b);

  //PRINT ADDRESS OF a1
  printf("\n\nthe address of a1 is %p" , a1);
  print_struct(a1 , h_a1);

  //INIALIZE a2
  a2 = a1;

  //PRINT ADDRESS OF a1
  printf("\n\nthe address of a2 is %p" , a2);
  print_struct(a2 , h_a2);

  //SHALLOW COPY
  a_shallow = shallow_copy(a1);

  //PRINT ADDRESS OF a_deep
  printf("\n\nthe address of a_shallow is %p" , a_shallow);
  print_struct(a_shallow , h_ashallow);

  //DEEP COPY
  a_deep = deep_copy(a1);

  //PRINT ADDRESS OF a_deep
  printf("\n\nthe address of a_deep is %p" , a_deep);
  print_struct(a_deep , h_adeep);

  //END OF QUESTION 2a
  printf("\n\n\n");







  //QUESTION 2b
  printf("\n--------------------------------------");
  printf("\n            Question 2b"               );
  printf("\n--------------------------------------");

  a1->array[0][1] = 100.0;
  a2->array[1][2] = 200.0;
  a_shallow->array[2][3] = 300.0;
  a_deep->array[3][4] = 400.0;

  //PRINT OUTPUT
  print_struct(a1 , h_a1);
  print_struct(a2 , h_a2);
  print_struct(a_shallow , h_ashallow);
  print_struct(a_deep , h_adeep);

  //END OF QUESTION 2b
  printf("\n\n\n");








  //QUESTION 2c
  printf("\n--------------------------------------");
  printf("\n            Question 2c"               );
  printf("\n--------------------------------------");

  //INITIALIZE ARRAY b1
  b1 = double_array();
  randomize_array(b1 , 10.0 , 20.0);

  a2->array = b1->array;

  print_struct(a1 , h_a1);
  print_struct(a2 , h_a2);
  print_struct(a_shallow , h_ashallow);
  print_struct(a_deep , h_adeep);
  print_struct(b1 , h_b1);

  a1->array[0][1] = 5000.0;
  a2->array[1][2] = 6000.0;
  a_shallow->array[2][3] = 700.0;
  a_deep->array[3][4] = 8000.0;
  b1->array[4][5] = 9000.0;

  print_struct(a1 , h_a1);
  print_struct(a2 , h_a2);
  print_struct(a_shallow , h_ashallow);
  print_struct(a_deep , h_adeep);
  print_struct(b1 , h_b1);

  //END OF QUESTION 2c
  printf("\n\n\n");






  //Question 2D (FREE MEMORY)
  for(i = 0; i < 6; i++){
    free(a1->array[i]);
    free(a_deep->array[i]);
    free(b1->array[i]);
  }
  free(a1->array);
  free(a_deep->array);
  free(b1->array);

  free(a1);
  free(a_deep);
  free(b1);
  free(a_shallow);


  return 0;
}



struct Double_Array * double_array(){
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

void print_struct(struct Double_Array * ptr , char * c){

  unsigned int i;

  //PRINT HEADER
  printf("\n\n");
  for(i = 0; i < strlen(c); i++){
    printf("%c" , c[i]);
  }

  //PRINT ADDRESS
  printf("\nstruct address = %p" , ptr);

  //PRINT ROW AND COL SIZE
  printf("\nrow_size = %d, col_size = %d" , ptr->rowsize , ptr->colsize);

  //PRINT ARRAY ADDRESS
  printf("\narray address = %p, with contents:" , ptr->array);
  printf("\n");

  //PRINT ARRAY
  print_array(ptr);
  printf("\n");
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

struct Double_Array * shallow_copy(struct Double_Array * ptr){

  struct Double_Array * copy;
  copy = (struct Double_Array*) malloc (sizeof(struct Double_Array));

  //memcpy(copy,ptr,sizeof(struct Double_Array));
  copy = ptr;

  return copy;
}

struct Double_Array * deep_copy(struct Double_Array * ptr){

  struct Double_Array * copy;
  copy = double_array();
  copy -> array = ptr->array;
  copy -> rowsize = ptr->rowsize;
  copy -> colsize = ptr->colsize;

  return copy;
}
