#include <SymbolList.h>
#include <SymbolTable.h>
ReplaceAll::ReplaceAll() : Symbol("ReplaceAll","/.",global_ReplaceAll,110,Protected,left,"",""){}
void ReplaceAll::printdoc(){printf(
	"                          expr /. rules applies a rule or list of rules in an attempt to transform each subpart of an expression expr.\n"
);}
