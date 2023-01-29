#pragma once
#include <iostream>

#include "tvector2d.h"
#include "tarray.h"
#include "action_response.h"

class Player;
class MapObject
{
public:
	MapObject();
	~MapObject();

	int GetID();

	bool operator==(const MapObject& other);
	
	// Positioning
	virtual void SetPosition(TVector2D<int> position);
	virtual TVector2D<int> GetPosition();
	virtual bool IsPosition(TVector2D<int> position);
	
	// Rendering	
	virtual bool ShouldRender() ;
	virtual TVector2D<int>& GetSpritePosition();

	// Actions
	virtual ActionResponse TriggerAction();
	virtual std::string GetNotification();
	
protected:
	int id = rand(); // TODO: This needs to be game unique.
	TVector2D<int> position;
	TVector2D<int> sprite_offset;
	std::string notification = "";
};