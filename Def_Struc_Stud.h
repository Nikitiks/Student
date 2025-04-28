#pragma once
#include <fstream>
#include <iostream>
using namespace std;
struct Stud {

	char fname[20];
	char lname[20];
	char special[25];
	char age[4];
	char curs[2];

};
struct ArrStud
{
	int size = 0;
	Stud* arr = nullptr;
};

void MainMenu();

Stud InitStud();
ArrStud InitArrStud(int size);

Stud InitFStud(char* line);
ArrStud InitFArrStud(const char* f);

void PrintArr(const ArrStud& arrst);
void PrintStud(const Stud st);


void RedactStud(ArrStud& arrst);
Stud* FindStud(ArrStud& arrst);

void DeleteStud(ArrStud& arrst);

void FindStudLN(const ArrStud& arrst,const char* ln);

int FindChFN(const char* gl_ln, const char* ln);
void PrintStudAgLn(const ArrStud& arrst, const char* ag,const char* ln);

void SafeArrStud(const ArrStud& arrst,const char* f);