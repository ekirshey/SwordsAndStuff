#ifndef MONSTERSPAWNER_H
#define MONSTERSPAWNER_H

#include <vector>
#include <string>
#include <cstdint>

class ECSManager;

class MonsterSpawner
{
    public:
        MonsterSpawner( std::string tag, int maxactivemonsters, ECSManager* ecsmanager);
        virtual ~MonsterSpawner() {}

        void SpawnMonsters();
    private:
        int maxactivemonsters_;
        std::string tag_;
        std::vector<uint_fast64_t>* taggedentities_;
        ECSManager* ecsmanager_;
};

#endif // MONSTERSPAWNER_H
