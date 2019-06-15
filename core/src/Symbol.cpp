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

#define KNRM  "\x1B[0m"
#define KCYN  "\x1B[36m"
#define KRED  "\x1B[31m"
#define KYEL  "\x1B[33m"
#define KWHT "\x1B[37m"
#define LONGBAR128 "================================================================================================================================\n"
#define LONGLINE128 "--------------------------------------------------------------------------------------------------------------------------------\n"

void Symbol::print(){
	Expr *e;
	std::cout << std::setw(26) << std::left << KCYN << this->name << " " << this->mark[0] << this->mark[1] << KNRM;
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
	std::cout << KWHT << LONGLINE128 << KNRM << '\n';
}

void Symbol::addAttributes(Attributes attributes){
	this->attributes = (Attributes) (this->attributes | attributes);
}

Expr* Symbol::function(Expr *e){return e;}
void Symbol::printdoc(){}
std::string Symbol::toString(){return this->name;}
Data* Symbol::createData(){return nullptr;}
void Symbol::deleteData(Data *data){delete data;}
bool Symbol::operator == (const Symbol& s){return name == s.name;}