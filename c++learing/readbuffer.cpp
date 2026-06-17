#include <iostream>
int main(){
    FILE* fp = fopen64("./in.txt","r");
    char buff;
    if (fp == nullptr)
    {
        printf("read file error");
    }
    while ( buff = fgetc(fp))
    {
        printf("%c",buff);
    }
    if (feof(fp))
    {
        printf("\nto the end");
    }
    fclose(fp);
}