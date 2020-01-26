#include <SymbolList.h>
#include <SymbolTable.h>
Decrement::Decrement() : Symbol("Decrement","--",global_Decrement,660,HoldFirst|Protected|ReadProtected,post,"",""){}
void Decrement::printdoc(){printf(
	"                          x-- decreses the value of x by 1, returning the old value of x.\n"
);}
