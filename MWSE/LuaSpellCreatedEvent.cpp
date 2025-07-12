#include "LuaSpellCreatedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Spell.h"

namespace mwse::lua::event {
	SpellCreatedEvent::SpellCreatedEvent(TES3::Spell* spell, const char* source) :
		GenericEvent("spellCreated"),
		m_Spell(spell),
		m_Source(source)
	{

	}

	sol::table SpellCreatedEvent::createEventTable() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto eventData = state.create_table();

		eventData["spell"] = m_Spell;
		eventData["source"] = m_Source;

		return eventData;
	}

	sol::object SpellCreatedEvent::getEventOptions() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto options = state.create_table();

		options["filter"] = m_Source;

		return options;
	}
}
