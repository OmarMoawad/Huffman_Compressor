#include "CodeTable.h"


CodeTable::CodeTable(char a,string b){
symbol=a;
code=b;


}

void CodeTable::setsymbol(char a){
symbol=a; 


}

void CodeTable::setcode(string b){
code=b;


}

char CodeTable::getsymbol(){

return symbol;

}

string CodeTable::getcode(){
return code;


}



void CodeTable::printcodetable(){

cout<<"symbol: "<<symbol<<"\t\t code: "<<code<<endl;




}
