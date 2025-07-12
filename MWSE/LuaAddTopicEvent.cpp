#include "LuaAddTopicEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Dialogue.h"

namespace mwse::lua::event {
	AddTopicEvent::AddTopicEvent(TES3::Dialogue* topic) :
		GenericEvent("topicAdded"),
		m_Topic(topic)
	{

	}

	sol::table AddTopicEvent::createEventTable() {
		const auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.getState();
		auto eventData = state.create_table();

		eventData["topic"] = m_Topic;

		return eventData;
	}
}
