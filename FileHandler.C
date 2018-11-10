#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "SymbolList.h"
#include "FileHandler.h"

static int localSymbolCounter = 0;

FileHandler::FileHandler(SymbolList * defined, SymbolList * undefined){}

//name mangles local symbols
//puts undefined symbols in undefined list (if not already defined or already in undefined)
//puts defined symbols in defined list (if not already in defined -- gives multiple definition
//    error for multiple strong symbols) and removes from undefined if in undefined
//updates type of symbol in defined list from weak to strong
//name parameter: name of symbol
//type parameter: type of symbol
void FileHandler::handleObjectSymbol(std::string name, char type)
{
    //if the currSymbol is undefined and is not in the defined list and not already in the undefined list
    if ((type == 'U') && (!(defined->findSymbol(name))) && (!(undefined->findSymbol(name)))) handleUndefinedSymbol(name, type);
    //else if strong, global symbol
    else if (type == 'T' || type == 'D') handleStrongGlobalSymbol(name, type);
    //else if it is a weak, global symbol
    else if (type == 'C') handleWeakGlobalSymbol(name, type);
    //else if it is a local symbol
    else if (type == 'b' || type == 'd') handleLocalSymbol(name, type);
}

//small, single-purpose function for handling undefined symbols
void FileHandler::handleUndefinedSymbol(std::string name, char type) {
    undefined->insertSymbol(name, type);
}

//small, single-purpose function for handling strong, global symbols
void FileHandler::handleStrongGlobalSymbol(std::string name, char type) {
    //Symbol is not already in the defined set
    if (!(defined->findSymbol(name))) {
        //Symbol is not in the undefined set either.
        //At this point, you will always neeed to insert into the defined set. go ahead and do that now.
        //Then check to see if you need to remove it from the undefined list too.
        defined->insertSymbol(name, type);
        //if the symboleName was already in the undefined set...
        if ((undefined->findSymbol(name))) {
            //you should remove it from there, as it is now defined!
            undefined->removeSymbol(name);    
        }
    }
    //Symbol is already in the defined set
    else { 
        //if the type of the already defined symbol is C then we're good
        //just update the symbol's type.
        if (defined->fetchType(name) == 'C') {
            defined->updateSymbol(name, type); 
        }
        //else it wasn't a C, so it must have been multiply defined. Spit out error
        //and move on to next one.
        std::cout << "Error: Strong Symbol is multiply defined\n"; 
    }
}

//small, single-purpose function for handling weak, global symbols
void FileHandler::handleWeakGlobalSymbol(std::string name, char type) {
    //if it is not already defined, add it to the defined list
    if (!(defined->findSymbol(name))) defined->insertSymbol(name, type);
    //if a symbol with this name was previously undefined, remove it from undefined list.
    if (undefined->findSymbol(name)) undefined->removeSymbol(name);
}

//small, single-purpose function for handling local symbols
void FileHandler::handleLocalSymbol(std::string name, char type) {
    //append .N to name and insert into defined list
    //where 'N' is a static counter, incremented every use in order to give unique
    //names to local symbols
    name.append(".");
    name.append(std::to_string(localSymbolCounter));
    //name has been appended, increment counter so next name is unique
    localSymbolCounter++;
    defined->insertSymbol(name, type);
}

//used to check whether an object file in an archive should be added to the
//defined and undefined list; that is, does the object file define something
//that is currently undefined?
bool FileHandler::objectFileNeeded(std::string filename)
{
    char buffer[80];
    FILE * fp;
    char type;
    int symbolValue;
    std::string symbolName;
    std::string command = ("nm " + filename);

    fp = popen(command.c_str(), "r");
    if (fp == NULL) { std::cout << "popen failed\n"; exit(1); }
    while (fgets(buffer, sizeof(buffer), fp)) {
        std::stringstream ss(buffer);
        
        //tests whether the symbol is defined on the current line
        if (buffer[0] == ' ') {
            ss >> symbolValue;
            ss >> type;
            ss >> symbolName;
            
            //this returns true if the symbol is currently in the 
            //undefined list 
            return (undefined->findSymbol(symbolName));
        }
    }
    pclose(fp);
    return false;
}

//returns true if the filename ends with a .a
bool FileHandler::isArchive(std::string filename)
{
    return(filename.substr(filename.length() - 2) == ".a");
}

//returns true if the filename ends with a .o
bool FileHandler::isObjectFile(std::string filename)
{
    return(filename.substr(filename.length() - 2) == ".o");
}

//handles .o files; uses nm to get the list of symbols
//calls handleObjectSymbol to handle each symbol
void FileHandler::handleObjectFile(std::string filename)
{
    char buffer[80];
    FILE * fp;
    int temp;
    char type;
    char name[15]; 
    std::string command = ("nm " + filename);
    fp = popen(command.c_str(), "r");
    if (fp == NULL) { std::cout << "popen failed\n"; exit(1); }
    while (fgets(buffer, sizeof(buffer), fp)) {
	    sscanf(buffer, "%d %c %s", &temp, &type, name);
	    handleObjectSymbol(name, type);	        
    }
    pclose(fp);
}

//handles .a files; gets the list of .o; determines whether
 //a .o should be added to the undefined and defined lists (by calling objectFileNeeded)
//if an object file should be added, it calls handleObjectFile to do the work
void FileHandler::handleArchive(std::string filename)
{
   // bool changed;
   //if (system("mkdir tmp") == -1) {std:: cout << "mkdir tmp failed\n"; exit(1); }
    char obj_list[80];
    FILE * fp;
    std::string copyCommand = ("cp " + filename + " tmp");
    std::string arCommand = ("cd tmp; ar -x " + filename);
    //make a tmp directory
    system("mkdir tmp");
    //copy the archive file tmp.a into tmp
    system(copyCommand.c_str());
    //go into the tmp directory, extract the object files from the archive file
    system(arCommand.c_str());
    //set fp to output of ls tmp -- should be a list of all of the object files
    fp = popen("ls tmp", "r");
    
    while (fgets(obj_list, 80, fp) != NULL) std::cout << obj_list;// printf("%s\n", obj_list);
    
    //printf("This is printf: %p\n", fp); 
    //std::cout << "filePointer: " << fp << "\n";

    pclose(fp);
    system("rm -f -r tmp");
}

