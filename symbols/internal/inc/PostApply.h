#include <Expr.h>
#include <Symbol.h>
class PostApply : public Symbol{
public :
	PostApply();
	Expr* preEvaluate(Expr* expr) override;	void printdoc() override;

};
