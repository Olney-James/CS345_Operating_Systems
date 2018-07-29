/***********************************************************************
* Program:
*    Lab 09, MMU Lab
*    Brother Ball, CS345
* Author:
*    James Olney
* Summary:
*    An MMU that will read a file containing the page table
* 	 convert a logical address to a vertical address, and
*	 implement a driver to test the MMU
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

int logicalPageNumber[7];
int validBit[7];
int physicalPageNumber[7];
int pageSize;

string retrieveFileNameFromUser();
void presentConvertedAddress(int input);
void promptTheUserForALogicalAddressAndPresentConvertedAddress();

/**********************************************************************
* Add text here to describe what the function "main" does. Also don't forget
* to fill this out with meaningful text or YOU WILL LOSE POINTS.
***********************************************************************/
int main()
{
	
	string filename = retrieveFileNameFromUser();
	ifstream inFile(filename);
	string line;
	getline(inFile, line);
	pageSize = stoi(line);
	string word;
	int count = 0;
	int index = 0;
	while (inFile >> word) {
		if (count == 0) {
			logicalPageNumber[index] = stoi(word);
		}
		if (count == 1) {
			validBit[index] = stoi(word);
		}
		if(count == 2){
			physicalPageNumber[index] = stoi(word);
		}
		count++;
		if (count > 2) {
			count = 0;
			index++;
		}
	}

	cout << "Enter logical address and the corresponding physical one will be displayed."
		<< "Enter 0 for an address when done." << endl;
	promptTheUserForALogicalAddressAndPresentConvertedAddress();
	return 0;
}

string retrieveFileNameFromUser() {
	string filename;
	cout << "What is the filename of the page table? ";
	cin >> filename;
	return filename;
}

void promptTheUserForALogicalAddressAndPresentConvertedAddress() {
	int input = 1;
	while (input != 0) {
		cout << "> ";
		cin >> input;
		presentConvertedAddress(input);
	}
}

void presentConvertedAddress(int input) {
	int pageOffset;
	int pageFault = 0;
	for (int x = 0; x < sizeof(logicalPageNumber)/sizeof(*logicalPageNumber); x++) {
		if (input == 0) {
			return;
		}
		pageOffset = input % pageSize;
		if (input / pageSize == logicalPageNumber[x]) {
			if (validBit[x] != 0) {
				cout << "\t" << (physicalPageNumber[x] * pageSize) + pageOffset << endl;
				pageFault = 1;
			}
			break;
		}
		
	}
	if (pageFault == 0) {
		cout << "\t" << "Page Fault" << endl;
	}
}

