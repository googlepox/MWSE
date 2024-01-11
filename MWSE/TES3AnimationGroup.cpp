#include "TES3AnimationGroup.h"

namespace TES3 {
	const auto TES3_AnimationGroup_calcNoteTimes = reinterpret_cast<void(__thiscall*)(AnimationGroup*)>(0x492B70);
	void AnimationGroup::calcNoteTimes() {
		TES3_AnimationGroup_calcNoteTimes(this);
	}

	AnimationGroup* AnimationGroup::findGroup(AnimGroupID id) {
		for (auto iter = this; iter; iter = iter->nextGroup) {
			if (iter->groupId == id) {
				return iter;
			}
		}
		return nullptr;
	}

	const auto TES3_data_animGroupActionClasses = reinterpret_cast<int*>(0x78B0A8);
	AnimGroupActionClass AnimationGroup::getActionClass(AnimGroupID id) {
		int actionClass = TES3_data_animGroupActionClasses[int(id)];
		return AnimGroupActionClass(actionClass);
	}

	nonstd::span<int> AnimationGroup::getActionFrames() {
		return { actionFrames, actionCount };
	}

	nonstd::span<float> AnimationGroup::getActionTimings() {
		return { actionTimings, actionCount };
	}

	nonstd::span<AnimationGroup::SoundGenKey> AnimationGroup::getSoundGenKeys() {
		return { soundGenKeys, soundGenCount };
	}

	const auto TES3_parseSeqTextKeysToAnimGroups = reinterpret_cast<int(__cdecl*)(NI::Sequence*, const char*, AnimationGroup**)>(0x4C30F0);
	int KeyframeDefinition::parseSeqTextKeysToAnimGroups(NI::Sequence* sequence, const char* meshPath, AnimationGroup** pAnimationGroups) {
		return TES3_parseSeqTextKeysToAnimGroups(sequence, meshPath, pAnimationGroups);
	}

}

MWSE_SOL_CUSTOMIZED_PUSHER_DEFINE_TES3(TES3::AnimationGroup)
