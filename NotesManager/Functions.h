#pragma once

//General
int  getsize(char arr[]);
int filesize(char filename[]);
bool cmpstring(char arr1[], char arr2[]);
//singup
int reademailfromfile(char word[], int col);
bool writetofile(char name[][20], char EP[][30], char cpass[]);
bool readpassfromfile(char word[], int col, int row);
bool extensioncheck(char string[], char string1[], int index);
bool signup(char name[][20], char EP[][30], char cpass[]);
bool login(char EP[][30]);
//All functions related to File manager
void getpath(char filename[], char email[], char filepath[], int size);
void indexArray(char arr[], int index[], char ch);
bool wordfound(char string1[], char string2[], int& count);
char* readDatafromUserfile();
void addData(char* arr, int size, char filename[], char email[]);
bool createFile(char filename[], char email[]);
bool showFiles(char email[]);
//All Functions which are used in writing a data into file
bool wordcheck(char string1[], char string2[]);
void regrow(char*& arr, int& size, char value);
void shrink(char*& arr, int& size);
bool openfile(char email[]);
//-------------------------------------------------------
void deletefile(char email[]);
void fileMangager(char EP[][30]);