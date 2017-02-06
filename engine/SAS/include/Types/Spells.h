#pragma once
#include <string>
#include <iostream>
#include "AITypes/AITemplate.h"
#include "Components/ScriptComponent.h"
#include "SpellMotion.h"

struct Spell {
	int spellId;
	std::string name;
	int casttime;
	int cooldown;
	int duration;
	int lastcast;	// Book keeping. Since I'm making copies of spells instead of using pointers I can modify them
	bool cancelable;
	std::string graphic;
	// NO. NOT GOING TO WORK! Needs to be mutable!
	std::shared_ptr<SpellMotion> motion;
	//std::unique_ptr<AITemplate> ai;
	//interruptible??
	
	Spell() 
		: spellId(0xFFFF)
		, name("")
		, casttime(0)
		, cooldown(0)
		, duration(0)
		, lastcast(0)
		, graphic("") 
	{
	}

	Spell(int spellId, std::string name, int casttime, int cooldown, int duration, std::string graphic, ScriptedMotion::Script script) 
		: spellId(spellId)
		, name(name)
		, casttime(casttime)
		, cooldown(cooldown)
		, duration(duration)
		, lastcast(0)
		, graphic(graphic)
		, motion(std::make_shared<ScriptedMotion>(script))
		, cancelable(false) 
	{
	}

	Spell(int spellId, std::string name, int casttime, int cooldown, int duration, std::string graphic, std::vector<std::vector<ScriptStep>> script, bool cancelable) 
		: spellId(spellId)
		, name(name)
		, casttime(casttime)
		, cooldown(cooldown)
		, duration(duration)
		, lastcast(0)
		, graphic(graphic)
		, motion(std::make_shared<ScriptedMotion>(script))
		, cancelable(cancelable) 
	{
	}

	Spell(const Spell& s) 
		: spellId(s.spellId)
		, name(s.name)
		, casttime(s.casttime)
		, cooldown(s.cooldown)
		, duration(s.duration)
		, lastcast(s.lastcast)
		, graphic(s.graphic)
		, motion(s.motion)
		, cancelable(s.cancelable) 
	{
	}

	void SetMotionComponents(ECSManager* ecs, uint_fast64_t id, uint_fast64_t casterid) const {
		motion->SetMotionComponents(ecs, id, casterid);
	}
};


