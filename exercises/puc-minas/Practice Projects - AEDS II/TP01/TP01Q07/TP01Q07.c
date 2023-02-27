/*
 * Author: Raick Miranda Rodrigues Santos
 * Registration Number: 781755
 * Objective: TP01Q07 - Practical project from the AEDS II course
 *
 * \_(*-*)/¨
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Takes an array of chars and says whether it is formed only by vowels
int isVowel(char in[1000])
{
    int answer = 0;

    // as long as the array of chars length is not reached, test each character
    for (int index = 0; index < strlen(in); index++)
    {
        // if the character is a vowel, return 1
        if (in[index] == 'a' || in[index] == 'A' || in[index] == 'e' ||
            in[index] == 'E' || in[index] == 'i' || in[index] == 'I' ||
            in[index] == 'o' || in[index] == 'O' || in[index] == 'u' ||
            in[index] == 'U')
        {
            answer = 1;
        }
        else
        {
            index = strlen(in);
            answer = 0;
        }
    }

    return answer;
}

// Takes an array of chars and says whether it is formed only by consonants
int isConsonant(char in[1000])
{
    int answer = 0;

    // as long as the array of chars length is not reached, test each character
    for (int index = 0; index < strlen(in); index++)
    {
        // if the character is not in the range of the Latin alphabet, skip to return
        if ((int)in[index] > 64 && (int)in[index] < 91 || (int)in[index] > 96 && (int)in[index] < 123)
        {
            // if the character is a vowel, return 0
            if (in[index] == 'a' || in[index] == 'A' || in[index] == 'e' ||
                in[index] == 'E' || in[index] == 'i' || in[index] == 'I' ||
                in[index] == 'o' || in[index] == 'O' || in[index] == 'u' ||
                in[index] == 'U')
            {
                index = strlen(in);
                answer = 0;
            }
            else
            {
                answer = 1;
            }
        }
    }

    return answer;
}

// Takes an array of chars and says whether it is formed only by an integer number
int isInteger(char in[1000])
{
    int answer = 0;

    // as long as the array of chars length is not reached, test each character
    for (int index = 0; index < strlen(in); index++)
    {
        // if the character is a number, return 1
        if ((int)in[index] > 47 && (int)in[index] < 58)
        {
            answer = 1;
        }
        else
        {
            index = strlen(in);
            answer = 0;
        }
    }

    return answer;
}

// Takes an array of chars and says whether it is formed only by a real number
int isReal(char in[1000])
{
    int answer = 0;

    // as long as the array of chars length is not reached, test each character
    for (int index = 0; index < strlen(in); index++)
    {
        // if the character isn't in range of numbers or isn't a period or a comma, then return 0
        if ((int)in[index] > 47 && (int)in[index] < 58 || in[index] == 46)
        {
            answer = 1;
        }
        else
        {
            answer = 0;
            index = strlen(in);
        }
    }

    return answer;
}

// The main part of the algorithm
int main()
{
    char input[1000][1000];
    int inCounter = 0;

    // read entries while 'FIM' has not yet been read
    do
    {
        scanf(" %[^\n]", input[inCounter]);
    } while (strcmp(input[inCounter++], "FIM") != 0);
    inCounter--; // disregard the line 'FIM'

    // calls each test method for each line stored in the array 'input'
    for (int index = 0; index < inCounter; index++)
    {
        if (isVowel(input[index]))
            printf("SIM ");
        else
            printf("NAO ");

        if (isConsonant(input[index]))
            printf("SIM ");
        else
            printf("NAO ");

        if (isInteger(input[index]))
            printf("SIM ");
        else
            printf("NAO ");

        if (isReal(input[index]))
            printf("SIM\n");
        else
            printf("NAO\n");
    }

}