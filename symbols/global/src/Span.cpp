#include <SymbolList.h>
#include <SymbolTable.h>
Span::Span() : Symbol("Span",";;",global_Span,305,Protected,none,"",""){}
void Span::printdoc(){printf(
	"                          i;;j represents a span of elements i through j.\n"
	"                          i;; represents a span from i to the end.\n"
	"                          ;;j represents a span from the beginning to j.\n"
	"                          ;; represents a span that includes all elements.\n"
	"                          i;;j;;k represents a span from i through j in steps of k.\n"
	"                          i;; ;;k represents a span from i to the end in steps of k.\n"
	"                          ;;j;;k represents a span from the beginning to j in steps of k.\n"
	"                          ;; ;;k represents a span from the beginning to the end in steps of k.\n"
);}
