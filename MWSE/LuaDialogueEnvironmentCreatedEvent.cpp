#include "LuaDialogueEnvironmentCreatedEvent.h"

#include "TES3Reference.h"
#include "TES3Sound.h"

#include "LuaManager.h"

namespace mwse::lua::event {
	DialogueEnvironmentCreatedEvent::DialogueEnvironmentCreatedEvent(sol::environment environment) :
		GenericEvent("dialogueEnvironmentCreated"),
		m_Environment(environment)
	{

	}

	sol::table DialogueEnvironmentCreatedEvent::createEventTable() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto eventData = state.create_table();

		eventData["environment"] = m_Environment;

		return eventData;
	}
}
