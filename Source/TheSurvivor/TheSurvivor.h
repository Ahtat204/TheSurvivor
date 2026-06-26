// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]
#define LOCOMOTION_MASK (static_cast<uint8>(0x0F)) // means the movement states are in the lowest 4 bytes
/**
 * @enum EWeaponType
 * @brief represents the type/size of the weapon ,used in animation to choose the proper animation for the weapon
 *
 * States:
 * -Pistol
 * -Rifle
 * -SMG
 */
UENUM(BlueprintType)
enum class EWeaponType:uint8
{
	Pistol = 0 UMETA(DisplayName="Pistol"),
	Rifle = 1 UMETA(DisplayName="Rifle"),
	Smg = 2 UMETA(DisplayName="SMG"),
};


#define LOG(msg) UE_LOG(LogTemp, Display, TEXT(msg))
//UE_LOG(msg, __FILE__, __LINE__, __func__)

/**@enum EPlayerCharacterState
 * @brief Defines the high-level traversal and locomotion state of the character.
 * This enum serves as the primary driver for the Animation Blueprint (AnimBP) state machine.
 * It distinguishes between grounded locomotion, airborne states, and specialized 
 * traversal actions (Climbing, Sprinting).
 * this enum is used in animations Layers to get exactly the state of the player and play the correct animation ,especially when holding a weapon
 * States:
 * - Idle:The player is standing
 * - Walk:the Player is Walking 
 * - Run:the Player is running 
 * - Jump: indicates the Player is jumping (this is a bit hard to detect since this state comes form the Base ACharacter clss)
* -  Unarmed   : The player has no weapon equipped (default state).
 * - Armed     : The player has a weapon equipped but is not actively using it.
 * - Firing    : The player is currently firing the equipped weapon.
 * - Reloading : The player is reloading the equipped weapon.
 * - Aiming    : The player is aiming down sights or focusing aim with the weapon.
 * - Traversing :used to implement climbing.
 * @attention - I moved to this merged enum to perform bitwise operators and to solve the extra  13 bytes padding from the  ASurvivorCharacter.CharacterState.
 * @remark there's no Unarmed since we just check if Armed&Idle is false.
 * @attention - Use assignment carefully because you might overwrite any existing bits ,assign only at the beginning of the game, use bitwise operators to add other states 
 */
UENUM(BlueprintType, Category="Weapons",
	meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true", ToolTip=
		"Represents the current weapon-related state of the player."))
enum class EPlayerCharacterState : uint8
{
	// --- ZONE 1: LOCOMOTION (Exclusive States: 0-7) ---
	// These use standard integers. Only one can be active at a time.
	Idle       = 0 UMETA(DisplayName="Idle",ToolTip="Indicates the Player isn't moving") ,   // 0000 0000 
	Moving        = 1 UMETA(DisplayName="Walking or Running",ToolTip="Indicates the Player is not in an Idle State"),   // 0000 0001
	Jump         = 2 UMETA(DisplayName="Jumping",ToolTip="Indicates the Player is Jumping"),   // 0000 0010
	Crouch =3 UMETA(DisplayName="Crouching",ToolTip="Indicates the Player is Crouching"),
	// --- ZONE 2: ACTION FLAGS (Additive: Bits 4-7) ---
	// We start at 1<<4 to avoid touching the Locomotion bits.
	Armed       = 1 << 4 UMETA(DisplayName="",ToolTip=""), // 0001 0000 (16)
	Firing      = 1 << 5 UMETA(DisplayName="",ToolTip=""), // 0010 0000 (32)
	Reloading   = 1 << 6 UMETA(DisplayName="",ToolTip=""), // 0100 0000 (64)
	Aiming      = 1 << 7 UMETA(DisplayName="",ToolTip=""), // 1000 0000 (128)
};
//to remove a state (ex:making Player just unarmed while walking ) ,we just do Player.CharacterState &= ~EPlayerCharacterState::Armed;

/**

 * @param CharacterState 
 */
inline void Toggle(EPlayerCharacterState CharacterState)
{
	//auto result=(__underlying_type(EPlayerCharacterState);
}

//ENUM_CLASS_FLAGS to enable bitwise operators (| , & , ^) for this enum
ENUM_CLASS_FLAGS(EPlayerCharacterState)
