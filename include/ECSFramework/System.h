#ifndef SYSTEM_H
#define SYSTEM_H

#include <cstdint>
#include <vector>
#include <queue>
#include <string>

class ECSManager;

class System
{
public:
	static const uint_fast64_t COMPONENTIDS = 0x0;
	System(ECSManager* ecsmanager);

	virtual ~System() {}

	void Update(int elapsedtime);
	virtual void ProcessEntities() = 0;

	virtual uint_fast64_t ComponentBits() { return COMPONENTIDS; }

	virtual void AddEntity(uint_fast64_t entityid);
	virtual void RemoveEntity(uint_fast64_t entityid);

	bool ContainsEntity(uint_fast64_t entityid);    // TODO Not sure if needed
	bool ValidEntity(uint_fast64_t componentbits, uint_fast64_t SYSTEMID);

	void SetECSManager(ECSManager* ecsmanager) { ecsmanager_ = ecsmanager; }
	ECSManager* GetECSManager() { return ecsmanager_; }

	uint_fast64_t GetEntityCount() { return entitycount_; }
	void EntityCount(uint_fast64_t entitycount) { entitycount_ = entitycount; }

	std::vector<uint_fast64_t> RelevantEntities();

	int ElapsedTime() { return elapsedtime_; }
	void SetElapsedTime(int elapsedtime) { elapsedtime_ = elapsedtime; }

	std::string SystemName() { return systemname_; }
	void SetSystemName(std::string name) { systemname_ = name; }

private:
	std::vector<uint_fast64_t> relevantentities_;
	uint_fast64_t entitycount_;
	ECSManager* ecsmanager_;
	int elapsedtime_;
	std::string systemname_;	// For debugging purposes


};


#endif // SYSTEM_H
