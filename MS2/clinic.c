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

#define _CRT_SECURE_NO_WARNINGS

//System library
#include <stdio.h>

//String library
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"

// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, invalid = 0;

    // If fmt is table format -> show the header
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            invalid++;
        }
        else
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    if (invalid == i)
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int opt;

    do {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");
        opt = inputIntRange(0, 2);
        putchar('\n');

        if (opt == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (opt == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
    } while (opt);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, valid = 1, index = 0;
    // Exit the loop once valid space found
    //for (i = 0; i < max && !valid; i++)
    //{
    //    if (patient[i].patientNumber == 0)
    //    {
    //        valid = 1;
    //        index = i;
    //    }
    //}
    index = findPatientIndexByPatientNum(0, patient, max);
    //if (index == -1)
    //{
    //    valid = 0;
    //}
    
    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientID, index;

    printf("Enter the patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[index]);
    }

}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientID, index;
    char option;
    struct Patient empty = { 0 };

    printf("Enter the patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n"
               "Are you sure you want to remove this patient record? (y/n): ");
        option = inputCharOption("yn");
        if (option == 'n')
        {
            printf("Operation aborted.\n\n");
        }
        else
        {
            patient[index] = empty;
            printf("Patient record has been removed!\n\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientID, index;

    printf("Search by patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');
    suspend();
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, valid = 0;
    char phone[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCString(phone, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (!strcmp(phone, patient[i].phone.number))
        {
            displayPatientData(&patient[i], FMT_TABLE);
            valid++;
        }
        //else
        //{
        //    invalid++;
        //}
    }
    //if (invalid == i)
    if(!valid)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int nextPatientNum = patient[0].patientNumber;
    
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > nextPatientNum)
        {
            nextPatientNum = patient[i].patientNumber;
        }
    }
    nextPatientNum += 1;

    return nextPatientNum;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i, index = 0, valid = 0;

    //exit the loop once valid
    for (i = 0; i < max && !valid; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            index = i;
            valid = 1;
        }
    }
    if (valid == 0)
    {
        index = -1;
    }

    return index;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int option = 0;

    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    option = inputIntRange(1, 4);
    putchar('\n');

    switch (option)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }

    if (option != 4)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
    }
}