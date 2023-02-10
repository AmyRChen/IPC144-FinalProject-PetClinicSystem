// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//1. Get valid integer from user, otherwise display an error message
int inputInt(void);

//2. Validates the value entered is greater than zero, otherwise display an error message
int inputIntPositive(void);

//3. Validates an integer value is entered within the range (inclusive) 
// and returned the value. Display error message if out of range.
int inputIntRange(int lowerBound,
                  int upperBound);

//4. Guarantee a single character value is entered within the list of valid characters
char inputCharOption(const char validateChar[]);

//5. Check a C string value is entered containing the number of characters within the range
void inputCString(char cString[],
                  int min, 
                  int max);

//6. Validate the phone number and display formatted phone number.
void displayFormattedPhone(const char cString[]);

