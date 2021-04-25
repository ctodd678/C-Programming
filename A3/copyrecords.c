#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

//FUNCTION DEFINITIONS
int     letter_count        (char *);
int     char_count          (char *);
int    *create_freq_table   ();
int     offset              (char);
int     encode              (char , int);
float   encode_shift        (char *);
int     to_decode           (int);
void    add_letters         (int *, char *);
float   chi_sq              (int , char* , char);

//GLOBAL DEFINTION OF ENGLISH LETTER FREQUENCIES    
float EF[26] = {8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.707,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074};



int main(int argc, char *argv[]){ 

    FILE *fp1 , *fp2;
    char *inputFile ,  *outputFile, *inputStr;
    int  *text_freq;
    int   numLetters , numCharacters, size;

    int flag_F = 0, flag_n = 0, flag_s = 0, flag_S = 0, flag_t = 0, flag_x = 0;

    outputFile = NULL;

    //CHECK FLAGS 
    int opt; 
    while((opt = getopt(argc, argv, "FOnsStx")) != -1){  
        switch(opt){  
            //INPUT FILE NAME
            case 'F':  
                printf("Input filename: %s\n", argv[optind]);  
                inputFile = argv[optind];
                flag_F = 1;
                break;
            //OUTPUT FILE NAME
            case 'O':  
                printf("Output filename: %s\n", argv[optind]);
                outputFile = argv[optind];  
                break; 
            //SUPPRESSES PRINTING OF DECODED FILE TO STDOUT 
            case 'n':  
                printf("option: %c\n", opt); 
                flag_n = 1; 
                break; 
            //COMPUTE CAESAR SHIFT VALUE FOR DECODING
            case 's':  
                printf("option: %c\n", opt);  
                flag_s = 1;
                break;  
            //COMPUTE CAESAR SHIFT VALUE FOR ENCODING
            case 'S':  
                printf("option: %c\n", opt); 
                flag_S = 1; 
                break;
            //COMPUTER CHARACTER COUNT AND LETTER FREQUENCY
            case 't':  
                printf("option: %c\n", opt);
                flag_t = 1;  
                break;  
            //COMPUTE CHI-SQUARED FOR ALL SHIFT VALUES
            case 'x':  
                printf("option: %c\n", opt); 
                flag_x = 1; 
                break;       
        }  
    }
    argc -= optind;
    argv += optind;  

    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 


    if(flag_F == 0){
        printf("\nNo -F flag entered. Reading from stdin...");

    }

    //OPEN FILE(s)
    if ((fp1 = fopen(inputFile, "r")) == NULL) {
        printf("\nError! opening file");
        goto end;
    }

    //CREATE OUTPUT FILE
    if(outputFile != NULL){
        fp2 = fopen(outputFile , "w+");
    }
    else{
        printf("\nNo file created...");
    }

    //CHECK FILE SIZE
    fseek(fp1, 0, SEEK_END); 
    size = ftell(fp1); 
    fseek(fp1, 0, SEEK_SET);
    printf("\nSize of file is:%d" , size);

    //ALLOCATE MEMORY FOR FILESIZE
    inputStr = (char*) malloc(sizeof(char*) * size);

    //READ TEXT FROM FILE AND PRINT TO STDOUT
    fscanf(fp1, "%[^\n]", inputStr);


    if(flag_n == 0){
        printf("\nData from the file:\n%s", inputStr);
    }

    if(flag_t == 0){
        //printf("\nData from the file:\n%s", inputStr);
    }
    if(flag_S == 0){
        //printf("\nData from the file:\n%s", inputStr);
    }
    if(flag_x == 0){
        //printf("\nData from the file:\n%s", inputStr);
    }


    //CREATE FREQ TABLE ARRAY W/ ALL ELEMENTS INITIALIZED TO 0
    text_freq = create_freq_table();

    //FIND NUMBER OF LETERS IN FILE/INPUT
    numLetters = letter_count(inputStr);
    numCharacters = char_count(inputStr);

    //FIND FREQUENCY OF EACH LETTER IN INPUT FILE
    add_letters(text_freq , inputStr);


    //PRINT STATEMENTS / OUTPUT
    printf("\nLETTER COUNT: %d" , numLetters);
    printf("\nSHIFT VALUE:");
    printf("\nCHARACTER COUNT: %d" , numCharacters);
    printf("\nFREQUENCY TABLE:\n");
  
    float chisq[26];
    //PRINT LETTER FREQUENCIES
    char c;
    for(int i = 0; i < 26; i++){
        c = i + 97;
        chisq[i] = chi_sq(0 , inputStr , c);
        printf("\n'%c' => %d" , c , text_freq[i]);
        if(text_freq[i] < 10){
            printf(" ");
        }
        printf("        %d" ,i );
        if(i < 10){
            printf(" ");
        }
        printf(" => ");
        if(chisq[i] < 10){
            printf(" ");
        }
        printf(" %.8f" , chisq[i]);
    }
    float minChi = 0;
    minChi = encode_shift(inputStr);
    int shiftValue;
    for(int i = 0; i < 26; i++){
        if(minChi = chisq[i]){
            shiftValue = i;
        }
    }

    //DECODE FILE (flag '-s')
    if(flag_s == 0){
        int decodeValue = 0;
        decodeValue = to_decode(shiftValue);
        printf("\nShift to decode vile:\n%s", inputStr);
    }

    printf("\nMinimum chi-quared with shift value %d is: %.8f" , shiftValue, minChi);

    //FREE AND FCLOSE STATEMENTS
    free(text_freq);
    fclose(fp1);
    free(inputStr);

    //END PROGRAM
    end:
    printf("\n\n\nQuitting...");
    return 0; 
} 

