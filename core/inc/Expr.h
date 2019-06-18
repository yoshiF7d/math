#ifndef Expr_H
#define Expr_H
#include <iostream>
/*double : 64 = 1 + 11 + 52 (sign,exponent,prec)*/
/*used for overflow prediction*/
#define R64_LIMIT 52
#define I32_LIMIT 31
#define LOG2 0.301029995663981
#define PREC_SYMBOL -1
#define PREC_MATCH -2
#include <Data.h>
class Symbol;

class Expr{
  public:
	Expr *next;
	Expr *previous;
	Expr *parent;
	Expr *child;
	Symbol *symbol;
	Data *data;
	
	Expr();
	Expr(int id);
	Expr(std::string str);
	Expr(Symbol *symbol);
	Expr(const Expr& other);
	
	~Expr();
	
	void deleteRoot();
	void deleteLast();
	void deleteChild(Expr *child);
	void deleteChildren();
	int getLength();
	std::string toString();
	Expr* copy();
	void swap(Expr& e1,Expr& e2);
	Expr* append(Expr *expr);
	static Expr* appendTo(Expr *expr,Expr *next);
    Expr* appendChild(Expr *expr);
	Expr* prependChild(Expr *expr);
	Expr* insert(Expr *parent, Expr *child);
	Expr* preinsert(Expr *parent, Expr *child);
	Expr* replace(Expr *expr);
	Expr* isolate();
	Expr* getChild(int index);
	friend void swap(Expr& e1,Expr& e2);

	Expr& operator = (const Expr&);
	bool operator == (const Expr&);

	friend void swap(Expr&,Expr&);
};
#endif
