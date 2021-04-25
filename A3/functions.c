void chi_sq(int shift , char * input, float * chi){

    //printf("\nRunning chi_sq...");

    int i, n;
    int *text_freq;
    char c = 'a';

    text_freq = create_freq_table();
    add_letters(text_freq , input);

    n = letter_count(input);

    //CALCULATE CHI-SQUARED VALUE
    for(i = 0; i < 26; i++){
        c = i + 97;
        chi[offset(c)] = chi[offset(c)] + ((((n * (EF[offset(c)] - text_freq[offset(encode(c, shift))])) * (n * (EF[offset(c)] - text_freq[offset(encode(c, shift))]))) / (n * n * EF[offset(c)])) / n);
        //printf("\nCHI VALUE: %.8f" , chi[offset(c)]); 
    }
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

float encode_shift(float * chi){

    printf("\n\nRunning encode_shift...");

    int i;
    
    float  lowValue;
  
    lowValue = 99999;

    //FIND SMALLEST CHI VALUE
    lowValue = chi[0];
   
    for (i = 0; i < 26; i++)
    {
        if (chi[i] < lowValue)
        {
           lowValue = chi[i];
        }
    }

    return lowValue;
}

int to_decode(int shift , char *input, float * chi){

    float minChi = 0;
    minChi = encode_shift(chi);
    int shiftValue;
    for(int i = 0; i < 26; i++){
        if(minChi == chi[i]){
            shiftValue = i;
        }
    }

    if(minChi >= 0.5){
        return 0;
    }
    else{
        return shiftValue;
    }
    printf("\nERROR in to_decode!");
    return 0;
} 