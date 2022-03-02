#ifndef DATA_H
#define DATA_H
struct Data{
	 virtual ~Data(){};
	 virtual bool operator ==(const Data& data){return false;};
	 virtual std::string toString(){return "";};
	 virtual long hash(){return 0;};
};
#define castData(T,data) (static_cast<T*>(data))
#endif