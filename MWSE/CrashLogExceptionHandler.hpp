#pragma once
#include "CrashLogger.hpp"
#include "Log.h"

#include "TES3Defines.h"

#define SYMOPT_EX_WINE_NATIVE_MODULES 1000

constexpr UINT32 ce_printStackCount = 256;

namespace CrashLogger::PDB
{
	extern std::string GetModule(UINT32 eip, HANDLE process)
	{
		IMAGEHLP_MODULE module = { 0 };
		module.SizeOfStruct = sizeof(IMAGEHLP_MODULE);
		if (!SymGetModuleInfo(process, eip, &module)) return "";

		return module.ModuleName;
	}

	inline extern UINT32 GetModuleBase(UINT32 eip, HANDLE process)
	{
		IMAGEHLP_MODULE module = { 0 };
		module.SizeOfStruct = sizeof(IMAGEHLP_MODULE);
		if (!SymGetModuleInfo(process, eip, &module)) return 0;

		return module.BaseOfImage;
	}

	inline extern std::string GetSymbol(UINT32 eip, HANDLE process)
	{
		char symbolBuffer[sizeof(SYMBOL_INFO) + 255];
		const auto symbol = (SYMBOL_INFO*)symbolBuffer;

		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = 254;
		DWORD64 offset = 0;

		if (!SymFromAddr(process, eip, &offset, symbol)) return "";

		const std::string functioName = symbol->Name;

		return fmt::format("{}+0x{:0X}", functioName, offset);
	}

	inline extern std::string GetLine(UINT32 eip, HANDLE process)
	{
		char lineBuffer[sizeof(IMAGEHLP_LINE) + 255];
		const auto line = (IMAGEHLP_LINE*)lineBuffer;
		line->SizeOfStruct = sizeof(IMAGEHLP_LINE);

		DWORD offset = 0;

		if (!SymGetLineFromAddr(process, eip, &offset, line)) return "";

		return fmt::format("{}:{:d}", line->FileName, line->LineNumber);
	}

	inline std::string& GetClassNameGetSymbol(void* object, std::string& buffer)
	{
		try {
			buffer = GetSymbol(*((UINT32*)object), GetCurrentProcess());
			return buffer;
		}
		catch (...) {
			return buffer;
		}
	}

	inline std::string& GetClassNameFromPDBSEH(void* object, std::string& buffer)
	{
		__try { GetClassNameGetSymbol(object, buffer); return buffer; }
		__except (EXCEPTION_EXECUTE_HANDLER) { return buffer; }

	}

	inline std::string GetClassNameFromPDB(void* object)
	{
		std::string name;
		GetClassNameFromPDBSEH(object, name);
		std::string delimiter = "vtbl_";
		if (name.find(delimiter) != std::string::npos) {
			name.erase(0, name.find(delimiter) + delimiter.length());
		}
		delimiter = "sg_";
		if (name.find(delimiter) != std::string::npos) {
			name.erase(0, name.find(delimiter) + delimiter.length());
		}
		return name;
	}

	struct RTTIType
	{
		void* typeInfo;
		UINT32	pad;
		char	name[0];
	};

	struct RTTILocator
	{
		UINT32		sig, offset, cdOffset;
		RTTIType* type;
	};

