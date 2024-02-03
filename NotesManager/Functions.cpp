#include<iostream>
#include<fstream>
#include<direct.h>
using namespace std;
//General
int  getsize(char arr[]) {
	int size = 0;
	for (int i = 0;arr[i] != '\0';i++) {
		size++;
	}
	return size;
}
int filesize(char filename[]) {
	int size = 0;
	char ch;
	fstream file;
	file.open(filename, ios::in);
	if (file.is_open()) {
		while (!file.eof()) {
			ch = file.get();
			size++;
		}
		return size;
	}
	return size;

}
bool cmpstring(char arr1[], char arr2[]) {
	if (getsize(arr1) == getsize(arr2)) {
		for (int i = 0;i < getsize(arr1);i++) {
			if (arr1[i] != arr2[i]) {
				return false;
			}
		}
	}
	else {
		return false;

	}
	return true;
}
//singup
int reademailfromfile(char word[], int col) {
	ifstream input;
	int words = 1;
	int line = 1;
	input.open("user.txt");
	if (input.is_open()) {
		while (!input.eof()) {
			if (words == 6) {
				words = 1;
				line++;
			}
			char data[40];
			input >> data;
			if (words == col) {
				if (cmpstring(data, word)) {
					return line;
				}
			}
			words++;
		}
		input.close();
	}
	return 0;
}
bool writetofile(char name[][20], char EP[][30], char cpass[]) {
	fstream fout;
	fout.open("user.txt", ios::app);
	if (fout.is_open()) {
		fout << name[0] << ' ' << name[1] << ' ' << EP[0] << ' ' << EP[1] << ' ' << cpass << endl;
		// writing to userfiles the username after signup
		fstream username;
		username.open("userfiles.txt", ios::app);
		username << EP[0] << endl;
		username.close();
		//Now creating folder name with respective username
		char path[70] = "";
		const int foldersize = getsize(path) + getsize(EP[0]) + 1;
		char* temp = new char[foldersize];
		for (int i = 0;i < foldersize;i++) {
			if (i < foldersize) {
				temp[i] = '\0';
				if (i == foldersize) {
					break;
				}
			}
		}
		int i = 0;
		for (i;i < getsize(path);i++) {
			if (i < foldersize) {
				temp[i] = path[i];
			}
		}
		for (int j = 0;j < getsize(EP[0]);i++, j++) {
			if (i < foldersize) {
				temp[i] = EP[0][j];
			}
		}
		if (i < foldersize) {
			temp[i] = '\0';
		}
		if (_mkdir(temp) == -1)
		{
			cout << "Error";
		}
		else {
			cout << "File Created";
		}
		return true;
	}
	else {
		return false;
	}
}
bool readpassfromfile(char word[], int col, int row) {
	ifstream input;
	int words = 1;
	int line = 1;
	input.open("user.txt");
	while (!input.eof()) {
		if (words == 6) {
			words = 1;
			line++;
		}
		char data[40];
		input >> data;
		if (words == col && line == row) {
			if (cmpstring(data, word)) {
				return true;
			}
		}
		words++;
	}
	return false;
}
bool extensioncheck(char string[], char string1[], int index) {
	int size = getsize(string);
	for (int i = size - index, j = 0;string[i] != '\0';i++) {
		if (string[i] == string1[j]) {
			j++;
		}
		else {
			return false;
		}
	}
	return true;
}
bool signup(char name[][20], char EP[][30], char cpass[]) {
	cout << "\n------------------------------------------------Sign up Form-------------------------------\n\n";
	cout << "\nEnter First name: ";
	cin >> name[0];
	cout << "\nEnter last name: ";
	cin >> name[1];
	cout << "\nEnter Email: ";
	do {
		cin >> EP[0];
		char ext[] = ".com";
		int size = getsize(ext);

		if (reademailfromfile(EP[0], 3)) {
			cout << "\nEmail Aleady Exists";
			cout << "\nEnter New Email: ";
			continue;
		}
		else if (!extensioncheck(EP[0], ext, size)) {
			cout << "\nWrong format";
			cout << "\nEnter Correct Format: ";
		}
		else if (extensioncheck(EP[0], ext, size)) {
			break;
		}
	} while (1);

	cout << "Enter password: ";
	cin >> EP[1];
	do {
		cout << "\nEnter confirm password: ";
		cin >> cpass;
	} while (!cmpstring(EP[1], cpass));

	if (writetofile(name, EP, cpass)) {
		return true;
	}
	else {
		return false;
	}
}
bool login(char EP[][30]) {
	cout << "\n---------------------------------------------------LOGIN IN FORM-----------------------------------------\n\n";
	cout << "Enter Email: ";
	do {
		cin >> EP[0];
		char ext[] = ".com";
		int size = getsize(ext);
		if (!extensioncheck(EP[0], ext, size)) {
			cout << "\nWrong format";
			cout << "\nEnter Correct Email Format: ";
		}
		else if (extensioncheck(EP[0], ext, size)) {
			break;
		}
	} while (1);
	int row = 0;
	row = reademailfromfile(EP[0], 3);
	if (row) {
		cout << "\nEnter password: ";
		cin >> EP[1];
		if (readpassfromfile(EP[1], 4, row)) {
			return true;
		}
		else {
			cout << "\npassword not matched ";
			do {
				cout << "\nEnter password again: ";
				cin >> EP[1];
				if (readpassfromfile(EP[1], 4, row)) {
					return true;
				}
			} while (1);
		}
	}
	else {
		cout << "\nEmail Not found\n";
		return false;
	}

}
//All functions related to File manager
void getpath(char filename[], char email[], char filepath[], int size) {
	for (int i = 0;i < size;i++) {
		filepath[i] = '\0';
	}
	int i = 0;
	for (i;i < getsize(email);i++) {
		filepath[i] = email[i];
	}
	filepath[i++] = '/';
	for (int j = 0;j < getsize(filename);i++, j++) {
		filepath[i] = filename[j];
	}
	filepath[i] = '\0';
}
void indexArray(char arr[], int index[], char ch) {
	int count = 0;
	for (int i = 0;i < getsize(arr);i++) {
		if (arr[i] == ch) {
			index[count] = i;
			//cout << index[count] << " count: " << count << endl;
			count++;
		}
	}
}
bool wordfound(char string1[], char string2[], int& count) {
	for (int i = 0, j = 0;i < getsize(string1);i++) {
		if (string1[i] == '\n') {
			count++;
		}
		if (string1[i] == string2[j]) {
			j++;
			if (j == getsize(string2) && (string1[i + 1] == '\n' || string1[i + 1] == '\0' || string1[i + 1] == ' ')) {
				j = 0;
				//cout << "Line no: " << count;
				return true;
			}
		}
		else {
			j = 0;
		}
	}
	return false;
}
char* readDatafromUserfile() {
	char* null = NULL;
	char userfile[] = "userfiles.txt";
	int userfilesize = filesize(userfile) + 2;
	//creatind dynamic array in order to read data from userfiles
	fstream input;
	input.open("userfiles.txt", ios::in);
	if (input.is_open()) {
		char* data;
		char ch;
		data = new char[userfilesize];
		int count = 0;
		for (int i = 0;i < userfilesize;i++) {
			data[i] = '\0';
		}

		// Getting data into the dynamic data array 
		while (ch = input.get()) {
			if (input.eof()) {
				break;
			}
			if (ch == '\n') {
				if (count < userfilesize) {
					data[count] = '\n';
				}
			}
			else {
				if (count < userfilesize) {
					data[count] = ch;
				}
			}
			count++;
		}
		input.close();
		data[count] = '\0';
		return data;
	}
	else {
		cout << "\nuserFiles not opened";
	}
	return null;
}
void addData(char* arr, int size, char filename[], char email[]) {
	char* temp;
	int index[20];
	temp = new char[size];
	for (int i = 0; i < size; i++) {
		temp[i] = '\0';
	}
	int line = 0;
	wordfound(arr, email, line);
	indexArray(arr, index, '\n');

	// Copying data before the filename
	int j = 0;
	int i = 0;
	for (i; i < index[line]; i++, j++) {
		if (j < size) {
			temp[j] = arr[i];
		}
	}
	if (j < size) {
		temp[j++] = ' ';
	}

	// Copying file name
	for (int k = 0; k < getsize(filename); k++, j++) {
		if (j < size) {
			temp[j] = filename[k];
		}
	}

	// Copying after file
	for (; i < getsize(arr) && j < size; i++, j++) {
		temp[j] = arr[i];
	}

	// Add null character at the end
	if (j < size) {
		temp[j] = '\0';
	}

	// Printing
	/*for (int k = 0; k < getsize(temp); k++) {
		if (k < size) {
			cout << temp[k];
		}
	}*/

	// Now entering this data into the userfiles
	fstream userfile;
	userfile.open("userfiles.txt", ios::out);
	userfile << temp;
	userfile.close();
	delete[] temp;
}
bool createFile(char filename[], char email[]) {
	//Now creating filepath with email and filename
	char filepath[100] = { '\0' };
	getpath(filename, email, filepath, 100);
	//---------------------------------------------
	fstream file;
	// Now checking whether the file already exits in username or not
	char* data;
	int line = 0;
	int indexline[20];
	char files[300] = { '\0' };
	data = readDatafromUserfile();
	wordfound(data, email, line);
	indexArray(data, indexline, '\n');
	//Now storing files with email in files array
	int j = 0;
	if (line == 0) {
		for (j;j < indexline[0];j++) {
			files[j] = data[j];
		}
	}
	else if (line > 0) {
		for (int i = indexline[line - 1] + 1;i < indexline[line];i++, j++) {
			files[j] = data[i];
		}
	}
	delete[]data;
	//Now checking whether the file already exits or not
	if (wordfound(files, filename, line)) {
		cout << "FILE ALREADY EXITS";
		cout << "\n-------------------------------------------------------------------------------\n";
		return false;
	}
	else {
		file.open(filepath, ios::out);
		if (file.is_open()) {
			data = readDatafromUserfile();
			// Now entering the filename in userfiles 
			addData(data, getsize(data) + getsize(filename) + 2, filename, email);
			cout << "\nFILE HAS BEEN CREATED";
			cout << "\n-------------------------------------------------------------------------------\n";
			delete[]data;
			return true;
		}
		return false;
	}
	return false;


}
bool showFiles(char email[]) {
	fstream file;
	file.open("userfiles.txt", ios::in);
	if (file.is_open()) {
		char* data;
		char files[300] = { '\0' };
		int line = 0;
		int indexline[20] = {};
		int indexspace[40] = { 0 };
		data = readDatafromUserfile();
		wordfound(data, email, line);
		indexArray(data, indexline, '\n');
		//Now storing files with email in files array
		int j = 0;
		if (line == 0) {
			for (j;j < indexline[0];j++) {
				files[j] = data[j];
			}
		}
		else if (line > 0) {
			for (int i = indexline[line - 1] + 1;i < indexline[line];i++, j++) {
				files[j] = data[i];
			}
		}
		indexArray(files, indexspace, ' ');
		//Now printing the files
		cout << "\n-----------------------------------------YOUR FILES------------------------------\n";
		if (indexspace[0] != 0) {
			for (int i = indexspace[0] + 1;files[i] != '\0';i++) {
				cout << files[i];
				if ((files[i] == ' ')) {
					if (i > 1 && files[i - 1] == ' ')
						continue;
				}
				if (files[i] == ' ')
					cout << endl;
			}
		}
		else {
			cout << "\nNO FILES";
		}
		cout << endl;
		cout << "\n-----------------------------------------------------------------------------\n";
		delete[]data;
		return true;
	}
	return false;
}
//All Functions which are used in writing a data into file
bool wordcheck(char string1[], char string2[]) {
	for (int i = 0, j = 0;i < getsize(string1);i++) {
		if (string1[i] == string2[j]) {
			j++;
			if (j == getsize(string2) && string1[i + 1] == '\0') {
				return true;
			}
		}
		else {
			j = 0;
		}
	}
	return false;
}
void regrow(char*& arr, int& size, char value) {
	if (size == 1) {
		int nsize = size + 1;
		char* temp = new char[nsize];
		temp[size - 1] = value;
		temp[size] = '\0';
		delete[] arr;
		arr = temp;
	}
	else {
		int nsize = size + 1;
		char* temp = new char[nsize];
		//Now copying previous data
		for (int i = 0;arr[i] != '\0';i++) {
			temp[i] = arr[i];
		}
		temp[size - 1] = value;
		temp[size] = '\0';
		delete[] arr;
		arr = temp;
	}
}
void shrink(char*& arr, int& size) {
	if (size == 1) {
		delete[] arr;
		arr = nullptr;
	}
	else {
		char* temp = new char[size];
		//Now copying previous data
		for (int i = 0;i < size - 1;i++) {
			temp[i] = arr[i];
		}
		temp[size - 1] = '\0';
		delete[] arr;
		arr = temp;
	}
}
bool openfile(char email[]) {
	cout << "\n----------------------------------------- FILE OPEN MENU------------------------------\n";
	char filename[30];
	do {
		cout << "\nENTER FILE NAME (with.txt extension): ";
		cin >> filename;
		char ext[] = ".txt";
		int size = getsize(ext);
		//Checking whether the file contains .txt extension..
		if (extensioncheck(filename, ext, size)) {
			break;
		}
	} while (1);
	char filepath[70];
	getpath(filename, email, filepath, 70);
	//cout << filepath;
	// Now Opening file
	fstream file;
	file.open(filepath, ios::in);
	bool fileopen = false;
	if (file.is_open()) {
		fileopen = true;
		system("cls");
		cout << "\n--------------File has opened-------------------------\n";
		cout << "Write /Exit to Exit from file";
		cout << "\n-------------------------------------------------------------\n";
		char* arr = new char[1];
		cin.ignore();
		while (!file.eof()) {
			char ch = file.get();
			cout << ch;
		}
		file.close();
		file.open(filepath, ios::app);
		int count = 1;
		do {
			char ch;
			ch = cin.get();
			regrow(arr, count, ch);
			char check[] = "/exit";
			if (wordcheck(arr, check)) {
				char chece = arr[count - 1];
				char chec1 = arr[count - getsize(check)];
				int size = count - getsize(check);
				int value = count;
				for (int i = 0;i < getsize(check);i++) {
					shrink(arr, value);
					if (value > 1) {
						value--;
					}
				}
				break;
			}
			count++;
		} while (1);
		cout << count;
		if (arr != nullptr) {
			file << arr;
		}
		file.close();
	}
	else {
		cout << "\nFILE DOESNOT EXISTS";
		cout << "\n----------------------------------------------------------------------------------------\n";
		return false;
	}
	cout << "\n----------------------------------------------------------------------------------------\n";
	if (fileopen) {
		system("cls");
		cout << "\n------------------------------------WELCOME " << email << "--------------------------\n";
	}
	return true;
}
//-------------------------------------------------------
void deletefile(char email[]) {
	cout << "\n----------------------------------------- FILE DELETE MENU------------------------------\n";
	char filename[30];
	do {
		cout << "\nENTER FILE NAME (with.txt extension): ";
		cin >> filename;
		char ext[] = ".txt";
		int size = getsize(ext);
		//Checking whether the file contains .txt extension..
		if (extensioncheck(filename, ext, size)) {
			break;
		}
	} while (1);
	char filepath[70];
	getpath(filename, email, filepath, 70);
	if (remove(filepath) == 0) {
		cout << "\nFILE HAS BEEN DELETED\n";
		fstream file;
		file.open("userfiles.txt", ios::in);
		char data[800] = { '\0' };
		int count = 0;
		int line;
		while (!file.eof()) {
			char temp[200];
			file.getline(temp, 200);
			if (wordfound(temp, email, line)) {
				int start = 0, end = 0;
				for (int i = 0, j = 0;i < getsize(temp);i++) {
					if (temp[i] == filename[j]) {
						j++;
						if (j == getsize(filename)) {
							end = i;
							start = i - getsize(filename);
							/*if (start>0 && temp[start-1]!='t') {
								cout << "not equal" << temp[start - 1];
								start = i - getsize(filename)+1;
							}*/
							/*cout << "Start: " << start << " " << temp[start] << "\tEnd: " << end << " " << temp[end] << endl;*/
							for (int i = 0;i < start;i++, count++) {
								data[count] = temp[i];
							}
							for (int i = end + 1;i <= getsize(temp);i++, count++) {
								if (temp[i] == '\0') {
									data[count++] = '\n';
									break;
								}
								data[count] = temp[i];
							}
						}
					}
					else {
						j = 0;
					}
				}
			}
			else {
				for (int i = 0;i < size(temp);i++, count++) {
					if (temp[i] == '\0') {
						data[count++] = '\n';
						break;
					}
					data[count] = temp[i];
				}
			}
		}
		file.close();
		if (count > 1) {
			data[--count] = '\0';
		}
		// Now entering data inot the userfiles.txt file
		file.open("userfiles.txt", ios::out);
		file << data;
		file.close();
	}

	else {
		cout << "\nFILE DOESNOT EXISTS";
	}
	cout << "\n----------------------------------------------------------------------------------------\n";


}
void fileMangager(char EP[][30]) {
	system("cls");
	cout << "\n------------------------------------WELCOME " << EP[0] << "--------------------------\n";
	char exit;
	bool elsepart = false;
	//Creating new menu after singup
	do {
		if (!elsepart) {
			cout << "\nPress 1: CREATE A FILE ";
			cout << "\nPress 2: SHOW ALL FILES ";
			cout << "\nPress 3: OPEN FILE";
			cout << "\nPress 4: DELETE FILE";
			cout << "\npress 5: CLEAR SCREEN ";
			cout << "\npress 6: EXIT ";
			cout << "\nENTER OPTION: ";
		}
		cin >> exit;
		if (exit == '1') {
			elsepart = false;
			char filename[20];
			cout << "\n-------------------------------CREATING FILE------------------------------------\n";
			do {
				cout << "\nENTER FILE NAME (with.txt extension): ";
				cin >> filename;
				char ext[] = ".txt";
				int size = getsize(ext);
				//Checking whether the file contains .txt extension..
				if (extensioncheck(filename, ext, size)) {
					break;
				}
			} while (1);
			createFile(filename, EP[0]);
		}
		else if (exit == '2') {
			elsepart = false;
			showFiles(EP[0]);
		}
		else if (exit == '3') {
			elsepart = false;
			openfile(EP[0]);
		}
		else if (exit == '4') {
			elsepart = false;
			deletefile(EP[0]);
		}
		else if (exit == '5') {
			elsepart = false;
			system("cls");
			cout << "\n------------------------------------WELCOME " << EP[0] << "--------------------------\n";
		}
		else if (exit == '6') {
			system("cls");
			break;
		}
		else {
			elsepart = true;
			continue;
		}
	} while (1);
}