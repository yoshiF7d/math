#include <SymbolList.h>
#include <SymbolTable.h>
True::True() : Symbol("True","",global_True,670,Protected,0,"",""){}
void True::printdoc(){printf(
	"                          True is the symbol for the Boolean value true.\n"
);}
