﻿#include "windows.h"
#include <stdint.h>
#include <iostream>
#include <Winternl.h>
#include "Canvas.h"
#include "decryption.h"
#include "hook.h"
#include "Decryptor.h"
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

using PostRenderHook = void(*)(uintptr_t _this, UCanvas* canvas);
PostRenderHook pRender = 0;

uintptr_t UWorldXOR;
AShooterCharacter* actor;
UWorld* UWorldClass;
UGameInstance* GameInstance;
ULocalPlayer* LocalPlayers;
ULocalPlayer* LocalPlayer;
APlayerController* MyControllers;

using namespace std;
float DegreeToRadian(float degrees) {
	return degrees * (PI / 180);
}

void DrawTextRGB(UCanvas* canvas, const wchar_t* text, float x, float y, FLinearColor color, bool CenterX = 0)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, bOutline, { 0, 0, 0, 1 });
}
void DrawTextRGBWithFString(UCanvas* canvas, FString text, float x, float y, FLinearColor color, bool CenterX = 0)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, bOutline, { 0, 0, 0, 1 });
}

void xxDrawTextRGB(UCanvas* canvas, FString text, float x, float y, FLinearColor color)
{
	canvas->K2_DrawText(text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 0, 0, false, { 0, 0, 0, 1 });
}
FLinearColor RGBtoFLC(float R, float G, float B)
{
	return { R / 255, G / 255, B / 255, 1 };
}

bool kekIsOff = 0; // debugging purposes ONLY solely for THAT

static FLinearColor VisibleChams{ 0.0f,1.0f,0.0f,5.9f };//Chams//Blue
static FLinearColor InvisibleChams{ 1.0f,0.0f,0.0f,5.9f };//Chams//Blue

static FLinearColor VisibleBox_ESPColor{ 255.0f,255.0f,255.0f,1.0f };//BoxVisible
static FLinearColor Invisible_ESPColor{ 255.0f,0.0f,0.0f,1.0f };//BoxInvisible

static FLinearColor VisibleSkeletonColor{ 0.0f,255.0f,0.0f,1.0f };//VisibleSkeletonColor

static FLinearColor InvisibleSnapColor{ 255.0f,0.0f,0.0f,1.0f };
static FLinearColor VisibleSnapColor{ 255.0f,255.0f,255.0f,1.0f };

static FLinearColor Name_Color{ 255.0f, 255.0f, 255.0f,255.0f };
static FLinearColor healthcolors = RGBtoFLC(0, 255, 0);
static FLinearColor circlecol = { 255.0f, 255.0f, 255.0f, 1.0f };
static FLinearColor fovcolor = { 255.0f, 255.0f, 255.0f, 1.0f };
static FLinearColor WeaponColor = { 255.0f, 255.0f, 255.0f, 1.0f };
static FLinearColor crosscolor = { 255.0f, 255.0f, 255.0f, 1.0f };

static bool menu_opened = true;
static bool menu = true;

FVector2D pos = { ((float)GetSystemMetrics(SM_CXSCREEN) / 2) - 500, ((float)GetSystemMetrics(SM_CYSCREEN) / 2) - 475 };
FVector2D poss = { ((float)GetSystemMetrics(SM_CXSCREEN) / 2) - 200, ((float)GetSystemMetrics(SM_CYSCREEN) / 2) - 175 };

static bool Auto360 = false;
static bool ChamsESP = false;

//SpinBot
static bool SpinBot = false;
static bool t = true;
static auto OldAimAngles = FVector();
float spinMULTIX = -1;
static float spinY = 10;
static float spinX = 10;
static float spinMULTIY = 0.f;
static float spinMULTIZ = 0.f;

static bool box2d = false;
static bool SpinBotBool = false;
static bool chammyteam = false;
static bool shieldhbar = false;
static bool Spike = false;
static bool fovchanger = false;

static bool EnableRageBot = false;
static bool autoshoot = false;
static bool autoaim = false;
static bool AutoFire = false;
int autofire;
static bool HeadCircleEsp = false;
static bool vischeckmenu = false;
static bool AgentName = false;
static bool ItsGamerDocMode = false;

//WireFrame*
static bool Always = false;
static bool Behind = false;

//Misc
static bool FlyHack = false;
static float PlayerDistange = 150;
static bool drawfov = false;
static bool RenderCross = true;
static bool HealthEsp = false;
float OverrideCrouchTimeSeconds = 0.0000001f;
static bool skiptutorial = false;

int SnapPositionint = 2;
int SnapPositionİnt = 0;
int SnapMesh = 0;

static bool Minimap = false;
static bool weaponesp = false;
static bool Watermark = true;
static bool drawcross = false;
static bool ThirdPerson = false;
static bool Visible_Check_ESP = false;
static bool skeleton = false;
static bool UnlockAllSkin = true;
static bool snaplinenz = false;
static bool enableaim = false;
static bool NoSpread = false;
static bool WireFrame = false;
static bool WeaponChams = false;
static bool WireFrameWeapon = false;
static bool WireFrameHand = false;
static bool setscale = false;
static bool Silent = false;
int NoSpreadKey;
//Misc
static float radius = 4.0f;
static float radius2 = 7.0f;
static float fovchangur = 0.0f;
static float Scale = 1.f;


//+++++++++++++++++++
static bool silentspinbot = false;

//Skins
static bool EnableKnife = false;
static bool EnableMarshall = false;
static bool EnableGhost = false;
static bool EnableVandal = false;
static bool EnableOperator = false;
static bool EnableGuardian = false;
static bool EnableStinger = false;
static bool EnableClassic = false;
static bool EnableSpectre = false;
static bool EnablePhantom = false;
static bool EnableSheriff = false;
static bool EnableFrenzy = false;
static bool SkinCheckControl = false;

int marshall = 1;
int skinvandal = 1;
int skinclassic = 1;
int skinsheriff = 1;
int skinphantom = 1;
int skinguardian = 1;
int skinspectre = 1;
int skinknife = 1;
int skinghost = 1;
int skinfrenzy = 1;
int skinoperator = 1;
int skinstinger = 1;

//++++++++++++++++++++

int SkinKey;
int skinlevel = 4;
int KEKWNOKEY;
static bool AutoStopBool = false;
int BhopKey = VK_SPACE;
int RageBotKeybind;
int spinbotkeybind;
int aimbotmode = 0;
int aimbone = 0;
int rageaimbone = 0;
bool healthbar = false;

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

float ScreenCenterX = Width / 2;
float ScreenCenterY = Height / 2;


float fovChanger = 21.0f;//Fov Changer
float smooth = 10.0f;
float LineamountCross = 35.0f;
float LineamountCircle = 25.0f;
float LineamountFov = 35.0f;
float chamsglowvalue = 1;
float ESPThickness = 1;

bool Mesh3PModifed = false;
bool Below = false;
bool Middle = false;
bool Bottom = false;
static bool SmootAimBool = false;


//Configs
bool LegitCFG = false;
bool RageCFG = false;
bool ApplyConfig = false;
bool ResetConfig = false;

struct FMinimalViewInfo {
	FVector Location;
	FVector Rotation;
	float FOV;
};
struct Bone {
	BYTE thing[0xCC];
	float x;
	BYTE thing2[0xC];
	float y;
	BYTE thing3[0xC];
	float z;
};

