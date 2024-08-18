
#include "../main.h"

DWORD dwSystemMemory;
DWORD dwStreamingMemory;

void RelocateScanListHack();
void RelocatePedsListHack();
void RelocateBaseModelInfoHack();

extern int iGtaVersion;

//----------------------------------------------------------

#define memadd(num,arr) dwAlloc+=num;cBytes=(char*)&dwAlloc;for(int i=0;i<4;i++)arr[i]=cBytes[i]
#define patch(a,b) _patch(a,b,sizeof(b))

//----------------------------------------------------------

void _patch(DWORD dwAddress,BYTE* bData,int iSize)
{
	DWORD dwProtect[2];
	VirtualProtect((PVOID)dwAddress,iSize,PAGE_EXECUTE_READWRITE,&dwProtect[0]);
	memcpy((PVOID)dwAddress,bData,iSize);
	VirtualProtect((PVOID)dwAddress,iSize,dwProtect[0],&dwProtect[1]);
}

//----------------------------------------------------------

void SetIPLs(int iIPLs, int iGtaVersion)
{
	DWORD dwAlloc = (DWORD) malloc(iIPLs+4);
	if(dwAlloc)
	{
		memset((void*)dwAlloc,0x0,iIPLs+4);
		char* cBytes = (char*)&dwAlloc;

		BYTE bIPLs[] = { cBytes[0], cBytes[1], cBytes[2], cBytes[3] };

		if(iGtaVersion == GTASA_VERSION_USA10)
		{
			patch(0x1569777,bIPLs);
			patch(0x15649FA,bIPLs);
			patch(0x1561160,bIPLs);
		}
		else
		{
			patch(0x1569717,bIPLs);
			patch(0x156495A,bIPLs);
			patch(0x156115C,bIPLs);
		}
		patch(0x40619B,bIPLs);
		patch(0x405C3D,bIPLs);
	}
}

//----------------------------------------------------------

void SetTimedObjects(int iTimedObjects)
{
	DWORD dwAlloc = (DWORD) malloc((0x24*iTimedObjects)+4);
	if(dwAlloc)
	{
		memset((LPVOID)dwAlloc,0x00,(0x24*iTimedObjects)+4);
		for(DWORD i=dwAlloc+4;i<(dwAlloc+4+(0x24*iTimedObjects));i+=0x24)
		{
			*(BYTE*) i = 0xB0;
			*(BYTE*) (i+1) = 0xBC;
			*(BYTE*) (i+2) = 0x85;
			*(BYTE*) (i+10) = 0xFF;
			*(BYTE*) (i+11) = 0xFF;
			*(BYTE*) (i+34) = 0xFF;
			*(BYTE*) (i+35) = 0xFF;
		}
		char* cBytes = (char*)&dwAlloc;
		BYTE bTimedObjects[] = { cBytes[0], cBytes[1], cBytes[2], cBytes[3] };
		patch(0x4C66B1,bTimedObjects);
		patch(0x4C66C2,bTimedObjects);
		patch(0x84BC51,bTimedObjects);
		patch(0x856261,bTimedObjects);
		patch(0x4C683B,bTimedObjects);
		memadd(4,bTimedObjects);
		patch(0x4C6464,bTimedObjects);
		patch(0x4C66BD,bTimedObjects);
		cBytes = (char*)&iTimedObjects;
		BYTE pushTimedObjects[] = { 0x68, cBytes[0], cBytes[1], cBytes[2], cBytes[3] };
		patch(0x4C58A5,pushTimedObjects);
	}
}

//----------------------------------------------------------

void UnFuckAndCheck(DWORD addr, int size, BYTE byteCheck)
{
	DWORD d;
	VirtualProtect((PVOID)addr,size,PAGE_EXECUTE_READWRITE,&d);

	if(byteCheck != *(PBYTE)addr) {
#ifdef _DEBUG
		char s[256];
		sprintf(s,"Failed Check At Addr: 0x%X",addr);
		OutputDebugString(s);
#endif
		while(byteCheck != *(PBYTE)addr) Sleep(1);

		VirtualProtect((PVOID)addr,size,PAGE_EXECUTE_READWRITE,&d);
	}
}

//----------------------------------------------------------

void UnFuck(DWORD addr, int size)
{
	DWORD d;
	VirtualProtect((PVOID)addr,size,PAGE_EXECUTE_READWRITE,&d);
}

//----------------------------------------------------------

DWORD dwPatchAddrColStoreSize[7] = {
	0x410DBB,0x410DE5,0x410F68,0x410AA4,0x410CC4,0x410EAD,0x411505
};

