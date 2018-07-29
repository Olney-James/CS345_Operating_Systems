/***********************************************************
Program:

Detail:

Author: James Olney
Created: 02/02/2018
Revisions: N/A
*******************/
#include "iostream"
#include "string"
#include "algorithm"
using namespace std;

string whiteList[] = { "a","abbr","acronym","b","blockquote","cite","code","del"\
,"em","i","q","strike","strong" };

bool whiteListContains(string temp) {
	for (int i = 0; i < 13; ++i) {
		if (temp == whiteList[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	string input = "</b>";
	while (input != "exit") {
		cout << "> ";
		getline(cin, input);
		string temp = "";
		string slash = "";
		for (int i = 0; i< input.length(); ++i) {
			if (input[i] == '<') {
				for (int j = i + 1; j< input.length(); ++j) {
					if (input[j] == '>') {
						if (whiteListContains(temp)) {
							if (slash == "/") {
								input = input.substr(0, j) + ">" + input.substr(j + 1);
							}
							else {
								input = input.substr(0, j) + "></" + temp + ">" + input\
									.substr(j + 1);
							}
							temp = "";
							cout << input << endl;
							break;
						}
						else {
							input = input.substr(0, i) + "&lt;" + temp + "&gt;" + inpu\
								t.substr(j + 1);
							temp = "";
							break;
						}
					}
					if (input[j] != '/') {
						temp = temp + input[j];
						slash = "";
					}
					else {
						slash = slash + "/";
					}
				}
			}
		}
		cout << "\t" << input << endl;
	}
}

