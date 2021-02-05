#ifndef MANAGER
#define MANAGER

#include <string>
#include <unordered_map>

template<typename Zasob>
class manager
{
public:
	manager(const std::string& _folder, const std::string& _rozszerzenie) : folder(_folder + "/"), rozszerzenie("." + _rozszerzenie)
	{

	}

	Zasob& get(const std::string& nazwa)
	{
		if (!istnieje(nazwa))
			dodaj(nazwa);

		return zasoby.at(nazwa);
	}

	void add(const std::string& nazwa)
	{
		if (!istnieje(nazwa))
			dodaj(nazwa);
	}

	bool istnieje(const std::string& nazwa) const
	{
		return zasoby.find(nazwa) != zasoby.end();
	}

	void dodaj(const std::string& nazwa)
	{
		Zasob r;

		if (!r.loadFromFile(calaNazwa(nazwa)))
		{
			Zasob nieudany;
			nieudany.loadFromFile(folder + "_fail_" + rozszerzenie);
			zasoby.insert(std::make_pair(nazwa, nieudany));
		}
		else
			zasoby.insert(std::make_pair(nazwa, r));
	}

private:
	std::string calaNazwa(const std::string& nazwa)
	{
		return folder + nazwa + rozszerzenie;
	}

	const std::string folder;
	const std::string rozszerzenie;

	std::unordered_map<std::string, Zasob> zasoby;
};

#endif