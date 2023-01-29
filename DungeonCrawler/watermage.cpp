#include "watermage.h"
#include "dc_const.h"
WaterMage::WaterMage()
{
	spritePosition = TVector2D<int>(WATER_MAGE_SPRITE_OFFSET_X, WATAR_MAGE_SPRITE_OFFSET_Y);
	attackPower = 30;
	health = 30;
	name = "Water Mage";
}
WaterMage::~WaterMage()
{

}

void WaterMage::Kill()
{
	SetSprite(TVector2D<int>(WATAR_MAGE_SPRITE_OFFSET_X_D, WATAR_MAGE_SPRITE_OFFSET_Y_D));
}





