#ifndef RESOLVE_H
#define RESOLVE_H
class Resolve
{
   private:
      SymbolList * defined;
      SymbolList * undefined;
      FileHandler * handler;
      bool fileExists(std::string filename);
      void printSymbolsAtEnd();   

   public:
      Resolve(int argc, char * argv[]);
};
#endif
