/**
 * @author Raick Miranda Rodrigues Santos
 * @file TP02Q01.java
 * @date 2023-03-12
 * @objective TP02Q02
 *
 *            Registration Number: 781755
 *            (⊙_⊙)？
 */

// Imported Libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definitions
#define MAX_FIELD_SIZE 30
#define MAX_STRING_ARRAY_SIZE 10
#define MAX_INPUT_SIZE 100
#define MAX_LENGTH 100

// Characters struct
typedef struct
{
    char name[MAX_FIELD_SIZE],
        date_of_birth[MAX_FIELD_SIZE],
        gender[MAX_FIELD_SIZE],
        homeworld[MAX_FIELD_SIZE],
        hair_color[MAX_STRING_ARRAY_SIZE][MAX_FIELD_SIZE],
        skin_color[MAX_STRING_ARRAY_SIZE][MAX_FIELD_SIZE],
        eyes_color[MAX_STRING_ARRAY_SIZE][MAX_FIELD_SIZE];

    int height, hair_color_count, skin_color_count, eyes_color_count;
    double mass;
} Character;

/**
 * @brief - It works like a constructor, the main purpose is to initialize
 * the members of the structure
 *
 * @param character - receives a structure of type Character
 */
void character_start(Character *character)
{
    strcpy(character->name, "");
    strcpy(character->date_of_birth, "");
    strcpy(character->gender, "");
    strcpy(character->homeworld, "");

    for (int index = 0; index < MAX_STRING_ARRAY_SIZE; index++)
    {
        strcpy(character->hair_color[index], "");
        strcpy(character->skin_color[index], "");
        strcpy(character->eyes_color[index], "");
    }

    character->height = -1;
    character->mass = -1;

    character->hair_color_count = 0;
    character->skin_color_count = 0;
    character->eyes_color_count = 0;
}

/**
 * @brief - Method for printing structure members
 *
 * @param character - receives a structure of type Character
 */
void print_character(Character *character)
{
    printf(" ## %s ## %d ## %.f ## ", character->name, character->height, character->mass);

    for (int index = 0; index < character->hair_color_count; index++)
        printf("%s%s", character->hair_color[index], index < character->hair_color_count - 1 ? ", " : "");

    printf(" ## ");

    for (int index = 0; index < character->skin_color_count; index++)
        printf("%s%s", character->skin_color[index], index < character->skin_color_count - 1 ? ", " : "");

    printf(" ## ");

    for (int index = 0; index < character->eyes_color_count; index++)
        printf("%s%s", character->eyes_color[index], index < character->eyes_color_count - 1 ? ", " : "");

    printf(" ## %s ## %s ## %s ## \n", character->date_of_birth, character->gender, character->homeworld);
}

/**
 * @brief - Clones a structure
 *
 * @param character - receives a structure of type Character
 * @return Character - returns a cloned structure
 */
Character character_clone(Character *character)
{
    Character cloned;

    strcpy(cloned.name, character->name);
    strcpy(cloned.date_of_birth, character->date_of_birth);
    strcpy(cloned.gender, character->gender);
    strcpy(cloned.homeworld, character->homeworld);

    for (int index = 0; index < character->hair_color_count; index++)
        strcpy(cloned.hair_color[index], character->hair_color[index]);

    for (int index = 0; index < character->skin_color_count; index++)
        strcpy(cloned.skin_color[index], character->skin_color[index]);

    for (int index = 0; index < character->eyes_color_count; index++)
        strcpy(cloned.eyes_color[index], character->eyes_color[index]);

    cloned.height = character->height;
    cloned.mass = character->mass;

    return cloned;
}

/**
 * @brief - Takes a character and says whether it is a number or not, according to the ASCII table
 *
 * @param in - receives any char
 * @return true - if it is a number
 * @return false - if it is not a number
 */
bool isNumber(char in)
{
    return in >= 48 && in <= 57;
}

/**
 * @brief - Reads a file, maps its contents, and assigns the respective values to the struct members
 *
 * @param character - receives a structure so that the items read are assigned to it
 * @param file - receives a file name
 */
