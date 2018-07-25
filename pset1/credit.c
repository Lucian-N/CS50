#include <stdio.h>
#include <cs50.h>
#include <math.h>



int main(void){
    long long int c,n,m, count = 0, count2 = 0 ;
    long long int numberArray[16], numberArray2[16];
    short int i,j,sume = 0,  sumo = 0, checkc = 0;


    printf(" Please enter a valid Credit card number: ");
    c = get_long_long();
    while ( c < 0 ) {
        c=get_long_long();
    }
    n=c;
    while (n >= 1 && n < 10000000000000000){
        n /= 10;
        count++;
    }
    if (count != 0) {
        count = 0;
        n = c;
        m = c;
        while (n >= 1 && n < 10000000000000000) {
           numberArray[count] = n % 10;
           n /= 10;
           count++;
       }
        if(count != 0) {
            if (count == 16) {
                for (i = count-2; i >= 0; i=i-2) {
                    sume += numberArray[i];
                }
            }
            else for (i = count - 1; i >= 0; i = i - 2) {
                sume += numberArray[i];
            }
            while (m >= 1 && m < 10000000000000000) {
                numberArray2[count2] = (( 2 * (m % 10)) / 10) + (( 2 * (m % 10)) % 10);
                m /= 10;
                count2++;
            }
            if (count == 16) {
                for (j = count - 1; j >= 0; j = j - 2) {
                    sumo += numberArray2[j];
                }
            }
            else for (j = count - 2; j >= 0; j = j - 2) {
                sumo += numberArray2[j];
            }

            checkc= (sume + sumo) % 10;
            if ( checkc != 0) {
                printf("INVALID\n");
                }
                else if ( numberArray[count-1] == 4) {
                    printf("VISA\n");
                }
                else if ( numberArray[count-1] == 3 && (numberArray[count-2] == 4 || numberArray[count-2] == 7)) {
                    printf("AMEX\n");
                }
                else if ( numberArray[count-1] == 5 && (numberArray[count-2] == 1 || numberArray[count-2] == 2)) {
                    printf("MASTERCARD\n");
                }
                else if ( numberArray[count-1] == 5 && (numberArray[count-2] == 3 || numberArray[count-2] == 4)) {
                    printf("MASTERCARD\n");
                }
                else if ( numberArray[count-1] == 5 && numberArray[count-2] == 5) {
                    printf("MASTERCARD\n");
                }
                return 0;
        }
    }
}