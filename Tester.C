#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <stdio.h>
#include "SymbolList.h"
#include "FileHandler.h"
#include "Tester.h"

//you need to implement printSymbolsAtEnd and fileExists.
//The stubs for these are below.

/* Resolve
 * Driver for the resolution process.
 * Uses a FileHandler object to handle each .a and .o
 * Maintains an undefined and defined list for symbols
 */
Tester::Tester(int argc, char * argv[])
{
   undefined = new SymbolList();
   defined = new SymbolList();
   handler = new FileHandler(defined, undefined);
   for (int i = 1; i < argc; i++)
   {
      
       if (!fileExists(argv[i]) || 
          (!handler->isArchive(argv[i]) && !handler->isObjectFile(argv[i])))
       {
          std::cout << "invalid file: "<< argv[i] << std::endl;
          exit(1);
       }
       handler->insertTest("Hello", 'T');
   }
}

/* fileExists
 * returns true if filename exists 
 */
bool Tester::fileExists(std::string filename)
{
   //add code to determine if a file exists
  if (FILE * file = fopen(filename.c_str(), "r")) {
      fclose(file);
      return true;
  }
  else return false;
}

