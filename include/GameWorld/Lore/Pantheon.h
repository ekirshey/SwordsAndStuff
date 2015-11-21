#pragma once
// THis class handles randomly generating the Gods of the game

#include <string>
#include <vector>

struct God
{
	std::string name;
	std::string domain;
};

class Pantheon
{
public:
	Pantheon();
	~Pantheon();

	void BuildPantheon();

private:
	int numberofgods_;
	std::vector<God> god_;
};

