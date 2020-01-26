#include <SymbolList.h>
#include <SymbolTable.h>
Thread::Thread() : Symbol("Thread","",global_Thread,670,Protected,0,"",""){}
void Thread::printdoc(){printf(
	"                          Thread[f[args]] threads f over any lists that appear in args.\n"
	"                          Thread[f[args],h] threads f over any objects with head h that appear in args.\n"
	"                          Thread[f[args],h,n] threads f over objects with head h that appear in the first n args.\n"
);}
