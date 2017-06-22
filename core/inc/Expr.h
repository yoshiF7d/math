#ifndef Expr_H
#define Expr_H
/*double : 64 = 1 + 11 + 52 (sign,exponent,prec)*/
/*used for overflow prediction*/
#define R64_LIMIT 52
#define I32_LIMIT 31
#define LOG2 0.301029995663981
#define PREC_SYMBOL -1
#define PREC_MATCH -2

enum en_eflag{
	ef_func=0x0001, /*to distinguish expressions like a[] and a*/
	ef_full=0x0002, /*to distinguish expressions like ^ and Power*/
	ef_mark=0x0004, /*this flag can be used in any way. marked node become red color when printed with TreeForm_mod*/
};

class Symbol;
union Data;

class Expr;

class Atom : public Expr{
  public:
	Symbol *symbol;
	Data data;
}

class List : public Expr{
  public:
	Expr *child;
}

class Expr{
  public:
	Expr *next;
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