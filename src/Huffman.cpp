// Huffman coding: tree construction, encoding and decoding.
#include "Huffman.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>


 const int buffer_size=8; 



// A Huffman tree node 
struct MinHeapNode { 
  
    // One of the input characters 
    char data; 
  
    // Frequency of the character 
     float freq; 
     bool rectangle;
  
    // Left and right child 
    MinHeapNode *left, *right; 
  
    MinHeapNode(bool rect,char data, float freq) 
  
    { 
  
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
        this->rectangle= rect;
    } 
}; 
  
// For comparison of 
// two heap nodes (needed in min heap) 
struct compare { 
  
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
  
    { 
        return (l->freq > r->freq); 
    } 
}; 
  
// Prints huffman codes from 
// the root of Huffman Tree. 
void generateCodes(vector <CodeTable>& code_vect,struct MinHeapNode* root, string str) 
{ 
  
    if (!root) 
        return; 
  
    if (root->rectangle ==false){ 
        cout<<"this is the data\n";
        cout<<"data: "<<root->data<<endl;
        CodeTable temp(root->data, str);
        code_vect.push_back(temp);
    }
    generateCodes(code_vect,root->left, str + "0"); 
    generateCodes(code_vect,root->right, str + "1"); 
} 
  
// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
void HuffmanCodes(vector <CodeTable>& code_vect,map<char,float> freq_map, int size) 
{ 
    struct MinHeapNode *left, *right, *top; 
  
    // Create a min heap & inserts all characters of data[] 
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  
    for (auto itr = freq_map.begin(); itr != freq_map.end(); itr++){
        minHeap.push(new MinHeapNode(false,itr->first, itr->second)); 
        
    }
  
    // Iterate while size of heap doesn't become 1 
    while (minHeap.size() != 1) { 
  
        // Extract the two minimum 
        // freq items from min heap 
        left = minHeap.top(); 
        minHeap.pop(); 
  
        right = minHeap.top(); 
        minHeap.pop(); 
  
        // Create a new internal node with 
        // frequency equal to the sum of the 
        // two nodes frequencies. Make the 
        // two extracted node as left and right children 
        // of this new node. Add this node 
        // to the min heap '$' is a special value 
        // for internal nodes, not used 
        top = new MinHeapNode(true,'$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        minHeap.push(top); 
    } 
  
    // Print Huffman codes using 
    // the Huffman tree built above 
    generateCodes(code_vect,minHeap.top(), ""); 
} 
 
 
 /*
 	ReadTheFile()
 	Input: pointer to a file
 	Output: Pointer to array of characters
 */
 char* ReadTheFile(FILE *f){
   	char *str = nullptr;
      // fseek(f, 0, SEEK_SET);
  	if (f != NULL){
  		//Get size of the file
  		fseek(f, 0 , SEEK_END); //put curose at the end of the file
  		long fSize = ftell(f); //get the size
  		rewind(f); //put the cursor at the beginning
  		//reserve place in the heap
  		str = (char *)calloc(fSize + 1, sizeof(char));
  		
  		//read file into the memory
  		fread(str, 1, fSize, f);
            
  		fclose(f);
  	} else {
  		cout << "Something went wrong" << endl; 
  	}
  	return str;
  	
 }

char* ReadTheFile_obj(FILE *f, int sizeofvect){
   	char *str = nullptr;
      // fseek(f, 0, SEEK_SET);
  	if (f != NULL){
  		//Get size of the file
  		fseek(f, sizeofvect, SEEK_SET); //put curose at the end of the file
  		long fSize = ftell(f); //get the size
  		//rewind(f); //put the cursor at the beginning
  		//reserve place in the heap
  		str = (char *)calloc(fSize + 1, sizeof(char));
  		
  		//read file into the memory
  		fread(str, 1, fSize, f);
            
  		fclose(f);
  	} else {
  		cout << "Something went wrong" << endl; 
  	}
  	return str;
  	
 }


string padwithzeros(string input,int n){
for (int i=0;i<n;i++)
input=input+"0";

return input;


}

int binaryToDecimal(string str)
{


    stringstream toInt(str); 
  
    // The object has the value 12345 and stream 
    // it to the integer x 
    int num = 0; 
    toInt >> num; 
    
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;
}


string getbitstream(vector<CodeTable> code_vect,int& numofpadbit,char* str, int sizeOfFile){
   string all_codes="";
for (int i = 0; i < sizeOfFile; i++){
    // cout<<"i: "<<i<<"\t";
//concatenation
    for (int j=0;j<code_vect.size();j++){
        
        //cout<<"j: "<<j<<endl;
        if (code_vect[j].getsymbol()==str[i])
            all_codes = all_codes+code_vect[j].getcode();

}

}
// int m = all_codes.size() / 8;
numofpadbit=0;
if (all_codes.size()!=8){
    numofpadbit = buffer_size- (all_codes.size() % 8);
    all_codes=padwithzeros(all_codes,numofpadbit);
    
}
return all_codes;
}


string decToBinary(int n) 
{ 
    if (n<0 || n>256)
        cout<<"This number "<<n<<" does not match any ascii code\n"<<endl;
    // array to store binary number 
    int binaryNum[8]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    
    string binstr="";
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        binstr=binstr+to_string(binaryNum[j]); 
    
    string compstring="";
    int size=8-(binstr.length());
    compstring=padwithzeros(compstring,size);
    binstr=compstring+binstr;
    
    return binstr;
} 


string phase1decode(vector<CodeTable> code_vect, string stream, int numofpadbit){
    string placeholder = ""; //0101011000111000
    bool found = false;
    string retstr1="";
 
    for (int i = 0; i < stream.length()-numofpadbit; i++){
        
        // if (found == true){
        //     placeholder = "";
        //     found = false;

        // } 
        
        // else {
        // placeholder = placeholder + stream[i];

        // }
        
    cout<<"i: "<<i<<"\t";
    
        placeholder=placeholder+stream[i];
        
        

        for (int j = 0; j < code_vect.size(); j++){
                if (code_vect[j].getcode() == placeholder){
                    found = true;
                    cout<<"Placeholder: "<<placeholder<<endl;
                    placeholder="";
                    retstr1=retstr1+code_vect[j].getsymbol();
                    cout << "retstr1: " << retstr1 << endl;
                    break;
                }
        }

    }
    return retstr1;
}


string phase2decode(vector<CodeTable> code_vect,string str, int sizeoffile, int numofpadbits){
int temp;
string all_stream="";

for (int i=0;i<sizeoffile;i++){


temp=str[i];

all_stream=all_stream+decToBinary(temp);
}

string retstr2;
retstr2=phase1decode(code_vect,all_stream,numofpadbits);

return retstr2;




}


