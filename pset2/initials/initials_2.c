#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


//#define NAME_SIZE 50
int main(void){
int i=0,j=0;
printf("Please enter your name: \n");
string name = get_string();
char space = {' '};
int  k = strlen(name);

//printf("K equals: %i", k);


for (i=0; i<k; i++)
    { 
    printf("letter is %c\n", name[i]);
    while ( j == 0) 
    {printf("%c", name[i]); j = 1;} 
    if (name[i] == space)
        {
        printf("SPACE LORD of debugging");
        j = 0;
        }
        }
return 0;
}