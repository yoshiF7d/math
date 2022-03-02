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

#define HASH_DEPTH_BITMASK ((long)0xffff << 48)
#define HASH_WIDTH_BITMASK ((long)0xffff << 32)
#define HASH_PATTERN_BITMASK 0x80000000
#define HASH_MAIN_BITMASK 0x7fffffff

#define KNRM  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT "\x1B[37m"

class Symbol;
class Expr{
  public:
	Expr *next;
	Expr *previous;
	Expr *parent;
	Expr *child;
	Symbol *symbol;
	Data *data;
	long hash;
	
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
	int length();
	Expr* last();
	int childCount();
	long setHash();
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
	
	static Expr* pushTo(Expr *stack,Expr *expr);
	Expr* push(Expr *expr);
	Expr* pop();
	Expr* top();
	
	friend void swap(Expr& e1,Expr& e2);
	Expr& operator = (const Expr&);
	bool operator == (const Expr&);

	friend void swap(Expr&,Expr&);
  private:
	void init();
	long str_to_hash(std::string);
	long scramble(long);
};
#endif