boolean in_rect(double centerX, double centerY, double radius, double x, double y) {
	return x >= centerX - radius && x <= centerX + radius &&
		y >= centerY - radius && y <= centerY + radius;
}
FVector GetBoneMatrix(void* Mesh, int Idx) {
	FMatrix Matrix;
	reinterpret_cast<FMatrix* (__fastcall*)(void*, FMatrix*, int)>((uintptr_t)VALORANT::Module + Offsets::bone_matrix)(Mesh, &Matrix, Idx); // E8 ?? ?? ?? ?? 48 8B 47 30 F3 0F 10 45 ??
	return  { Matrix.WPlane.X, Matrix.WPlane.Y, Matrix.WPlane.Z };
}
FVector FindSkeleton(APlayerController* controller, void* mesh, int i)
{
	FVector2D drawtextat;
	return controller->ProjectWorldLocationToScreen(GetBoneMatrix(mesh, i), drawtextat, 0);
}
__forceinline void Clamp(FVector& Ang) {
	if (Ang.X < 0.f)
		Ang.X += 360.f;

	if (Ang.X > 360.f)
		Ang.X -= 360.f;

	if (Ang.Y < 0.f) Ang.Y += 360.f;
	if (Ang.Y > 360.f) Ang.Y -= 360.f;
	Ang.Z = 0.f;
}
void normalize(FVector& in) {
	if (in.X > 89.f) in.X -= 360.f;
	else if (in.X < -89.f) in.X += 360.f;

	// in.y = fmodf(in.y, 360.0f);
	while (in.Y > 180)in.Y -= 360;
	while (in.Y < -180)in.Y += 360;
	in.Z = 0;
}

FVector smooth_aim(FVector target, FVector delta_rotation, float smooth) {
	FVector diff = target - delta_rotation;
	normalize(diff);
	return delta_rotation + diff / smooth;
}

FVector get_error_angle(uint64_t actor, uint64_t firing_state_component) {
	static auto get_spread_values_fn =
		(float* (__fastcall*)(uint64_t, float*))(BaseAddress + Offsets::get_spread_values_fn);
	static auto get_spread_angles_fn =
		(void(__fastcall*)(uint64_t, FVector*, float, float, int, int, uint64_t))(BaseAddress + Offsets::get_spread_angles_fn);
	static auto get_firing_location_and_direction_fn =
		(void(__fastcall*)(uint64_t, FVector*, FVector*))(BaseAddress + Offsets::get_firing_location_and_direction_fn);
	static auto to_vector_and_normalize_fn =
		(FVector * (__fastcall*)(FVector*, FVector*))(BaseAddress + Offsets::to_vector_and_normalize_fn);
	static auto to_angle_and_normalize_fn =
		(FVector * (__fastcall*)(FVector*, FVector*))(BaseAddress + Offsets::to_angle_and_normalize_fn);

	static uint8_t error_values[0x900] = { 0 };
	static uint8_t seed_data_snapshot[0x118] = { 0 };
	static uint8_t spread_angles[0x900] = { 0 };
	static uint8_t out_spread_angles[0x900] = { 0 };

	if (!actor || !firing_state_component)
		return FVector(0, 0, 0);

	memset(error_values, 0, sizeof(error_values));
	memset(seed_data_snapshot, 0, sizeof(seed_data_snapshot));
	memset(spread_angles, 0, sizeof(spread_angles));
	memset(out_spread_angles, 0, sizeof(out_spread_angles));

	*(uint64_t*)(&out_spread_angles[0]) = (uint64_t)&spread_angles[0];
	*(int*)(&out_spread_angles[0] + 8) = 1;
	*(int*)(&out_spread_angles[0] + 12) = 1; //It's a TArray but I'm lazy

	uint64_t seed_data = Memory::ReadStub<uint64_t>(firing_state_component + 0x420);
	memcpy((void*)seed_data_snapshot, (void*)seed_data, sizeof(seed_data_snapshot)); //Make our own copy since we don't want to desync our own seed component

	uint64_t stability_component = Memory::ReadStub<uint64_t>(firing_state_component + 0x410);
	if (stability_component)
		get_spread_values_fn(stability_component, (float*)&error_values[0]);

	FVector temp1, temp2 = FVector(0, 0, 0);
	FVector previous_firing_direction, firing_direction = FVector(0, 0, 0);
	get_firing_location_and_direction_fn(actor, &temp1, &previous_firing_direction);
	to_vector_and_normalize_fn(&previous_firing_direction, &temp2);
	to_angle_and_normalize_fn(&temp2, &temp1);
	previous_firing_direction = temp1;
	temp1.X += *(float*)(&error_values[0] + 12); //Your recoil angle
	temp1.Y += *(float*)(&error_values[0] + 16);
	to_vector_and_normalize_fn(&temp1, &firing_direction);

	float error_degrees = *(float*)(&error_values[0] + 8) + *(float*)(&error_values[0] + 4);
	float error_power = *(float*)(firing_state_component + 0x3f0);
	int error_retries = *(int*)(firing_state_component + 0x3f4);
	get_spread_angles_fn(((uint64_t)&seed_data_snapshot[0]) + 0xE8, &firing_direction, error_degrees, error_power, error_retries, 1, (uint64_t)&out_spread_angles[0]);

	FVector spread_vector = *(FVector*)(&spread_angles[0]);
	to_angle_and_normalize_fn(&spread_vector, &firing_direction);

	return firing_direction - previous_firing_direction; //Get the difference. Now subtract it against your aimbot!
}


