#pragma once
#include "AITypes\AITemplate.h"

struct Spell {
	std::string name;
	int lastcast;	// Book keeping. Since I'm making copies of spells instead of using pointers I can modify them
	int casttime;
	int cooldown;
	std::string graphic;
	//std::unique_ptr<AITemplate> ai;
	//interruptible??
	Spell() {}
	Spell(std::string name, double casttime, double cooldown, std::string graphic) :
		name(name), casttime(casttime), cooldown(cooldown), graphic(graphic), lastcast(0) {
	}

	Spell(const Spell& s) :
		name(s.name), casttime(s.casttime), cooldown(s.cooldown), graphic(s.graphic), lastcast(s.lastcast) {

	}
};