void ApplyNewColStoreSizePatch(DWORD dwCount)
{
	DWORD oldProt;

	VirtualProtect((PVOID)0x411458,4,PAGE_EXECUTE_READWRITE,&oldProt);
	*(DWORD*)0x411458 = dwCount;

	int x=0;
	while(x!=7) {
		UnFuck(dwPatchAddrColStoreSize[x] + 2, 4);
		*(PDWORD)(dwPatchAddrColStoreSize[x] + 2) = 44 * dwCount;
		x++;
	}
}

//----------------------------------------------------------

void FUNC_100AA540()
{
	*(BYTE*)0x71A223 = 3;
	*(BYTE*)0x71A5D5 = 3;
	*(BYTE*)0x71A247 = 3;
	*(BYTE*)0x71A282 = 3;
	*(BYTE*)0x71A26A = 3;
	*(BYTE*)0x71A2E5 = 3;
	*(BYTE*)0x71A3AC = 3;
	*(BYTE*)0x71A4B9 = 3;
	*(BYTE*)0x71A53C = 3;
	*(BYTE*)0x71A37F = 3;
	*(BYTE*)0x71A518 = 3;
	*(BYTE*)0x71A525 = 3;
	*(BYTE*)0x71A54B = 3;
	*(BYTE*)0x71A5B6 = 3;
	*(BYTE*)0x71A3BB = 3;
}

//----------------------------------------------------------

BYTE pbyteVehiclePoolAllocPatch[] = {0x6A,0x00,0x68,0xC6,0x2,0x00,0x00}; // 710
BYTE pbyteCollisionPoolAllocPatch[] = { 0x68,0xFF,0x7E,0x00,0x00 }; // 32511

void ApplyGameLimitPatches()
{
	// Increase the vehicle pool limit (see top of proc for patch)
	UnFuckAndCheck(0x551024,sizeof(pbyteVehiclePoolAllocPatch),0x68);
	memcpy((PVOID)0x551024,pbyteVehiclePoolAllocPatch,sizeof(pbyteVehiclePoolAllocPatch));

	// Increase Buildings
	UnFuck(0x55105F,4);
	*(DWORD *)0x55105F = 20000;

	// Increase Dummys
	UnFuck(0x5510CF,4);
	*(DWORD *)0x5510CF = 4000;

	// Increase Ptr Node Single
	UnFuck(0x550F46,4);
	*(DWORD *)0x550F46 = 100000;

	// Increase Ptr Node Double
	UnFuck(0x550F82,4);
	*(DWORD *)0x550F82 = 8000;

	// Increase EntryInfoNode
	UnFuck(0x550FBA,4);
	*(DWORD *)0x550FBA = 5000;

	// Increase Object Pool
	UnFuck(0x551097,4);
	*(DWORD *)0x551097 = 3000;

	// Increase the ped pool limit (240)
	UnFuck(0x550FF2,1);
	*(PBYTE)0x550FF2 = 240;

	// And we need 240 ped intelligence too plz
	UnFuck(0x551283,1);
	*(PBYTE)0x551283 = 240;

	// And a larger task pool
	UnFuck(0x551140,1);
	*(PBYTE)0x551140 = 0x05; // 1524

	// And a larger event pool
	UnFuck(0x551178,1);
	*(PBYTE)0x551178 = 0x01; // 456

	// Increase CPlaceable matrix array
	UnFuck(0x54F3A1,4);
	*(DWORD *)0x54F3A1 = 6000;

	// Increase the collision model ptr
	UnFuck(0x551106,sizeof(pbyteCollisionPoolAllocPatch));
	memcpy((PVOID)0x551106,pbyteCollisionPoolAllocPatch,sizeof(pbyteCollisionPoolAllocPatch));
}

//----------------------------------------------------------

