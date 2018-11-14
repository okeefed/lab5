#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <list>
#include <iterator>
#include <assert.h>

#ifndef SYMBOLLIST_H
#include "SymbolList.h"
#endif

#ifndef FILEHANDLER_H
#include "FileHandler.h"
#endif

//static int count;

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
bool SymbolList::getSymbol(std::string symbolName, char * type) {
    startIterate();
    if(first->name == symbolName) {
        *type = first->type;
        return true;
    }
    /*iterates through linked list. 
     * if it didn't check iterate and did iterate->next, it would
     * never check the last element. */
    while(iterate != NULL) {
        //if it finds a match it sets the pointer value and returns true
        if(iterate->name == symbolName) {
            *type = iterate->type;
            return true;
        }
        iterate = iterate->next;
    }
    //if no match is found, it falls through and returns false
    return false;
}

//returns true if the list is empty
bool SymbolList::isListEmpty() {
    return(first == NULL);
}

//returns true if the symbol with the name symbolName is in the list
bool SymbolList::findExactMatch(std::string symbolName, char type) {
    startIterate();
    if(first != NULL) {
        if(first->name == symbolName && first->type == type) {
            return true;
        }
        /*iterates through linked list. 
         * if it didn't check iterate and did iterate->next, it would
         * never check the last element. */
        while(iterate != NULL) {
            //if it finds a match it sets the pointer value and returns true
            if(iterate->name == symbolName && iterate->type == type) {
                return true;
            }
            iterate = iterate->next;
        }
    }
    //if no match is found, it falls through and returns false
    return false;
}

//returns true if the symbol with the name symbolName is in the list
bool SymbolList::findSymbol(std::string symbolName) {
      if (first != NULL) {
        SymbolList::startIterate();
        if(first->name == symbolName) {
            return true;
        }
        /*iterates through linked list. 
         * if it didn't check iterate and did iterate->next, it would
         * never check the last element. */
        while(iterate != NULL) {
            //if it finds a match it sets the pointer value and returns true
            if(iterate->name == symbolName) {
                return true;
            }
            iterate = iterate->next;
        }
    }
    //if no match is found, or the list is empty, it falls through and returns false
    return false;
}

//returns the symbol's type if one with the same name is found
char SymbolList::fetchType(std::string symbolName) {
    startIterate();
    if(first->name == symbolName) {
        return first->type;
    }
    /*iterates through linked list. 
     * if it didn't check iterate and did iterate->next, it would
     * never check the last element. */
    while(iterate->next != NULL) {
        //if it finds a match it sets the pointer value and returns true
        if(iterate->name == symbolName) {
            return iterate->type;
        }
        iterate = iterate->next;
    }
    //if no match is found, it falls through and returns ' '
    return ' ';
}

//updates the type of the symbol with name symbolName
void SymbolList::updateSymbol(std::string symbolName, char type) {
    //handles case where first entry is a match
    if (first->name == symbolName) {
        first->type = type;
        return;
    }
    SymbolList::startIterate();
    while(iterate != NULL) {
        if(iterate->name == symbolName) {
            iterate->type = type;
            return;
        }
        iterate = iterate->next;
    }
}

/*
 *Doesn't compile right now
 *
struct SymbolEntry * SymbolList::createSymbolEntry(std::string name, char type, SymbolEntry * next) {
    SymbolList::symbolEntry * ptr = (struct symbolEntry *)malloc(sizeof(symbolEntry));
    ptr->type = type;
    ptr->name = name;
    ptr->next = NULL; 
    return ptr;
}
*/

//inserts a symbol with the name symbolName and the type char
//at the ***end*** of the linked list
void SymbolList::insertSymbol(std::string symbolName, char type) {
    //symbolEntry * ptr = (struct symbolEntry *)malloc(sizeof(symbolEntry));
    symbolEntry * ptr = new symbolEntry();
    ptr->type = type;
    ptr->name = symbolName;
    ptr->next = NULL; 
    //if the list is empty...
    if (first == NULL) {
        first = ptr;
        return;
    }        
    startIterate();
    //find the end of the list
    while (iterate->next != NULL) {
        iterate = iterate->next;
    }
    //initialize the new Symbol
    //setup a pointer
    iterate->next = ptr;
    //free(ptr); 
}

//removes the symbolEntry node with the name symbolName
void SymbolList::removeSymbol(std::string symbolName) {
    startIterate();
    //symbolEntry * prev = new symbolEntry();
    symbolEntry * prev = (struct symbolEntry *)malloc(sizeof(symbolEntry));
    prev = NULL;
    /*handles both a list where the first matches and where there is only
    one element and it matches.*/
    
    if(first->name == symbolName) {
        first = first->next;
        return;
    }
    //if the first wasn't a match...iterate through list
    while(iterate->next != NULL) {
        /*if the current symbols name matches, set the prev's next pointer to be the 
        following element, essentially deleting the current element from the middle*/
       if(iterate->name == symbolName) {
            prev->next = iterate->next;
            return;
       }
       //otherwise no match...set prev to current. set current to next.
       prev = iterate;
       iterate = iterate->next;
    }
}

//sets iterate to first
void SymbolList::startIterate() {

    //iterate = (struct symbolEntry *)malloc(sizeof(symbolEntry));
    if (first != NULL) iterate = first;
    else {
        std::cout << "error\n"; 
        exit(1);
    }
}

//return NULL if iterate is NULL
//if iterate is not NULL, it returns the name value in the
//symbolEntry node pointed to by iterate and sets (*type) to its
//type; it also makes iterate point to the next node
std::string SymbolList::getNext(char * type) {
    std::string oldName;
    if (iterate == NULL) return NULL;
    else {
        //save the old values name so you can return it
        oldName = iterate->name;
        *type = iterate->type;
        iterate = iterate->next;
        return oldName;
    }
}

//Constructor: sets first to NULL
SymbolList::SymbolList(){
       //first = (struct symbolEntry *)malloc(sizeof(symbolEntry));
       first = new symbolEntry();
       //first = NULL; 
       //count = 0;
}
