
/*
	Unused RPC IDs:
		\x00 \x01 \x02 \x03 \x04 \x05 \x06 \x07 \x08 \x09
		\x0A \x33 \x64 \x6D \x6E \x72 \x8D \x8E \x8F \xB3
		\xB4 \xB5 \xB6 \xB7 \xB8 \xB9 \xBA \xBB \xBC \xBD
		\xBE \xBF \xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7
		\xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF \xD0 \xD1
		\xD2 \xD3 \xD4 \xD5 \xD6 \xD7 \xD8 \xD9 \xDA \xDB
		\xDC \xDD \xDE \xDF \xE0 \xE1 \xE2 \xE3 \xE4 \xE5
		\xE6 \xE7 \xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF
		\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 \xF8 \xF9
		\xFA \xFB \xFC \xFD \xFE \xFF
*/

#define RPC_Unk22					"\x22"
#define RPC_Unk24					"\x24"
#define RPC_Unk3A					"\x3A"
#define RPC_Unk3B					"\x3B"
#define RPC_Unk3D					"\x3D"
#define RPC_SetCheckpoint			"\x6B"
#define RPC_DisableCheckpoint		"\x25"
#define RPC_SetRaceCheckpoint		"\x26"
#define RPC_DisableRaceCheckpoint	"\x27"
#define RPC_UpdateScoresPingsIPs	"\x9B"
#define RPC_SvrStats				"\x66"
#define RPC_GameModeRestart			"\x28"
#define RPC_ConnectionRejected		"\x82"
#define RPC_ClientMessage			"\x5D"
#define RPC_WorldTime				"\x5E"
#define RPC_Unk5F					"\x5F"
#define RPC_Unk3F					"\x3F"
#define RPC_Unk97					"\x97"
#define RPC_ScmEvent				"\x60"
#define RPC_Weather					"\x98"
#define RPC_Unk1D					"\x1D"
#define RPC_Unk1E					"\x1E"
#define RPC_Unk3C					"\x3C"
#define RPC_UnkA6					"\xA6"
#define RPC_UnkA3					"\xA3"
#define RPC_UnkA4					"\xA4"
#define RPC_UnkA5					"\xA5"
#define RPC_WorldPlayerAdd			"\x20"
#define RPC_DamageVehicle			"\x6A"
#define RPC_Unk18					"\x18"
#define RPC_EnterVehicle			"\x1A"
#define RPC_ExitVehicle				"\x9A"
#define RPC_Unk89					"\x89"
#define RPC_ServerQuit				"\x8A"
#define RPC_InitGame				"\x8B"
#define RPC_Chat					"\x65"
#define RPC_RequestClass			"\x80"
#define RPC_RequestSpawn			"\x81"
#define RPC_EditAttachedObject		"\x74"
#define RPC_EditObject				"\x75"
#define RPC_SelectObject			"\x1B"
#define RPC_Unk1C					"\x1C"
#define RPC_UnkAA					"\xAA"
#define RPC_ClientCheck				"\x67"
#define RPC_UnkAB					"\xAB"
#define RPC_UnkAC					"\xAC"
#define RPC_PlayerDamage			"\x73"
#define RPC_SetInteriorId			"\x76"
#define RPC_ScriptCash				"\x1F"
#define RPC_ClickMap				"\x77"
#define RPC_VehicleDestroyed		"\x88"
#define RPC_PickedUpWeapon			"\x61"
#define RPC_PickedUpPickup			"\x83"
#define RPC_MenuSelect				"\x84"
#define RPC_MenuQuit				"\x8C"
#define RPC_DialogResponse			"\x3E"
#define RPC_ClickPlayer				"\x17"
#define RPC_ClientJoin				"\x19"
#define RPC_NPCJoin					"\x36"
#define RPC_Spawn					"\x34"
#define RPC_Death					"\x35"
#define RPC_ServerCommand			"\x32"
#define RPC_ClickTextDraw			"\x53"
#define RPC_CameraTarget			"\xA8"
#define RPC_ActorDamage				"\xB1"

