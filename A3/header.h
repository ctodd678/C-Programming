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
float   encode_shift        (float *);
int     to_decode           (int , char*, float*);
void    add_letters         (int *, char *);
void    chi_sq              (int , char* , float*);

//GLOBAL DEFINTION OF ENGLISH LETTER FREQUENCIES    
float EF[26] = {8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.707,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074};