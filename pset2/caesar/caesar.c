#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{   
if (argc != 2) { return 1;}
int k = atoi(argv[1]), astoalu = 65, astoall = 97;
printf ("plaintext: ");
string ciphert = get_string();
printf ("ciphertext: ");
for (int i = 0, n = strlen(ciphert); i < n; i++)
{
    if (isalpha(ciphert[i])) 
        {
        if (isupper(ciphert[i])) 
        {
            int tu = ciphert[i] - astoalu;
            int cu = ( tu + k) % 26;
            int tru = cu + astoalu;
            printf("%c", tru);}
        if (islower(ciphert[i])) 
        {
            int tl = ciphert[i] - astoall;
            int cu = ( tl + k) % 26;
            int trl = cu + astoall;
            printf("%c", trl);}
        }
}
    printf("\n");
    return 0;
}