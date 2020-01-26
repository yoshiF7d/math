#include <SymbolList.h>
#include <SymbolTable.h>
Factorial::Factorial() : Symbol("Factorial","!",global_Factorial,610,Listable|NumericFunction|Protected|ReadProtected,0,"",""){}
void Factorial::printdoc(){printf(
	"                          n! gives the factorial of n.\n"
);}