void read_character(Character *character, char *file)
{
    int index = 0, auxQuoteMark = 0;

    // opens the file and applies error handling
    FILE *f;
    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("File could not be opened.");
        return;
    }

    // finding out the size of the file content
    fseek(f, 0, SEEK_END);
    long file_length = ftell(f);
    rewind(f);

    // copying the contents of the file to a variable with dynamic allocation
    char *aux = (char *)malloc(sizeof(char) * file_length);
    fread(aux, 1, file_length, f);
    fclose(f);

    // declaring an auxiliary variable and clearing its contents
    char *tempString = malloc(sizeof(char) * MAX_FIELD_SIZE);
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
    character_start(character); // reset all fields before reading

    // find - character name -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->name, tempString);
            index += 2;
            break;
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character heigth -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            // if the height is unknown, set 0
            if (aux[index] == 'u')
            {
                character->height = 0;

                while (aux[index] != '\'')
                    index++;

                index += 2;
                break;
            }
            else
            {
                int i = 0;
                while (aux[index] != '\'' && isNumber(aux[index]))
                {
                    tempString[i] = aux[index];
                    i++;
                    index++;
                }
                character->height = atoi(tempString);
                index += 2;
                break;
            }
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character mass -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            // if the mass is unknown, set 0
            if (aux[index] == 'u')
            {
                character->mass = 0;

                while (aux[index] != '\'')
                    index++;

                index += 2;
                break;
            }
            else
            {
                int i = 0;
                while (aux[index] != '\'' && (isNumber(aux[index]) || aux[index] == '.'))
                {
                    // if it's a comma, replace it with a blank space
                    if (aux[index] == ',')
                    {
                        tempString[i] = ' ';
                        index++;
                    }
                    tempString[i] = aux[index];
                    i++;
                    index++;
                }
                character->mass = atof(tempString);
                index += 2;
                break;
            }
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character hair color -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 4)
        {
            index += 2;
            break;
        }

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                if (aux[index] == ',')
                {
                    index++;
                    break;
                }
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->hair_color[character->hair_color_count++], tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index--; // decrementing by 1 to ensure that it doesn't loop infinitely
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character skin color -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 4)
        {
            index += 2;
            break;
        }

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                if (aux[index] == ',')
                {
                    index++;
                    break;
                }
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->skin_color[character->skin_color_count++], tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index--; // decrementing by 1 to ensure that it doesn't loop infinitely
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character eyes color -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 4)
        {
            index += 2;
            break;
        }

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                if (aux[index] == ',')
                {
                    index++;
                    break;
                }
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->eyes_color[character->eyes_color_count++], tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index--; // decrementing by 1 to ensure that it doesn't loop infinitely
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character date of birth -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->date_of_birth, tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index += 2;
            break;
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character gender -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->gender, tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index += 2;
            break;
        }
    }
    auxQuoteMark = 0;
    memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);

    // find - character homeworld -
    while (1)
    {
        index++;

        if (aux[index] == '\'')
            auxQuoteMark++;

        if (auxQuoteMark == 3)
        {
            index++;

            while (aux[index] != '\'')
            {
                tempString[strlen(tempString)] = aux[index];
                index++;
            }
            strcpy(character->homeworld, tempString);
            memset(tempString, 0, sizeof(char) * MAX_FIELD_SIZE);
            index += 2;
            break;
        }
    }
    auxQuoteMark = 0;
    tempString[0] = '\0';
}

/**
 * @brief Main part of the algorithm, reads the names of the files to be used and invokes the
 * functions to be used
 *
 * @return int - end of the program
 */
int main()
{
    setlocale(LC_ALL, "");
    char filename[MAX_LENGTH];
    int count = 0;
    char **files = NULL;

    // if the input reads the word 'FIM', stop reading and skip the algorithm to the next part
    while (1)
    {
        fgets(filename, MAX_LENGTH, stdin);
        filename[strcspn(filename, "\n")] = 0; // removes the '\n' from the end of the string

        if (strcmp(filename, "FIM") == 0)
            break;

        // allocates space to store the file name
        if (files == NULL)
            files = malloc(sizeof(char *));
        else
            files = realloc(files, (count + 1) * sizeof(char *));

        // copy the file name to the allocated space
        files[count] = malloc(strlen(filename) + 1);
        strcpy(files[count], filename);
        count++;
    }

    // calling methods for each 'input' file
    Character character;
    for (int i = 0; i < count; i++)
    {
        FILE *fp = fopen(files[i], "r");
        if (fp == NULL)
            printf("Não foi possível abrir o arquivo %s\n", files[i]);
        else
        {
            read_character(&character, files[i]);
            print_character(&character);
            fclose(fp);
        }
        free(files[i]);
    }
    free(files);

    return 0;
}