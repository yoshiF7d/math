#include <SymbolList.h>
#include <SymbolTable.h>
Plus::Plus() : Symbol("Plus","+",global_Plus,310,Flat | Listable | NumericFunction | OneIdentity | Orderless | Protected,none,"","{加算}"){}
void Plus::printdoc(){printf(
	"                          x + y + z represents a sum of terms.\n"
);}