#include "LuaLeveledItemPickedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Actor.h"
#include "TES3MobileActor.h"
#include "TES3Reference.h"
#include "TES3Inventory.h"
#include "TES3LeveledList.h"

namespace mwse::lua::event {
	LeveledItemPickedEvent::LeveledItemPickedEvent(TES3::LeveledItem* list, TES3::PhysicalObject* vanillaResult) :
		ObjectFilteredEvent("leveledItemPicked", list),
		m_List(list),
		m_Result(vanillaResult)
	{

	}

	sol::table LeveledItemPickedEvent::createEventTable() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto eventData = state.create_table();

		eventData["list"] = m_List;
		eventData["pick"] = m_Result;

		if (m_Reference) {
			eventData["spawner"] = m_Reference;
		}

		return eventData;
	}
	TES3::Reference* LeveledItemPickedEvent::m_Reference = nullptr;
}
