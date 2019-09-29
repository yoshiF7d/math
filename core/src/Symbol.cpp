#include <Symbol.h>
#include <Expr.h>
#include <Data.h>
#include <iomanip>

Symbol::Symbol(
		   std::string name,
		   std::string mark,
		   unsigned int id,
		   unsigned int precedence,
		   int attributes,
		   int associativity,
		   std::string rulesstr,
		   std::string aliasstr
		   ):
			name(name),
			id(id),
			precedence(precedence)
{
	setmark(mark,associativity);
	this->attributes = (Attributes) attributes;
	this->associativity = (Associativity) associativity;
	this->rulesstr = rulesstr;
	this->aliasstr = aliasstr;
	this->rules = nullptr;
	this->alias = nullptr;
};

Symbol::~Symbol(){
	if(rules){rules->deleteRoot();}
	if(alias){alias->deleteRoot();}
}

void Symbol::setmark(std::string mark, int asso){
	if(asso==Associativity::bracket){
		int len = mark.length();
		this->mark[0] = mark.substr(0,len/2);
		this->mark[1] = mark.substr(len/2,len/2);
	}else{
		this->mark[0] = mark;
		this->mark[1] = std::string();
	}
}

void Symbol::print(){
	Expr *e;
	std::cout << KCYN << this->name << " " << this->mark[0] << this->mark[1] << KNRM;
	if(this->alias){
		std::cout << KRED << "Alias : " << KYEL;
		for(e=this->alias->child;e;e=e->next){
			std::cout << e->toString();
			if(e->next){std::cout << ',';}
		}
		std::cout << KNRM;
	}
	std::cout << '\n';
	this->printdoc();
	std::cout << KWHT << LONGLINE128 << KNRM;
}

void Symbol::addAttributes(Attributes attributes){
	this->attributes = (Attributes) (this->attributes | attributes);
}

Expr* Symbol::parse(std::string::iterator *current){
	std::string::iterator save,it;
	it = save = *current;
	if(!isalpha(*it)){
		if(!(*it & 0x80)){*current = save; return nullptr;} /*UTF*/
	}
	while(isalnum(*it) || (*it & 0x80)){it++;}
	*current = it;
	return new Expr(std::string(save,it));
}

Expr* Symbol::evaluate(Expr *e){return e;}
Expr* Symbol::preEvaluate(Expr *e){return e;}
void Symbol::printdoc(){}
std::string Symbol::toString(){return this->name;}
Data* Symbol::createData(){return nullptr;}
void Symbol::deleteData(Data *data){delete data;}
bool Symbol::operator == (const Symbol& s){return name == s.name;}
