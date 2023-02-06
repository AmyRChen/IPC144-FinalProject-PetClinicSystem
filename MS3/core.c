/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

// System library
#include <stdio.h>

// Striing library
#include <string.h>

// Character type library
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

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

// Validate the phone number and display formatted phone number
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

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

// Get valid integer from user, otherwise display an error message
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

// Validates the value entered is greater than zero, otherwise display an error message
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

// Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range
int inputIntRange(int lowerBound, int upperBound)
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

// Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char validateChar[])
{
    int i, invalid;
    char optionChar, checkChar;

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

// Check a C string value is entered containing the number of characters within the range
void inputCString(char cString[], int min, int max)
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


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Consider leap year and month, and calculate the number of days
int checkDayInMonth(int year, int month)
{
    int leapYear = 0;
    int days = 31;

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        leapYear = 1;
    }
    if (month == 2 && leapYear)
    {
        days = 29;
    }
    else if (month == 2 && !leapYear)
    {
        days = 28;
    }
    else if (month == 4 || month == 6 || 
             month == 9 || month == 11)
    {
        days = 30;
    }

    return days;
}