#include <SymbolList.h>
#include <SymbolTable.h>
PreDecrement::PreDecrement() : Symbol("PreDecrement","--",global_PreDecrement,660,HoldFirst|Protected|ReadProtected,pre,"",""){}
void PreDecrement::printdoc(){printf(
	"                          --x decreases the value of x by 1, returning the new value of x.\n"
);}
