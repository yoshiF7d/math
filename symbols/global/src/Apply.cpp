#include <SymbolList.h>
#include <SymbolTable.h>
Apply::Apply() : Symbol("Apply","@@",global_Apply,620,Protected,right,"",""){}
void Apply::printdoc(){printf(
	"                          Apply[f,expr] or f@@expr replaces the head of expr by f.\n"
	"                          Apply[f,expr,{1}] or f@@@expr replaces heads at level 1 of expr by f.\n"
	"                          Apply[f,expr,levelspec] replaces heads in parts of expr specified by levelspec.\n"
);}
