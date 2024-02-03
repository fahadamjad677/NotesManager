#include<iostream>
#include <cstdlib>
#include<fstream>
#include"Functions.h"
using namespace std;

int main() {
	char option;
	bool elsepart = false;
	do {
		if (!elsepart) {
			cout << "\n---------------------------------------------WELCOME TO NOTES MANAGER---------------------------------\n";
			cout << "\n1:SIGNUP";
			cout << "\n2:LOGIN";
			cout << "\n3:Exit";
			cout << "\n Enter option: ";
		}
		cin >> option;
		cin.ignore();
		if (option == '1') {
			elsepart = false;
			char name[2][20] = {};
			char EP[2][30] = {}, cpass[100] = {};
			if (signup(name, EP, cpass)) {
				fileMangager(EP);
			}
			else {
				cout << "\nsorry there was some error\n";
			}
		}
		else if (option == '2') {
			elsepart = false;
			char EP[2][30];
			if (login(EP)) {
				fileMangager(EP);
			}
		}
		else if (option == '3') {
			break;
		}
		else {
			elsepart = true;
			continue;
		}
	} while (1);


	return 0;
}