#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

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

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

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
            menuAppointment(data);
            break;
        }
    } while (selection);
}

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


// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}



// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int option;
    int valid = 1;
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        option = inputInt();
        switch (option)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            break;
        case 0:
            valid = 0;
            putchar('\n');
        }

    } while (valid);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i;
    int newPatientNo;
    int emptyFound = 0;
    int valid = 0;
    for (i = 0; i < max; i++)
    {
        if (emptyFound == 0)
        {
            if (patient[i].patientNumber == 0)
            {
                newPatientNo = nextPatientNumber(patient, max);
                patient[i].patientNumber = newPatientNo;
                inputPatient(&patient[i]);
                emptyFound = 1;
                printf("*** New patient record added ***");
                putchar('\n');
            }
            else
            {
                valid++;
            }
        }
    }
    if (valid == max)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    putchar('\n');
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int userInput;
    int patientIndex;
    printf("Enter the patient number: ");
    userInput = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(userInput, patient, max);
    if (patientIndex != -1)
    {
        putchar('\n');
        menuPatientEdit(&patient[patientIndex]);
    }
    else
    {
        printf("ERROR: Patient record not found!");
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int userInput;
    char characterInput;
    int patientIndex;
    struct Patient empty = { 0 };
    printf("Enter the patient number: ");
    userInput = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(userInput, patient, max);
    if (patientIndex != -1)
    {
        putchar('\n');
        displayPatientData(&patient[patientIndex], FMT_FORM);

        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        characterInput = inputCharOption("yn");
        if (characterInput == 'y')
        {
            patient[patientIndex] = empty;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
        putchar('\n');
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }

}


// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    int j;
    int record = 0;
    
    displayScheduleTableHeader(&data->appointments->date, ALLRECORD);
    sortAppoint(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)                   
    {
        if (data->appointments[i].patientNum != 0)
        {
            for (j = 0; j < data->maxPatient; j++)                
            {
                if (data->patients[j].patientNumber == data->appointments[i].patientNum)     
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], ALLRECORD);
                    record++;
                }
            }
        }
    }
    putchar('\n');
    if (record == 0)
    {
        printf("*** No records found ***");
    }
}
// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i = 0;
    int j = 0;
    int year = 0; int month = 0;int day = 0;
    int record = 0;
    
    sortAppoint(data->appointments, data->maxAppointments);
    inputYearMonthDay(&year, &month, &day);
   
    putchar('\n');
    printf("Clinic Appointments for the Date: %d-%02d-%02d\n\n", year, month, day);
    printf("Time  Pat.# Name            Phone#\n");
    printf("----- ----- --------------- --------------------\n");
    for (i = 0; i < data->maxAppointments; i++)                    
    {
        for (j = 0; j < data->maxPatient; j++)                
        {
            if (data->patients[j].patientNumber == data->appointments[i].patientNum)
            {
                if (year == data->appointments[i].date.year &&
                    month == data->appointments[i].date.month &&
                    day == data->appointments[i].date.day)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], SPECIFIC_DATE);
                    record++;
                }
            }
        }
    }
    
    if (record == 0)
    {
        printf("*** No records found ***");
    }
        putchar('\n');
}

// Add an appointment record to the appointment array

void addAppointment(struct Appointment* appoint, int maxAppointments,
    struct Patient* patient, int maxPatient)
{
    int i,j; int valid = 1; int isValid = 1;
    int patientNumInput;
    int appointmentScheduled = 0; 
    int appointmentFound = 0; 
    int year, month, day, hour, minute;
    int isValidAppointment = 0;

    printf("Patient Number: ");
    patientNumInput = inputIntPositive(); 

    int patientIndex = findPatientIndexByPatientNum(patientNumInput, patient, maxPatient);

