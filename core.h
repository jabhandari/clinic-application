#ifndef CORE_H
#define CORE_H

#define FMT_LEN 20
#define STR_LEN 5000

#define TOTAL_MONTHS 12
#define LEAP_YEAR_MONTH_DAYS 29
#define NON_LEAP_YEAR_MONTH_DAYS 29
#define MONTHS_DAYS_31 31
#define MONTHS_DAYS_30 30
///////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//get an int as input from the user and retruns that int
int inputInt(void);

///get a positive int as input from the user and retruns that int and ensure that value entered 
//is a positive  int
int inputIntPositive(void);

//check if the input int values are in range which are passed as arguments 
int inputIntRange(const int minValue, const int maxValue);

//get input for a character from the character range
char inputCharOption(const char* charOption);

//get user input for a C string value within length character range specified by arguments  
void inputCString(char* cString, const int minCharacters, const int maxCharacters);

//display phone number after formatting the entered phone number if phone number is invalid display
//blank space with underscores
void displayFormattedPhone(const char phoneNumber[]);

//check if the year is a leap year
int checkLeapYear(int year);

//get input from user to enter details of data
void inputYearMonthDay(int* year, int* month, int* day);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
