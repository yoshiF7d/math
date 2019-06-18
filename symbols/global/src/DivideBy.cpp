#include <SymbolList.h>
#include <SymbolTable.h>
DivideBy::DivideBy() : Symbol("DivideBy","/=",global_DivideBy,100,HoldFirst|Protected,left,"",""){}
void DivideBy::printdoc(){printf(
	"                          x/=c divides x by c and returns the new value of x.\n"
);}
