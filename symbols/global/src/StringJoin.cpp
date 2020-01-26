#include <SymbolList.h>
#include <SymbolTable.h>
StringJoin::StringJoin() : Symbol("StringJoin","<>",global_StringJoin,600,Flat|OneIdentity|Protected,none,"",""){}
void StringJoin::printdoc(){printf(
	"                          \"s_1\" <> \"s_2\" <> ..., StringJoin[\"s_1\",\"s_2\",...], or StringJoin[{\"s_1\",\"s_2\",...}]\n"
	"                          yields a string consisting of a concatenation of the s_i\n"
);}