    if (patientIndex != -1)
    {
        
        for (i = 0; i < maxAppointments && appointmentScheduled==0; i++)
        {
            if (appoint[i].patientNum == 0) 
            { 
                appointmentFound = 1;
                isValidAppointment = 0;
                
                    do {
                        inputYearMonthDay(&year, &month, &day);
                        do {
                            isValid = 1;
                            printf("Hour (0-23)  : ");
                            hour = inputIntRange(0, 23);
                            printf("Minute (0-59): ");
                            minute = inputIntRange(0, 59);

                            if (hour < OPENHOUR || hour > CLOSEHOUR || minute % INTERVAL != 0 ||
                                (hour == CLOSEHOUR && minute != 0))
                            {
                                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute "
                                    "intervals.\n\n", OPENHOUR, CLOSEHOUR, INTERVAL);
                                isValid = 0;
                            }
                       
                        } while (isValid == 0);
                        if ((isValidAppointment = 1))
                        {
                            

                            for (j = 0 && valid == 0; j < maxAppointments; j++)
                            {
                                if (appoint[j].patientNum != 0 &&
                                    appoint[j].date.year == year &&
                                    appoint[j].date.month == month &&
                                    appoint[j].date.day == day &&
                                    appoint[j].time.hour == hour &&
                                    appoint[j].time.min == minute) {
                                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                                    isValidAppointment = 0;
                                    valid = 0;
                                    
                                }
                            }
                        }

                    } while (!isValidAppointment);

              
                if (isValidAppointment) 
                {
                    appoint[i].patientNum = patientNumInput;
                    appoint[i].date.year = year;
                    appoint[i].date.month = month;
                    appoint[i].date.day = day;
                    appoint[i].time.hour = hour;
                    appoint[i].time.min = minute;

                    printf("\n*** Appointment scheduled! ***\n\n");
                    appointmentScheduled = 1;
                }
            }
        }

        if (!appointmentFound) 
        {
            printf("ERROR: No available appointment slots.\n\n");
        }
    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoint, int maxAppointments,
    struct Patient* patient, int maxPatient)
{
    char selection = 0;
    int i;
    int patientNumberInput = 0;
    int yearInput = 0;
    int monthInput = 0;
    int dayInput = 0;
    int appointmentCount = 0;
    int patIndex = 0;       
    int appIndex = 0;       
    struct Appointment empty = { 0 };

    printf("Patient Number: ");
    patientNumberInput = inputIntPositive();
    patIndex = findPatientIndexByPatientNum(patientNumberInput, patient, maxPatient);

