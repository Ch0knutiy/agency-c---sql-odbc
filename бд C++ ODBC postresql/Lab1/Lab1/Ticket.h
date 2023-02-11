#include <iostream>
#include <vector>
#include "Client.h"

using namespace std;

class Ticket
{
public:
	Ticket();
	Ticket(long id,
		int seat,
		Flights* flights,
		Client* client);
	Ticket(const Ticket& other);
	~Ticket();

	Ticket& operator = (Ticket other);

	void setId(int id);
	void setSeat(int seat);
	void setFlights(Flights* flights);
	void setClient(Client* client);

	int getId();
	int getSeat();
	Flights* getFlights();
	Client* getClient();

private:
	int id;
	int seat;
	Flights* flights;
	Client* client;
};

