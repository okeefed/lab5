
class Tester
{
   private:
      SymbolList * defined;
      SymbolList * undefined;
      FileHandler * handler;
      bool fileExists(std::string filename);

   public:
      Tester(int argc, char * argv[]);
};
