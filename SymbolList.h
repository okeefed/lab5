#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

class SymbolList
{
   typedef struct symbolEntry
   {
      char type;
      std::string name;
      struct symbolEntry * next;
   } symbolEntry; 

   private:
      //points to the first symbolEntry in the linked list
      symbolEntry * first;
      //used to iterate through the nodes in the linked list
      symbolEntry * iterate;

   public:
      SymbolList();  //set first to NULL

      //returns true if the symbol with the name symbolName is in the list
      //and sets (*type) to the type of the symbol
      bool getSymbol(std::string symbolName, char * type);

      //returns true if the symbolList is empty
      bool isListEmpty();

      //returns true if the symbol with the name symbolName is in the list
      bool findSymbol(std::string symbolName);

      //returns true if there is an exact match, with type and symbolName 
      //both taken into account.
      bool findExactMatch(std::string symbolName, char type);
    
      //returns the char type of the symbol if a match is found
      char fetchType(std::string symbolName);

      //updates the type of the symbol with name symbolName       
      void updateSymbol(std::string symbolName, char type);

      //inserts a symbol with the name symbolName and the type char
      //at the ***end*** of the linked list
      void insertSymbol(std::string symbolName, char type);
      
      //struct SymbolEntry * createSymbolEntry(std::string name, char type, SymbolEntry * next);

      //removes the symbolEntry node with the name symbolName
      void removeSymbol(std::string symbolName);

      //prints the symbolEntry list
      void printSymbols(std::string header);

      //sets iterate to first
      void startIterate();

      //return NULL if iterate is NULL
      //if iterate is not NULL, it returns the name value in the
      //symbolEntry node pointed to by iterate and sets (*type) to its
      //type; it also makes iterate point to the next node
      std::string getNext(char * type);
};

#endif

