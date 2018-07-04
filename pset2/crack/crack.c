#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, string argv[])
{   
char a[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
if (argc != 2) { printf("In order to crack a password you must pass a SINGLE hash to the program!\n"); return 1;}
char *hash = argv[1];
// printf("%s\n", hash);
char pass[5];
for ( int i = 0; i < 56; i ++ )
{
  pass[0] = a[i];
    for ( int j = 0; j < 56; j ++ )
    {
    pass[1] = a[j];
        for ( int k = 0; k < 56; k ++ )
        {
        pass[2] = a[k];
            for ( int l = 0; l < 56; l ++ )
            {
            pass[3] = a[l];
            pass[4] = '\0';
            if (strcmp (hash, crypt(pass,"50")) == 0)
            {
                 printf("%s \n", pass);
                 return 0;
            }
            }
        }
    }
}
for ( int i = 0; i < 56; i ++ )
{
  pass[0] = a[i];
    for ( int j = 0; j < 56; j ++ )
    {
    pass[1] = a[j];
    pass[2] = '\0';
            if (strcmp (hash, crypt(pass,"50")) == 0)
            {
                 printf("%s \n", pass);
                 return 0;
            }
        }
}
for ( int i = 0; i < 56; i ++ )
{
  pass[0] = a[i];
    for ( int j = 0; j < 56; j ++ )
    {
    pass[1] = a[j];
        for ( int k = 0; k < 56; k ++ )
        {
        pass[2] = a[k];
        pass[3] = '\0';
            if (strcmp (hash, crypt(pass,"50")) == 0)
            {
                 printf("%s \n", pass);
                 return 0;
            }
        }
    }
}
for ( int i = 0; i < 56; i ++ )
{
  pass[0] = a[i];
  pass[1] = '\0';
            if (strcmp (hash, crypt(pass,"50")) == 0)
            {
                 printf("%s \n", pass);
                 return 0;
            }
}
return 0;
}