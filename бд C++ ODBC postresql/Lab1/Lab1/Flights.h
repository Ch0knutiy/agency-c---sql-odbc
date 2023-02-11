#include <iostream>

using namespace std;

class Flights
{
public:
	Flights();
	Flights(
		string num,
		string date,
		string time,
		string aircraft,
		string _class,
		int free);
	Flights(const Flights& other);
	~Flights();

	Flights& operator = (Flights other);

	void setNum(string num);
	void setDate(string date);
	void setTime(string time);
	void setAircraft(string aircraft);
	void setClass(string _class);
	void setFree(int free);

	string getNum();
	string getDate();
	string getTime();
	string getAircraft();
	string getClass();
	int getFree();

private:
	string num;
	string date;
	string time;
	string aircraft;
	string _class;
	int free;
};

