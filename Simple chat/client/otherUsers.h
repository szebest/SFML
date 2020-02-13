#ifndef OTHERUSERS_H
#define OTHERUSERS_H

#include <string>

class OtherUsers
{
public:
	OtherUsers(int id, std::string name);

	void setID(int id) { m_id = id; }
	int getID() { return m_id; }

	void setName(std::string name) { m_name = name; }
	std::string getName() { return m_name; }
private:
	int m_id;
	std::string m_name;
};

#else
#endif