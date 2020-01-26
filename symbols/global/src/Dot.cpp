#include <SymbolList.h>
#include <SymbolTable.h>
Dot::Dot() : Symbol("Dot",".",global_Dot,490,Flat|OneIdentity|Protected,none,"",""){}
void Dot::printdoc(){printf(
	"                          a.b.c or Dot[a,b,c] gives products of vectors, matrices, and tensors.\n"
);}
