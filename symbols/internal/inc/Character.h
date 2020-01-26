#include <Expr.h>
#include <Symbol.h>
class Character : public Symbol{
public :
	Character();

	Data* createData() override;

};
struct CharacterData : Data{
    int character;
	~CharacterData();
	bool operator ==(const Data& data) override;
	std::string toString() override;
};

