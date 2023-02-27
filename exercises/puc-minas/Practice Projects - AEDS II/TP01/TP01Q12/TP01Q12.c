/*
 * Author: Raick Miranda Rodrigues Santos
 * Registration Number: 781755
 * Objective: TP01Q12 - Practical project from the AEDS II course
 *
 * \_(*-*)/¨
 */

// Imported Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Receives an array of chars and tells whether it is a palindrome or not, recursively
int isPalindrome(char in[1000], int left, int right)
{
    int answer = 1; // true

    // checks the internal conditionals as long as the left index is smaller than
    // the right one
    if (left <= right)
    {
        // if the comparison between the characters results in a difference, then it is
        // not a palindrome
        if (in[left] != in[right])
            answer = 0;
        else
            answer = isPalindrome(in, (left + 1), (right - 1));
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
        if (isPalindrome(text[index], 0, strlen(text[index]) - 1))
            printf("SIM\n");
        else
            printf("NAO\n");
    }
    
}