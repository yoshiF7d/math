#include <SymbolList.h>
#include <SymbolTable.h>
BlankNullSequence::BlankNullSequence() : Symbol("BlankNullSequence","___",global_BlankNullSequence,730,Protected,pre,"",""){}
void BlankNullSequence::printdoc(){printf(
	"                          ___(three _ characters) or BlankNullSequence[] is a pattern object that can stand for any squence of zero or more expressions.\n"
	"                          ___h or BlankNullSequence[h] can stand for any sequence of expressions, all of which have head h.\n"
);}
