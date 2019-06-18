#include <SymbolList.h>
#include <SymbolTable.h>
Blank::Blank() : Symbol("Blank","_",global_Blank,730,Protected,one,"",""){}
void Blank::printdoc(){printf(
	"                          _ or Blank[] is a pattern object that can stand for any expression.\n"
	"                          _h or Blank[h] can stand for any expression with head h.\n"
);}
