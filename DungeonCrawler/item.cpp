#include "item.h"
Item::Item()
{
}
Item::~Item()
{

}
// Returns basic ActionResponse for all items. PICKUP.
ActionResponse Item::TriggerAction()
{
	return ActionResponse{ true, GetNotification(), ActionType::PICKUP };
}
