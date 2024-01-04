#include "TES3AnimationGroup.h"

namespace TES3 {
	nonstd::span<int> AnimationGroup::getActionFrames() {
		return { actionFrames, actionCount };
	}

	nonstd::span<float> AnimationGroup::getActionTimings() {
		return { actionTimings, actionCount };
	}

	nonstd::span<AnimationGroup::SoundGenKey> AnimationGroup::getSoundGenKeys() {
		return { soundGenKeys, soundGenCount };
	}

	const auto TES3_data_animGroupActionClasses = reinterpret_cast<int*>(0x78B0A8);
	AnimGroupActionClass AnimationGroup::getActionClass(AnimGroupID groupId) {
		int actionClass = TES3_data_animGroupActionClasses[int(groupId)];
		return AnimGroupActionClass(actionClass);
	}
}

MWSE_SOL_CUSTOMIZED_PUSHER_DEFINE_TES3(TES3::AnimationGroup)
