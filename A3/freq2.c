#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>


int letter_count(char *);
int * create_freq_table();
void add_letters(int *, char *);

int main(int argc, char *argv[]){ 

    FILE *fp;
    char *fileName , *inputStr;
    int *freqTable;
    int numLetters , numCharacters;
    numLetters = 0;
    numCharacters = 0;


    //CHECK FLAGS 
    int opt; 

    while((opt = getopt(argc, argv, "F")) != -1){  
        switch(opt){  
            case 'o':  
                printf("option: %c\n", opt);  
                break;  
            case 'r':  
                printf("option: %c\n", opt);  
                break;  
            case 'F':  
                printf("filename: %s\n", argv[optind]);  
                fileName = argv[optind];
                break;  
        }  
    }  

    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 



    //OPEN FILE
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    // reads text until newline is encountered
    fscanf(fp, "%[^\n]", inputStr);
    printf("\nData from the file:\n%s", inputStr);
  

    //CREATE FREQ TABLE ARRAY W/ ALL ELEMENTS INITIALIZED TO 0
    freqTable = create_freq_table();

    //FIND NUMBER OF LETERS IN FILE/INPUT
    numLetters = letter_count(inputStr);
    numCharacters = char_count(inputStr);


    printf("\nTotal number of letters in file '%s': %d" , fileName , numLetters);
    printf("\nTotal number of characters in file '%s': %d" , fileName , numCharacters);


    //END PROGRAM
    printf("\n\n\nQuitting...");
    return 0; 
} 



int letter_count(char *str){

    int i, letter, character;
    i = 0;
    letter = 0;
    while(str[i] != '\0'){
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
            letter++;
        }
      //else{
      //character++;
      //}
        i++;
    }

    return letter;
}

int char_count(char *str){

    int i;
    i = 0;

    while(str[i] != '\0'){
        i++;
    }

    return i;
}

int * create_freq_table(){

    int * table;
    int i;

    table = (int*) malloc (sizeof(int) *26);

    for(i=0; i < 26; i++){
        table[i] = 0;
    }

    return table;
}

void add_letters(int *freq_table, char * string){

    int i, c, letterCount;

    letterCount = letter_count(string);
    
    for(i = 0; i < letterCount; i++){

        c = string[i];

        if('a' <= c && c <= 'z'){
            freq_table[c - 'a']++;
        }      
        else if('A' <= c && c <= 'Z'){
            freq_table[c - 'A']++;
        }     
    }

}




