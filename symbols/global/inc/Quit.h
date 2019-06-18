#include <Expr.h>
#include <Symbol.h>
class Quit : public Symbol{
public :
	Quit();
	Expr* function(Expr* expr) override;	void printdoc() override;

};