void DrawSkeletonBot(APlayerController* controller, UCanvas* Canvas, void* mesh, FLinearColor cColor, float kalinlik = ESPThickness)
{

	FVector vHipOut = FindSkeleton(controller, mesh, 3);

	FVector vHeadBoneOut = FindSkeleton(controller, mesh, 8);
	FVector vNeckOut = FindSkeleton(controller, mesh, 7);

	FVector vUpperArmLeftOut = FindSkeleton(controller, mesh, 11);
	FVector vLeftHandOut = FindSkeleton(controller, mesh, 12);
	FVector vLeftHandOut1 = FindSkeleton(controller, mesh, 13);

	FVector vUpperArmRightOut = FindSkeleton(controller, mesh, 36);
	FVector vRightHandOut = FindSkeleton(controller, mesh, 37);
	FVector vRightHandOut1 = FindSkeleton(controller, mesh, 38);



	FVector vLeftThighOut = FindSkeleton(controller, mesh, 63);
	FVector vLeftCalfOut = FindSkeleton(controller, mesh, 65);
	FVector vLeftFootOut = FindSkeleton(controller, mesh, 69);

	FVector vRightThighOut = FindSkeleton(controller, mesh, 77);
	FVector vRightCalfOut = FindSkeleton(controller, mesh, 79);
	FVector vRightFootOut = FindSkeleton(controller, mesh, 83);
	{

		Canvas->K2_DrawLine({ vNeckOut.X, vNeckOut.Y }, { vHeadBoneOut.X, vHeadBoneOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vHipOut.X, vHipOut.Y }, { vNeckOut.X, vNeckOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vUpperArmLeftOut.X, vUpperArmLeftOut.Y }, { vNeckOut.X, vNeckOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vUpperArmRightOut.X, vUpperArmRightOut.Y }, { vNeckOut.X, vNeckOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vLeftHandOut.X, vLeftHandOut.Y }, { vUpperArmLeftOut.X, vUpperArmLeftOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vRightHandOut.X, vRightHandOut.Y }, { vUpperArmRightOut.X, vUpperArmRightOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vLeftHandOut.X, vLeftHandOut.Y }, { vLeftHandOut1.X, vLeftHandOut1.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vRightHandOut.X, vRightHandOut.Y }, { vRightHandOut1.X, vRightHandOut1.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vLeftThighOut.X, vLeftThighOut.Y }, { vHipOut.X, vHipOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vRightThighOut.X, vRightThighOut.Y }, { vHipOut.X, vHipOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vLeftCalfOut.X, vLeftCalfOut.Y }, { vLeftThighOut.X, vLeftThighOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vRightCalfOut.X, vRightCalfOut.Y }, { vRightThighOut.X, vRightThighOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vLeftFootOut.X, vLeftFootOut.Y }, { vLeftCalfOut.X, vLeftCalfOut.Y }, kalinlik, cColor);
		Canvas->K2_DrawLine({ vRightFootOut.X, vRightFootOut.Y }, { vRightCalfOut.X, vRightCalfOut.Y }, kalinlik, cColor);
	}

}
FString character_name(FString in)
{
	if (in.ToString().find("Training") != std::string::npos)
		return FString(L"Bot");
	if (in.ToString().find("BountyHunter_PC_C") != std::string::npos)
		return FString(L"Fade");
	if (in.ToString().find("Stealth_PC_C") != std::string::npos)
		return FString(L"Yoru");
	if (in.ToString().find("Pandemic_PC_C") != std::string::npos)
		return FString(L"Viper");
	if (in.ToString().find("Hunter_PC_C") != std::string::npos)
		return FString(L"Sova");
	if (in.ToString().find("Guide_PC_C") != std::string::npos)
		return FString(L"Skye");
	if (in.ToString().find("Thorne_PC_C") != std::string::npos)
		return FString(L"Sage");
	if (in.ToString().find("Vampire_PC_C") != std::string::npos)
		return FString(L"Reyna");
	if (in.ToString().find("Clay_PC_C") != std::string::npos)
		return FString(L"Raze");
	if (in.ToString().find("Phoenix_PC_C") != std::string::npos)
		return FString(L"Phoenix");
	if (in.ToString().find("Wraith_PC_C") != std::string::npos)
		return FString(L"Omen");
	if (in.ToString().find("Sprinter_PC_C") != std::string::npos)
		return FString(L"Neon");
	if (in.ToString().find("Killjoy_PC_C") != std::string::npos)
		return FString(L"Killjoy");
	if (in.ToString().find("Grenadier_PC_C") != std::string::npos)
		return FString(L"Kayo");
	if (in.ToString().find("Wushu_PC_C") != std::string::npos)
		return FString(L"Jett");
	if (in.ToString().find("Gumshoe_PC_C") != std::string::npos)
		return FString(L"Cypher");
	if (in.ToString().find("Deadeye_PC_C") != std::string::npos)
		return FString(L"Chamber");
	if (in.ToString().find("Sarge_PC_C") != std::string::npos)
		return FString(L"Brimstone");
	if (in.ToString().find("Breach_PC_C") != std::string::npos)
		return FString(L"Breach");
	if (in.ToString().find("Rift_TargetingForm_PC_C") != std::string::npos)
		return FString(L"Astra");
	if (in.ToString().find("Rift_PC_C") != std::string::npos)
		return FString(L"Astra");
	if (in.ToString().find("Mage_PC_C") != std::string::npos)
		return FString(L"Harbor");
	else
		return FString(L"N/A");
}
FString ItsGamerDoc(FString in)
{
	if (in.ToString().find("Training") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("BountyHunter_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Stealth_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Pandemic_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Hunter_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Guide_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Thorne_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Vampire_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Clay_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Phoenix_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Wraith_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Sprinter_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Killjoy_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Grenadier_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Wushu_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Gumshoe_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Deadeye_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Sarge_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Breach_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Rift_TargetingForm_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Rift_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	if (in.ToString().find("Mage_PC_C") != std::string::npos)
		return FString(L"ItsGamerDoc");
	else
		return FString(L"N/A");
}
FString weapon_name(FString in)
{
	if (in.ToString().find("Ability_Melee_Base_C") != std::string::npos)
		return FString(L"Knife");
	if (in.ToString().find("BasePistol_C") != std::string::npos)
		return FString(L"Classic");
	if (in.ToString().find("TrainingBotBasePistol_C") != std::string::npos)
		return FString(L"Classic");
	if (in.ToString().find("SawedOffShotgun_C") != std::string::npos)
		return FString(L"Shorty");
	if (in.ToString().find("AutomaticPistol_C") != std::string::npos)
		return FString(L"Frenzy");
	if (in.ToString().find("LugerPistol_C") != std::string::npos)
		return FString(L"Ghost");
	if (in.ToString().find("RevolverPistol_C") != std::string::npos)
		return FString(L"Sheriff");
	if (in.ToString().find("Vector_C") != std::string::npos)
		return FString(L"Stinger");
	if (in.ToString().find("SubMachineGun_MP5_C") != std::string::npos)
		return FString(L"Spectre");
	if (in.ToString().find("PumpShotgun_C") != std::string::npos)
		return FString(L"Bucky");
	if (in.ToString().find("AssaultRifle_Burst_C") != std::string::npos)
		return FString(L"Bulldog");
	if (in.ToString().find("DMR_C") != std::string::npos)
		return FString(L"Guardian");
	if (in.ToString().find("AssaultRifle_ACR_C") != std::string::npos)
		return FString(L"Phantom");
	if (in.ToString().find("AssaultRifle_AK_C") != std::string::npos)
		return FString(L"Vandal");
	if (in.ToString().find("LeverSniperRifle_C") != std::string::npos)
		return FString(L"Marshall");
	if (in.ToString().find("BoltSniper_C") != std::string::npos)
		return FString(L"Operator");
	if (in.ToString().find("LightMachineGun_C") != std::string::npos)
		return FString(L"Ares");
	if (in.ToString().find("HeavyMachineGun_C") != std::string::npos)
		return FString(L"Odin");
	else
		return FString(L"N/A");
}




void DrawBox(UCanvas* can, FVector2D& topleft, FVector2D& downright, FLinearColor clr)
{
	auto h = downright.Y - topleft.Y;
	auto w = downright.X - topleft.X;

	auto downleft = FVector2D{ topleft.X , downright.Y };
	auto topright = FVector2D{ downright.X, topleft.Y };

	auto thicc = ESPThickness;

	FLinearColor xclr = RGBtoFLC(0, 0, 0);

	can->K2_DrawLinex(topleft, { downright.X, topleft.Y }, thicc, clr);
	can->K2_DrawLinex(topleft, { topleft.X , downright.Y }, thicc, clr);
	can->K2_DrawLinex(downright, { topleft.X , downright.Y }, thicc, clr);
	can->K2_DrawLine(downright, { downright.X, topleft.Y }, thicc, clr);
}
uintptr_t OffsetGetActorBounds;
void GetActorBounds(AShooterCharacter* Actor, bool bOnlyCollidingComponents, FVector* Origin, FVector* BoxExtent, bool bIncludeFromChildActors)
{
	reinterpret_cast<void(*)(AShooterCharacter*, bool, FVector * pos, FVector * screen, bool)> ((uintptr_t)GetModuleHandleA(0) + Offsets::GetActorBounds)(Actor, 0, Origin, BoxExtent, 0);
}
static FVector2D scr[8];
void FMath::SinCos(float* ScalarSin, float* ScalarCos, float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = (INV_PI * 0.5f) * Value;
	if (Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = Value - (2.0f * PI) * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	float sign;
	if (y > HALF_PI)
	{
		y = PI - y;
		sign = -1.0f;
	}
	else if (y < -HALF_PI)
	{
		y = -PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	// 11-degree minimax approximation
	*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

	// 10-degree minimax approximation
	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	*ScalarCos = sign * p;
}
float FMath::Fmod(float X, float Y)
{
	const float AbsY = fabsf(Y);
	if (AbsY <= 1.e-8f) { return 0.f; }
	const float Div = (X / Y);
	// All floats where abs(f) >= 2^23 (8388608) are whole numbers so do not need truncation, and avoid overflow in TruncToFloat as they get even larger.
	const float Quotient = fabsf(Div) < FLOAT_NON_FRACTIONAL ? truncf(Div) : Div;
	float IntPortion = Y * Quotient;

	// Rounding and imprecision could cause IntPortion to exceed X and cause the result to be outside the expected range.
	// For example Fmod(55.8, 9.3) would result in a very small negative value!
	if (fabsf(IntPortion) > fabsf(X)) { IntPortion = X; }

	const float Result = X - IntPortion;
	// Clamp to [-AbsY, AbsY] because of possible failures for very large numbers (>1e10) due to precision loss.
	// We could instead fall back to stock fmodf() for large values, however this would diverge from the SIMD VectorMod() which has no similar fallback with reasonable performance.
	return FMath::Clamp(Result, -AbsY, AbsY);
}
static bool bLockedCameraRotation = false;
uintptr_t camMan;
FVector	LocalCameraLocation; //FVector	LocalCameraLocation = Memory::ReadStub<uintptr_t>(camMan + 0x1260);
float LocalCameraFOV; //float LocalCameraFOV = Memory::ReadStub<float>(camMan + 0x1278);
FVector	LocalCameraRotation; //FVector	LocalCameraRotation = Memory::ReadStub<uintptr_t>(camMan + 0x126C)
static bool bFlickSilent = true;
void(*SetCameraCachePOVOriginal)(uintptr_t, FMinimalViewInfo*) = nullptr;
UAresOutlineComponent* Mesh;
FVector2D head_scren;

auto SetCameraCachePOVHook(uintptr_t PlayerCameraManager, FMinimalViewInfo* ViewInfo)
{
	FVector CameraPos = *(FVector*)(PlayerCameraManager + 0x1260);
	FVector CameraRot = *(FVector*)(PlayerCameraManager + 0x126C);

	// Cache camera values for our own purposes, in this case we are simply using the left button to decide whether the person is shooting or not.
	if (Silent)
	{
		// Cache camera values for our own purposes, in this case we are simply using the left button to decide whether the person is shooting or not.
		if (!GetAsyncKeyState(KEKWNOKEY)) //menu is alt
		{

			if (!GetAsyncKeyState(VK_LBUTTON))
			{
				// Cache wanted camera values.
				LocalCameraLocation = ViewInfo->Location, LocalCameraRotation = ViewInfo->Rotation;
				LocalCameraFOV = ViewInfo->FOV;

				bLockedCameraRotation = false;
			}

		}
		else
		{
			if (GetAsyncKeyState(VK_LBUTTON) && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y))
				bLockedCameraRotation = true;



			// Lock camera
			if (bFlickSilent && LocalCameraRotation != FVector())
				ViewInfo->Rotation = LocalCameraRotation;

		}

		SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);



	}/**/

	if (ThirdPerson) {
		float TPDistance = PlayerDistange; // Third Person Distance
		float FixZAngle = (-TPDistance - (sin(DegreeToRadian(-CameraRot.X)) * (TPDistance - (TPDistance / 3.5))));

		if (CameraRot.X < 0.0f)
			FixZAngle = -(TPDistance - (sin(DegreeToRadian(-CameraRot.X)) * (TPDistance - (TPDistance / 3.5))));

		FVector CamOff = FVector{ cos(DegreeToRadian(CameraRot.Y)) * FixZAngle, sin(DegreeToRadian(CameraRot.Y)) * FixZAngle, sin(DegreeToRadian(-CameraRot.X)) * TPDistance };


		ViewInfo->Location = CameraPos + CamOff;
	}

	SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
}
FQuat FRotator::Quaternion() const
{
	float SP, SY, SR;
	float CP, CY, CR;
	const float PitchNoWinding = FMath::Fmod(Pitch, 360.0f);
	const float YawNoWinding = FMath::Fmod(Yaw, 360.0f);
	const float RollNoWinding = FMath::Fmod(Roll, 360.0f);
	FMath::SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
	FMath::SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
	FMath::SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);
	FQuat RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;
	return RotationQuat;
}
const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);
const FVector FVector::OneVector(1.0f, 1.0f, 1.0f);
FVector FTransform::TransformPosition(FVector& V) const
{
	return Rotation.RotateVector(Scale3D * V) + Translation;
}
FVector FQuat::RotateVector(const FVector& V) const
{
	const FVector Q(X, Y, Z);
	const FVector T = (Q ^ V) * 2.f;
	const FVector Result = V + (T * W) + (Q ^ T);
	return Result;
}

