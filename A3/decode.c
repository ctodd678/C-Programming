#include <D:\OneDrive\OneDrive - University of Guelph\CIS2500\A3\header.h>  
#include <D:\OneDrive\OneDrive - University of Guelph\CIS2500\A3\functions.c>

int main(int argc, char *argv[]){ 

    FILE *fp1 , *fp2;
    char *inputFile ,  *outputFile, *inputStr, *outputStr, c;
    int  *text_freq;
    int   numLetters = 0 , numCharacters = 0, size = 0, sizeOut = 0, i = 0, decodeValue = 0;
    float *chisq;

    int flag_F = 0, flag_n = 0, flag_s = 0, flag_S = 0, flag_t = 0, flag_x = 0;

    outputFile = NULL;



    //CHECK FLAGS 
    int opt; 
    while((opt = getopt(argc, argv, "FOnsStx")) != -1){  
        switch(opt){  
            //INPUT FILE NAME
            case 'F':
                printf("flag: %c\n", opt); 
                flag_F = 1;    
                inputFile = argv[optind];
                break;
            //OUTPUT FILE NAME
            case 'O':  
                printf("flag: %c\n", opt); 
                outputFile = argv[optind];  
                break; 
            //SUPPRESSES PRINTING OF DECODED FILE TO STDOUT 
            case 'n':  
                printf("flag: %c\n", opt); 
                flag_n = 1; 
                break; 
            //COMPUTE CAESAR SHIFT VALUE FOR DECODING
            case 's':  
                printf("flag: %c\n", opt);  
                flag_s = 1;
                break;  
            //COMPUTE CAESAR SHIFT VALUE FOR ENCODING
            case 'S':  
                printf("flag: %c\n", opt); 
                flag_S = 1; 
                break;
            //COMPUTER CHARACTER COUNT AND LETTER FREQUENCY
            case 't':  
                printf("flag: %c\n", opt);
                flag_t = 1;  
                break;  
            //COMPUTE CHI-SQUARED FOR ALL SHIFT VALUES
            case 'x':  
                printf("flag: %c\n", opt); 
                flag_x = 1; 
                break;       
        }  
    }
    argc -= optind;
    argv += optind;  

    for(; optind < argc; optind++){      
        printf("extra arguments: %s\n", argv[optind]);  
    } 

    //READ FILE (flag '-F')
    if(flag_F == 1){
        //OPEN FILE(s)
        if ((fp1 = fopen(inputFile, "r")) == NULL) {
            printf("\nError! opening file");
            exit(1);
        }
        //CHECK FILE SIZE
        fseek(fp1, 0, SEEK_END); 
        size = ftell(fp1); 
        fseek(fp1, 0, SEEK_SET);
 
        //ALLOCATE MEMORY FOR FILESIZE
        inputStr = (char*) malloc(sizeof(char*) * size);

        //READ TEXT FROM FILE
        fscanf(fp1, "%[^\n]", inputStr);
    }

    //READ FROM STDIN IF NO '-F' FLAG IS ENTERED
    if(flag_F == 0){
        printf("\nNo '-F' flag detected reading from stdin...");
        printf("\nEnter string:\n");
        inputStr = (char*) malloc(sizeof(char*) * 1000);
        fgets(inputStr , 1000 , stdin);
    } 

   
    //CREATE FREQ TABLE ARRAY W/ ALL ELEMENTS INITIALIZED TO 0
    text_freq = create_freq_table();

    //FIND FREQUENCY OF EACH LETTER IN INPUT FILE
    add_letters(text_freq , inputStr);


    chisq = (float*) malloc(sizeof(float*) * 26);
    for(i = 0; i < 26; i++){
        chisq[i] = 0;
    }
    for(i = 0; i < 26; i++){
        chisq[i] = 0;
        chi_sq(i , inputStr, chisq);
    }

    //PRINT LETTER FREQUENCY TABLE (flag '-t')
    if(flag_t == 1){
        //FIND NUMBER OF LETERS IN FILE/INPUT
        numLetters = letter_count(inputStr);
        numCharacters = char_count(inputStr);

        //PRINT NUMBER OF LETTERS AND CHARACTERS 
        printf("\nLETTERS IN TEXT: %d" , numLetters);
        printf("\nCHARACTERS IN TEXT: %d" , numCharacters);
        printf("\nFREQUENCY TABLE:");
        for(i = 0; i < 26; i++){
            c = i + 97;
            printf("\n'%c' => %d" , c , text_freq[i]);
            if(text_freq[i] < 10){
                printf(" ");
            }
        }
    }

    //PRINT CHI SQUARED VALUES FOR ALL SHIFTS (flag '-x')
    if(flag_x == 1){
        printf("\n\nCHI VALUES:");
        for(i = 0; i < 26; i++){
            printf("\n%d" ,i );
            if(i < 10){
                printf(" ");
            }
            printf(" => ");
            if(chisq[i] < 10){
                printf(" ");
            }
            printf(" %.8f " , chisq[i]);
        }

    }

    //PRINT SHIFT VALUE TO DECODE (flag '-s')
    if(flag_s == 1){
        decodeValue = to_decode(0 , inputStr , chisq);
        printf("\nShift to decode file: %d", decodeValue);
    }

    //PRINT SHIFT VALUE TO ENCODE MESSAGE (flag '-S')
    if(flag_S == 1){
        decodeValue = to_decode(0 , inputStr , chisq);
        printf("\nShift used to encode file: %d", decodeValue);
    }

    //CREATE OUTPUT FILE
    if(outputFile != NULL){
        fp2 = fopen(outputFile , "w+");
        i = 0;
        c = inputStr[0];
        while(c != '\0' ){
            c = inputStr[i];
            if (c >= 'a' && c <= 'z'){
                c = (c-'a' + (decodeValue * -1)) % 26 + 'a';
            }
            else if (c >= 'a' && c <= 'z'){
                c = (c-'A' + (decodeValue * -1)) % 26 + 'A';
            }
            fputc(c, fp2);
            i++;
        }
    }
    else{
        printf("\nNo file created. Please use -O flag.");
    }

    //SUPPRESS PRINTING OF DECODED DATA (flag '-n')
    if(flag_n == 0 && outputFile != NULL){

        //CHECK FILE SIZE
        fseek(fp2, 0, SEEK_END); 
        sizeOut = ftell(fp2); 
        fseek(fp2, 0, SEEK_SET);

        //ALLOCATE MEMORY FOR FILESIZE
        outputStr = (char*) malloc(sizeof(char*) * sizeOut);

        //READ CONTENTS OF FILE AND PRINTS
        fscanf(fp2, "%[^\n]", outputStr); 
        printf("\n\nDECODED DATA IN FILE '%s'\n%s\n" , outputFile , outputStr);
    }



    //FREE AND FCLOSE STATEMENTS
    free(chisq);
    free(text_freq);
    free(inputStr);
    if(flag_n == 0){
        free(outputStr);
    }
    if(flag_F == 1){
        fclose(fp1);
    }
    if(outputFile != NULL){
        fclose(fp2);
    }

    //END PROGRAM
    printf("\n\n\nQuitting...");
    return 0; 
} 