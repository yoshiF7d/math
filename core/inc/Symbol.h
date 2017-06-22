#ifndef SYMBOL_H
#define SYMBOL_H

#include <Attributes.h>
#include <Associativity.h>

class Expr;
union Data;
class Symbol{
  public:
	Expr *field = nullptr;
	string name;
	string symbol;
	unsigned int id;
	unsigned int precedence;
	Attributes attributes;
	Associativity associativity;
	Expr *rules;
	Expr *alias;
	
	Symbol(string name, 
		   string symbol,
		   unsigned int id, 
		   unsigned int precedence,
		   Attributes attributes,
		   Associativity associativity,
		   Expr *rules,
		   Expr *alias
		   );
	void print();
	void addAttributes(Attributes attributes);
	
	virtual Expr* function(Expr *);
	virtual void printdoc();
	virtual string toString();
	virtual string toString(&Data);
	virtual bool operator == (const Symbol&, const Symbol&);
	virtual void data_init(&Data);
	virtual void data_finish(&Data);
}
#endif