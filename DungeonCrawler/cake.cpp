#include <string>

#include "cake.h"
#include "tvector2d.h"


// Setting cake initial attributes
Cake::Cake()
{
	sprite_offset = { CAKE_SPRITE_OFFSET_X, CAKE_SPRITE_OFFSET_Y };
	value = 20,
    name = "Cake";

}
// Setting a Cake with a specifiic name and location.
Cake::Cake(std::string name, TVector2D<int> position)
{
	this->name = name;
	this->position = position;
	Cake();
}

Cake::~Cake()
{
}

ActionResponse Cake::Consume()
{
	return { false, value, "You Heal for " + std::to_string(value), ActionType::HEAL };
}

