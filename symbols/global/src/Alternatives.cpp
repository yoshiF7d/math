#include <SymbolList.h>
#include <SymbolTable.h>
Alternatives::Alternatives() : Symbol("Alternatives","|",global_Alternatives,160,Protected,none,"",""){}
void Alternatives::printdoc(){printf(
	"                          p_1 | p_2 | ... is a pattern object which represents any of the patterns p_i.\n"
);}
