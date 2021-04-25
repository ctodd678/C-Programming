#include "header.h"

int main(int argc, char *argv[]){

  FILE        *fp;
  char        *inputFile = NULL , *inputStr = NULL;
  int          i, size , read_size , push1 = 0 , order = 0;
  value_type  temp_d;
  key_type    temp_f;
  long long t1, t2;

  value_type d;
  key_type f;

  Sorted_List * list = NULL;

  push1 = push1 + 0;

  printf("\n\n======= Q1A MAIN =======");

  /*CHCEK COMMAND LINE FOR FILE NAME - GET USER INPUT IF NONE ENTERED */
  if (argc >= 2){
    fp = fopen(argv[1], "r");
    printf("\nFile: %s opened for reading!" , argv[1]);
    inputFile = argv[1];
  }
  /*IF NO FILE IS ENTERED IN COMMAND LINE GET FILE FROM STDIN */
  else{
    printf("\n\nNo file entered, please enter file: ");
    inputFile = (char*) malloc(sizeof(char*) * 100);
    gets(inputFile);
    inputFile = (char*) realloc(inputFile , strlen(inputFile) + 1);

    printf("\nFILE NAME: %s" , inputFile);
    fp = fopen(inputFile, "r");
    printf("\nFILE: %s opened for reading!" , inputFile);
    /* IF NO FILE IS FOUND */
    if(fp == NULL){
      printf("\nERROR! No file with that name");
      printf("\n\nQuitting...\n");
      return 0;
    }
  }

  /*CHECK FILE SIZE*/
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  /* READ FILE INTO STIRNG AND CHECK SIZE */
  inputStr = (char*) malloc(sizeof(char) * (size + 1));     /* ALLOCATE MEMORY                 */
  read_size = fread(inputStr, sizeof(char), size, fp);      /* READ INTO STRING AND CHECK SIZE */
  printf("\nsize: %d read size: %d" , size , read_size);
  inputStr[read_size] = '\0';                               /* ADD NULL TERMINATOR             */

  if (size != read_size){
    printf("\nERROR! Size mismatch.");
  }

  /* CREATE LIST */
  list = create_list ();

  /* READ COMMANDS FROM FILE */
  i = 0;
  do{
    /* add node head commands */
    if((inputStr[i] == 'p' && inputStr[i+1] == ' ') && (inputStr[i - 1] == '\n' || i == 0)){

      i++;
      while(inputStr[i] == ' '){
        i++;
      };
      sscanf(&inputStr[i] , "%lf", &f);
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%d", &d);
      push1 = push(list , d , f);
      printf("\np:          %.2lf   %d" , f , d);


      list->head_sort = list->head;

      if(list->size == 1){
        list->tail = list->head;
        list->tail_sort = list->head;
      }
    }

    /* add node tail commands */
    if((inputStr[i] == 'a' && inputStr[i+1] == ' ') && (inputStr[i - 1] == '\n' || i == 0)){
      i++;

      while(inputStr[i] == ' '){
        i++;
      };

      sscanf(&inputStr[i] , "%lf", &f);

      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }

      sscanf(&inputStr[i] , "%d", &d);
      push1 = append(list , d , f);
      printf("\na:          %.2lf   %d" , f , d);


      list->head_sort = list->head;

      if(list->size == 1){
        list->tail = list->head;
        list->tail_sort = list->head;
      }
    }

    /* print_list command */
    if(inputStr[i] == 'p' && inputStr[i+1] == 'r' && inputStr[i+6] == 'a' && (inputStr[i - 1] == '\n' || i == 0)){
      print_list(list);
    }

    /* print_sort command */
    if(inputStr[i] == 's' && inputStr[i+1] == 'o'){
      sort_list_key(list);
      print_sort(list);
    }

    /* rem_first */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'f'){
      push1 = remove_first(list , &temp_d , &temp_f);
      printf("\nrem_first:  %.2lf   %d" , temp_f , temp_d);
    }

     /* rem_last */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'l' && inputStr[i+7] == 't'){
      push1 = remove_last(list , &temp_d , &temp_f);
      printf("\nrem_last:  %.2lf   %d" , temp_f , temp_d);
    }

    /* rem_smallest */
    if(inputStr[i] == 'r' && inputStr[i+4] == 's'){
      push1 = remove_smallest_key(list , &temp_d , &temp_f);
      printf("\nrem_smallest:  %.2lf   %d" , temp_f , temp_d);
    }

    /* rem_largest */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'l' && inputStr[i+10] == 't' ){
      push1 = remove_largest_key(list , &temp_d , &temp_f);
      printf("\nrem_largest:  %.2lf   %d" , temp_f , temp_d);
    }

    /* empty */
    if(inputStr[i] == 'e' && inputStr[i+1] == 'm' && inputStr[i+2] == 'p' ){
      empty_list(list);
    }


    /* Q2 COMMANDS8 */
    /* count_up command */
    if((inputStr[i] == 'c' && inputStr[i+8] == ' ') && (inputStr[i - 1] == '\n' || i == 0)){
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%d", &d);
      printf("\ncurrent inputStr: %c" , inputStr[i]);
      printf("count_up from 0 to %d \n", d);

      count_up(0,d);
    }

    /* count_down command */
    if((inputStr[i] == 'c' && inputStr[i+6] == 'd') && (inputStr[i - 1] == '\n' || i == 0)){
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%d", &d);
      printf("\ncurrent inputStr: %c" , inputStr[i]);
      printf("\ncount_down from %d to 0 by 2\n" , 2 * d);
      count_down(d);
    }

    /* nth command */
    if(inputStr[i] == 'n' && inputStr[i+1] == 't' && inputStr[i+2] == 'h'){
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%d", &d);
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      if(inputStr[i] == 'I'){
        Node *temp = list->head;
        order = 0;
        printf("\nnth:       n = %d, Insertion Order" , d);
        nth(temp , d - 1, order);
      }
      if(inputStr[i] == 'S'){
        Node *temp = list->head_sort;
        order = 1;
        printf("\nnth:       n = %d, Key Sort Order" , d);
        nth(temp , d - 1 , order);
      }
      if(d > list->size){
        printf("\nERROR! trying to run remove_nth - input greater than size.");
        return 0;
      }
    }

    /* nth_remove command */
    if(inputStr[i] == 'r' && inputStr[i+1] == 'e' && inputStr[i+2] == 'm' && inputStr[i+7] == 'n'){
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%d", &d);
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      if(inputStr[i] == 'I'){
        Node *temp = list->head;
        order = 0;
        printf("\nremove_nth:       n = %d, Insertion Order" , d);
        remove_nth(temp , d - 1, order);
      }
      if(inputStr[i] == 'S'){
        Node *temp = list->head_sort;
        order = 1;
        printf("\nremove_nth:       n = %d, Key Sort Order" , d);
        remove_nth(temp , d - 1 , order);
      }
      if(d > list->size){
        printf("\nERROR! trying to run remove_nth - input greater than size.");
        return 0;
      }
    }

    /* gcd commands */
    if((inputStr[i] == 'g' && inputStr[i+1] == 'c' && inputStr[i+2] == 'd') && (inputStr[i - 1] == '\n' || i == 0)){
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%I64d", &t1);
      i++;
      while(inputStr[i] != ' '){
        i++;
      }
      while(inputStr[i] == ' '){
        i++;
      }
      sscanf(&inputStr[i] , "%I64d", &t2);
      printf("\ngcd(%I64d,  %I64d) == %I64d" , t1 , t2 , gcd(t1 , t2));

    }


    i++;
  }while(inputStr[i] != '\0');

  //destroy_list(list);

  printf("\n\nQuitting...\n");

  return 0;
}
