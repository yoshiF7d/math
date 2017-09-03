#include <Symbol.h>

Symbol::Symbol(string name, 
			   string[2] mark,
			   unsigned int id, 
			   unsigned int precedence,
			   Attributes attributes,
			   Associativity associativity,
			   Expr *rules,
			   Expr *alias
			   )
:
		name(name),
		mark(mark),
		id(id),
		precedence(precedence)
{
	this->attributes = attributes;
	this->associativity = associativity;
	this->rules = rules;
	this->alias = alias;
}

void Symbol::print(){
	Expr *e;
	if(this->symbol){
		cout << setw(26) << left << KCYN << this->name << this->mark[0] <<
				this->mark[1] << KNRM;
	}else{
		cout << setw(26) << left << KCYN << this->name << KNRM;
	}
	if(this->alias){
		cout << KRED << "Alias : " << KYEL;
		for(e=this->alias->child;e;e=e->next){
			cout << e->toString();
			if(e->next){cout << ',';}
		}
		cout << KNRM;
	}
	cout << '\n';
	this->printdoc();
	cout << KWHT << LONGLINE128 << KNRM << '\n';
}

void Symbol::addAttriutes(Attributes attributes){
	this->attributes |= attributes;
}

bool Symbol::operator == (const Symbol& s1, const Symbol& s2){
	return s1.name == s2.name;
}

virtual Expr* Symbol::function(Expr *e){return e;}
virtual void printdoc(){}
virtual string Symbol::toString(&Data){return this->toString();}
virtual string Symbol::toString(){return this->name;}
virtual void data_init(&Data data){}
virtual void data_finish(&Data data){}