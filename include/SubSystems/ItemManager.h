#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "../ECSFramework/ECSManager.h"

class ItemManager
{
    public:
        ItemManager();
        virtual ~ItemManager();

        void Process();
        ECSManager* GetECSManager() {return &ecsmanager_;}
    private:
        ECSManager ecsmanager_;
};

#endif // ITEMMANAGER_H
