#include <SymbolList.h>
#include <SymbolTable.h>
Replace::Replace() : Symbol("Replace","",global_Replace,670,Locked|Protected,0,"",""){}
void Replace::printdoc(){printf(
	"                          Replace[expr,rules] applies a rule or list of rules in an attempt to transform the entire expression expr.\n"
	"                          Replace[expr,rules,levelspec] applies rules to parts of expr specified by levelspec.\n"
);}
