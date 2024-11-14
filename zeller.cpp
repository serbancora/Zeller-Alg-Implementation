#include <iostream>
#include <string>
#include <array>
#include <limits>

using namespace std;

string dayOfTheWeek(int day, int month, int year); // Function that returns the day of the week
bool isValidDate(int day, int month, int year);    // Function that checks if the entered date is valid
bool isLeapYear(int year);                         // Function that checks if a year is a leap year

int main(void)
{
    int day, month, year;
    cout << "Enter the date (day month year): ";
    while (true)
    {
        if (cin >> day >> month >> year) // Check if the entered values are numbers
        {
            // Check if the entered date is valid
            if (isValidDate(day, month, year))
            {
                // Display the day of the week
                cout << "The day of the week is: " << dayOfTheWeek(day, month, year) << endl;
                break;
            }
            else
            {
                // If the date is invalid, show an error message and ask for a new date
                cout << "The entered date is invalid. Please enter a valid date: ";
            }
        }
        else // If the entered values are not numbers, show an error message and ask for a new date
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "The entered date is invalid. Please enter a valid date: ";
        }
    }
    return 0;
}

bool isValidDate(int day, int month, int year)
{
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
    {
        return false;
    }
    // Array with the number of days in each month
    array<int, 12> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year))
    {
        daysInMonth[1] = 29; // If the year is a leap year, February has 29 days
    }

    if (day > daysInMonth[month - 1]) // Check if the entered day is valid for the respective month
    {
        return false;
    }
    return true;
}

bool isLeapYear(int year)
{
    // A year is a leap year if it is divisible by 4 and not divisible by 100, or it is divisible by 400
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

string dayOfTheWeek(int day, int month, int year)
{
    // Zeller's algorithm for calculating the day of the week
    if (month == 1) // January and February are considered months of the previous year
    {
        month = 13;
        year--;
    }
    else if (month == 2)
    {
        month = 14;
        year--;
    }

    int k = year % 100;
    int j = year / 100;
    int f = (day + (13 * (month + 1) / 5) + k + (k / 4) + (j / 4) + 5 * j) % 7; // Zeller's formula

    const array<string, 7> daysOfTheWeek = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}; // Array with the days of the week
    return daysOfTheWeek[f];
}
