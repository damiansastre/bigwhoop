#include "key.h"
#include "item_sprite_offset.h"

Key::Key()
{
	sprite_offset = { KEY_SPRITE_OFFSET_X , KEY_SPRITE_OFFSET_Y };
	name = "Key";
}

Key::~Key()
{
}
