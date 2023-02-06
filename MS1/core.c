/*
*****************************************************************************
                        Assignment 1 - Milestone 1
Full Name  : Ping-Ju, Chen
Student ID#: 151043205
Email      : pchen72@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "core.h"

// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//1. Get valid integer from user, otherwise display an error message
int inputInt(void)
{
    int intVal, invalid;
    char newLine = 'x';

    do {
        invalid = 0;
        scanf("%d%c", &intVal, &newLine);
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
            invalid = 1;
        }
    } while (invalid);

    return intVal;
}

//2. Validates the value entered is greater than zero, otherwise display an error message
int inputIntPositive(void)
{
    int intPositive, invalid;

    do {
        invalid = 0;
        intPositive = inputInt();
        if (intPositive < 1)
        {
            printf("ERROR! Value must be > 0: ");
            invalid = 1;
        }
    } while (invalid);

    return intPositive;
}

//3. Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range.
int inputIntRange(int lowerBound,
    int upperBound)
{
    int rangeVal, invalid;

    do {
        invalid = 0;
        rangeVal = inputInt();
        if (rangeVal < lowerBound || rangeVal > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ",
                lowerBound, upperBound);
            invalid = 1;
        }
    } while (invalid);

    return rangeVal;
}

//4. Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char validateChar[])
{
    int i, invalid;
    char optionChar;
    char checkChar;

    do {
        invalid = 1;
        scanf("%c%c", &optionChar, &checkChar);

        if (checkChar == '\n')
        {
            for (i = 0; validateChar[i] != '\0' && invalid == 1; i++)
            {
                if (optionChar == validateChar[i])
                {
                    invalid = 0;
                }
            }
            if (invalid)
            {
                printf("ERROR: Character must be one of [%s]: ", validateChar);
            }
        }
        else
        {
            printf("ERROR: Character must be one of [%s]: ", validateChar);
            clearInputBuffer();
        }
    } while (invalid);

    return optionChar;
}

//5. Check a C string value is entered containing the number of characters within the range
void inputCString(char cString[],
    int min,
    int max)
{
    int len, invalid;
    char input[1000 + 1] = { 0 };

    do
    {
        invalid = 0;
        scanf("%1000[^\n]", input);
        clearInputBuffer();
        len = strlen(input);

        if (min == max)
        {
            if (len != max)
            {
                printf("ERROR: String length must be exactly %d chars: ",
                    max);
                invalid = 1;
            }
        }
        else  //max > min
        {
            if (len > max)
            {
                printf("ERROR: String length must be no more than %d chars: ",
                    max);
                invalid = 1;
            }
            else if (len < min)
            {
                printf("ERROR: String length must be between %d and %d chars: ",
                    min, max);
                invalid = 1;
            }
        }
    } while (invalid);

    strcpy(cString, input);
}

//6. Validate the phone number and display formatted phone number.
void displayFormattedPhone(const char cString[])
{
    int i, nonNum = 0;

    for (i = 0; cString != NULL && cString[i] != '\0'; i++)
    {
        if (!isdigit(cString[i]))
        {
            nonNum++;
        }
    }
    if (i != 10 || nonNum > 0)
    {
        printf("(___)___-____");
    }
    else
    {
        i = 0;
        printf("(");
        while (i < 3)
        {
            putchar(cString[i]);
            i++;
        }
        printf(")");
        while (i < 6)
        {
            putchar(cString[i]);
            i++;
        }
        printf("-");
        printf("%s", &cString[6]);
    }
}
