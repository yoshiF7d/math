#ifndef PARSER_H
#define PARSER_H
#include <Expr.h>
#include <cctype>
#include <iostream>

class Parser{
  private:
	class Tokenizer{
	  public:
		Expr *optree;
		std::string string;
		std::string::iterator current;
		Tokenizer();
		~Tokenizer();
		void set(std::string string);
		Expr *read(Symbol *endtoken);
	};
	Tokenizer *tokenizer;
	Expr *root;
	Expr *current;
	Symbol *end;
	void push(Expr *expr);
	void pushToRoot(Expr *expr);
	void pushDirect(Expr *expr);
	void pushBracket(Expr *expr);
	void setRoot(Expr *expr);
	Expr* preEvaluate(Expr* expr);
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
