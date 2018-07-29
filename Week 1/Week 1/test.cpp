/***********************************************************************
* Program:
*    Lab 01, Submission Lab
*    Brother Ball, CS345
* Author:
*    James Olney
* Summary:
*     A program to prompt the user for an integer. If the provided number is
* not zero, then him/her is prompted for another integer. This continues
* until the user is worn down and he/she enters '0'. At this point, the
* program will display how many integers were entered.
************************************************************************/

#include <iostream>
using namespace std;

int promptTheUserForAnInteger();
int getHowManyIntegersWereEnteredBeforeZero(int, int);
void displayHowManyIntegersWereEntered(int);

/**********************************************************************
* Prompts user for an integer n times until user enters 0.
* At this point, the program will display how many integers were entered.
***********************************************************************/
int main()
{
	int num = 1;
	int count = 0;

	count = getHowManyIntegersWereEnteredBeforeZero(num, count);
	displayHowManyIntegersWereEntered(count);

	return 0;
}

/**********************************************************************
* Prompts user for an integer n times until user enters 0.
* Returns number of times user entered integer before 0
***********************************************************************/
int getHowManyIntegersWereEnteredBeforeZero(int number, int count)
{
	while (number != 0)
	{
		number = promptTheUserForAnInteger();
		if (number == 0)
			break;
		count++;
	}
	return count;
}

/**********************************************************************
* Displays how many integers were entered.
***********************************************************************/
void displayHowManyIntegersWereEntered(int count)
{
	if (count == 1)
		cout << "You entered 1 integer." << endl;
	else if (count == 0)
		cout << "No non-zero integers were entered." << endl;
	else
		cout << "You entered " << count << " integers." << endl;
	
}

/**********************************************************************
* Prompts user for an integer and returns that number
***********************************************************************/
int promptTheUserForAnInteger()
{
	int number = 0;
	cout << "Enter an integer: ";
	cin >> number;
	return number;
}
