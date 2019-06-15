#ifndef DATA_H
#define DATA_H
struct Data{
	 virtual ~Data(){};
	 virtual bool operator ==(const Data& data){return false;};
	 virtual std::string toString(){return "";};
};
#define getData(T,data,content) (static_cast<T*>(data))->content
#endif