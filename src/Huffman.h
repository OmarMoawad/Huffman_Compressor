#pragma once
#include <map>
#include <string>
#include <vector>
#include "CodeTable.h"

// Code table plus the number of zero bits padded onto the last byte.
struct compressingData {
    vector<CodeTable> code_table;
    int numofpadzero;
};

// Builds the Huffman tree from character frequencies and fills code_vect.
void HuffmanCodes(vector<CodeTable>& code_vect, map<char, float> freq_map, int size);

// Reads a whole file into a heap-allocated, null-terminated buffer.
char* ReadTheFile(FILE* f);

// Encodes str with the code table; pads to a whole byte and reports the pad count.
string getbitstream(vector<CodeTable> code_vect, int& numofpadbit, char* str, int sizeOfFile);

// Bit/byte conversion helpers.
int binaryToDecimal(string str);
string decToBinary(int n);

// Decodes a bit string back to text using the code table.
string phase1decode(vector<CodeTable> code_vect, string stream, int numofpadbit);
