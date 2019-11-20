#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <HFL/Source/HFL.h>
#include <cstdint>
#include <cstddef>


void PatchUnitArrayAddress()
{
	constexpr std::uintptr_t unitArrayPointerAddress = 0x54F848;
	auto unitArrayPointer = reinterpret_cast<std::uintptr_t*>(unitArrayPointerAddress);
	*unitArrayPointer += -(*unitArrayPointer) % 120;
}

//void PatchUnitArrayAddress()
//{
//	std::uintptr_t unitArray = 0x04170030;
//	constexpr std::size_t unitArraySize = 0x3c078;
//
//	LPVOID result = VirtualAlloc(reinterpret_cast<LPVOID>(unitArray), unitArraySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//	while (result == NULL) {
//		unitArray += 0x04170030;
//		result = VirtualAlloc(reinterpret_cast<LPVOID>(unitArray), unitArraySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//	}
//
//	constexpr std::uintptr_t unitArrayPointer = 0x54F848;
//	*reinterpret_cast<std::uintptr_t*>(unitArrayPointer) = unitArray;
//}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		HFLInit();
		PatchUnitArrayAddress();
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		HFLCleanup();
	}

	return true;
}
