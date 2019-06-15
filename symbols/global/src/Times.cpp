#include <SymbolList.h>
#include <SymbolTable.h>
Times::Times() : Symbol("Times","*",global_Times,400,Flat | Listable | NumericFunction | OneIdentity | Orderless | Protected,none,"","{乗算}"){}
