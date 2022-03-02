#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <SymbolList.h>
#include <iostream>
#include <list>
#include <unordered_map>
#include <parser.h>

using SymbolMap = std::unordered_map<std::string,Symbol*>;
using Context = std::pair<std::string,SymbolMap>;

class SymbolTable{
  private: SymbolTable();
  public:
	static Parser* parser;
	static Context *local;
	static std::list<Context> context;
	static SymbolMap alias;
	static Symbol *idtable[id_end];
	
	static void init();
	static void finish();
	static Symbol* get(int);
	static Symbol* get(std::string);
	static void print(int);
	static void print();
	static void append(Symbol);
};
#endif
