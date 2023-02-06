/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// Validate the phone number and display formatted phone number.
void displayFormattedPhone(const char cString[]);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get valid integer from user, otherwise display an error message
int inputInt(void);

// Validates the value entered is greater than zero, otherwise display an error message
int inputIntPositive(void);

// Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range.
int inputIntRange(int lowerBound, int upperBound);

// Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char validateChar[]);

// Check a C string value is entered containing the number of characters within the range
void inputCString(char cString[], int min, int max);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
