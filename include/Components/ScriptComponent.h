#pragma once
#include <vector>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

struct ScriptStep{
	int dX;
	int dY;
	int steplength;
		// May or may not have an anchor
	ScriptStep() {}
	ScriptStep(int x, int y, int hold) : 
		dX(x), dY(y), steplength(hold) {}
};

class ScriptComponent : public Component
{
	public:
		static const uint_fast64_t ID = ScriptComponentID;

		ScriptComponent(std::vector<ScriptStep> v, uint_fast64_t anchor) : script_(v) , anchor_(anchor), currentstep_(0), stepstarttime_(0) {}
		ScriptComponent(std::vector<ScriptStep> v) : script_(v), anchor_(-1), currentstep_(0), stepstarttime_(0) {}
		ScriptComponent(const ScriptComponent& c) : script_(c.script_), anchor_(c.anchor_), currentstep_(c.currentstep_), stepstarttime_(c.stepstarttime_) {}

		~ScriptComponent() {}

		uint_fast64_t UniqueBits() const { return ID; }

		const std::vector<ScriptStep>& ScriptVector() const { return script_; }
		void AddScriptStep(const ScriptStep& s) { script_.push_back(s); }

		uint_fast64_t GetAnchor() const { return anchor_;  }
		void GetAnchor(uint_fast64_t entity) { anchor_ = entity; }

		int StepStartTime() { return stepstarttime_; }
		void SetStepStartTime(int time) { stepstarttime_ = time; }

		int CurrentStep() { return currentstep_; }
		void IncCurrentStep() { currentstep_++; }

	private:		
		std::vector<ScriptStep> script_;
		uint_fast64_t anchor_;
		int currentstep_;
		int stepstarttime_;

};