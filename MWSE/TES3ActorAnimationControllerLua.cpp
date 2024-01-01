#include "TES3ActorAnimationControllerLua.h"

#include "LuaUtil.h"
#include "LuaManager.h"

#include "TES3ActorAnimationController.h"
#include "TES3AnimationGroup.h"
#include "TES3MobileActor.h"

#include "NIKeyframeManager.h"

namespace mwse::lua {
	void bindTES3ActorAnimationController() {
		// Get our lua state.
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		auto& state = stateHandle.state;

		// Bind TES3::ActorAnimationController
		{
			// Start our usertype.
			auto usertypeDefinition = state.new_usertype<TES3::ActorAnimationController>("tes3actorAnimationController");
			usertypeDefinition["new"] = sol::no_constructor;

			// Basic property binding.
			usertypeDefinition["alphaProperty"] = &TES3::ActorAnimationController::alphaProperty;
			usertypeDefinition["animGroupIdle"] = &TES3::ActorAnimationController::animGroupIdle;
			usertypeDefinition["animGroupIdle2"] = &TES3::ActorAnimationController::animGroupIdle2;
			usertypeDefinition["animGroupMovement"] = &TES3::ActorAnimationController::animGroupMovement;
			usertypeDefinition["attachTiming"] = &TES3::ActorAnimationController::attachTiming;
			usertypeDefinition["attackFollowTiming"] = &TES3::ActorAnimationController::attackFollowTiming;
			usertypeDefinition["groundPlaneRotation"] = &TES3::ActorAnimationController::groundPlaneRotation;
			usertypeDefinition["hitTiming"] = &TES3::ActorAnimationController::hitTiming;
			usertypeDefinition["animationData"] = &TES3::ActorAnimationController::animationData;
			usertypeDefinition["materialProperty"] = &TES3::ActorAnimationController::materialProperty;
			usertypeDefinition["maxAttackTiming"] = &TES3::ActorAnimationController::maxAttackTiming;
			usertypeDefinition["minAttackTiming"] = &TES3::ActorAnimationController::minAttackTiming;
			usertypeDefinition["minHitTiming"] = &TES3::ActorAnimationController::minHitTiming;
			usertypeDefinition["mobile"] = sol::readonly_property(&TES3::ActorAnimationController::mobileActor);
			usertypeDefinition["patchedOverrideState"] = &TES3::ActorAnimationController::patchedOverrideState;
			usertypeDefinition["remainingBlockTime"] = &TES3::ActorAnimationController::remainingBlockTime;
			usertypeDefinition["shouldJump"] = &TES3::ActorAnimationController::shouldJump;
			usertypeDefinition["speedMultiplier"] = &TES3::ActorAnimationController::speedMultiplier;
			usertypeDefinition["startTime"] = &TES3::ActorAnimationController::startTime;
			usertypeDefinition["strikeWhenAttackSwingReaches"] = &TES3::ActorAnimationController::strikeWhenAttackSwingReaches;
			usertypeDefinition["verticalRotation"] = &TES3::ActorAnimationController::verticalRotation;
			usertypeDefinition["vertexColorProperty"] = &TES3::ActorAnimationController::vertexColorProperty;

			// Custom properties.
			usertypeDefinition["weaponSpeed"] = sol::property(&TES3::ActorAnimationController::getWeaponAnimSpeed, &TES3::ActorAnimationController::setWeaponAnimSpeed);

			// Basic function binding.
			usertypeDefinition["calculateAttackSwing"] = &TES3::ActorAnimationController::calculateAttackSwing;
		}

		// Bind TES3::KeyframeDefinition
		{
			// Start our usertype.
			auto usertypeDefinition = state.new_usertype<TES3::KeyframeDefinition>("tes3keyframeDefinition");
			usertypeDefinition["new"] = sol::no_constructor;

			// Basic property binding.
			usertypeDefinition["filename"] = sol::readonly_property(&TES3::KeyframeDefinition::filename);
			usertypeDefinition["sequences"] = sol::readonly_property([](TES3::KeyframeDefinition& kf) { return std::ref(kf.sequences); });
			usertypeDefinition["animationGroup"] = sol::readonly_property(&TES3::KeyframeDefinition::animationGroup);
			usertypeDefinition["groupCount"] = sol::readonly_property(&TES3::KeyframeDefinition::groupCount);
			usertypeDefinition["refCount"] = sol::readonly_property(&TES3::KeyframeDefinition::refCount);
		}
	}
}