	inline const char* GetObjectClassNameInternal(void* objBase)
	{
		__try {
			const char* result = "";
			void** obj = (void**)objBase;
			RTTILocator** vtbl = (RTTILocator**)obj[0];
			RTTILocator* rtti = vtbl[-1];
			
			switch ((UINT32)vtbl) {
			case TES3::VirtualTableAddress::VirtualTableAddress::Activator:
				result = "Activator";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::ActorAnimController:
				result = "ActorAnimController";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::ActorWearsObjects:
				result = "ActorWearsObjects";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageActivate:
				result = "AIPackageActivate";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageBase:
				result = "AIPackageBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageEscort:
				result = "AIPackageEscort";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageFollow:
				result = "AIPackageFollow";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageTravel:
				result = "AIPackageTravel";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AIPackageWander:
				result = "AIPackageWander";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Alchemy:
				result = "Alchemy";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AnimatedObject:
				result = "AnimatedObject";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AnimationGroup:
				result = "AnimationGroup";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Apparatus:
				result = "Apparatus";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::ArchiveFile:
				result = "ArchiveFile";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Armor:
				result = "Armor";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Attribute:
				result = "Attribute";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AttributeFatigue:
				result = "AttributeFatigue";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::AttributeSkill:
				result = "AttributeSkill";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::BaseObject:
				result = "BaseObject";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Birthsign:
				result = "Birthsign";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::BodyPart:
				result = "BodyPart";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Book:
				result = "Book";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Cell:
				result = "Cell";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Class:
				result = "Class";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Clothing:
				result = "Clothing";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::ContainerBase:
				result = "ContainerBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::ContainerInstance:
				result = "ContainerInstance";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::CreatureBase:
				result = "CreatureBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::CreatureInstance:
				result = "CreatureInstance";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::CutscenePlayer:
				result = "CutscenePlayer";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Dialogue:
				result = "Dialogue";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::DialogueInfo:
				result = "DialogueInfo";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Door:
				result = "Door";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Enchantment:
				result = "Enchantment";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Faction:
				result = "Faction";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Game:
				result = "Game";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::GameBase:
				result = "GameBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::GameSetting:
				result = "GameSetting";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::GlobalVariable:
				result = "GlobalVariable";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Ingredient:
				result = "Ingredient";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Land:
				result = "Land";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::LandTexture:
				result = "LandTexture";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::LeveledCreature:
				result = "LeveledCreature";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::LeveledItem:
				result = "LeveledItem";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Light:
				result = "Light";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Lockpick:
				result = "Lockpick";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MagicEffect:
				result = "MagicEffect";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MagicSourceInstance:
				result = "MagicSourceInstance";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Miscellaneous:
				result = "Miscellaneous";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobileActor:
				result = "MobileActor";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobileCreature:
				result = "MobileCreature";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobileNPC:
				result = "MobileNPC";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobileObject:
				result = "MobileObject";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobilePlayer:
				result = "MobilePlayer";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::MobileProjectile:
				result = "MobileProjectile";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::NPCBase:
				result = "NPCBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::NPCInstance:
				result = "NPCInstance";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Object:
				result = "Object";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::PathGrid:
				result = "PathGrid";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::PhysicalObject:
				result = "PhysicalObject";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::PlayerAnimController:
				result = "PlayerAnimController";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Probe:
				result = "Probe";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Quest:
				result = "Quest";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Race:
				result = "Race";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Reference:
				result = "Reference";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Region:
				result = "Region";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::RepairTool:
				result = "RepairTool";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Script:
				result = "Script";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Skill:
				result = "Skill";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Sound:
				result = "Sound";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::SoundGenerator:
				result = "SoundGenerator";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Spell:
				result = "Spell";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::SpellProjectile:
				result = "SpellProjectile";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Static:
				result = "Static";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::TArray:
				result = "TArray";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::TES3Archive:
				result = "TES3Archive";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::Weapon:
				result = "Weapon";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherAshstorm:
				result = "WeatherAshstorm";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherBase:
				result = "WeatherBase";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherBlight:
				result = "WeatherBlight";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherBlizzard:
				result = "WeatherBlizzard";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherClear:
				result = "WeatherClear";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherCloudy:
				result = "WeatherCloudy";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherFog:
				result = "WeatherFog";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherOvercast:
				result = "WeatherOvercast";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherRain:
				result = "WeatherRain";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherSnow:
				result = "WeatherSnow";
				break;
			case TES3::VirtualTableAddress::VirtualTableAddress::WeatherStorm:
				result = "WeatherStorm";
				break;
			default:
				break;
			}
			return result;
		}
		__except (ExceptionFilter(GetExceptionCode()))
		{
			return "";
		}
	}


	// use the RTTI information to return an object's class name
	inline const char* GetObjectClassNameInternal2(void* objBase)
	{
		__try {
			const char* result = "";
			void** obj = (void**)objBase;
			RTTILocator** vtbl = (RTTILocator**)obj[0];
			RTTILocator* rtti = vtbl[-1];
			RTTIType* type = rtti->type;

			// starts with .?AV
			if ((type->name[0] == '.') && (type->name[1] == '?'))
			{
				// is at most MAX_PATH chars long
				for (UINT32 i = 0; i < MAX_PATH; i++) if (type->name[i] == 0)
				{
					result = type->name;
					break;
				}
			}
			return result;
		}
		__except (ExceptionFilter(GetExceptionCode()))
		{
			return "";
		}
	}

	inline std::string GetClassNameFromRTTI(void* object)
	{
		return GetObjectClassNameInternal(object);
	}

	extern std::string GetClassNameFromRTTIorPDB(void* object)
	{
		if (const auto str = GetClassNameFromRTTI(object); !str.empty()) return str;
		return GetClassNameFromPDB(object);
		//if (const auto str = GetClassNameFromPDB(object); !str.contains("0x")) return str;
	}
};

namespace CrashLogger
{

	inline void LogPlaytime(EXCEPTION_POINTERS* info) {
		__try {
			Playtime::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log playtime. \n");
		}
	}

	inline void LogException(EXCEPTION_POINTERS* info) {
		__try {
			Exception::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log exception. \n");
		}
	}

	inline void LogThread(EXCEPTION_POINTERS* info) {
		__try {
			Thread::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log thread. \n");
		}
	}

	inline void LogCalltrace(EXCEPTION_POINTERS* info) {
		__try {
			Calltrace::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log calltrace. \n");
		}
	}