BOOL ApplyPreGamePatches()
{
	BYTE * pbyteVersionDetermination = (PBYTE)ADDR_BYPASS_VIDS_USA10;
	int iCounter=0;

	// MAIN VERSION DETERMINING LOGIC
	while( (*pbyteVersionDetermination != 0x89) &&
		   (*pbyteVersionDetermination != 0xC8) )
	{
		if (*(PBYTE)ADDR_GAME_STARTED == 1) {
			return FALSE;
		} else {
			Sleep(10);
			iCounter++;
			if(iCounter>6000) { // 60 seconds have passed
				return FALSE;
			}
		}
	}

	if(*pbyteVersionDetermination == 0x89) {
		iGtaVersion = GTASA_VERSION_USA10;
	} 
	else if(*pbyteVersionDetermination == 0xC8) {
		iGtaVersion = GTASA_VERSION_EU10;
	}

	// (skip to starting screen)
	if(iGtaVersion == GTASA_VERSION_USA10) {
		UnFuck(ADDR_BYPASS_VIDS_USA10,6);
		*(BYTE *)ADDR_ENTRY = 5;
		memset((PVOID)ADDR_BYPASS_VIDS_USA10,0x90,6);
	}
	else if (iGtaVersion == GTASA_VERSION_EU10) {
		UnFuck(ADDR_BYPASS_VIDS_EU10,6);
		*(BYTE *)ADDR_ENTRY = 5;
		memset((PVOID)ADDR_BYPASS_VIDS_EU10,0x90,6);
	}

	// Loading screens
	UnFuck(0x866CD8,10);
	UnFuck(0x866CCC,10);
	strcpy((PCHAR)0x866CD8,"title");
	strcpy((PCHAR)0x866CCC,"title");

	UnFuck(0x745B87,68);
	memset((PVOID)0x745B87,0x90,68);

	UnFuck(0x7459E1,2);
	memset((LPVOID)0x7459E1,0x90,2);

	UnFuckAndCheck(0x561872,30,0x85);
	*(PBYTE)0x561872 = 0x33;
	*(PBYTE)0x561873 = 0xC0;
	memset((LPVOID)0x561874,0x90,27);

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	dwSystemMemory = statex.ullTotalPhys / (1024 * 1024);

	if(dwSystemMemory > 4000)
		dwStreamingMemory = 0x40000000; // 1024MB
	else if(dwSystemMemory > 2000)
		dwStreamingMemory = 0x20000000; // 512MB
	else if(dwSystemMemory > 1000)
		dwStreamingMemory = 0x10000000; // 256MB
	else if(dwSystemMemory > 500)
		dwStreamingMemory = 0x08000000; // 128MB
	else
		dwStreamingMemory = 0x06000000; // 96MB

	// Modify the streaming memory hardcoded values
	UnFuck(0x5B8E6A,4);
	*(DWORD *)0x5B8E6A = dwStreamingMemory;

	UnFuckAndCheck(0x4083C0,1,0xB8);
	*(PBYTE)0x4083C0 = 0xC3;

	UnFuck(0x590099,5);
	memset((LPVOID)0x590099,0x90,5);

	UnFuck(0x53E94C,1);
	*(PBYTE)0x53E94C = 2;

	UnFuck(0x731F60,4);
	*(PDWORD)0x731F60 = 20000;

	return TRUE;
}

//----------------------------------------------------------

BOOL GLOBAL_1026B3E0;
BOOL GLOBAL_1026B3E4;

void FUNC_100AABE0()
{
	if(!GLOBAL_1026B3E0) {
		UnFuck(0x6E1BE3,37);
		memset((PVOID)0x6E1BE3,0x90,37);

		UnFuck(0x6E1C38,8);
		memset((PVOID)0x6E1C38,0x90,8);

		UnFuck(0x6E1D98,15);
		memset((PVOID)0x6E1D98,0x90,15);

		UnFuck(0x6E1DBC,8);
		memset((PVOID)0x6E1DBC,0x90,8);

		UnFuck(0x6E1BA0,6);
		memset((PVOID)0x6E1BA0,0x90,6);

		UnFuck(0x6E1BB1,6);
		memset((PVOID)0x6E1BB1,0x90,6);

		UnFuck(0x6E1BD2,7);
		memset((PVOID)0x6E1BD2,0x90,7);

		BYTE byteReplacement[] = { 0x8A,0x86,0x28,0x04,0x00,0x00,0xA8,0x40,0x74,0x28 };
		memcpy((PVOID)0x6E1BE5,byteReplacement,sizeof(byteReplacement));

		GLOBAL_1026B3E0 = TRUE;
		GLOBAL_1026B3E4 = TRUE;
	}
}

//----------------------------------------------------------

