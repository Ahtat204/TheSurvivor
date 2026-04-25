// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]
#define LOCOMOTION_MASK (static_cast<uint8>(0x0F))
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
 * - Traversing :used to implement climbing
 * @attention I moved to this merged enum to perform bitwise operators and to solve the extra  13 bytes padding from the @code ASurvivorCharacter.CharacterState.
 * @remark there's no Unarmed since we just check if Armed&Idle is false
 */
UENUM(BlueprintType, Category="Weapons",
	meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true", ToolTip=
		"Represents the current weapon-related state of the player."))
enum class EPlayerCharacterState : uint8
{
	// --- ZONE 1: LOCOMOTION (Exclusive States: 0-7) ---
	// These use standard integers. Only one can be active at a time.
	Idle        = 0,   // 0000 0000
	Walk        = 1,   // 0000 0001
	Run         = 2,   // 0000 0010
	Jump        = 3,   // 0000 0011
	Traversing  = 4,   // 0000 0100

	// --- ZONE 2: ACTION FLAGS (Additive: Bits 4-7) ---
	// We start at 1<<4 to avoid touching the Locomotion bits.
	Armed       = 1 << 4, // 0001 0000 (16)
	Firing      = 1 << 5, // 0010 0000 (32)
	Reloading   = 1 << 6, // 0100 0000 (64)
	Aiming      = 1 << 7, // 1000 0000 (128)
};

//ENUM_CLASS_FLAGS to enable bitwise operators (| , & , ^) for this enum
ENUM_CLASS_FLAGS(EPlayerCharacterState)