#define RPC_ScrUnkA7				"\xA7"
#define RPC_ScrUnk38				"\x38"
#define RPC_ScrUnk90				"\x90"
#define RPC_ScrUnk91				"\x91"
#define RPC_ScrSetGravity			"\x92"
#define RPC_ScrUnk93				"\x93"
#define RPC_ScrUnk94				"\x94"
#define RPC_ScrUnk95				"\x95"
#define RPC_ScrUnk2C				"\x2C"
#define RPC_ScrUnk2D				"\x2D"
#define RPC_ScrUnk2E				"\x2E"
#define RPC_ScrUnk2F				"\x2F"
#define RPC_ScrUnk4F				"\x4F"
#define RPC_ScrUnk50				"\x50"
#define RPC_ScrUnk63				"\x63"
#define RPC_ScrUnk7A				"\x7A"
#define RPC_ScrUnk7B				"\x7B"
#define RPC_ScrUnk7C				"\x7C"
#define RPC_ScrUnk7D				"\x7D"
#define RPC_ScrUnk7E				"\x7E"
#define RPC_ScrUnk7F				"\x7F"
#define RPC_ScrUnk39				"\x39"
#define RPC_ScrUnk4A				"\x4A"
#define RPC_ScrUnk4B				"\x4B"
#define RPC_ScrUnk85				"\x85"
#define RPC_ScrUnk86				"\x86"
#define RPC_ScrUnk87				"\x87"
#define RPC_ScrUnk69				"\x69"
#define RPC_ScrAddGangZone			"\x6C"
#define RPC_ScrRemoveGangZone		"\x78"
#define RPC_ScrFlashGangZone		"\x79"
#define RPC_ScrStopFlashGangZone	"\x55"
#define RPC_ScrUnk56				"\x56"
#define RPC_ScrUnk57				"\x57"
#define RPC_ScrUnk58				"\x58"
#define RPC_ScrUnk68				"\x68"
#define RPC_ScrUnk59				"\x59"
#define RPC_ScrUnk5A				"\x5A"
#define RPC_ScrUnk5B				"\x5B"
#define RPC_ScrUnk6F				"\x6F"
#define RPC_ScrUnk62				"\x62"
#define RPC_ScrUnk5C				"\x5C"
#define RPC_ScrUnk96				"\x96"
#define RPC_ScrUnk70				"\x70"
#define RPC_ScrSetSpawnInfo			"\x44"
#define RPC_ScrUnk45				"\x45"
#define RPC_ScrUnk99				"\x99"
#define RPC_ScrUnk0B				"\x0B"
#define RPC_ScrSetPlayerPos			"\x0C"
#define RPC_ScrUnk0D				"\x0D"
#define RPC_ScrUnk0E				"\x0E"
#define RPC_ScrPutPlayerInVehicle	"\x46"
#define RPC_ScrRemovePlayerFromVehicle "\x47"
#define RPC_ScrUnk48				"\x48"
#define RPC_ScrDisplayGameText		"\x49"
#define RPC_ScrUnk9C				"\x9C"
#define RPC_ScrUnk9D				"\x9D"
#define RPC_ScrUnk9E				"\x9E"
#define RPC_ScrUnk9F				"\x9F"
#define RPC_ScrUnkA0				"\xA0"
#define RPC_ScrUnkA1				"\xA1"
#define RPC_ScrUnkA2				"\xA2"
#define RPC_ScrUnk0F				"\x0F"
#define RPC_ScrUnk10				"\x10"
#define RPC_ScrUnk11				"\x11"
#define RPC_ScrUnk12				"\x12"
#define RPC_ScrSetPlayerFacingAngle	"\x13"
#define RPC_ScrUnk14				"\x14"
#define RPC_ScrUnk15				"\x15"
#define RPC_ScrUnk16				"\x16"
#define RPC_ScrUnk40				"\x40"
#define RPC_ScrUnk41				"\x41"
#define RPC_ScrUnk42				"\x42"
#define RPC_ScrUnk37				"\x37"
#define RPC_ScrUnk21				"\x21"
#define RPC_ScrUnk23				"\x23"
#define RPC_ScrUnk43				"\x43"
#define RPC_ScrUnk71				"\x71"
#define RPC_ScrUnk29				"\x29"
#define RPC_ScrUnk2A				"\x2A"
#define RPC_ScrUnk2B				"\x2B"
#define RPC_ScrUnk51				"\x51"
#define RPC_ScrUnk52				"\x52"
#define RPC_ScrUnk53				"\x53"
#define RPC_ScrUnk54				"\x54"
#define RPC_ScrUnkA9				"\xA9"
#define RPC_ScrUnkAD				"\xAD"
#define RPC_ScrUnkAE				"\xAE"
#define RPC_ScrUnkAF				"\xAF"
#define RPC_ScrUnkB0				"\xB0"
#define RPC_ScrUnkB2				"\xB2"
#define RPC_ScrUnk30				"\x30"
#define RPC_ScrInitMenu				"\x4C"
#define RPC_ScrShowMenu				"\x4D"
#define RPC_ScrHideMenu				"\x4E"
#define RPC_ScrUnk31				"\x31"