RGBA NewVehicleColors[256] = {
{0x00,0x00,0x00,0xFF},{0xF5,0xF5,0xF5,0xFF},{0x2A,0x77,0xA1,0xFF},{0x84,0x04,0x10,0xFF},
{0x26,0x37,0x39,0xFF},{0x86,0x44,0x6E,0xFF},{0xD7,0x8E,0x10,0xFF},{0x4C,0x75,0xB7,0xFF},
{0xBD,0xBE,0xC6,0xFF},{0x5E,0x70,0x72,0xFF},{0x46,0x59,0x7A,0xFF},{0x65,0x6A,0x79,0xFF},
{0x5D,0x7E,0x8D,0xFF},{0x58,0x59,0x5A,0xFF},{0xD6,0xDA,0xD6,0xFF},{0x9C,0xA1,0xA3,0xFF},
{0x33,0x5F,0x3F,0xFF},{0x73,0x0E,0x1A,0xFF},{0x7B,0x0A,0x2A,0xFF},{0x9F,0x9D,0x94,0xFF},
{0x3B,0x4E,0x78,0xFF},{0x73,0x2E,0x3E,0xFF},{0x69,0x1E,0x3B,0xFF},{0x96,0x91,0x8C,0xFF},
{0x51,0x54,0x59,0xFF},{0x3F,0x3E,0x45,0xFF},{0xA5,0xA9,0xA7,0xFF},{0x63,0x5C,0x5A,0xFF},
{0x3D,0x4A,0x68,0xFF},{0x97,0x95,0x92,0xFF},{0x42,0x1F,0x21,0xFF},{0x5F,0x27,0x2B,0xFF},
{0x84,0x94,0xAB,0xFF},{0x76,0x7B,0x7C,0xFF},{0x64,0x64,0x64,0xFF},{0x5A,0x57,0x52,0xFF},
{0x25,0x25,0x27,0xFF},{0x2D,0x3A,0x35,0xFF},{0x93,0xA3,0x96,0xFF},{0x6D,0x7A,0x88,0xFF},
{0x22,0x19,0x18,0xFF},{0x6F,0x67,0x5F,0xFF},{0x7C,0x1C,0x2A,0xFF},{0x5F,0x0A,0x15,0xFF},
{0x19,0x38,0x26,0xFF},{0x5D,0x1B,0x20,0xFF},{0x9D,0x98,0x72,0xFF},{0x7A,0x75,0x60,0xFF},
{0x98,0x95,0x86,0xFF},{0xAD,0xB0,0xB0,0xFF},{0x84,0x89,0x88,0xFF},{0x30,0x4F,0x45,0xFF},
{0x4D,0x62,0x68,0xFF},{0x16,0x22,0x48,0xFF},{0x27,0x2F,0x4B,0xFF},{0x7D,0x62,0x56,0xFF},
{0x9E,0xA4,0xAB,0xFF},{0x9C,0x8D,0x71,0xFF},{0x6D,0x18,0x22,0xFF},{0x4E,0x68,0x81,0xFF},
{0x9C,0x9C,0x98,0xFF},{0x91,0x73,0x47,0xFF},{0x66,0x1C,0x26,0xFF},{0x94,0x9D,0x9F,0xFF},
{0xA4,0xA7,0xA5,0xFF},{0x8E,0x8C,0x46,0xFF},{0x34,0x1A,0x1E,0xFF},{0x6A,0x7A,0x8C,0xFF},
{0xAA,0xAD,0x8E,0xFF},{0xAB,0x98,0x8F,0xFF},{0x85,0x1F,0x2E,0xFF},{0x6F,0x82,0x97,0xFF},
{0x58,0x58,0x53,0xFF},{0x9A,0xA7,0x90,0xFF},{0x60,0x1A,0x23,0xFF},{0x20,0x20,0x2C,0xFF},
{0xA4,0xA0,0x96,0xFF},{0xAA,0x9D,0x84,0xFF},{0x78,0x22,0x2B,0xFF},{0x0E,0x31,0x6D,0xFF},
{0x72,0x2A,0x3F,0xFF},{0x7B,0x71,0x5E,0xFF},{0x74,0x1D,0x28,0xFF},{0x1E,0x2E,0x32,0xFF},
{0x4D,0x32,0x2F,0xFF},{0x7C,0x1B,0x44,0xFF},{0x2E,0x5B,0x20,0xFF},{0x39,0x5A,0x83,0xFF},
{0x6D,0x28,0x37,0xFF},{0xA7,0xA2,0x8F,0xFF},{0xAF,0xB1,0xB1,0xFF},{0x36,0x41,0x55,0xFF},
{0x6D,0x6C,0x6E,0xFF},{0x0F,0x6A,0x89,0xFF},{0x20,0x4B,0x6B,0xFF},{0x2B,0x3E,0x57,0xFF},
{0x9B,0x9F,0x9D,0xFF},{0x6C,0x84,0x95,0xFF},{0x4D,0x84,0x95,0xFF},{0xAE,0x9B,0x7F,0xFF},
{0x40,0x6C,0x8F,0xFF},{0x1F,0x25,0x3B,0xFF},{0xAB,0x92,0x76,0xFF},{0x13,0x45,0x73,0xFF},
{0x96,0x81,0x6C,0xFF},{0x64,0x68,0x6A,0xFF},{0x10,0x50,0x82,0xFF},{0xA1,0x99,0x83,0xFF},
{0x38,0x56,0x94,0xFF},{0x52,0x56,0x61,0xFF},{0x7F,0x69,0x56,0xFF},{0x8C,0x92,0x9A,0xFF},
{0x59,0x6E,0x87,0xFF},{0x47,0x35,0x32,0xFF},{0x44,0x62,0x4F,0xFF},{0x73,0x0A,0x27,0xFF},
{0x22,0x34,0x57,0xFF},{0x64,0x0D,0x1B,0xFF},{0xA3,0xAD,0xC6,0xFF},{0x69,0x58,0x53,0xFF},
{0x9B,0x8B,0x80,0xFF},{0x62,0x0B,0x1C,0xFF},{0x5B,0x5D,0x5E,0xFF},{0x62,0x44,0x28,0xFF},
{0x73,0x18,0x27,0xFF},{0x1B,0x37,0x6D,0xFF},{0xEC,0x6A,0xAE,0xFF},{0x00,0x00,0x00,0xFF},
{0x17,0x75,0x17,0xFF},{0x21,0x06,0x06,0xFF},{0x12,0x54,0x78,0xFF},{0x45,0x2A,0x0D,0xFF},
{0x57,0x1E,0x1E,0xFF},{0x01,0x07,0x01,0xFF},{0x25,0x22,0x5A,0xFF},{0x2C,0x89,0xAA,0xFF},
{0x8A,0x4D,0xBD,0xFF},{0x35,0x96,0x3A,0xFF},{0xB7,0xB7,0xB7,0xFF},{0x46,0x4C,0x8D,0xFF},
{0x84,0x88,0x8C,0xFF},{0x81,0x78,0x67,0xFF},{0x81,0x7A,0x26,0xFF},{0x6A,0x50,0x6F,0xFF},
{0x58,0x3E,0x6F,0xFF},{0x8C,0xB9,0x72,0xFF},{0x82,0x4F,0x78,0xFF},{0x6D,0x27,0x6A,0xFF},
{0x1E,0x1D,0x13,0xFF},{0x1E,0x13,0x06,0xFF},{0x1F,0x25,0x18,0xFF},{0x2C,0x45,0x31,0xFF},
{0x1E,0x4C,0x99,0xFF},{0x2E,0x5F,0x43,0xFF},{0x1E,0x99,0x48,0xFF},{0x1E,0x99,0x99,0xFF},
{0x99,0x99,0x76,0xFF},{0x7C,0x84,0x99,0xFF},{0x99,0x2E,0x1E,0xFF},{0x2C,0x1E,0x08,0xFF},
{0x14,0x24,0x07,0xFF},{0x99,0x3E,0x4D,0xFF},{0x1E,0x4C,0x99,0xFF},{0x19,0x81,0x81,0xFF},
{0x1A,0x29,0x2A,0xFF},{0x16,0x61,0x6F,0xFF},{0x1B,0x66,0x87,0xFF},{0x6C,0x3F,0x99,0xFF},
{0x48,0x1A,0x0E,0xFF},{0x7A,0x73,0x99,0xFF},{0x74,0x6D,0x99,0xFF},{0x53,0x38,0x7E,0xFF},
{0x22,0x24,0x07,0xFF},{0x3E,0x19,0x0C,0xFF},{0x46,0x21,0x0E,0xFF},{0x99,0x1E,0x1E,0xFF},
{0x8D,0x4C,0x8D,0xFF},{0x80,0x5B,0x80,0xFF},{0x7B,0x3E,0x7E,0xFF},{0x3C,0x17,0x37,0xFF},
{0x73,0x35,0x17,0xFF},{0x78,0x18,0x18,0xFF},{0x83,0x34,0x1A,0xFF},{0x8E,0x2F,0x1C,0xFF},
{0x7E,0x3E,0x53,0xFF},{0x7C,0x6D,0x7C,0xFF},{0x02,0x0C,0x02,0xFF},{0x07,0x24,0x07,0xFF},
{0x16,0x30,0x12,0xFF},{0x16,0x30,0x1B,0xFF},{0x64,0x2B,0x4F,0xFF},{0x36,0x84,0x52,0xFF},
{0x99,0x95,0x90,0xFF},{0x81,0x8D,0x96,0xFF},{0x99,0x99,0x1E,0xFF},{0x7F,0x99,0x4C,0xFF},
{0x83,0x92,0x92,0xFF},{0x78,0x82,0x22,0xFF},{0x2B,0x3C,0x99,0xFF},{0x3A,0x3A,0x0B,0xFF},
{0x8A,0x79,0x4E,0xFF},{0x0E,0x1F,0x49,0xFF},{0x15,0x37,0x1C,0xFF},{0x15,0x27,0x3A,0xFF},
{0x37,0x57,0x75,0xFF},{0x06,0x08,0x20,0xFF},{0x07,0x13,0x26,0xFF},{0x20,0x39,0x4B,0xFF},
{0x2C,0x50,0x89,0xFF},{0x15,0x42,0x6C,0xFF},{0x10,0x32,0x50,0xFF},{0x24,0x16,0x63,0xFF},
{0x69,0x20,0x15,0xFF},{0x8C,0x8D,0x94,0xFF},{0x51,0x60,0x13,0xFF},{0x09,0x0F,0x02,0xFF},
{0x8C,0x57,0x3A,0xFF},{0x52,0x88,0x8E,0xFF},{0x99,0x5C,0x52,0xFF},{0x99,0x58,0x1E,0xFF},
{0x99,0x3A,0x63,0xFF},{0x99,0x8F,0x4E,0xFF},{0x99,0x31,0x1E,0xFF},{0x0D,0x18,0x42,0xFF},
{0x52,0x1E,0x1E,0xFF},{0x42,0x42,0x0D,0xFF},{0x4C,0x99,0x1E,0xFF},{0x08,0x2A,0x1D,0xFF},
{0x96,0x82,0x1D,0xFF},{0x19,0x7F,0x19,0xFF},{0x3B,0x14,0x1F,0xFF},{0x74,0x52,0x17,0xFF},
{0x89,0x3F,0x8D,0xFF},{0x7E,0x1A,0x6C,0xFF},{0x0B,0x37,0x0B,0xFF},{0x27,0x45,0x0D,0xFF},
{0x07,0x1F,0x24,0xFF},{0x78,0x45,0x73,0xFF},{0x8A,0x65,0x3A,0xFF},{0x73,0x26,0x17,0xFF},
{0x31,0x94,0x90,0xFF},{0x56,0x94,0x1D,0xFF},{0x59,0x16,0x3D,0xFF},{0x1B,0x8A,0x2F,0xFF},
{0x38,0x16,0x0B,0xFF},{0x04,0x18,0x04,0xFF},{0x35,0x5D,0x8E,0xFF},{0x2E,0x3F,0x5B,0xFF},
{0x56,0x1A,0x28,0xFF},{0x4E,0x0E,0x27,0xFF},{0x70,0x6C,0x67,0xFF},{0x3B,0x3E,0x42,0xFF},
{0x2E,0x2D,0x33,0xFF},{0x7B,0x7E,0x7D,0xFF},{0x4A,0x44,0x42,0xFF},{0x28,0x34,0x4E,0xFF},
};
RGBA UseVehicleColors[256];

