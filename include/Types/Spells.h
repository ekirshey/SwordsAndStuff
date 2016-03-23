#pragma once
#include <string>
#include "AITypes\AITemplate.h"
#include "../Components/ScriptComponent.h"

struct Spell {
	std::string name;
	int casttime;
	int cooldown;
	int duration;
	int lastcast;	// Book keeping. Since I'm making copies of spells instead of using pointers I can modify them
	bool cancelable;
	std::string graphic;
	std::vector<std::vector<ScriptStep>> spellscript;
	//std::unique_ptr<AITemplate> ai;
	//interruptible??
	
	Spell() : name(""), casttime(0), cooldown(0), duration(0), lastcast(0), graphic("") {}

	Spell(std::string name, int casttime, int cooldown, int duration, std::string graphic, std::vector<std::vector<ScriptStep>> script) :
		name(name), casttime(casttime), cooldown(cooldown), duration(duration), lastcast(0), graphic(graphic), spellscript(script), cancelable(false) {
	}

	Spell(std::string name, int casttime, int cooldown, int duration, std::string graphic, std::vector<std::vector<ScriptStep>> script, bool cancelable) :
		name(name), casttime(casttime), cooldown(cooldown), duration(duration), lastcast(0), graphic(graphic), spellscript(script), cancelable(cancelable) {
	}

	Spell(const Spell& s) :
		name(s.name), casttime(s.casttime), cooldown(s.cooldown), duration(s.duration), lastcast(s.lastcast), graphic(s.graphic), spellscript(s.spellscript), cancelable(s.cancelable) {

	}
};


