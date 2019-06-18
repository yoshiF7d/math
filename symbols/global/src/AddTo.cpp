#include <SymbolList.h>
#include <SymbolTable.h>
AddTo::AddTo() : Symbol("AddTo","+=",global_AddTo,100,HoldFirst|Protected,left,"",""){}
void AddTo::printdoc(){printf(
	"                          x+=dx adds dx to x and returns the new value of x.\n"
);}