float chi_sq(int shift , char * input , char c){

    //printf("\nRunning chi_sq...");

    float chi[26];
    int i, n;
    int *text_freq;

    text_freq = create_freq_table();
    add_letters(text_freq , input);

    n = letter_count(input);


    chi[offset(c)] = 0;
    
    //CALCULATE CHI-SQUARED VALUE
    for(i = 0; i < 26; i++){
        chi[offset(c)] = chi[offset(c)] + ((pow((n * (EF[offset(c)] - text_freq[offset(encode(c, shift))])) , 2) / (n * n * EF[offset(c)])) / n);
        //printf("\nCHI VALUE: %.8f" , chi[offset(c)]); 
    }

    return chi[offset(c)];
}

int letter_count(char *str){

    int i, letter;
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
    int c;

    table = (int*) malloc (sizeof(int) *26);

    for(c=0; c < 26; c++){
        table[c] = 0;
    }

    return table;
}

void add_letters(int *freq_table, char * string){

    int i , charCount;

    charCount = char_count(string);
    
    for(i = 0; i < charCount; i++){

        if('a' <= string[i] && string[i] <= 'z'){
            freq_table[string[i] - 97]++;
        }      
        if('A' <= string[i] && string[i] <= 'Z'){
            freq_table[string[i] - 65]++;
        }     
    }
}

int offset(char c){

    if('a' <= c && c <= 'z'){
            return c - 97;
        }      
    else if('A' <= c && c <= 'Z'){
            return c - 97;
        } 
    printf("\nERROR in offset.");
    return 0;   
}

int encode(char c , int shift){
     
        if (islower(c)) {
            c = (c-'a' + shift) % 26 + 'a';
        }
        else if (isupper(c)) {
            c = (c-'A' + shift) % 26 + 'A';
        }

    return c;
}

float encode_shift(char *input){

    printf("\n\nRunning encode_shift...");

    int i;
    
    float chiValue[26], lowValue;
    chiValue[0] = 99999;
    lowValue = 99999;

    //FIND SMALLEST CHI VALUE
    for(i = 0; i < 26; i++){
        char c = i + 97;
        chiValue[i] = chi_sq(i , input , c);
        //printf("\nCHI VALUE %d: %.8f" , i , chiValue[i]);
        if(chiValue[i] < lowValue){
            lowValue = chiValue[i];
            //printf("\nNEW LOW VALUE: %.8f" , lowValue);
        }
    }

    return lowValue;
}

int to_decode(int shift, ){

    return shift;
}