void ApplyVehicleColorPatches()
{
	memcpy(UseVehicleColors,NewVehicleColors,sizeof(UseVehicleColors));

	UnFuck(0x44B1C1,4);
	*(DWORD*)0x44B1C1 = (DWORD)&UseVehicleColors[0];
	UnFuck(0x4C8390,4);
	*(DWORD*)0x4C8390 = (DWORD)&UseVehicleColors[0];
	UnFuck(0x4C8399,4);
	*(DWORD*)0x4C8399 = (DWORD)&UseVehicleColors[0].g;
	UnFuck(0x4C83A3,4);
	*(DWORD*)0x4C83A3 = (DWORD)&UseVehicleColors[0].b;
	UnFuck(0x5817CC,4);
	*(DWORD*)0x5817CC = (DWORD)&UseVehicleColors[0];
	UnFuck(0x582176,4);
	*(DWORD*)0x582176 = (DWORD)&UseVehicleColors[0];
	UnFuck(0x6A6FFA,4);
	*(DWORD*)0x6A6FFA = (DWORD)&UseVehicleColors[0];
}

//----------------------------------------------------------

extern DWORD dwFarClipHookAddr;
extern DWORD dwFarClipReturnAddr;

void ApplyInGamePatches()
{
	if(GTASA_VERSION_USA10 == iGtaVersion) {
		dwFarClipHookAddr = 0x7EE2A0;
		dwFarClipReturnAddr = dwFarClipHookAddr+9;
	} else {
		dwFarClipHookAddr = 0x7EE2E0;
		dwFarClipReturnAddr = dwFarClipHookAddr+9;
	}

	RelocateScanListHack();
	RelocatePedsListHack(); // allows us to use all 300 ped model slots

	RelocateBaseModelInfoHack();

}

