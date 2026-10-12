// Command-line entry point: compress (c) or decompress (d) a file.
#include "Huffman.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>

// Driver program to test above functions 
int main(int argC, char **argv) //main takes arguments at runtime
{ 
  
    
  
  	
  		// This function will be uncommented at the end
  		// Checks the user entered the correct the parameters
  		if (argC < 4){
  			cout << "You passed wrong parameters" << endl;
  			exit(0);
  		}
  
    //this is to handle compressing
    if (*(argv[3])=='c'){
        cout<<"Compressing............\n"<<endl;
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) {
            cout << "Could not open input file: " << argv[1] << endl;
            exit(1);
        }
        
        //str is an array character contains the whole text of the input file
        char *str = ReadTheFile(f);
        
        //freq_map is a map for the frequencies
        map<char, float> freq_map;
        
        //loop to calculate how many times each character is repeated in the file
        for (int i = 0; i < strlen(str); i++){
        bool found = false;
            for (auto itr = freq_map.begin(); itr != freq_map.end(); ++itr) {
                if (str[i] == itr->first) {
                    found = true; 
                    break;
                } 
            }
            if (found){
        
                freq_map[str[i]] = freq_map[str[i]] + 1; //increment the frequency
        
            } else {
                freq_map[str[i]] = 1; //introduce the element for the first time to the map
            }
        
        }

        //calculate the frequence of each chareacter  = divide the number of occurences / whole file size
        double sizeOfFile = strlen(str);
        for (auto itr = freq_map.begin(); itr != freq_map.end(); itr++) {
            freq_map[itr->first] = freq_map[itr->first] / sizeOfFile; 
        }
  	

        //printing the map
         for (auto itr = freq_map.begin(); itr != freq_map.end(); itr++) {
            cout << itr->first << " " << itr->second << endl;; 
        }        
         vector<CodeTable> test;
         HuffmanCodes(test,freq_map, freq_map.size());
         string all_codes;
      int numofpadbit;
    all_codes=getbitstream(test,numofpadbit,str,sizeOfFile);
      
      compressingData compressdata;
    compressdata.code_table=test;
    compressdata.numofpadzero=numofpadbit;

    
    
       ofstream outfile;
    outfile.open(argv[2]);
    for (int i=0; i<test.size();i++){
        if (test[i].getsymbol()=='\n'){
            outfile<<"en"<<" "<<test[i].getcode()<<endl;;

        }
        else
            outfile<<test[i].getsymbol()<<" "<<test[i].getcode()<<"\n";
        test[i].printcodetable();
    }
    outfile <<"#"<<endl<<numofpadbit<<endl;
    outfile<<"$"<<endl;
    cout<<all_codes<<endl;
    
    for (int i=0;i<all_codes.length();i+=8){ 
         
        char x = binaryToDecimal(all_codes.substr(i,8));
        cout<<"string: "<<all_codes.substr(i,8);
        cout<<"here it is"<<endl;
        cout<<binaryToDecimal(all_codes.substr(i,8))<<endl;
        cout<<x<<endl;
        cout << "all codess: "<<all_codes<<endl;
        outfile<< x;
    }
        
       outfile.close();
       cout<<"Done compressing. Open \""<<argv[2]<<"\" to see the compressed file.\n";
    

    }



    else if (*(argv[3])=='d'){
        cout<<"Decompressing.............\n"<<endl;
        compressingData newone;
        ifstream infile;
        infile.open(argv[1]);
        vector <CodeTable> code_table;
        int numofpadbits;
         CodeTable temp('/',"#");
            char symbol; 
            string  code;
        string info;
            //reading metadata 
        while (!infile.eof()){
            getline(infile,info);
            // infile>>symbol>>code; 
            cout<<"info: "<<info<<endl;
            
            if (info.length()>2 ){
                if (info[0]=='e'&&info[1]=='n'){
                    symbol='\n';
                info.erase(info.begin());
                info.erase(info.begin());
                info.erase(info.begin());
                code=info;
                temp.setsymbol(symbol);
                temp.setcode(code);
                code_table.push_back(temp);  

                }

                else{
                symbol=info[0];
                info.erase(info.begin());
                info.erase(info.begin());
                code=info;
                temp.setsymbol(symbol);
                temp.setcode(code);
                code_table.push_back(temp);  
                
                }              
            }
         
            
            else{
                infile>>numofpadbits;
                //cout<<"symbol: "<< numofpadbits<<endl;
                break;
            }
            
        }
        char data; 
        unsigned int b;
        char newdata;

        int a;
        int result;


        string filedata="";
        while (!infile.eof()){
            infile.get(data);
            a=data;
            result= a & 255;
            //cout<<result<<endl;
            string temp=decToBinary(result);
            filedata=filedata+temp;
            //out << "filedata now: "<< filedata << endl;
            // newdata=a & 255;
            // a=newdata; 
            // cout<<"a: "<<a<<endl;
            
            // cout<<"heythere "<<endl;
            // cout<<char(result)<<endl;
            //  //string temp(1,char(result));
             
            // filedata=filedata+newdata;

        }
        infile.close();
        cout<<"code Table : "<<endl;
        for (int i=0;i<code_table.size(); i++)
            code_table[i].printcodetable();
        cout<<"length: "<<filedata.length()<<endl;
        cout<<"filedata: "<<filedata<<endl;
        string compressed_data; 
/*
        for (int i=0;i<24;i++)
            filedata.erase(filedata.begin());
            cout<<"filedata: "<<filedata<<endl;
        for (int i=0;i<7;i++)
            filedata.erase(filedata.end());
*/
filedata.erase(0, 24);
filedata.erase(filedata.length() - 8, 8);
//  string filedata1 = filedata.substr(24, 8);
//  cout << filedata1 << endl;    
        //compressed_data=filedata.substr(24,filedata.length()-32);
        cout<<"filedata: "<<filedata<<endl;
        cout<<"numofpadbits: "<<numofpadbits<<endl;

        string outputstring;
    //   outputstring=phase2decode(code_table, compressed_data,compressed_data.length() ,numofpadbits);
      outputstring=phase1decode(code_table, filedata,numofpadbits);
       
      ofstream outfilefinal;
      outfilefinal.open(argv[2]);
      outfilefinal<<outputstring; 
      outfilefinal.close();
      cout<<"Done Decompressing. Open \""<<argv[2]<<"\" to see the original file.\n";
         
    }




    else{
        cout<<"The flag is not defined. The fourth parameter should be lower case \'c\' for compressing or lowercase \'d\' for decompressing\n";
        exit(1);
    }
  	
    return 0; 
} 
