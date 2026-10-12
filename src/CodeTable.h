#pragma once 
#include <iostream>
#include "CodeTable.h"
#include <string>
using namespace std;

class CodeTable{

private:
char symbol;
string code; 

public: 
CodeTable();
CodeTable(char,string);
void setsymbol(char);
void setcode(string);
char getsymbol();
string getcode();
void printcodetable();
};