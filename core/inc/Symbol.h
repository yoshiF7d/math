#ifndef SYMBOL_H
#define SYMBOL_H

#include <Attributes.h>
#include <Associativity.h>
#include <iostream>

class Expr;
union Data;
class Symbol{
  public:
	Expr *field;
	std::string name;
	std::string mark[2];
	unsigned int id;
	unsigned int precedence;
	Attributes attributes;
	Associativity associativity;
	Expr *rules;
	Expr *alias;
	
	Symbol(std::string name, 
		   string mark[2],
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
	virtual std::string toString();
	virtual std::string toString(&Data);
	virtual bool operator == (const Symbol&, const Symbol&);
	virtual void data_init(&Data);
	virtual void data_finish(&Data);
}
#endif