bool a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18;
void  Draw3DBox(UCanvas* _this, APlayerController* plc, FVector origin, FVector extends, FLinearColor col)
{
	origin -= extends / 2.f;

	// bottom plane
	FVector one = origin;
	FVector two = origin; two.X += extends.X;
	FVector three = origin; three.X += extends.X; three.Y += extends.Y;
	FVector four = origin; four.Y += extends.Y;

	FVector five = one; five.Z += extends.Z;
	FVector six = two; six.Z += extends.Z;
	FVector seven = three; seven.Z += extends.Z;
	FVector eight = four; eight.Z += extends.Z;



	if (plc->ProjectWorldLocationToScreen(one, scr[0], 0) || plc->ProjectWorldLocationToScreen(two, scr[1], 0) || plc->ProjectWorldLocationToScreen(three, scr[2], 0) || plc->ProjectWorldLocationToScreen(four, scr[3], 0))
	{
		if (plc->ProjectWorldLocationToScreen(five, scr[4], 0) || plc->ProjectWorldLocationToScreen(six, scr[5], 0) || plc->ProjectWorldLocationToScreen(seven, scr[6], 0) || plc->ProjectWorldLocationToScreen(eight, scr[7], 0))
		{
			_this->K2_DrawLine(scr[0], scr[1], ESPThickness, col);
			_this->K2_DrawLine(scr[1], scr[2], ESPThickness, col);
			_this->K2_DrawLine(scr[2], scr[3], ESPThickness, col);
			_this->K2_DrawLine(scr[3], scr[0], ESPThickness, col);

			_this->K2_DrawLine(scr[4], scr[5], ESPThickness, col);
			_this->K2_DrawLine(scr[5], scr[6], ESPThickness, col);
			_this->K2_DrawLine(scr[6], scr[7], ESPThickness, col);
			_this->K2_DrawLine(scr[7], scr[4], ESPThickness, col);

			_this->K2_DrawLine(scr[0], scr[4], ESPThickness, col);
			_this->K2_DrawLine(scr[1], scr[5], ESPThickness, col);
			_this->K2_DrawLine(scr[2], scr[6], ESPThickness, col);
			_this->K2_DrawLine(scr[3], scr[7], ESPThickness, col);
		}
	}

}
bool Render3DBox(APlayerController* controller, UCanvas* Engine, const FVector& origin, const FVector& extent, const FRotator& rotation, const FLinearColor color)
{
	FVector vertex[2][4];
	vertex[0][0] = { -extent.X, -extent.Y,  -extent.Z };
	vertex[0][1] = { extent.X, -extent.Y,  -extent.Z };
	vertex[0][2] = { extent.X, extent.Y,  -extent.Z };
	vertex[0][3] = { -extent.X, extent.Y, -extent.Z };

	vertex[1][0] = { -extent.X, -extent.Y, extent.Z };
	vertex[1][1] = { extent.X, -extent.Y, extent.Z };
	vertex[1][2] = { extent.X, extent.Y, extent.Z };
	vertex[1][3] = { -extent.X, extent.Y, extent.Z };

	FVector2D screen[2][4];
	FTransform const Transform(rotation);
	for (auto k = 0; k < 2; k++)
	{
		for (auto i = 0; i < 4; i++)
		{
			auto& vec = vertex[k][i];
			vec = Transform.TransformPosition(vec) + origin;
			if (!controller->ProjectWorldLocationToScreen(vec, screen[k][i], false)) return false;
		}

	}

	auto SurfaceScreen = reinterpret_cast<FVector2D(&)[2][4]>(screen);

	for (auto i = 0; i < 4; i++)
	{
		Engine->K2_DrawLine(SurfaceScreen[1][i], SurfaceScreen[2][(i + 1) % 2], ESPThickness, color);
		Engine->K2_DrawLine(SurfaceScreen[3][i], SurfaceScreen[4][(i + 1) % 2], ESPThickness, color);
		Engine->K2_DrawLine(SurfaceScreen[5][i], SurfaceScreen[6][(i + 1) % 2], ESPThickness, color);
	}

	return true;
}


UWorld* OldWorld = 0;
void PostRender(uintptr_t _this, UCanvas* canvas)

