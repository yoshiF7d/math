#ifndef Expr_H
#define Expr_H
/*double : 64 = 1 + 11 + 52 (sign,exponent,prec)*/
/*used for overflow prediction*/
#define R64_LIMIT 52
#define I32_LIMIT 31
#define LOG2 0.301029995663981
#define PREC_SYMBOL -1
#define PREC_MATCH -2

class Symbol;
union Data;

class Expr{
  public:
	Expr *next;
	Expr *previous;
	Expr *parent;
	Expr *child;
	Symbol *symbol;
	Data data;
	
	Expr(int id);
	Expr(string str);
	Expr(Symbol *symbol);
	Expr(const Expr& other);
	
	void deleteRoot();
	void deleteLast();
	void deleteChild(Expr *child);
	void deleteChildren();
	int getLength();
	string toString();
	static Expr append(Expr *expr);
	void appendChild(Expr *expr);
	void prependChild(Expr *expr);
	Expr* insert(Expr *parent, Expr *child);
	Expr getChild();
	//Expr copy();
	//Expr copyRoot();
	
	Expr& operator = (const Expr&);
	bool operator == (const Expr&, const Expr&);
	
	friend void swap(Expr&,Expr&);
}
#endif