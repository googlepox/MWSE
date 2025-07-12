#include "LuaPotionBrewedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Alchemy.h"
#include "TES3Apparatus.h"
#include "TES3Ingredient.h"
#include "TES3MobilePlayer.h"
#include "TES3WorldController.h"

namespace mwse::lua::event {
	PotionBrewedEvent::PotionBrewedEvent(TES3::Alchemy* object, const TES3::AlchemyBrewingItems& items) :
		GenericEvent("potionBrewed"),
		m_Object(object),
		m_Items(items)
	{

	}

	sol::table PotionBrewedEvent::createEventTable() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto eventData = state.create_table();

		eventData["object"] = m_Object;

		// Add the apparatus used.
		eventData["alembic"] = m_Items.alembic;
		eventData["calcinator"] = m_Items.calcinator;
		eventData["mortar"] = m_Items.mortar;
		eventData["retort"] = m_Items.retort;

		// Add the ingredients used.
		sol::table ingredients = state.create_table();
		if (m_Items.ingredient1) ingredients.add(m_Items.ingredient1);
		if (m_Items.ingredient2) ingredients.add(m_Items.ingredient2);
		if (m_Items.ingredient3) ingredients.add(m_Items.ingredient3);
		if (m_Items.ingredient4) ingredients.add(m_Items.ingredient4);
		eventData["ingredients"] = ingredients;

		return eventData;
	}
}
