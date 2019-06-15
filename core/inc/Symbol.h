#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include <Attributes.h>
#include <Associativity.h>
#include <Data.h>

class Expr;
class Symbol{
  public:
	std::string name;
	std::string mark[2];
	unsigned int id;
	unsigned int precedence;
	Attributes attributes;
	Associativity associativity;
	Expr *field;
	Expr *rules;
	Expr *alias;
	std::string rulesstr;
	std::string aliasstr;
	
	Symbol(std::string name, 
		   std::string mark,
		   unsigned int id,
		   unsigned int precedence,
		   int attributes,
		   int associativity,
		   std::string rulesstr,
		   std::string aliasstr
		   );
	virtual ~Symbol();
	void setmark(std::string mark, int asso);
	void print();
	void addAttributes(Attributes attributes);
	virtual Expr* function(Expr *);
	virtual void printdoc();
	virtual std::string toString();
	virtual Data* createData();
	virtual void deleteData(Data *data);
	virtual bool operator == (const Symbol&);
};
#endif
