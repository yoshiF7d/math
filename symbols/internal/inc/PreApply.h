#include <Expr.h>
#include <Symbol.h>
class PreApply : public Symbol{
public :
	PreApply();
	Expr* preEvaluate(Expr* expr) override;	void printdoc() override;

};
