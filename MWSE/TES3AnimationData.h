#pragma once

#include "TES3Defines.h"
#include "TES3Vectors.h"
#include "TES3AnimationGroup.h"

#include "NIDefines.h"
#include "NIPointer.h"

namespace TES3 {
	struct AnimationDataVanilla {
		struct SequenceGroup {
			NI::Sequence* lower;
			NI::Sequence* upper;
			NI::Sequence* leftArm;

			SequenceGroup() : lower(nullptr), upper(nullptr), leftArm(nullptr) {}
			~SequenceGroup() {}

			NI::Sequence* get(int section);
		};
		static_assert(sizeof(SequenceGroup) == 0xC, "TES3::AnimationAttachment::SequenceGroup failed size validation");

		NI::Node* actorNode; // 0x0
		NI::Node* movementRootNode; // 0x4
		TES3::Vector3 positionDeltaMovementRoot; // 0x8
		NI::Node* spine1Node; // 0x14
		NI::Node* spine2Node; // 0x18
		float spineAngle; // 0x1C
		NI::Node* headNode; // 0x20
		float headLookTargetAngleX; // 0x24
		float headLookTargetAngleZ; // 0x28
		float headLookAngleX; // 0x2C
		float headLookAngleZ; // 0x30
		float headLookClosestDistance; // 0x34
		AnimGroupID currentAnimGroup[3]; // 0x38
		int currentActionIndices[3]; // 0x3C
		int loopCounts[3]; // 0x48
		unsigned int flags; // 0x54
		float timing[3]; // 0x58
		float deltaTime; // 0x5C
		AnimationGroup* animationGroups[150]; // 0x68
		NI::KeyframeManager* manager; // 0x2C0
		SequenceGroup keyframeLayers[3]; // 0x2C4
		NI::Geometry* headGeometry; // 0x2E8
		float lipsyncLevel; // 0x2EC
		float timeToNextBlink; // 0x2F0
		float headMorphTiming; // 0x2F4
		float talkMorphStartTime; // 0x2F8
		float talkMorphEndTime; // 0x2FC
		float blinkMorphStartTime; // 0x300
		float blinkMorphEndTime; // 0x304
		int currentAnimGroupLayer[3];
		unsigned char animGroupLayerIndices[150]; // 0x314
		short approxRootTravelSpeeds[150]; // 0x3AA
		unsigned short patchedCastSpeed; // 0x4D6 (8.8 fixed point format)
		float movementSpeed; // 0x4D8
		float weaponSpeed; // 0x4DC
		int currentSoundGenIndices[3]; // 0x4E0
		unsigned char animGroupSoundGenCounts[150]; // 0x4EC
		AnimationGroup::SoundGenKey** animGroupSoundGens[150]; // 0x584
		AnimGroupID nextAnimGroup; // 0x7DC
		int nextLoopCount; // 0x7E0

		AnimationDataVanilla() = delete;
		~AnimationDataVanilla() = delete;

		//
		// Other related this-call functions.
		//

		AnimationDataVanilla* ctor();

		void calcRootMovement(AnimGroupID animGroup);
		void playAnimationGroupForSection(AnimGroupID animationGroup, int bodySection, int startFlag = 0, int loopCount = -1);
		void mergeAnimGroups(AnimationGroup* firstGroup, int layerIndex);
		void setHeadNode(NI::Node* head);
		bool setLayerKeyframes(KeyframeDefinition* kfData, int layerIndex, bool isBiped);
		void updateMovementDelta(float timing, Vector3* inout_startingPosition, bool dontUpdatePositionDelta);

		//
		// Custom functions.
		//

		Reference* getReference() const;

		void playAnimationGroup(AnimGroupID animationGroup, int startFlag = 0, int loopCount = -1);
		bool setOverrideLayerKeyframes(KeyframeDefinition* animData);
		bool hasOverrideAnimations() const;
		void swapAnimationGroups(AnimGroupID animationGroup1, AnimGroupID animationGroup2);

		float getCastSpeed() const;
		void setCastSpeed(float speed);

		std::reference_wrapper<decltype(currentAnimGroup)> getCurrentAnimGroups();
		std::reference_wrapper<decltype(currentActionIndices)> getCurrentActionIndices();
		std::reference_wrapper<decltype(loopCounts)> getLoopCounts();
		std::reference_wrapper<decltype(timing)> getTimings();
		std::reference_wrapper<decltype(animationGroups)> getAnimationGroups();
		std::reference_wrapper<decltype(keyframeLayers)> getKeyframeLayers();
		std::reference_wrapper<decltype(currentAnimGroupLayer)> getCurrentAnimGroupLayers();
		std::reference_wrapper<decltype(animGroupLayerIndices)> getAnimGroupLayerIndices();
		std::reference_wrapper<decltype(approxRootTravelSpeeds)> getApproxRootTravelSpeeds();
		std::reference_wrapper<decltype(currentSoundGenIndices)> getCurrentSoundGenIndices();
		std::reference_wrapper<decltype(animGroupSoundGenCounts)> getAnimGroupSoundGenCounts();
		std::reference_wrapper<decltype(animGroupSoundGens)> getAnimGroupSoundGens();

	};
	static_assert(sizeof(AnimationDataVanilla) == 0x7E4, "TES3::AnimationDataVanilla failed size validation");

	struct AnimationData : AnimationDataVanilla {
		struct TargetAnimGroup {
			AnimationGroup* group;
			int layer;
		};
		struct TemporarySwitchedGroup {
			TargetAnimGroup temporary;
			TargetAnimGroup original;
			std::array<bool, 3> activeSections;
		};

		// These members need to be explicitly constructed in ctor().
		std::vector<SequenceGroup> customLayers;
		std::vector<KeyframeDefinition*> customAnims;
		std::unordered_map<std::string_view, TargetAnimGroup> namedGroups;
		std::vector<TemporarySwitchedGroup> temporarySwitchedGroups;

		AnimationData() = delete;
		~AnimationData() = delete;

		//
		// Other related this-call functions.
		//

		AnimationData* ctor();
		void dtor();

		void mergeAnimGroups(AnimationGroup* animGroup, int layerIndex);
		void playAnimationGroupForSection(AnimGroupID groupId, int bodySection, int startFlag = 0, int loopCount = -1);
		void playNamedAnimationGroup(std::string_view name, int bodySection, int startFlag = 0, int loopCount = -1);
		bool setLayerKeyframes(KeyframeDefinition* kfData, int layerIndex, bool isBiped);

		//
		// Custom functions.
		//

		bool applyTargetGroup(const TargetAnimGroup& targetGroup);
		bool getVanillaTarget(AnimGroupID groupId, TargetAnimGroup& out_target);
		bool hasNamedGroup(std::string_view name);
		void mergeAnimGroup(AnimationGroup* animGroup, int layerIndex);
		void onSectionInheritAnim(int bodySection);

		void revertTemporarySwitches(int bodySection);
		void setTemporarySwitch(TargetAnimGroup& target, int bodySection);

		bool addCustomAnim(KeyframeDefinition* kfData);
		bool applyCustomAnim(std::string_view name);
		bool removeCustomAnim(std::string_view name);
		void resetCustomAnims();

		std::reference_wrapper<decltype(customLayers)> getKeyframeLayers();
		std::reference_wrapper<decltype(customAnims)> getAnimations();

		static void patch();
	};
}
