#include <cs50.h>
#include <stdint.h> // standard int cant store 16 characters, this provides int64_t
#include <stdio.h>
#include <stdlib.h> // gives exit(), instead of using break in a while loop as this seems
                    // only useful as a one-time run code
#include <string.h> // used for strlen

void printdigits(int digits[], int dsize) // debugging print command
{
    for (int i = 0; i < dsize; i++)
    {
        printf("%d,", digits[i]);
    }
    printf("\n\n");
}


int main(void)
{
    int digits[32]; // 16 is the largest valid CC number length, but two digit numbers can go over this
    int64_t ccnum;  // int_64 to ensure it can take long numbers
    char ccstr[21];
    int check; // Used as a variable to store all sums
    int64_t cc1;  // used to write the array
    int64_t cc2; // used to reference the first 2 digits

    printf("Please enter the credit card number: ");
    scanf("%ld", &ccnum);            // Take input as the int64 from earlier
    sprintf(ccstr, "%ld", ccnum);    // Convert to a string to check length below
    size_t cclength = strlen(ccstr); // read length of string to cclength to check length below
                                     // also used later on for array length
    // I could have just taken a string from the user and skipped this
    // why do I think it'll be easier to keep it an int forever?

    if (cclength == 14)
    {
        printf("INVALID\n");
        exit(0);
    }

    else if (cclength > 16) // checks length is less than 16
    {
        printf("INVALID\n");
        exit(0);
    }
    else if (cclength < 13) // checks length is more than 13
    {
        printf("INVALID\n");
        exit(0);
    }

    // Array writing
    cc1 = ccnum;

    for (int count = 0; cc1 > 0; count++)  // turning the CC into a BACKWARDS array
    {
        digits[count] = cc1 % 10;   // Pulls the last digit into the digits array
        cc1 /= 10;                  // Remove last digit
    }

    int size = sizeof(digits) / sizeof(digits[0]); // part of debugging but used for the next part
    // printdigits(digits, size); // debugging array print

    // Array *2 part
    for (int i = 1; i < cclength; i += 2)
    {
        digits[i] *= 2;  // Pulls every other digit (starting from pos1, but pos1 is the 2nd-last cc number)
    }                    // then times each one by 2                // TO DO: MAKE IT BREAK 2 DIGIT NUMBERS INTO 2. I.E 12 = 1,2

    // size = sizeof(digits) / sizeof(digits[0]);    // debugging array print
    // printdigits(digits, size);

    // Break the array back into single digits, incase *2 make 2 digit numbers
    for (int i = 0; i < size; i++)
    {
        if (digits[i] >= 10)
        {
            for (int j = size; j > i; j--)  // shifts data forward so it doesn't overwrite the next number
            {
                digits[j] = digits[j - 1];
            }
            size++;

            digits[i+1] = digits[i] % 10; // makes the next position hold the single unit
            digits[i] = digits[i] / 10;   // makes the current position hold the tens unit
        }
    }

    // size = sizeof(digits) / sizeof(digits[0]);
    // printdigits(digits, size);  // debugging array print

    // Add all digits together
    check = 0;
    for (int i = 0; i < size; i += 1)
    {
        check += digits[i]; // Adds all digits to "check"
    }

    // printf("Check: %i\n", check);  // debug print check

    if (check % 10 != 0)
    {
        printf("INVALID\n");
        exit(0);
    }

    // Get the first two digits of ccnum

    cc2 = ccnum;
    while (cc2 >= 100)
    {
        cc2 /= 10;
    }

    // printf("cc2: %li     ccnum: %ld", cc2, ccnum); // debug print

    //Visa check. Starts with a 4, 13 or 16 digits
    if (cc2 >=40 && cc2 <= 49)
    {
        if (cclength == 13 || cclength == 16)
        {
            printf("VISA\n");
            exit(0);
        }
        else
        {
            printf("INVALID\n");
            exit(0);
        }
    }

    //AE check. Starts with 34 or 37, 15 digits
    if (cc2 == 34 || cc2 ==37)
    {
        if (cclength == 15)
        {
            printf("AMEX\n");
            exit(0);
        }
        else
        {
            printf("INVALID\n");
            exit(0);
        }
    }

    //MC check. Starts with 51-55, 16 digit.
    if (cc2 >=51 && cc2 <= 55)
    {
        if (cclength == 16)
        {
            printf("MASTERCARD\n");
            exit(0);
        }
        else
        {
            printf("INVALID\n");
            exit(0);
        }
    }

    printf("INVALID\n"); // Final catch, if it somehow
                         // doesn't get caught earlier and exit
    exit(0);
}

