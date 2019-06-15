#include <Expr.h>
#include <Symbol.h>
class String : public Symbol{
public :
	String();
	static Expr *create(std::string string);
Data* createData() override;

};
struct StringData : Data{
	std::string string;
	StringData();
	StringData(std::string);
	~StringData();
};

