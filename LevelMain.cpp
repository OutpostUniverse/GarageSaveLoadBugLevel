#include <Outpost2DLL/Outpost2DLL.h>	// Main Outpost 2 header to interface with the game
#include <OP2Helper/OP2Helper.h>		// Optional header to make level building easier
#include <cstdint>
#include <cstddef>


void DetectProblemUnitArrayAllocation();


ExportLevelDetails("A - Garage Save Load Bug", "cm02.map", "MULTITEK.TXT", MissionTypes::Colony, 1)

// Alternative style allowing more advanced settings such as AI players and max tech level:
// Required data exports  (Description, Map, TechTree, GameType, NumPlayers, maxTechLevel, bUnitOnlyMission, numAIPlayers)
// ExportLevelDetailsFullEx("5P, LoS, '<map name>'", "on6_01.map", "MULTITEK.TXT", MultiLastOneStanding, 6, 12, false, 1)


// Note: Place any global variables in the following struct so that your
//		level works right when saving and loading.
// Note: Feel free to rename the following struct and variable declaration to whatever you want
// Holder for global script variables (for Saved game files)
struct ScriptGlobal
{
} scriptGlobal;
// This macro automatically generates the GetSaveRegions export which tells Outpost2.exe about
// the scriptGlobal variable. Data in this struct is preserved during game save/load.
// Note: This implies all level data must be statically sized.
ExportSaveLoadData(scriptGlobal);


// Note: The following function is called once by Outpost2.exe when the
//		 level is first initialized. This is where you want to create
//		 all the initial units and structures as well as setup any 
//		 map/level environment settings such as day and night.
// Note: Returns true if level loaded successfully and is playable, false to abort
Export int InitProc()
{
	Unit garage, truck;
	TethysGame::CreateUnit(garage, map_id::mapGarage, LOCATION(10 + X_, 10 + Y_), Player0, mapNone, 0);
	TethysGame::CreateUnit(truck, map_id::mapCargoTruck, garage.Location(), Player0, mapNone, 0);
	truck.PutInGarage(0, garage.Location().x, garage.Location().y);

	Player[Player0].CenterViewOn(garage.Location().x, garage.Location().y);

	DetectProblemUnitArrayAllocation();

	return true;
}

void DetectProblemUnitArrayAllocation()
{
	// Find address of unit array
	constexpr std::uintptr_t unitArrayPointerAddress = 0x54F848;
	auto unitArrayPointer = *reinterpret_cast<std::uintptr_t*>(unitArrayPointerAddress);
	// Determine unit array alignment
	std::size_t alignment = unitArrayPointer % 120;
	// Set warning sound based on problem alignment
	auto soundId = (alignment == 0) ? sndGar_sel : sndBld_not;
	// Build info message
	char buffer[64];
	scr_snprintf(buffer, sizeof(buffer), "UnitArrayAddress: %x,  Alignment: %i", unitArrayPointer, alignment);
	// Inform user about unit array alignment
	AddGameMessage(buffer, soundId);
}


// Note: The following function seems to be intended for use in
//		 controlling an AI. It is called once every game cycle. 
//		 Use it for whatever code needs to run on a continual basis.
// Note: The standard level DLLs released by Sierra leave this function
//		 empty and handle all AI controls through triggers.
Export void AIProc() 
{
}


// Note: This is a trigger callback function. This function is
//		 intentionally left empty and is used as the trigger
//		 callback function for triggers that don't want or need
//		 any special callback function.
// Note: The use of Export is used by all trigger functions
//		 to ensure they are exported correctly.
Export void NoResponseToTrigger()
{
}