//----------------------------------------------------------

#pragma pack(1)
typedef struct _PED_MODEL
{
	DWORD func_tbl;
	BYTE  data[64];
} PED_MODEL;

PED_MODEL PedModelsMemory[319];

void RelocatePedsListHack()
{
	BYTE *aPedsListMemory = (BYTE*)&PedModelsMemory[0];

	// Init the mem
	int x=0;
	while(x!=319) {
		PedModelsMemory[x].func_tbl = 0x85BDC0;
		memset(PedModelsMemory[x].data,0,64);
		x++;
	}
	// Patch the GetPedsModelInfo to use us
	// instead of the gta_sa.exe mem.
	UnFuck(0x4C67AD,4);
	*(DWORD *)0x4C67AD = (DWORD)aPedsListMemory;
}

//----------------------------------------------------------

#pragma pack(1)
typedef struct _BASE_MODEL_INFO
{
	DWORD func_tbl;
	BYTE  data[28];
} BASE_MODEL_INFO;

BASE_MODEL_INFO BaseModelInfoMemory[20000];

DWORD dwPatchAddrBaseModelInfoReloc[14] = {
0x4C63F2,0x4C662D,0x4C6822,0x4C6829,0x4C6877,0x4C6881,
0x4C6890,0x4C68A5,0x4C68F3,0x4C6932,0x4C6971,0x4C69B0,
0x4C69EF,0x4C6A2E };

