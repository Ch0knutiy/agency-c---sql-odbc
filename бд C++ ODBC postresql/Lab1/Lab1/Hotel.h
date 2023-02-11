#include <iostream>

using namespace std;

class Hotel
{
public:
	Hotel();
	Hotel(long id,
		string name,
		int _class,
		string categories);
	Hotel(const Hotel& other);
	~Hotel();

	Hotel& operator = (Hotel other);

	void setId(int id);
	void setName(string name);
	void setClass(int _class);
	void setCategories(string categories);

	int getId();
	string getName();
	int getClass();
	string getCategories();

private:
	int id;
	string name;
	int _class;
	string categories;
};
