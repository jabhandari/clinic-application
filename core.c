#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
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


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
//get an int as input from the user and retruns that int
int inputInt(void)
{
    int value;
    char newLineCharacter;
    int valid = 1;
    do {
        valid = 1;
        scanf("%d%c", &value, &newLineCharacter);
        if (newLineCharacter != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
            valid = 0;
        }
    } while (!valid);
    return value;
}

///get a positive int as input from the user and retruns that int and ensure that value entered 
//is a positive  int
int inputIntPositive(void)
{
    int positiveValue;
    int valid = 1;
    do {
        valid = 1;
        positiveValue = inputInt();
        if (positiveValue <= 0)
        {
            printf("ERROR! Value must be > 0: ");
            valid = 0;
        }
    } while (!valid);
    return positiveValue;
}

//check if the input int values are in range which are passed as arguments 
int inputIntRange(const int minValue, const int maxValue)
{
    int value;
    int valid = 1;
    do {
        valid = 1;
        value = inputInt();
        if (value<minValue || value>maxValue)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", minValue, maxValue);
            valid = 0;
        }
    } while (!valid);
    return value;
}

//get input for a character from the character range
char inputCharOption(const char* charOption)
{
    int i;
    int valid = 1;
    char inputChar;
    char newline;

    do {
        scanf("%c%c", &inputChar, &newline);

        if (newline == '\n')
        {
            for (i = 0; charOption[i] != '\0'; i++)
            {
                if (inputChar == charOption[i])
                {
                    valid = 0;
                }
            }
            if (valid == 1)
            {
                printf("ERROR: Character must be one of [%s]: ", charOption);
            }
        }
    } while (valid == 1);

    return inputChar;
}

//get user input for a C string value within length character range specified by arguments 
void inputCString(char* cString, const int minLength, const int maxLength)
{
    int flag = 1;
    char fmt[FMT_LEN + 1] = { 0 };
    char string[STR_LEN + 1] = { 0 };
    sprintf(fmt, "%%%d[^\n]", STR_LEN);

    do {
        scanf(fmt, string);
        clearInputBuffer();

        if (minLength == maxLength && strlen(string) != maxLength)
        {
            printf("Invalid %d-digit number! Number: ",maxLength);
            flag = 1;
        }
        else if (strlen(string) < minLength || strlen(string) > maxLength)
        {
            if (strlen(string) > maxLength)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxLength);
            }
            else if (strlen(string) < minLength)
            {
                printf("ERROR: String length must be between %d and %d chars: ",
                    minLength, maxLength);
            }
            flag = 1;
        }
        else
        {
            flag = 0;
            strcpy(cString, string);
        }
    } while (flag);
}

//display phone number after formatting the entered phone number if phone number is invalid display
//blank space with underscores
void displayFormattedPhone(const char phoneNumber[])
{
    int i;
    int valid = 1;
    if (phoneNumber == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        for (i = 0; phoneNumber[i] != '\0'; i++)
        {
            if (phoneNumber[i] < '0' || phoneNumber[i] > '9')
            {
                valid = 0;
            }
        }
        if (strlen(phoneNumber) != 10 || !(valid))
        {
            printf("(___)___-____");
        }
        else
        {
            printf("(%3.3s)%3.3s-%3.4s", phoneNumber, &phoneNumber[3], &phoneNumber[6]);
        }
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//check if the year is a leap year
int checkLeapYear(int year)
{
    int result = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        result = 1;
    }

    return result;
}

//get input from user to enter details of data
void inputYearMonthDay(int* year, int* month, int* day)
{
    int yearInput = 0;
    int monthInput = 0;
    int dayInput = 0;
    int leapYear = 0;

    printf("Year        : ");
    yearInput = inputIntPositive();
    leapYear = checkLeapYear(yearInput);
    *year = yearInput;

    printf("Month (1-%d): ",TOTAL_MONTHS);
    monthInput = inputIntRange(1, TOTAL_MONTHS);
    *month = monthInput;

    if (monthInput == 1 || monthInput == 3 || monthInput == 5 || monthInput == 7 ||
        monthInput == 8 || monthInput == 10 || monthInput == 12)
    {
        printf("Day (1-%d)  : ",MONTHS_DAYS_31);
        dayInput = inputIntRange(1, MONTHS_DAYS_31);

    }
    else if (monthInput == 4 || monthInput == 6 || monthInput == 9 || monthInput == 11)
    {
        printf("Day (1-%d)  : ",MONTHS_DAYS_30);
        dayInput = inputIntRange(1, MONTHS_DAYS_30);

    }
    else
    {
        if (leapYear == 1)
        {
            printf("Day (1-29)  : ");
            dayInput = inputIntRange(1,29);
        }
        else
        {
            printf("Day (1-28)  : ");
            dayInput = inputIntRange(1,28);
        }
    }
    *day = dayInput;
}