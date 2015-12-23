#pragma once
/*
Component                       ID          Notes
************************************************************************
PositionComponent               0x01
VelocityComponent               0x02
RenderComponent                 0x04
TargetingComponent              0x08        
InputComponent                  0x10
AngleComponent                  0x20
ShootingComponent               0x40
BoundingRectangleComponent      0x80
InventoryComponent              0x100
ItemStatsComponent              0x200       NOT SURE IF THIS WILL STAY A COMPONENT
RPGStatsComponent               0x400

*/

#define PositionComponentID               0x01
#define VelocityComponentID               0x02
#define RenderComponentID                 0x04
#define TargetingComponentID              0x08       
#define InputComponentID                  0x10
#define AngleComponentID                  0x20
#define ShootingComponentID               0x40
#define BoundingRectangleComponentID      0x80
#define InventoryComponentID              0x100
#define ItemStatsComponentID              0x200       // NOT SURE IF THIS WILL STAY A COMPONENT
#define RPGStatsComponentID               0x400
#define CollisionComponentID			  0x800
#define SpellbookComponentID			  0x1000
#define SpellCastingComponentID			  0x2000