#pragma once
#include <string>

enum BuffType {STATIC,CONDITIONAL};
enum BuffCategory {SELF,TARGET};
enum BuffSpecific {STAT};

struct Buff
{
	std::string name;
	Result buffresult;
};


struct ConditionalBuff : public Buff
{
	
};

struct Condition
{

};

struct Result
{

};