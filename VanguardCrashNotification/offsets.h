#pragma once
namespace Offsets
{
    constexpr auto
        State = 0x9094F40, //uworld_state
        Key = State + 0x38,//stade + key
        relative_rotation = 0x164,
        ProcessEvent = 0x336A200,
        StaticFindObject = 0x33A8410,
        SkinChanger = 0x2410890,
        TriggerVEH = 0x1BA1AA0,//pakman offset
        bone_matrix = 0x49EDB00,
        ControlRotation = 0x440,
        PlayerCameraManager = 0x478,//aPlayerCameraManager 
        GetActorBounds = 0x47B95A0, //   Engine.Actor.GetActorBounds
        portrait_map = 0x1100, //UCharacterPortraitMinimapComponent_C
        character_map = portrait_map + 0x8, // UCharacterCharacterMinimapComponent_C

        get_spread_values_fn = 0x2412AA0,
        get_spread_angles_fn = 0x2AA13B0,
        get_firing_location_and_direction_fn = 0x28E3B00,
        to_vector_and_normalize_fn = 0x30B0400,
        to_angle_and_normalize_fn = 0x30AA300;
}
