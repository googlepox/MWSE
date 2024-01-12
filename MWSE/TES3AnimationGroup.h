#pragma once

#include "TES3Object.h"

#include "NIDefines.h"

namespace TES3 {
	enum class AnimGroupID : unsigned char {
		Idle,
		Idle2,
		Idle3,
		Idle4,
		Idle5,
		Idle6,
		Idle7,
		Idle8,
		Idle9,
		Idlehh,
		Idle1h,
		Idle2c,
		Idle2w,
		IdleSwim,
		IdleSpell,
		IdleCrossbow,
		IdleSneak,
		IdleStorm,
		Torch,
		Hit1,
		Hit2,
		Hit3,
		Hit4,
		Hit5,
		SwimHit1,
		SwimHit2,
		SwimHit3,
		Death1,
		Death2,
		Death3,
		Death4,
		Death5,
		DeathKnockDown,
		DeathKnockOut,
		KnockDown,
		KnockOut,
		SwimDeath,
		SwimDeath2,
		SwimDeath3,
		SwimDeathKnockDown,
		SwimDeathKnockOut,
		SwimKnockOut,
		SwimKnockDown,
		SwimWalkForward,
		SwimWalkBack,
		SwimWalkLeft,
		SwimWalkRight,
		SwimRunForward,
		SwimRunBack,
		SwimRunLeft,
		SwimRunRight,
		SwimTurnLeft,
		SwimTurnRight,
		WalkForward,
		WalkBack,
		WalkLeft,
		WalkRight,
		TurnLeft,
		TurnRight,
		RunForward,
		RunBack,
		RunLeft,
		RunRight,
		SneakForward,
		SneakBack,
		SneakLeft,
		SneakRight,
		Jump,
		WalkForwardhh,
		WalkBackhh,
		WalkLefthh,
		WalkRighthh,
		TurnLefthh,
		TurnRighthh,
		RunForwardhh,
		RunBackhh,
		RunLefthh,
		RunRighthh,
		SneakForwardhh,
		SneakBackhh,
		SneakLefthh,
		SneakRighthh,
		Jumphh,
		WalkForward1h,
		WalkBack1h,
		WalkLeft1h,
		WalkRight1h,
		TurnLeft1h,
		TurnRight1h,
		RunForward1h,
		RunBack1h,
		RunLeft1h,
		RunRight1h,
		SneakForward1h,
		SneakBack1h,
		SneakLeft1h,
		SneakRight1h,
		Jump1h,
		WalkForward2c,
		WalkBack2c,
		WalkLeft2c,
		WalkRight2c,
		TurnLeft2c,
		TurnRight2c,
		RunForward2c,
		RunBack2c,
		RunLeft2c,
		RunRight2c,
		SneakForward2c,
		SneakBack2c,
		SneakLeft2c,
		SneakRight2c,
		Jump2c,
		WalkForward2w,
		WalkBack2w,
		WalkLeft2w,
		WalkRight2w,
		TurnLeft2w,
		TurnRight2w,
		RunForward2w,
		RunBack2w,
		RunLeft2w,
		RunRight2w,
		SneakForward2w,
		SneakBack2w,
		SneakLeft2w,
		SneakRight2w,
		Jump2w,
		SpellCast,
		SpellTurnLeft,
		SpellTurnRight,
		Attack1,
		Attack2,
		Attack3,
		SwimAttack1,
		SwimAttack2,
		SwimAttack3,
		HandToHand,
		Crossbow,
		BowAndArrow,
		ThrowWeapon,
		WeaponOneHand,
		WeaponTwoHand,
		WeaponTwoWide,
		Shield,
		PickProbe,
		InventoryHandToHand,
		InventoryWeaponOneHand,
		InventoryWeaponTwoHand,
		InventoryWeaponTwoWide,
		First = Idle,
		Last = InventoryWeaponTwoWide,
		NONE = 0xFF,
	};

	enum struct AnimGroupActionClass {
		NonLooping,
		Looping,
		CreatureAttack,
		ProjectileWeapon,
		Blocking,
		PickProbe,
		Casting,
		MeleeWeapon,
	};

	struct AnimationGroup : BaseObject {
		struct SoundGenKey {
			int startFrame; // 0x0
			float startTime; // 0x4
			unsigned char volume; // 0x8
			float pitch; // 0xC
			Sound* sound; // 0x10

			SoundGenKey() = delete;
			~SoundGenKey() = delete;
		};

		AnimGroupID groupId; // 0x10
		unsigned int actionCount; // 0x14
		int* actionFrames; // 0x18
		float* actionTimings; // 0x1C
		AnimationGroup* nextGroup; // 0x20
		unsigned int soundGenCount; // 0x24
		SoundGenKey* soundGenKeys; // 0x28

		AnimationGroup() = delete;
		~AnimationGroup() = delete;

		//
		// Other related this-call functions.
		//

		AnimationGroup* ctor(int animGroupId);
		void dtor();

		void calcNoteTimes();
		void setSoundGenCount(unsigned int newCount);
		void setSoundGenVolume(unsigned int index, float volume);
		void setSoundGenPitch(unsigned int index, float volume);

		//
		// Custom functions.
		//

		AnimationGroup* findGroup(AnimGroupID groupId);
		static AnimGroupActionClass getActionClass(AnimGroupID groupId);

		nonstd::span<int> getActionFrames();
		nonstd::span<float> getActionTimings();
		nonstd::span<SoundGenKey> getSoundGenKeys();
	};
	static_assert(sizeof(AnimationGroup) == 0x2C, "TES3::AnimationGroup failed size validation");
	static_assert(sizeof(AnimationGroup::SoundGenKey) == 0x14, "TES3::AnimationGroup::SoundGenKey failed size validation");

	struct KeyframeDefinition {
		const char* filename; // 0x0
		NI::Sequence* sequences[3]; // 0x4
		AnimationGroup* animationGroups; // 0x10
		unsigned short groupCount; // 0x14
		unsigned short refCount; // 0x16

		KeyframeDefinition() = delete;
		~KeyframeDefinition() = delete;

		static int parseSeqTextKeysToAnimGroups(NI::Sequence* sequence, const char* meshPath, AnimationGroup** pAnimationGroups);
	};
	static_assert(sizeof(KeyframeDefinition) == 0x18, "TES3::KeyframeDefinition failed size validation");
}

MWSE_SOL_CUSTOMIZED_PUSHER_DECLARE_TES3(TES3::AnimationGroup)
