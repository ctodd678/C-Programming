#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char *argv[]){

  FILE        *fp;
  char        *inputFile = NULL , *inputStr = NULL , *tempStr = NULL;
  int          i, size , read_size , push1 = 0 , begI = 0 , endI = 0;
  value_type  *temp_d;
  key_type    *temp_f;

  value_type d;
  key_type f;
  
  Sorted_List * list = NULL;

  push1 = push1 + 0;



  /*CHECK COMMAND LINE FOR FILE NAME - GET USER INPUT IF NONE ENTERED */
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

  if (size != read_size)
    {
    printf("\nERROR! Size mismatch.\n");
  }

  /* CREATE LIST */
  list = create_list ();
  

  /* READ COMMANDS FROM FILE */
  i = 0;
  int j;
  do{
    /* add node head commands */
    if((inputStr[i] == 'p' && inputStr[i+1] == ' ') && (inputStr[i - 1] == '\n' || i == 0)){
      
      i++;
      while(inputStr[i] == ' '){
        i++;
      };
      begI = 0;
      endI = 0;

      begI = i;
      while(inputStr[i] != '\n'){
        i++;
      }
      endI = i;

      tempStr = malloc(sizeof(char) * (endI - begI) + 1);
      for(j = 0; j < (endI - begI); j++){
        tempStr[j] = inputStr[j + begI];
      }
      tempStr[j] = '\0';

      strcpy(d , tempStr);
      f = strlen(d);
      free(tempStr);
      push1 = push(list , d , f);
      printf("\np:          %d   %s" , f , d);

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
      begI = 0;
      endI = 0;

      begI = i;
      while(inputStr[i] != '\n'){
        i++;
      }
      endI = i;

      tempStr = malloc(sizeof(char) * (endI - begI) + 1);
      for(j = 0; j < (endI - begI); j++){
        tempStr[j] = inputStr[j + begI];
      }
      tempStr[j] = '\0';

      strcpy(d , tempStr);
      f = strlen(d);
      free(tempStr);
      push1 = append(list , d , f);
      printf("\na:          %d   %s" , f , d);

      list->head_sort = list->head;

      if(list->size == 1){
        list->tail = list->head;
        list->tail_sort = list->head;
      }
    }

    /* print_list command */
    if(inputStr[i] == 'p' && inputStr[i+1] == 'r'){
      print_list(list);
    }

    /* print_sort command */
    if(inputStr[i] == 's' && inputStr[i+1] == 'o'){
      sort_list_key(list);
      print_sort(list);
    }

    /* rem_first */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'f'){
      temp_d = malloc(sizeof(char) * 80);
      temp_f = malloc(sizeof(int));
      strcpy(*temp_d , list->head->value);
      remove_first(list , temp_d , temp_f);
      printf("\nrem_first:  %d   %s" , *temp_f , *temp_d);  
      //free(temp_d);
      free(temp_f);
    }

     /* rem_last */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'l' && inputStr[i+7] == 't'){
      push1 = remove_last(list , temp_d , temp_f); 
    }

    /* rem_smallest */
    if(inputStr[i] == 'r' && inputStr[i+4] == 's'){
      push1 = remove_smallest_key(list , temp_d , temp_f); 
    }

    /* rem_largest */
    if(inputStr[i] == 'r' && inputStr[i+4] == 'l' && inputStr[i+10] == 't' ){
      push1 = remove_largest_key(list , temp_d , temp_f); 
    }

    /* empty */
    if(inputStr[i] == 'e' && inputStr[i+1] == 'm' && inputStr[i+2] == 'p' ){
      empty_list(list); 
    }
    
    i++;
  }while(inputStr[i] != '\0'); 

  //printf("\n\nTAIL TEST: %s" , list->tail->value);
  //printf("\n\nTAIL TEST: %s" , list->tail_sort->value);

  //destroy_list(list);
  
  printf("\n\nQuitting...\n");

  return 0;
}


