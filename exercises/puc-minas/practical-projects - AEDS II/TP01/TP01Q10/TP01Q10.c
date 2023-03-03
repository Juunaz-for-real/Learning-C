/*
 * Author: Raick Miranda Rodrigues Santos
 * Registration Number: 781755
 * Objective: TP01Q10 - Practical project from the AEDS II course
 *
 * \_(*-*)/¨
 */

// Imported Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The main part of the algorithm
int main()
{
    int num;
    scanf("%d", &num);

    FILE *archive;
    archive = fopen("aux.txt", "w+");

    // writes to the file 'aux.txt'
    for (int index = 0; index < num; index++)
    {
        float read;
        scanf("%f", &read);

        if (index != num - 1)
            fprintf(archive, "%g\n", read);
        else
            fprintf(archive, "%g", read);
    }
    // move the file pointer to the end of the file
    fseek(archive, 0, SEEK_END);

    // scans the file and prints in reverse
    for (int i = ftell(archive); i > 0; i--)
    {
        float n;

        if (i == 1)
        {
            fseek(archive, i - 1, SEEK_SET);
            fscanf(archive, "%f", &n);
            printf("%g\n", n);
        }
        else if (fgetc(archive) == '\n')
        {
            fseek(archive, i + 2, SEEK_SET);
            fscanf(archive, "%f", &n);
            printf("%g\n", n);
        }

        fseek(archive, i, SEEK_SET);
    }

    // closes the file
    fclose(archive);
}