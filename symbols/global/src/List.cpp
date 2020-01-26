#include <SymbolList.h>
#include <SymbolTable.h>
List::List() : Symbol("List","{}",global_List,670,Locked|Protected,bracket,"",""){}
void List::printdoc(){printf(
	"                          {e1,e2,...} is a list of elements.\n"
);}
