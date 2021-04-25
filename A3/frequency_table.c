#include <D:\OneDrive\OneDrive - University of Guelph\CIS2500\A3\header.h>  
#include <D:\OneDrive\OneDrive - University of Guelph\CIS2500\A3\functions.c>



int main(int argc, char *argv[]){ 

    FILE *fp;
    char *inputFile , *inputStr;
    int *freqTable;
    int numLetters = 0 , numCharacters = 0 , size;
    int flag_F = 0;

    //CHECK FLAGS 
    int opt; 

    while((opt = getopt(argc, argv, "F")) != -1){  
        switch(opt){  
            case 'F':    
                flag_F = 1;
                inputFile = argv[optind];
                break;  
        }
    }  

    //READ FILE (flag '-F')
    if(flag_F == 1){
        
        //OPEN FILE
        if ((fp = fopen(inputFile, "r")) == NULL) {
            printf("Error! opening file");
        exit(1);
        }

        //CHECK FILE SIZE
        fseek(fp, 0, SEEK_END); 
        size = ftell(fp); 
        fseek(fp, 0, SEEK_SET);

        //ALLOCATE MEMORY FOR FILESIZE
        inputStr = (char*) malloc(sizeof(char*) * size);

    
        //READ CONTENTS OF FILE AND PRINTS
        fscanf(fp, "%[^\n]", inputStr);
        printf("\nData from the file:\n%s\n", inputStr);    
    }

    //READ FROM STDIN IF NO '-F' FLAG IS ENTERED
    if(flag_F == 0){
        printf("\nNo '-F' flag detected reading from stdin...");
        printf("\nEnter string:\n");
        inputStr = (char*) malloc(sizeof(char*) * 1000);
        fgets(inputStr , 1000 , stdin);
    }
    
    //CREATE FREQ TABLE ARRAY W/ ALL ELEMENTS INITIALIZED TO 0
    freqTable = create_freq_table();

    //FIND NUMBER OF LETERS IN FILE/INPUT
    numLetters = letter_count(inputStr);
    numCharacters = char_count(inputStr);

    //GET FREQUENCY OF EACH LETTER
    add_letters(freqTable , inputStr);


    //PRINT FREQUENCY TABLE
    printf("\nFREQUENCY TABLE:");
    char c;
    int i;
    for(i = 0; i < 26; i++){
        c = i + 97;
        printf("\n'%c' => %d" , c , freqTable[i]);
        if(freqTable[i] < 10){
            printf(" ");
        }
    }
    
    //FREE EVERYTHING
    free(freqTable);
    if(flag_F == 1){
        fclose(fp);
    }
    free(inputStr);

    //END PROGRAM
    printf("\n\n\nQuitting...");
    return 0; 
} 






