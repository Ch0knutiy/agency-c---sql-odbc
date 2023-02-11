#include <iostream>

using namespace std;

class Transfer
{
public:
	Transfer();
	Transfer(long id,
		long num,
		string post,
		string reason,
		string date);
	Transfer(const Transfer& other);
	~Transfer();

	Transfer& operator = (Transfer other);

	void setId(long id);
	void setNum(long num);
	void setPost(string post);
	void setReason(string reason);
	void setDate(string date);

	int getId();
	long getNum();
	string getPost();
	string getReason();
	string getDate();

private:
	int id;
	long num;
	string post;
	string reason;
	string date;
};
