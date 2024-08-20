
#include "../main.h"
#include "util.h"

//-----------------------------------------------------------
// CONSTRUCTOR

CVehicle::CVehicle(int iType, float fPosX, float fPosY,
				   float fPosZ, float fRotation, BOOL bKeepModelLoaded,
				   int a8)
{
	// TODO: CVehicle::CVehicle .text:100B88F0
}

//-----------------------------------------------------------

void CVehicle::LinkToInterior(int iInterior)
{
	if(GamePool_Vehicle_GetAt(m_dwGTAId)) {
		ScriptCommand(&link_vehicle_to_interior, m_dwGTAId, iInterior);
	}
}

//-----------------------------------------------------------
// If the game has internally destroyed the vehicle
// during this frame, the vehicle pointer should become 0

void CVehicle::ResetPointers()
{
	if(!m_pVehicle) return;

	m_pVehicle = GamePool_Vehicle_GetAt(m_dwGTAId);
	m_pEntity = (ENTITY_TYPE *)m_pVehicle;
}

//-----------------------------------------------------------

BOOL CVehicle::HasADriver()
{
	if(!m_pVehicle) return FALSE;
	if(!GamePool_Vehicle_GetAt(m_dwGTAId)) return FALSE;

	if(m_pVehicle) {
		if(m_pVehicle->pDriver && IN_VEHICLE(m_pVehicle->pDriver) && m_pVehicle->pDriver->dwPedType == 0)
			return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------

BOOL CVehicle::IsOccupied()
{
	if(m_pVehicle) {
		if(m_pVehicle->pDriver) return TRUE;
		if(m_pVehicle->pPassengers[0]) return TRUE;
		if(m_pVehicle->pPassengers[1]) return TRUE;
		if(m_pVehicle->pPassengers[2]) return TRUE;
		if(m_pVehicle->pPassengers[3]) return TRUE;
		if(m_pVehicle->pPassengers[4]) return TRUE;
		if(m_pVehicle->pPassengers[5]) return TRUE;
		if(m_pVehicle->pPassengers[6]) return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------

void CVehicle::SetLockedState(int iLocked)
{
	if(!m_pVehicle) return;

	if(iLocked) {
		ScriptCommand(&lock_car,m_dwGTAId,1);
	} else {
		ScriptCommand(&lock_car,m_dwGTAId,0);
	}
}

//-----------------------------------------------------------

void CVehicle::SetEngineState(BOOL bState)
{
	if(!m_pVehicle) return;

	if(!bState) {
		m_pVehicle->byteFlags &= 0xDF;
	} else {
		m_pVehicle->byteFlags |= 0x20;
	}
}

//-----------------------------------------------------------

