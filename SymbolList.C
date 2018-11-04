#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "SymbolList.h"

//lots of methods are missing that you need to add 
//See SymbolList.h for the declarations

/* printSymbols
 * prints a header and then the contents of the linked list
 */
void SymbolList::printSymbols(std::string header)
{
    symbolEntry * ptr = first;
    std::cout << header << " Symbol Table\n";
    std::cout << "-----------------------\n";
    while (ptr != NULL)
    {
       
       std::cout << std::setw(32) << std::left 
                 << ptr->name << " " << ptr->type 
                 << std::endl;
       ptr = ptr->next;
    }
}
//returns true if the symbol with the name symbolName is in the list
//and sets (*type) to the type of the symbol
bool getSymbol(std::string symbolName, char * type) {
    return false;
}

//updates the type of the symbol with name symbolName
void updateSymbol(std::string symbolName, char type) {
    
}

//inserts a symbol with the name symbolName and the type char
//at the ***end*** of the linked list
void insertSymbol(std::string symbolName, char type) { 

}

//removes the symbolEntry node with the name symbolName
void removeSymbol(std::string symbolName) {

}

//prints the symbolEntry list
void printSymbols(std::string header) {

}

//sets iterate to first
void startIterate() {

}

//return NULL if iterate is NULL
//if iterate is not NULL, it returns the name value in the
//symbolEntry node pointed to by iterate and sets (*type) to its
//type; it also makes iterate point to the next node
std::string getNext(char * type) {
    return "";
}

SymbolList::SymbolList(){}
