#include <SymbolTable.h>
#include <Symbol.h>

Context * SymbolTable::local;
std::list<Context> SymbolTable::context;
SymbolMap SymbolTable::alias;
Symbol * SymbolTable::idtable[id_end];
Parser * SymbolTable::parser;

void SymbolTable::init(){
	context.push_back(make_pair("local",SymbolMap{}));
	local = &context.front();
	MAKE_CONTEXT(context,idtable)
	idtable[global_Symbol] = new Symbol("Symbol","",global_Symbol,670,Locked|Protected,0,"","");
	for(auto&& c : context){
		for(auto&& t : c.second){
			Symbol *symbol = t.second;
			if(!symbol->aliasstr.empty()){
				
			}
			if(!symbol->rulesstr.empty()){
				
			}
		}
	}
	parser = new Parser();
}

void SymbolTable::finish(){
	parser->finish();
	delete parser;
	parser = nullptr;
	for(auto&& c : context){
		for(auto&& t : c.second){
			delete t.second;
		}
		c.second.clear();
	}
	/*
	for(auto& t : idtable){
		delete t;
	}
	*/
	context.clear();
}

void SymbolTable::print(){
	for(auto&& c : context){
		std::cout << KRED << c.first << "`\n" << KNRM;
		std::cout << LONGBAR128;
		for(auto&& t : c.second){
			Symbol *symbol = t.second;
			symbol->print();
		}
	}
}

void SymbolTable::print(int id){
	idtable[id]->print();
}

Symbol* SymbolTable::get(int id){
	return idtable[id];
}

Symbol* SymbolTable::get(std::string name){
	for(auto&& c : context){
		if(c.second.find(name) != c.second.end()){
			return c.second.find(name)->second;
		}
	}
	/*
	if(alias.find(name) != alias.end()){
		symbol = alias.find(name)->second;
		return symbol;
	}
	*/
	Symbol* symbol = new Symbol(name,"",0,670,0,0,"","");
	local->second[name] = symbol;
	return symbol;
}
