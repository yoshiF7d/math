#ifndef PARSER_H
#define PARSER_H
#include <SymbolTable.h>
#include <Expr.h>
#include <cctype>
#include <iostream>

class Parser{
  private:
	class Tokenizer{
	  private:
		enum ExpType{False=0,Plus,Minus};
		ExpType readexp();
		bool readint();
		Expr* readnum();
		Expr* readsymbol();
		Expr* readstring();
	  public:
		Expr *optree;
		std::string string;
		std::string::iterator current;
		Tokenizer();
		~Tokenizer();
		void set(std::string string);
		Expr *read();
	};
	Tokenizer *tokenizer;
	Expr *root;
	Expr *previous;
	Expr *current;
	Symbol *end;
	void push(Expr *expr);
	void pushToRoot(Expr *expr);
	void pushDirect(Expr *expr);
	void setRoot(Expr *expr);
	Expr* removeBrackets(Expr* expr);
  public:
	Parser();
	Parser(Tokenizer *tokenizer,Symbol *end);
	void finish();
	~Parser();
	Expr *parse();
	void set(std::string string);
	void print();
};
#endif 
