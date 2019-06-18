#include <Expr.h>
#include <Symbol.h>
class Number : public Symbol{
public :
	Number();
	static Expr* parse(std::string::iterator *current);	void printdoc() override;

};