	inline void LogRegistry(EXCEPTION_POINTERS* info) {
		__try {
			Registry::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log registry. \n");
		}
	}

	inline void LogStack(EXCEPTION_POINTERS* info) {
		__try {
			Stack::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log stack. \n");
		}
	}

	inline void LogInstall(EXCEPTION_POINTERS* info) {
		__try {
			//Install::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log install. \n");
		}
	}

	inline void LogMemory(EXCEPTION_POINTERS* info) {
		__try {
			Memory::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log memory. \n");
		}
	}

	inline void LogDevice(EXCEPTION_POINTERS* info) {
		__try {
			Device::Process(info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << ("Failed to log device. \n");
		}
	}

	inline void Log(EXCEPTION_POINTERS* info)
	{
		
		const auto begin = std::chrono::system_clock::now();
		//
		//mwse::log::getLog() << ("Processing playtime \n");
		//LogPlaytime(info);
		//mwse::log::getLog() << ("Processing exception \n");
		LogException(info);
		//mwse::log::getLog() << ("Processing thread \n");
		LogThread(info);
		//mwse::log::getLog() << ("Processing memory \n");
		LogMemory(info);
		//mwse::log::getLog() << ("Processing device");
		//LogDevice(info);
		//mwse::log::getLog() << ("Processing calltrace \n");
		LogCalltrace(info);
		//mwse::log::getLog() << ("Processing registry \n");
		LogRegistry(info);
		//mwse::log::getLog() << ("Processing stack \n");
		LogStack(info);
		//mwse::log::getLog() << ("Processing mods);
		//Mods::Process(info)
		//mwse::log::getLog() << ("Processing install");
		//LogInstall(info);
		//mwse::log::getLog() << ("processing modules");
		//Modules::Process(info);
		//AssetTracker::Process(info);

		const auto processing = std::chrono::system_clock::now();

		//mwse::log::getLog() << ("%s", Playtime::Get().str().c_str());
		mwse::log::getLog() << ("%s", Exception::Get().str().c_str());
		mwse::log::getLog() << ("%s", Thread::Get().str().c_str());
		mwse::log::getLog() << ("================================");
		mwse::log::getLog() << ("%s", Calltrace::Get().str().c_str());
		mwse::log::getLog() << ("================================\n");
		mwse::log::getLog() << ("%s", Registry::Get().str().c_str());
		mwse::log::getLog() << ("================================\n");
		mwse::log::getLog() << ("%s", Stack::Get().str().c_str());
		mwse::log::getLog() << ("================================\n");
		//mwse::log::getLog() << ("%s", Device::Get().str().c_str());
		//mwse::log::getLog() << ("================================");
		mwse::log::getLog() << ("%s", Memory::Get().str().c_str());
		mwse::log::getLog() << ("================================\n");
		//mwse::log::getLog() << ("================================");
		//mwse::log::getLog() << ("%s", Mods::Get().str());
		//mwse::log::getLog() << ("================================");
		//mwse::log::getLog() << ("%s", AssetTracker::Get().str());
		//mwse::log::getLog() << ("================================");
		//Modules::Process(info);
		//mwse::log::getLog() << ("%s", Modules::Get().str().c_str());
		//mwse::log::getLog() << ("================================\n");
		//mwse::log::getLog() << ("%s", Install::Get().str().c_str());

		const auto printing = std::chrono::system_clock::now();

		const auto timeProcessing = std::chrono::duration_cast<std::chrono::milliseconds>(processing - begin);

		const auto timePrinting = std::chrono::duration_cast<std::chrono::milliseconds>(printing - processing);

		mwse::log::getLog() << ("%s", fmt::format("Processed in {:d} ms, printed in {:d} ms", (long)timeProcessing.count(), (long)timePrinting.count()).c_str());

		//Logger::Copy();

		SymCleanup(GetCurrentProcess());
	};

	inline void AttemptLog(EXCEPTION_POINTERS* info) {
		__try { Log(info); }
		__except (EXCEPTION_EXECUTE_HANDLER) {
			mwse::log::getLog() << "Failed to log exception info";
		};
	}

	static LPTOP_LEVEL_EXCEPTION_FILTER s_originalFilter = nullptr;

	inline LONG WINAPI Filter(EXCEPTION_POINTERS* info) {

		static bool caught = false;
		bool ignored = false;
		if (caught) ignored = true;
		else
		{
			caught = true;
			AttemptLog(info);
		}
		if (s_originalFilter) s_originalFilter(info); // don't return
		return !ignored ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
	};

	inline LPTOP_LEVEL_EXCEPTION_FILTER WINAPI FakeSetUnhandledExceptionFilter(__in LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter) {
		s_originalFilter = lpTopLevelExceptionFilter;
		return nullptr;
	}

}