    if (patIndex != -1)      
    {
        inputYearMonthDay(&yearInput, &monthInput, &dayInput);
        appIndex = findAppointIndexByDate(yearInput, monthInput, dayInput,
                                               appoint, maxAppointments);

        for (i = 0; i < maxAppointments; i++)
        {
            if (patient[patIndex].patientNumber == appoint[i].patientNum &&   
                appoint[appIndex].date.year == appoint[i].date.year &&
                appoint[appIndex].date.month == appoint[i].date.month &&
                appoint[appIndex].date.day == appoint[i].date.day)
            {
                putchar('\n');
                displayPatientData(&patient[patIndex], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = inputCharOption("yn");

                if (selection == 'y')
                {
                    appoint[i] = empty;
                    appointmentCount++;
                }
                else
                {
                    putchar('\n');
                    printf("Operation aborted.\n\n");
                }
            }
        }
        if (appointmentCount)
        {
            putchar('\n');
            printf("Appointment record has been removed!\n\n");
        }
        else
        {
            putchar('\n');
            printf("ERROR: Appointment record not found!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int userinput;
    int i;
    printf("\nSearch by patient number: ");
    userinput = inputIntPositive();
    putchar('\n');
    i = findPatientIndexByPatientNum(userinput, patient, max);

    if (i >= 0 && i < max)
    {
        displayPatientData(&patient[i], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char userInput[PHONE_LEN + 1] = { 0 };
    int i;
    int recordFound = 0;
    int valid = 1;

    printf("\nSearch by phone number: ");
    inputCString(userInput, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    do {
        for (i = 0; i < max; i++)
        {
            if (strcmp(userInput, patient[i].phone.number) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
                recordFound = 1;
                valid = 0;
            }
        }
        if (recordFound == 0)
        {
            putchar('\n');
            printf("*** No records found ***\n");
            valid = 0;
        }
    } while (valid);

    putchar('\n');
    suspend();
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int nextPatientNumber = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > nextPatientNumber)
        {
            nextPatientNumber = patient[i].patientNumber;
        }
    }
    return nextPatientNumber + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int  i;
    int recordExistIndex = 0;
    int recordFound = 0;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            recordExistIndex = i;
            recordFound++;
        }
    }
    if (recordFound == 0)
    {
        recordExistIndex = -1;
    }

    return recordExistIndex;
}

void sortAppoint(struct Appointment* appoint, int max)
{
    int i, j, minIndex;
    struct Appointment temp = { 0 };
    char timeString1[50], timeString2[50];

    for (i = 0; i < max - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < max; j++)
        {
            
            sprintf(timeString1, "%04d-%02d-%02d %02d:%02d",
                appoint[minIndex].date.year, appoint[minIndex].date.month, 
                appoint[minIndex].date.day, appoint[minIndex].time.hour,
                appoint[minIndex].time.min);
            sprintf(timeString2, "%04d-%02d-%02d %02d:%02d",
                appoint[j].date.year, appoint[j].date.month, appoint[j].date.day,
                appoint[j].time.hour, appoint[j].time.min);

           
            if (strcmp(timeString1, timeString2) > 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            temp = appoint[i];
            appoint[i] = appoint[minIndex];
            appoint[minIndex] = temp;
        }
    }
}

int findAppointIndexByDate(int year, int month, int day,
    const struct Appointment appoint[], int max)
{
    int i = 0;
    int existRecordIndex = 0;
    int matchNum = 0;

    for (i = 0; i < max; i++)
    {
        if (year == appoint[i].date.year)
        {
            if (month == appoint[i].date.month)
            {
                if (day == appoint[i].date.day)
                {
                    existRecordIndex = i;
                    matchNum = 1;
                }
            }
        }
    }

    if (matchNum == 0)
    {
        existRecordIndex = -1;
    }

    return existRecordIndex;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char name[NAME_LEN + 1] = { 0 };
    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d", patient->patientNumber);
    printf("\nName  : ");
    inputCString(name, 1, NAME_LEN);
    putchar('\n');
    strcpy(patient->name, name);
    inputPhoneData(&patient->phone);

}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{

    int phoneDescription;
    char phoneNumber[PHONE_LEN + 1] = { 0 };
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    phoneDescription = inputIntRange(1, PHONE_DESC_LEN);

    if (phoneDescription > 0 && phoneDescription < 4)
    {
        if (phoneDescription == 1)
        {
            strcpy(phone->description, "CELL");
        }
        else if (phoneDescription == 2)
        {
            strcpy(phone->description, "HOME");
        }
        else if (phoneDescription == 3)
        {
            strcpy(phone->description, "WORK");
        }
        printf("\nContact: %s", phone->description);
        printf("\nNumber : ");
        inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);
        strcpy(phone->number, phoneNumber);
        putchar('\n');
    }
    else
    {
        strcpy(phone->description, "TBD");
        putchar('\n');
        phone->number[0] = '\0';
    }
}



/////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int records = 0;

  
    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (records < max)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[records].patientNumber,
                patients[records].name, patients[records].phone.description, 
                patients[records].phone.number);
            records++;
        }
        
        fclose(fp);
        fp = NULL;
    }
  
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return records;
}


int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int records = 0;
    int field = 6;

    FILE* fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (records < max && field == 6)
        {
            field = fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[records].patientNum,
                &appoints[records].date.year,&appoints[records].date.month, 
                &appoints[records].date.day, &appoints[records].time.hour, 
                &appoints[records].time.min);
            if (field == 6)             
            {
                records++;
            }
        }
    
        fclose(fp);
        fp = NULL;
    }
  
    else
    {
        printf("ERROR: Unable to open %s file!\n\n", datafile);
    }

    return records;
}