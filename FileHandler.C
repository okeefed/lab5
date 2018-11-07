#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "SymbolList.h"
#include "FileHandler.h"

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

        if (buffer[0] != ' ') {
            return false;
        }
        else {
            ss >> symbolValue;
            ss >> type;
            ss >> symbolName;
            
            return (undefined->SymbolList::getSymbol(symbolName));
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

