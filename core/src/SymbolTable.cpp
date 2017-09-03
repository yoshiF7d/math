#include <SymbolTable.h>
static void SymbolTable::init(){
	MAKE_CONTEXT(list,idtable)
	break;
}

static void SymbolTable::finish(){
	for(auto& t : idtable){
		delete t;
	}
	list.clear();
}

static Symbol** SymbolTable::getTable(){
	return idtable;
}

static Symbol* SymbolTable::get(int id){
	return idtable[id];
}

static Symbol* SymbolTable::get(string name){
	SymbolMap::iterator s;
	for(auto&& c : context){
		if((s=c.second.find(name))!=c.second.end()){
			return s->second;
		}
	}
	if((s = alias.find(name))!=alias.end()){
		return s->second;
	}
	this->local->second[name] = make_unique<Symbol>(name,"",0,0,nullptr,0,0,nullptr,nullptr);
}