{

	if (!canvas)
		return PostRender(_this, canvas);

	if (kekIsOff)
		return PostRender(_this, canvas);

	CWINGui::SetupCanvas(canvas);
	UWorld* World = Memory::ReadStub<UWorld*>(_this + 0x80);


	APlayerController* MyController = ShooterGameBlueprints::GetFirstLocalPlayerController(World);//crash 456 this was crashing because of pointer
	AShooterCharacter* MyShooter = MyController->GetShooterCharacter();
	TArray<AShooterCharacter*> Actors = ShooterGameBlueprints::FindAllShooterCharactersWithAlliance(World, MyShooter, EAresAlliance::Alliance_Any, false, true);
	CWINGui::Input::Handle();



	if (drawcross)
	{
		if (GetAsyncKeyState(VK_LBUTTON)) {
			CWINGui::DrawCircle({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2.045f }, radius, LineamountCross, crosscolor);
		}
		else {
			CWINGui::DrawCircle({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }, radius, LineamountCross, crosscolor);
		}

	}
	if (drawfov)
	{
		if (RenderCross) {
			CWINGui::DrawCircle({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / 2 }, fovChanger, LineamountFov, fovcolor);
		}

	}


	if (GetAsyncKeyState(VK_INSERT) & 1) menu_opened = !menu_opened; //Our menu key 
	if (Watermark) {
		canvas->K2_DrawText(L"Staff-Besting | Menu-Ins", { 49,40 }, { 1.0f,1.0f/*Size*/ }, { 1.0f,1.0f,1.0f,2.0f/*RGBA*/ }, 0.f, { 0,0,0,1 }, { 0,0 }, 0, 0, 0, { 0,0,0,1 });
	}


	if (CWINGui::Window(skCrypt("STAFFBESTING | discord.gg/staffbesting"), &pos, FVector2D{ 400.0f, 447.0f }, menu_opened))
	{
		//Simple Tabs
		static int tabss = 0;
		if (CWINGui::ButtonTab(L"Aimbot", FVector2D{ 110, 32 }, tabss == 0)) tabss = 0;
		CWINGui::SameLine();
		if (CWINGui::ButtonTab(L"Visual", FVector2D{ 110, 32 }, tabss == 1)) tabss = 1;
		CWINGui::SameLine();
		if (CWINGui::ButtonTab(L"Misc", FVector2D{ 110, 32 }, tabss == 2)) tabss = 2;
		CWINGui::SameLine();
		CWINGui::PushNextElementY(10);

		if (tabss == 0)
		{
			CWINGui::Checkbox(L"Enable", &enableaim);
			if (enableaim) {
				if (enableaim && !NoSpread) {
					CWINGui::Checkbox(L"Draw FOV", &drawfov);
					CWINGui::Checkbox(L"VisibleCheck", &vischeck);
					CWINGui::Hotkey("Keybind", { 90,32 }, &KEKWNOKEY);
					CWINGui::SameLine();
					CWINGui::Combobox(L"", { 95,32 }, &aimbone, L"Head", L"Chest", L"Leg", NULL);
					CWINGui::SliderFloat(L"FOV", &fovChanger, 10, 1500);
					CWINGui::ColorPicker(L"FOV Color", &fovcolor);
					CWINGui::Text(L"Settings");
					CWINGui::Checkbox(L"Auto Target", &autoaim);

				}



			}



		}
		if (tabss == 1) {

			CWINGui::Checkbox(L"Skeleton ESP", &skeleton);
			CWINGui::Checkbox(L"Head ESP", &HeadCircleEsp);
			CWINGui::Checkbox(L"Draw Traces", &snaplinenz);
			CWINGui::Combobox(L"", { 95,30 }, &SnapPositionint, L"Below", L"Middle", L"Bottom", NULL);
		}


		if (tabss == 2) {
			static int tabs = 0;
			if (CWINGui::ButtonTab(L"Settings", FVector2D{ 315, 30 }, tabs == 0)) tabs = 0;
			CWINGui::SameLine();
			if (CWINGui::ButtonTab(L"Developed", FVector2D{ 315, 30 }, tabs == 1)) tabs = 1;
			if (tabs == 0) {
				CWINGui::Checkbox(L"Fast Crouch", &FlyHack);
				CWINGui::Checkbox(L"Draw Recoil Crosshair", &drawcross);
				if (CWINGui::Button(L"Skip Tutorial", FVector2D{ 95, 32 })) {
					skiptutorial = true;
				}
				CWINGui::SliderFloat(L"Field of Wiew", &fovchangur, 0, 170);
				if (CWINGui::Button(L"Apply Fov", FVector2D{ 87, 30 })) {
					fovchanger = true;
				}

			}
			if (tabs == 3) {
				CWINGui::Checkbox(L"ThirdPerson", &ThirdPerson);
				CWINGui::SliderFloat(L"Distange", &PlayerDistange, 100, 700);
				CWINGui::Text(L"");
				CWINGui::Checkbox(L"SpinBot", &SpinBot);
				CWINGui::SameLine();
				CWINGui::Hotkey("Keybind", { 90,32 }, &spinbotkeybind);
				CWINGui::SliderFloat(L"Spinbot Pitch", &spinMULTIX, -5, 50.f);

			}


		}


	}

	CWINGui::Draw_Cursor(menu_opened);
	CWINGui::Render();



	bool hasTarget = false;
	for (int Index = 0; Index < Actors.Num(); Index++)
	{
		if (!Actors.IsValidIndex(Index))
			continue;


		if (SpinBot && GetAsyncKeyState(spinbotkeybind))
		{
			if (t)
			{

				OldAimAngles = FVector();
				if (OldAimAngles == FVector())
				{
					OldAimAngles = MyController->GetControlRotation();

					if (OldAimAngles == FVector()) break;
				}
				t = false;

			}
			float Pitch = 0;
			float Roll = 0;
			if (!GetAsyncKeyState(VK_LBUTTON)) {
				MyShooter->K2_SetActorRotation({ Pitch, spinX, Roll }, NULL);
				MyShooter->GetPawnMesh(), MyController->ClientForceSetControlRotation({ Pitch, spinX, Roll }); // Pitch, Yaw, Roll 
				spinX = spinX + spinMULTIX;
				Pitch = Pitch + spinMULTIY;
				Roll = Roll + spinMULTIZ;

			}
			//printf("spin : %f", spinX);
			if (spinX > 1000)
			{
				spinX = 10;
			}

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (OldAimAngles != FVector())
				{


					MyController->SetControlRotation(OldAimAngles);

					OldAimAngles = FVector();
					spinX != 0;
					Pitch = 0;
					Roll = 0;
					t = true;
				}
			}




		}

		AShooterCharacter* Actor = Actors[Index];
		actor = Actor;
		UObject* Object;
		if (Actor->GetHealth() == 0)
			continue;

		if (!MyShooter) continue;

		if (kismentsystemlibrary::get_object_name(Actor).ToString().find("_PC") != std::string::npos) {
			InGame = 1;
		}
		else {
			InGame = 0;
		}
		Mesh = Actor->GetPawnMesh();

		if (ThirdPerson)
		{
			MyShooter->Set3pMeshVisible(true);

		}
		else//hazır 
		{

			MyShooter->Set3pMeshVisible(false);

		}


		if (BaseTeamComponent::IsAlly(Actor, MyShooter))
			continue;

		if (!InGame) continue;

		bool IsAlive = Actor->IsAlive();
		if (Mesh && Actor->IsAlive())
		{
			FLinearColor BoxColor;
			FLinearColor SnapColor;
			FLinearColor SkeletonColor;
			FLinearColor ChamsColor;

			if (true)
			{
				if (MyController->LineOfSightTo(Actor, { 0,0,0 }, false)) {

					ChamsColor = VisibleChams;
					SnapColor = VisibleSnapColor;
					BoxColor = VisibleBox_ESPColor;
					SkeletonColor = VisibleBox_ESPColor;


				}
				else {
					ChamsColor = InvisibleChams;
					SnapColor = InvisibleSnapColor;
					BoxColor = Invisible_ESPColor;
					SkeletonColor = Invisible_ESPColor;
				}

			}
			if (HeadCircleEsp) {

				FVector2D vHeadBoneOut;
				if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 8), vHeadBoneOut, 0) && vHeadBoneOut.IsValid())
				{
					CWINGui::DrawCircle({ vHeadBoneOut.X, vHeadBoneOut.Y }, radius2, LineamountCircle, BoxColor);
				}

			}
			if (box2d)
			{
				FVector Origin, Extend;

				auto location = Actor->K2_GetActorLocation(); FVector2D footPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + (Extend.Z / 2) }, footPos, 0)) continue;

				FVector2D headPos;
				if (!MyController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - (Extend.Z / 2) }, headPos, 0)) continue;


				const float height = abs(footPos.Y - headPos.Y);
				const float width = height * 0.4f;
				FVector2D top = { headPos.X - width * 0.5f, headPos.Y };
				FVector2D bottom = { headPos.X + width * 0.5f, footPos.Y };

				if (Visible_Check_ESP)
				{
					if (MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false))
					{

						DrawBox(canvas, top, bottom, BoxColor);
					}
				}
				else
				{
					DrawBox(canvas, top, bottom, BoxColor);
				}
			}
			if (enableaim) {

				FVector Target;
				if (aimbone == 0) {//Head
					Target = GetBoneMatrix(Mesh, 8);
				}
				else if (aimbone == 1) {//Chets
					Target = GetBoneMatrix(Mesh, 6);
				}
				else if (aimbone == 2) {//leg
					Target = GetBoneMatrix(Mesh, 3);
				}


				FVector2D head_screen;
				//Normal Aimbot
				if (MyController->ProjectWorldLocationToScreen(Target, head_screen, 0) && head_screen.IsValid()) {

					if (enableaim && !autoaim && SmootAimBool && !autoshoot && !NoSpread && !hasTarget && GetAsyncKeyState(KEKWNOKEY) && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{
						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector new_aim_rotation;
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector ControlRotation = MyController->GetControlRotation();
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);

						FVector recoil;
						recoil.X = CameraRot.X - ControlRotation.X;
						recoil.Y = CameraRot.Y - ControlRotation.Y;
						recoil.Z = 0.f;

						FVector vector_pos = Target - CameraPos;
						float distance = (double)(sqrtf(vector_pos.X * vector_pos.X + vector_pos.Y * vector_pos.Y + vector_pos.Z * vector_pos.Z));
						float x, y, z;
						x = -((acosf(vector_pos.Z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
						y = atan2f(vector_pos.Y, vector_pos.X) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
						z = 0;

						FVector target_rotation = FVector(x, y, z);
						new_aim_rotation.X = target_rotation.X - recoil.X - recoil.X;;
						new_aim_rotation.Y = target_rotation.Y - recoil.Y - recoil.Y;;
						new_aim_rotation.Z = 0;

						FVector new_rotation = smooth_aim(new_aim_rotation, ControlRotation, smooth);

						if (new_rotation.X < 0)
						{
							new_rotation.X += 360.f;
						}

						if (new_rotation.Y < 0)
						{
							new_rotation.Y += 360.f;
						}

						new_rotation.Z = 0;


						MyController->SetControlRotation(new_rotation);

					}

				}

				if (MyController->ProjectWorldLocationToScreen(Target, head_screen, 0) && head_screen.IsValid()) {

					if (enableaim && !autoaim && !SmootAimBool && !autoshoot && !NoSpread && !hasTarget && GetAsyncKeyState(KEKWNOKEY) && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{

						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);
						FVector DeltaRotation;
						FVector ConvertRotation = { CameraRot.X < 0.f ? 360.f + CameraRot.X : CameraRot.X, CameraRot.Y < 0.f ? 360.f + CameraRot.Y : CameraRot.Y, 0 };
						FVector ControlRotation = MyController->GetControlRotation();

						FVector Delta = { CameraPos.X - Target.X, CameraPos.Y - Target.Y, CameraPos.Z - Target.Z };
						float hyp = sqrtf(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);

						FVector Rotation = { acosf(Delta.Z / hyp) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), atanf(Delta.Y / Delta.X) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), 0 };

						Rotation.X += 270.f;

						if (Delta.X >= 0.0f) Rotation.Y += 180.0f;

						if (Rotation.Y < 0.f) Rotation.Y += 360.f;


						// Calculate recoil/aimpunch
						DeltaRotation.X = fmodf(ConvertRotation.X - ControlRotation.X, 360.f);
						DeltaRotation.Y = fmodf(ConvertRotation.Y - ControlRotation.Y, 360.f);


						// Remove 2x aimpunch from CameraRotation
						ConvertRotation.X = fmodf(Rotation.X - DeltaRotation.X - DeltaRotation.X, 360.f);
						ConvertRotation.Y = fmodf(Rotation.Y - DeltaRotation.Y - DeltaRotation.Y, 360.f);
						if (ConvertRotation.X < 0.f) ConvertRotation.X = 360.f + ConvertRotation.X;

						if (ConvertRotation.Y < 0.f) ConvertRotation.Y = 360.f + ConvertRotation.Y;

						MyController->SetControlRotation(ConvertRotation);
						hasTarget = true;


					}

				}

				//SilentSystem
				if (Silent)
				{

					FVector Target;
					if (aimbone == 0) {//Head
						Target = GetBoneMatrix(Mesh, 8);
					}
					else if (aimbone == 1) {//Chets
						Target = GetBoneMatrix(Mesh, 6);
					}
					else if (aimbone == 2) {//Penis
						Target = GetBoneMatrix(Mesh, 3);
					}


					//FovandKey
					if (MyController->ProjectWorldLocationToScreen(Target, head_scren, 0) && head_scren.IsValid()) {

						if (Silent && !hasTarget && GetAsyncKeyState(KEKWNOKEY) && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
						{
							uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
							FVector CameraPos = *(FVector*)(cmanager + 0x1260);
							FVector CameraRot = *(FVector*)(cmanager + 0x126C);
							FVector DeltaRotation;
							FVector ConvertRotation = { CameraRot.X < 0.f ? 360.f + CameraRot.X : CameraRot.X, CameraRot.Y < 0.f ? 360.f + CameraRot.Y : CameraRot.Y, 0 };
							FVector ControlRotation = MyController->GetControlRotation();

							FVector Delta = { CameraPos.X - Target.X, CameraPos.Y - Target.Y, CameraPos.Z - Target.Z };
							float hyp = sqrtf(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);

							FVector Rotation = { acosf(Delta.Z / hyp) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), atanf(Delta.Y / Delta.X) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), 0 };

							Rotation.X += 270.f;

							if (Delta.X >= 0.0f) Rotation.Y += 180.0f;

							if (Rotation.Y < 0.f) Rotation.Y += 360.f;

							DeltaRotation.X = fmodf(ConvertRotation.X - ControlRotation.X, 360.f);
							DeltaRotation.Y = fmodf(ConvertRotation.Y - ControlRotation.Y, 360.f);

							ConvertRotation.X = fmodf(Rotation.X - DeltaRotation.X - DeltaRotation.X, 360.f);
							ConvertRotation.Y = fmodf(Rotation.Y - DeltaRotation.Y - DeltaRotation.Y, 360.f);

							if (ConvertRotation.X < 0.f) ConvertRotation.X = 360.f + ConvertRotation.X;

							if (ConvertRotation.Y < 0.f) ConvertRotation.Y = 360.f + ConvertRotation.Y;

							MyController->SetControlRotation(ConvertRotation);
							hasTarget = true;
						}

					}



				}
				if (autoaim) {
					autoshoot = false;
				}
				if (autoshoot) {
					autoaim = false;
				}

				//AutoAim
				if (MyController->ProjectWorldLocationToScreen(Target, head_scren, 0) && head_scren.IsValid()) {

					if (enableaim && autoaim && !SmootAimBool && !NoSpread && !hasTarget && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{
						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);
						FVector DeltaRotation;
						FVector ConvertRotation = { CameraRot.X < 0.f ? 360.f + CameraRot.X : CameraRot.X, CameraRot.Y < 0.f ? 360.f + CameraRot.Y : CameraRot.Y, 0 };
						FVector ControlRotation = MyController->GetControlRotation();

						FVector Delta = { CameraPos.X - Target.X, CameraPos.Y - Target.Y, CameraPos.Z - Target.Z };
						float hyp = sqrtf(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);

						FVector Rotation = { acosf(Delta.Z / hyp) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), atanf(Delta.Y / Delta.X) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), 0 };

						Rotation.X += 270.f;

						if (Delta.X >= 0.0f) Rotation.Y += 180.0f;

						if (Rotation.Y < 0.f) Rotation.Y += 360.f;


						// Calculate recoil/aimpunch
						DeltaRotation.X = fmodf(ConvertRotation.X - ControlRotation.X, 360.f);
						DeltaRotation.Y = fmodf(ConvertRotation.Y - ControlRotation.Y, 360.f);


						// Remove 2x aimpunch from CameraRotation
						ConvertRotation.X = fmodf(Rotation.X - DeltaRotation.X - DeltaRotation.X, 360.f);
						ConvertRotation.Y = fmodf(Rotation.Y - DeltaRotation.Y - DeltaRotation.Y, 360.f);
						if (ConvertRotation.X < 0.f) ConvertRotation.X = 360.f + ConvertRotation.X;

						if (ConvertRotation.Y < 0.f) ConvertRotation.Y = 360.f + ConvertRotation.Y;

						MyController->SetControlRotation(ConvertRotation);
						hasTarget = true;
					}

				}

				//Shoot
				if (MyController->ProjectWorldLocationToScreen(Target, head_scren, 0) && head_scren.IsValid()) {

					if (enableaim && autoshoot && !SmootAimBool && !NoSpread && !hasTarget && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{
						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);
						FVector DeltaRotation;
						FVector ConvertRotation = { CameraRot.X < 0.f ? 360.f + CameraRot.X : CameraRot.X, CameraRot.Y < 0.f ? 360.f + CameraRot.Y : CameraRot.Y, 0 };
						FVector ControlRotation = MyController->GetControlRotation();

						FVector Delta = { CameraPos.X - Target.X, CameraPos.Y - Target.Y, CameraPos.Z - Target.Z };
						float hyp = sqrtf(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);

						FVector Rotation = { acosf(Delta.Z / hyp) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), atanf(Delta.Y / Delta.X) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), 0 };

						Rotation.X += 270.f;

						if (Delta.X >= 0.0f) Rotation.Y += 180.0f;

						if (Rotation.Y < 0.f) Rotation.Y += 360.f;


						// Calculate recoil/aimpunch
						DeltaRotation.X = fmodf(ConvertRotation.X - ControlRotation.X, 360.f);
						DeltaRotation.Y = fmodf(ConvertRotation.Y - ControlRotation.Y, 360.f);


						// Remove 2x aimpunch from CameraRotation
						ConvertRotation.X = fmodf(Rotation.X - DeltaRotation.X - DeltaRotation.X, 360.f);
						ConvertRotation.Y = fmodf(Rotation.Y - DeltaRotation.Y - DeltaRotation.Y, 360.f);
						if (ConvertRotation.X < 0.f) ConvertRotation.X = 360.f + ConvertRotation.X;

						if (ConvertRotation.Y < 0.f) ConvertRotation.Y = 360.f + ConvertRotation.Y;

						MyController->SetControlRotation(ConvertRotation);
						hasTarget = true;
					}

				}

				//AutoAim+Smooth
				if (MyController->ProjectWorldLocationToScreen(Target, head_scren, 0) && head_scren.IsValid()) {

					if (enableaim && autoaim && SmootAimBool && !NoSpread && !hasTarget && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{
						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector new_aim_rotation;
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector ControlRotation = MyController->GetControlRotation();
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);

						FVector recoil;
						recoil.X = CameraRot.X - ControlRotation.X;
						recoil.Y = CameraRot.Y - ControlRotation.Y;
						recoil.Z = 0.f;

						FVector vector_pos = Target - CameraPos;
						float distance = (double)(sqrtf(vector_pos.X * vector_pos.X + vector_pos.Y * vector_pos.Y + vector_pos.Z * vector_pos.Z));
						float x, y, z;
						x = -((acosf(vector_pos.Z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
						y = atan2f(vector_pos.Y, vector_pos.X) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
						z = 0;

						FVector target_rotation = FVector(x, y, z);
						new_aim_rotation.X = target_rotation.X - recoil.X - recoil.X;;
						new_aim_rotation.Y = target_rotation.Y - recoil.Y - recoil.Y;;
						new_aim_rotation.Z = 0;

						FVector new_rotation = smooth_aim(new_aim_rotation, ControlRotation, smooth);

						if (new_rotation.X < 0)
						{
							new_rotation.X += 360.f;
						}

						if (new_rotation.Y < 0)
						{
							new_rotation.Y += 360.f;
						}

						new_rotation.Z = 0;


						MyController->SetControlRotation(new_rotation);

					}

				}

				//Shoot+Smooth
				if (MyController->ProjectWorldLocationToScreen(Target, head_scren, 0) && head_scren.IsValid()) {

					if (enableaim && autoshoot && SmootAimBool && !NoSpread && !hasTarget && in_rect(ScreenCenterX, ScreenCenterY, fovChanger, head_scren.X, head_scren.Y) && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck))
					{
						uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
						FVector new_aim_rotation;
						FVector CameraPos = *(FVector*)(cmanager + 0x1260);
						FVector ControlRotation = MyController->GetControlRotation();
						FVector CameraRot = *(FVector*)(cmanager + 0x126C);

						FVector recoil;
						recoil.X = CameraRot.X - ControlRotation.X;
						recoil.Y = CameraRot.Y - ControlRotation.Y;
						recoil.Z = 0.f;

						FVector vector_pos = Target - CameraPos;
						float distance = (double)(sqrtf(vector_pos.X * vector_pos.X + vector_pos.Y * vector_pos.Y + vector_pos.Z * vector_pos.Z));
						float x, y, z;
						x = -((acosf(vector_pos.Z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
						y = atan2f(vector_pos.Y, vector_pos.X) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
						z = 0;

						FVector target_rotation = FVector(x, y, z);
						new_aim_rotation.X = target_rotation.X - recoil.X - recoil.X;;
						new_aim_rotation.Y = target_rotation.Y - recoil.Y - recoil.Y;;
						new_aim_rotation.Z = 0;

						FVector new_rotation = smooth_aim(new_aim_rotation, ControlRotation, smooth);

						if (new_rotation.X < 0)
						{
							new_rotation.X += 360.f;
						}

						if (new_rotation.Y < 0)
						{
							new_rotation.Y += 360.f;
						}

						new_rotation.Z = 0;


						MyController->SetControlRotation(new_rotation);

					}

				}

				FVector Target2;
				if (rageaimbone == 0) {//Head
					Target2 = GetBoneMatrix(Mesh, 8);
				}
				else if (rageaimbone == 1) {//Chets
					Target2 = GetBoneMatrix(Mesh, 6);
				}
				else if (rageaimbone == 2) {//leg
					Target2 = GetBoneMatrix(Mesh, 3);
				}

				if (enableaim && NoSpread && GetAsyncKeyState(NoSpreadKey) && !hasTarget && (vischeck && MyController->LineOfSightTo(Actor, { 0, 0, 0 }, false) || !vischeck)) {
					uintptr_t cmanager = *(uintptr_t*)((uintptr_t)MyController + 0x478);
					FVector CameraPos = *(FVector*)(cmanager + 0x1260);
					FVector CameraRot = *(FVector*)(cmanager + 0x126C);
					FVector ControlRotation = MyController->GetControlRotation();
					FVector Delta = { CameraPos.X - Target2.X, CameraPos.Y - Target2.Y, CameraPos.Z - Target2.Z };
					float hyp = sqrtf(Delta.X * Delta.X + Delta.Y * Delta.Y + Delta.Z * Delta.Z);

					FVector Rotation = { acosf(Delta.Z / hyp) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), atanf(Delta.Y / Delta.X) * (float)(180.0f / 3.1415926535897932384626433832795028841971693993751), 0 };

					Rotation.X += 270.f;

					if (Delta.X >= 0.0f) Rotation.Y += 180.0f;

					if (Rotation.Y < 0.f) Rotation.Y += 360.f;


					uint64 Firing_State_Component = Memory::ReadStub<uint64_t>((uint64_t)MyShooter->GetInventory()->GetCurrentWeapon() + 0x1010);
					APawn* MyPawn = MyController->K2_GetPawn();
					MyController->SetControlRotation(Rotation - get_error_angle((uintptr_t)MyPawn, Firing_State_Component));
					hasTarget = true;
					if (AutoFire && GetAsyncKeyState(autofire)) {
						mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}


				}

			}
			if (snaplinenz) {
				box2d = true;
				FVector2D drawtextat;
				if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, SnapMesh), drawtextat, 0) && drawtextat.IsValid());
				canvas->K2_DrawLine({ (float)GetSystemMetrics(SM_CXSCREEN) / 2, (float)GetSystemMetrics(SM_CYSCREEN) / SnapPositionİnt/*135*/ }, drawtextat, ESPThickness, SnapColor);

			}
			

			if (skeleton)
			{
				FVector2D vHipOut;
				FVector2D vNeckOut;
				FVector2D vUpperArmLeftOut;
				FVector2D vLeftHandOut;
				FVector2D vLeftHandOut1;
				FVector2D vUpperArmRightOut;
				FVector2D vRightHandOut;
				FVector2D vRightHandOut1;
				FVector2D vLeftThighOut;
				FVector2D vLeftCalfOut;
				FVector2D vLeftFootOut;
				FVector2D vRightThighOut;
				FVector2D vRightCalfOut;
				FVector2D vRightFootOut;
				if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 3), vHipOut, 0) && vHipOut.IsValid())
					if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 7), vNeckOut, 0) && vNeckOut.IsValid())
						if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 11), vUpperArmLeftOut, 0) && vUpperArmLeftOut.IsValid())
							if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 12), vLeftHandOut, 0) && vLeftHandOut.IsValid())
								if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 13), vLeftHandOut1, 0) && vLeftHandOut1.IsValid())
									if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 36), vUpperArmRightOut, 0) && vUpperArmRightOut.IsValid())
										if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 37), vRightHandOut, 0) && vRightHandOut.IsValid())
											if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 38), vRightHandOut1, 0) && vRightHandOut1.IsValid())
												if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 63), vLeftThighOut, 0) && vLeftThighOut.IsValid())
													if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 65), vLeftCalfOut, 0) && vLeftCalfOut.IsValid())
														if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 69), vLeftFootOut, 0) && vLeftFootOut.IsValid())
															if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 77), vRightThighOut, 0) && vRightThighOut.IsValid())
																if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 79), vRightCalfOut, 0) && vRightCalfOut.IsValid())
																	if (MyController->ProjectWorldLocationToScreen(GetBoneMatrix(Mesh, 83), vRightFootOut, 0) && vRightFootOut.IsValid())

																		canvas->K2_DrawLine({ vHipOut.X, vHipOut.Y }, { vNeckOut.X, vNeckOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vUpperArmLeftOut.X, vUpperArmLeftOut.Y }, { vNeckOut.X, vNeckOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vUpperArmRightOut.X, vUpperArmRightOut.Y }, { vNeckOut.X, vNeckOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vLeftHandOut.X, vLeftHandOut.Y }, { vUpperArmLeftOut.X, vUpperArmLeftOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vRightHandOut.X, vRightHandOut.Y }, { vUpperArmRightOut.X, vUpperArmRightOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vLeftHandOut.X, vLeftHandOut.Y }, { vLeftHandOut1.X, vLeftHandOut1.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vRightHandOut.X, vRightHandOut.Y }, { vRightHandOut1.X, vRightHandOut1.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vLeftThighOut.X, vLeftThighOut.Y }, { vHipOut.X, vHipOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vRightThighOut.X, vRightThighOut.Y }, { vHipOut.X, vHipOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vLeftCalfOut.X, vLeftCalfOut.Y }, { vLeftThighOut.X, vLeftThighOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vRightCalfOut.X, vRightCalfOut.Y }, { vRightThighOut.X, vRightThighOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vLeftFootOut.X, vLeftFootOut.Y }, { vLeftCalfOut.X, vLeftCalfOut.Y }, 1, BoxColor);
				canvas->K2_DrawLine({ vRightFootOut.X, vRightFootOut.Y }, { vRightCalfOut.X, vRightCalfOut.Y }, 1, BoxColor);
			}

			if (FlyHack)//fast crouch
			{
				MyShooter->SetCrouchTimeOverride(OverrideCrouchTimeSeconds);

			}
			else {
				MyShooter->SetCrouchTimeOverride(0.1);
			}
			if (SnapPositionint == 0) {
				SnapPositionİnt = 1;
				SnapMesh = 0;
				if (Below == true) {
					Below = false;
				}

			}
			else if (SnapPositionint == 1) {
				SnapPositionİnt = 2;
				SnapMesh = 8;

				if (Middle == true) {
					Middle = false;
				}
			}
			else if (SnapPositionint == 2) {
				SnapPositionİnt = 400;
				SnapMesh = 8;

				if (Bottom == true) {
					Bottom = false;
				}
			}
		}
	}
	return pRender(_this, canvas);
}
void Init()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	VALORANT::Module = (uintptr_t)GetModuleHandleA(0);
	uintptr_t WorldKey = *(uintptr_t*)(VALORANT::Module + Offsets::Key);
	State StateKey = *(State*)(VALORANT::Module + Offsets::State);
	UWorldXOR = Decryption::Decrypt_UWorld(WorldKey, (uintptr_t*)&StateKey);

	UWorldClass = Memory::ReadStub<UWorld*>(UWorldXOR);
	GameInstance = Memory::ReadStub<UGameInstance*>((uintptr_t)UWorldClass + 0x1A0);
	LocalPlayers = Memory::ReadStub<ULocalPlayer*>((uintptr_t)GameInstance + 0x40); //this is tarray but im paster lol
	LocalPlayer = Memory::ReadStub<ULocalPlayer*>((uintptr_t)LocalPlayers); //
	APlayerController* LocalController = Memory::ReadStub<APlayerController*>((uintptr_t)LocalPlayer + 0x38);
	uintptr_t ViewportClient = Memory::ReadStub<uintptr_t>((uintptr_t)LocalPlayer + 0x78);//struct UGameViewportClient* ViewportClient; 
	uintptr_t Engine = Memory::ReadStub<uintptr_t>((uintptr_t)GameInstance + 0x28);
	DefaultMediumFont = Memory::ReadStub<UObject*>(Engine + 0xd8);
	APlayerCameraManager* PlayerCameraManager = Memory::ReadStub<APlayerCameraManager*>((uintptr_t)LocalController + Offsets::PlayerCameraManager);// this may need to be swapped back if so dm me

	LocalCameraLocation = Memory::ReadStub<uintptr_t>((uintptr_t)PlayerCameraManager + 0x1260);
	LocalCameraFOV = Memory::ReadStub<float>((uintptr_t)PlayerCameraManager + 0x1278);
	LocalCameraRotation = Memory::ReadStub<uintptr_t>((uintptr_t)PlayerCameraManager + 0x126C);//this should work

	NamePoolData = reinterpret_cast<FNamePool*>(VALORANT::Module + NamePoolDataOffset);
	Hook::VMT((void*)ViewportClient, PostRender, 0x68, (void**)&pRender);
	Hook::VMT((void*)PlayerCameraManager, SetCameraCachePOVHook, 0xD4, (void**)&SetCameraCachePOVOriginal); //swap the method back to urs if this crash

}

extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, code, wParam, lParam); }
//TRY

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();

		Init();

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}