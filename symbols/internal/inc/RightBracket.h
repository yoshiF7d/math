#include <Expr.h>
#include <Symbol.h>
class RightBracket : public Symbol{
public :
	RightBracket();

Data* createData() override;

};
struct RightBracketData : Data{
	Expr *expr;
	RightBracketData();
	~RightBracketData();
	bool operator ==(const Data& data) override;
	std::string toString() override;
};

