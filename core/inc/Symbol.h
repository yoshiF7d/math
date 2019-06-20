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
	static Expr* parse(std::string::iterator *current);
	virtual Expr* evaluate(Expr *);
	virtual Expr* preEvaluate(Expr *);
	virtual void printdoc();
	virtual std::string toString();
	virtual Data* createData();
	virtual void deleteData(Data *data);
	virtual bool operator == (const Symbol&);
};
#define KNRM  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT "\x1B[37m"
#define LONGBAR128 "================================================================================================================================\n"
#define LONGLINE128 "--------------------------------------------------------------------------------------------------------------------------------\n"
#endif
