int strlen(char* str){
    char c = str[0];
    int i = 0; 
    while (c != '\0')
    {
        i++;
        c = str[i];
    }
    return i;
    
}