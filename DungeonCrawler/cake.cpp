#include "cake.h"
#include "tvector2d.h"

// Setting cake initial attributes
Cake::Cake()
{
	sprite_offset = { CAKE_SPRITE_OFFSET_X, CAKE_SPRITE_OFFSET_Y };
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

