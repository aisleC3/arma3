#pragma once

enum EventHandlerEnum { // Credits to Douggem
	Killed = 0,
	Hit = 1,
	Engine = 2,
	GetIn = 3,
	GetOut = 4,
	Take = 5,
	Put = 6,
	InventoryOpened = 7,
	InventoryClosed = 8,
	ContainerOpened = 9,
	ContainerClosed = 10,
	Fired = 11,
	FiredNear = 12,
	IncomingMissile = 13,
	Dammaged = 14,
	Gear = 15,
	Fuel = 16,
	AnimChanged = 17,
	AnimDone = 18,
	Init0 = 19,
	Delete = 20,
	LandedTouchDown = 21,
	LandedStopped = 22,
	HandleDamage = 23,
	HitPart = 24,
	Suppressed = 25,
	LoadOutChanged = 26,
	CargoChanged = 27,
	GetInMan = 28,
	GetOutMan = 29,
	Respawn = 30,
	TurnOut = 31,
	TurnIn = 32,
	AttachTo = 33,
	HandleHeal = 34,
	HandleIdentity = 35,
	AnimStateChanged = 36,
	WeaponAssembled = 37,
	WeaponDisassembled = 38,
	Local = 39,
	SelectedActionChanged = 40,
	SelectedActionPerformed = 41,
	EpeContactStart = 42,
	EpeContactEnd = 43,
	EpeContact = 44,
	SelectedRotorLibActionChanged = 45,
	SelectedRotorLibActionPerformed = 46,
	RopeBreak = 47,
	RopeAttach = 48,
	Explosion = 49,
	PostReset = 50,
	ControlsShifted = 51,
	FastropeDone = 52,
	SoundPlayed = 53,
	TaskSetAsCurrent = 54,
	curatorObjectSelectionChanged = 55,
	curatorGroupSelectionChanged = 56,
	curatorWaypointSelectionChanged = 57,
	curatorMarkerSelectionChanged = 58,
	curatorObjectEdited = 59,
	curatorWaypointEdited = 60,
	curatorMarkerEdited = 61,
	curatorObjectDeleted = 62,
	curatorWaypointDeleted = 63,
	curatorMarkerDeleted = 64,
	curatorObjectPlaced = 65,
	curatorGroupPlaced = 66,
	curatorMarkerPlaced = 67,
	curatorWaypointPlaced = 68,
	curatorObjectRegistered = 69,
	curatorObjectDoubleClicked = 70,
	curatorGroupDoubleClicked = 71,
	curatorWaypointDoubleClicked = 72,
	curatorMarkerDoubleClicked = 73,
	curatorFeedbackMessage = 74,
	curatorObjectGetOut = 75,
	curatorPinged = 76,
	HandleRating = 77,
	HandleScore = 78
};


class EventHandlerContainer
{
public:
	char pad_0x0000[0x10]; //0x0000
	ArmaString* Name; //0x0010 
	char pad_0x0018[0x8]; //0x0018

}; //Size=0x0020

class Event
{
public:
	char pad_0x0000[0x8]; //0x0000
	__int32 type; //0x0008 
	char pad_0x000C[0x4]; //0x000C
	EventHandlerContainer* Container; //0x0010 
	__int32 size; //0x0018 
	char pad_0x001C[0x4]; //0x001C
	__int32 maxSize; //0x0020 
	char pad_0x0024[0x4]; //0x0024

	void ModEventHandler(std::string execute)// this shit dont work
	{
		*(int*)(this + 0x8) = InventoryOpened;

		char HandlerString[256];
		sprintf(HandlerString, "%s", execute.c_str());
		strcpy((char*)(Container->Name + 0x10), HandlerString);
	}

}; //Size=0x0028

class EventHandler
{
public:
	Event GetEvent(int idx)
	{
		return *(Event*)(this + (0x28 * idx));
	}

}; //Size=0x00E8