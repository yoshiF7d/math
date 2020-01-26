#include <SymbolList.h>
#include <SymbolTable.h>
Character::Character() : Symbol("Character","",internal_Character,1000,Protected,0,"",""){}
Data* Character::createData(){return new CharacterData ();}
bool CharacterData::operator ==(const Data& data){
	return this->character == static_cast<const CharacterData&>(data).character;
};
std::string CharacterData::toString(){
	return std::string(1,character);
}
CharacterData::~CharacterData(){};

