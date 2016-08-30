#pragma once
#include <string>
#include <iostream>
#include "AITypes\AITemplate.h"
#include "../Components/ScriptComponent.h"

struct Spell {
	int spellId;
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
	
	Spell() : spellId(0xFFFF), name(""), casttime(0), cooldown(0), duration(0), lastcast(0), graphic("") {
	}

	Spell(int spellId, std::string name, int casttime, int cooldown, int duration, std::string graphic, std::vector<std::vector<ScriptStep>> script) :
		spellId(spellId), name(name), casttime(casttime), cooldown(cooldown), duration(duration), lastcast(0), graphic(graphic), spellscript(script), cancelable(false) {
	}

	Spell(int spellId, std::string name, int casttime, int cooldown, int duration, std::string graphic, std::vector<std::vector<ScriptStep>> script, bool cancelable) :
		spellId(spellId), name(name), casttime(casttime), cooldown(cooldown), duration(duration), lastcast(0), graphic(graphic), spellscript(script), cancelable(cancelable) {
	}

	Spell(const Spell& s) :
		spellId(s.spellId), name(s.name), casttime(s.casttime), cooldown(s.cooldown), duration(s.duration), lastcast(s.lastcast), graphic(s.graphic), spellscript(s.spellscript), cancelable(s.cancelable) {
	}
};


