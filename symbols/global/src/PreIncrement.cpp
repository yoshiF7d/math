#include <SymbolList.h>
#include <SymbolTable.h>
PreIncrement::PreIncrement() : Symbol("PreIncrement","++",global_PreIncrement,660,HoldFirst|Protected|ReadProtected,pre,"",""){}
void PreIncrement::printdoc(){printf(
	"                          ++x increses the value of x by 1, returning the new value of x.\n"
);}
