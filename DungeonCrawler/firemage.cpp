#include "firemage.h"

FireMage::FireMage()
{
	spritePosition = TVector2D<int>(377, 26);
	attackPower = 1000;
	health = 1000;
	name = "Fire Mage";
}
FireMage::~FireMage()
{
	
}

void FireMage::Kill()
{
	SetSprite(TVector2D<int>(326, 143));
}
