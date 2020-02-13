#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	void setID(int id) { m_id = id; m_isReady = true; }
	int getID() { return m_id; }

	bool isReady() { return m_isReady; }

	void setName(std::string name) { m_name = name; }
	std::string getName() { return m_name; }

private:
	int m_id = -1;
	bool m_isReady;
	std::string m_name;
};

#else
#endif