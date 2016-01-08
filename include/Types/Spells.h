#pragma once
#include <string>
#include "AITypes\AITemplate.h"

struct Spell {
	std::string name;
	int casttime;
	int cooldown;
	int duration;
	int lastcast;	// Book keeping. Since I'm making copies of spells instead of using pointers I can modify them
	std::string graphic;
	//std::unique_ptr<AITemplate> ai;
	//interruptible??
	
	Spell() : name(""), casttime(0), cooldown(0), duration(0), lastcast(0), graphic("") {}

	Spell(std::string name, int casttime, int cooldown, int duration, std::string graphic) :
		name(name), casttime(casttime), cooldown(cooldown), duration(duration), lastcast(0), graphic(graphic) {
	}

	Spell(const Spell& s) :
		name(s.name), casttime(s.casttime), cooldown(s.cooldown), duration(s.duration), lastcast(s.lastcast), graphic(s.graphic) {

	}
};