void RelocateBaseModelInfoHack()
{
	DWORD oldProt;
	BYTE *aModelListMemory = (BYTE*)&BaseModelInfoMemory[0];

	// Init the mem
	int x=0;
	while(x!=20000) {
		BaseModelInfoMemory[x].func_tbl = 0x85BBF0;
		memset(BaseModelInfoMemory[x].data,0,28);
		x++;
	}

	x=0;
	while(x!=14) {
		VirtualProtect((LPVOID)dwPatchAddrBaseModelInfoReloc[x],4,PAGE_EXECUTE_READWRITE,&oldProt);
		*(PDWORD)dwPatchAddrBaseModelInfoReloc[x] = (DWORD)aModelListMemory;
		x++;
	}
}

//----------------------------------------------------------
// FOLLOWING IS TO RELOCATE THE SCANLIST MEMORY, A BIG
// HACK THAT ALLOWS US TO HAVE MORE THAN 2 CPlayerInfo STRUCTURES.

#define SCANLIST_SIZE 8*20000

unsigned char ScanListMemory[SCANLIST_SIZE];

// Pointers to actual code addresses to patch. The first list
// has taken into account the instruction bytes, second list
// does not. The second list is guaranteed to have 3 byte
// instructions before the new address.

DWORD dwPatchAddrScanReloc1USA[14] = {
0x5DC7AA,0x41A85D,0x41A864,0x408259,0x711B32,0x699CF8,
0x4092EC,0x40914E,0x408702,0x564220,0x564172,0x563845,
0x84E9C2,0x85652D };

DWORD dwPatchAddrScanReloc1EU[14] = {
0x5DC7AA,0x41A85D,0x41A864,0x408261,0x711B32,0x699CF8,
0x4092EC,0x40914E,0x408702,0x564220,0x564172,0x563845,
0x84EA02,0x85656D };

// Lots of hex.. that's why they call us a "determined group of hackers"

DWORD dwPatchAddrScanReloc2USA[56] = {
0x0040D68C,0x005664D7,0x00566586,0x00408706,0x0056B3B1,0x0056AD91,0x0056A85F,0x005675FA,
0x0056CD84,0x0056CC79,0x0056CB51,0x0056CA4A,0x0056C664,0x0056C569,0x0056C445,0x0056C341,
0x0056BD46,0x0056BC53,0x0056BE56,0x0056A940,0x00567735,0x00546738,0x0054BB23,0x006E31AA,
0x0040DC29,0x00534A09,0x00534D6B,0x00564B59,0x00564DA9,0x0067FF5D,0x00568CB9,0x00568EFB,
0x00569F57,0x00569537,0x00569127,0x0056B4B5,0x0056B594,0x0056B2C3,0x0056AF74,0x0056AE95,
0x0056BF4F,0x0056ACA3,0x0056A766,0x0056A685,0x0070B9BA,0x0056479D,0x0070ACB2,0x006063C7,
0x00699CFE,0x0041A861,0x0040E061,0x0040DF5E,0x0040DDCE,0x0040DB0E,0x0040D98C,0x01566855 };

