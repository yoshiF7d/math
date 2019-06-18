#include <SymbolList.h>
#include <SymbolTable.h>
BlankSequence::BlankSequence() : Symbol("BlankSequence","__",global_BlankSequence,730,Protected,one,"",""){}
void BlankSequence::printdoc(){printf(
	"                          __(two _ characters) or BlankSequence[] is a pattern object that can stand for any squence of one or more expressions.\n"
	"                          __h or BlankSequence[h] can stand for any sequence of one or more expressions, all of which have head h.\n"
);}
