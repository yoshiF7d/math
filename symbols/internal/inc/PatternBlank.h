#include <Expr.h>
#include <Symbol.h>
class PatternBlank : public Symbol{
public :
	PatternBlank();
	Expr* preEvaluate(Expr* expr) override;	void printdoc() override;

};
