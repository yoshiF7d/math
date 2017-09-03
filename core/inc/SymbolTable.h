#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <SymbolList.h>
#include <Symbol.h>
class Symbol;

using SymbolMap = unordered_map<string,*Symbol>;
using Context = pair<string,SymbolMap>;

class SymbolTable{
  private:	SymbolTable();
  public:
	static Context *local;
	static list<Context> context;
	static SymbolMap alias;
	static Symbol *idtable[id_end];
	
	static void init();
	static void finish();
	static Symbol* get(int);
	static Symbol* get(string);
	static void print();
	static void append(Symbol);
}
#endif