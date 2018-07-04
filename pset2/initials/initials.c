#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
int i=0,j=0;

string name = get_string();
char space = {' '};
int  k = strlen(name);
for (i=0; i<k; i++)
    {
    while ( j == 0 && name[i] != '\0') 
    { if (name[i] != space ) {printf("%c", toupper(name[i])); j = 1;}
        else i++;
    } 
    if (name[i] == space )
        {
        j = 0;
        }
        }
printf("\n");
return 0;
}