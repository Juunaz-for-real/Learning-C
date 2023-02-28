/*
 * Author: Raick Miranda Rodrigues Santos
 * Registration Number: 781755
 * Objective: TP01Q02 - Practical project from the AEDS II course
 *
 * \_(*-*)/¨
 */

// Imported Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Receives an array of chars and tells whether it is a palindrome or not
int isPalindrome(char in[1000])
{
    int answer = 1;
    int length = strlen(in);

    // compares the first character with the last until the counter reaches the midpoint
    for (int index = 0; index < length / 2; index++)
    {
        // if it's different, then it is not a palindrome
        if (in[index] != in[length - 1 - index])
        {
            answer = 0;
            index = length;
        }
    }

    return answer;
}

// The main part of the algorithm
int main()
{
    char input[1000], text[1000][1000];
    int inCounter = 0;

    // read entries while 'FIM' has not yet been read
    do
    {
        scanf(" %[^\n]", input);
        strcpy(text[inCounter], input);
        inCounter++;
    } while (strcmp(input, "FIM") != 0);
    inCounter--; // disregard the line 'FIM'

    // calls isPalindrome for each line stored in the array 'input'
    for (int index = 0; index < inCounter; index++)
    {
        if (isPalindrome(text[index]))
            printf("SIM\n");
        else
            printf("NAO\n");
    }

}