DWORD dwPatchAddrScanReloc2EU[56] = {
0x0040D68C,0x005664D7,0x00566586,0x00408706,0x0056B3B1,0x0056AD91,0x0056A85F,0x005675FA,
0x0056CD84,0x0056CC79,0x0056CB51,0x0056CA4A,0x0056C664,0x0056C569,0x0056C445,0x0056C341,
0x0056BD46,0x0056BC53,0x0056BE56,0x0056A940,0x00567735,0x00546738,0x0054BB23,0x006E31AA,
0x0040DC29,0x00534A09,0x00534D6B,0x00564B59,0x00564DA9,0x0067FF5D,0x00568CB9,0x00568EFB,
0x00569F57,0x00569537,0x00569127,0x0056B4B5,0x0056B594,0x0056B2C3,0x0056AF74,0x0056AE95,
0x0056BF4F,0x0056ACA3,0x0056A766,0x0056A685,0x0070B9BA,0x0056479D,0x0070ACB2,0x006063C7,
0x00699CFE,0x0041A861,0x0040E061,0x0040DF5E,0x0040DDCE,0x0040DB0E,0x0040D98C,0x01566845 };

DWORD dwPatchAddrScanReloc3[11] = {
0x004091C5,0x00409367,0x0040D9C5,0x0040DB47,0x0040DC61,0x0040DE07,0x0040DF97,
0x0040E09A,0x00534A98,0x00534DFA,0x0071CDB0 };

// For End
// 0xB992B8 is reffed for checking end of scanlist... rewrite this to point to end of new list
DWORD dwPatchAddrScanRelocEnd[4] = { 0x005634A6, 0x005638DF, 0x0056420F, 0x00564283 };

//-----------------------------------------------------------

void RelocateScanListHack()
{
	DWORD oldProt;
	memset(&ScanListMemory[0], 0, SCANLIST_SIZE);
	unsigned char *aScanListMemory = &ScanListMemory[0];

	// FIRST PREPARED LIST OF ACCESSORS
	int x=0;
	while(x!=14) {
		if(iGtaVersion == GTASA_VERSION_USA10) {
			VirtualProtect((PVOID)dwPatchAddrScanReloc1USA[x],4,PAGE_EXECUTE_READWRITE,&oldProt);
			*(PDWORD)dwPatchAddrScanReloc1USA[x] = (DWORD)aScanListMemory;
		}
		else if(iGtaVersion == GTASA_VERSION_EU10) {
			VirtualProtect((PVOID)dwPatchAddrScanReloc1EU[x],4,PAGE_EXECUTE_READWRITE,&oldProt);
			*(PDWORD)dwPatchAddrScanReloc1EU[x] = (DWORD)aScanListMemory;
		}
		x++;
	}

	// SECOND PREPARED LIST OF ACCESSORS <G>
	x=0;
	while(x!=56) {
		if(iGtaVersion == GTASA_VERSION_USA10) {
			VirtualProtect((PVOID)dwPatchAddrScanReloc2USA[x],8,PAGE_EXECUTE_READWRITE,&oldProt);
			*(PDWORD)(dwPatchAddrScanReloc2USA[x] + 3) = (DWORD)aScanListMemory;
		}
		else if(iGtaVersion == GTASA_VERSION_EU10) {
			VirtualProtect((PVOID)dwPatchAddrScanReloc2EU[x],8,PAGE_EXECUTE_READWRITE,&oldProt);
			*(PDWORD)(dwPatchAddrScanReloc2EU[x] + 3) = (DWORD)aScanListMemory;
		}
		x++;
	}

	// THIRD LIST THAT POINTS TO THE BASE SCANLIST MEMORY + 4
	x=0;
	while(x!=11) {
		VirtualProtect((PVOID)dwPatchAddrScanReloc3[x],8,PAGE_EXECUTE_READWRITE,&oldProt);
		*(PDWORD)(dwPatchAddrScanReloc3[x] + 3) = (DWORD)(aScanListMemory+4);
		x++;
	}

	// FOURTH LIST THAT POINTS TO THE END OF THE SCANLIST
	x=0;
	while(x!=4) {
		VirtualProtect((PVOID)dwPatchAddrScanRelocEnd[x],4,PAGE_EXECUTE_READWRITE,&oldProt);
		*(PDWORD)(dwPatchAddrScanRelocEnd[x]) = (DWORD)(aScanListMemory+sizeof(ScanListMemory));
		x++;
	}

	// Others that didn't fit.
	VirtualProtect((PVOID)0x564DC7,4,PAGE_EXECUTE_READWRITE,&oldProt);
	*(PDWORD)0x564DC7 = (DWORD)(aScanListMemory+115200);

	VirtualProtect((PVOID)0x40936A,4,PAGE_EXECUTE_READWRITE,&oldProt);
	*(PDWORD)0x40936A = (DWORD)(aScanListMemory+4);

	// Reset the exe scanlist mem for playerinfo's
	memset((BYTE*)0xB7D0B8,0,8*14400);
}

//----------------------------------------------------------
