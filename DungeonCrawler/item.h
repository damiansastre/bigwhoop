#pragma once
#include "mapobject.h"

/*
Item
Items are Map Objects that are able to be pickedup/used.
*/
class Item : public MapObject
{
public:
    Item();
    ~Item();
    
    virtual ActionResponse TriggerAction();

protected:
	std::string name;
};
