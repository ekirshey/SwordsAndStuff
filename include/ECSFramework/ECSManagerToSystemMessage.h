#ifndef ecsmanager_TOSYSTEMMESSAGE_H
#define ecsmanager_TOSYSTEMMESSAGE_H

// Message Types
#define ENTITYADDED 0x0
#define ENTITYREMOVED 0x1

// Message format for ecsmanager_ to system messages
struct ecsmanager_ToSystemMessage
{
    int messagetype;    // Message type i.e. Add Remove etc
    int entity;         // Entity the Message pertains to
};


#endif // ecsmanager_TOSYSTEMMESSAGE_H
