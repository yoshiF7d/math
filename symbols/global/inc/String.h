#include <Expr.h>
#include <Symbol.h>
class String : public Symbol{
public :
	String();
	static Expr *parse(std::string::iterator *current,std::string::iterator end);
	static Expr *create(std::string string);	void printdoc() override;

	Data* createData() override;

};
struct StringData : Data{
	bool initialized;
	std::string string;
	StringData();
	StringData(std::string);
	~StringData();
	std::string toString() override;
};

