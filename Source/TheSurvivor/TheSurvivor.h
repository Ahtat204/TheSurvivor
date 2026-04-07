// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#define NODISCARD [[nodiscard]]
#define MAYBEUNUSED [[maybe_unused]]

/**
 * @enum ECharacterState
 * @brief Defines the high-level traversal and locomotion state of the character.
 * * This enum serves as the primary driver for the Animation Blueprint (AnimBP) state machine.
 * It distinguishes between grounded locomotion, airborne states, and specialized 
 * traversal actions (Climbing, Sprinting).
 * this enum is used in animations Layers to get exactly the state of the player and play the correct animation ,especially when holding a weapon
 * States:
 * - Idle:The player is standing , maybe holding a weapon maybe not
 * - Walk:the Player is Walking ,again ,maybe holding a weapon maybe not
 * - Run:the Player is running #############################
 * - Jump: indicates the Player is jumping (this is a bit hard to detect since this state comes form the Base ACharacter clss)
 * - Spring:
 * - Traversing :used to implement climbing
 * 
 */
UENUM(BlueprintType,Flags)
enum class ECharacterState : uint8
{
	/** Standing still or minimal movement; typical baseline state. */
	Idle = 0 UMETA(DisplayName = "Idle"),

	/** Standard intentional movement, usually blended with Idle in a 1D/2D BlendSpace. */
	Walk = 1 UMETA(DisplayName = "Walk"),

	/** High-speed locomotion; typically the default 'forward' move state for the survivor. */
	Run = 2 UMETA(DisplayName = "Run"),

	/** * Vertical traversal state. 
	 * @note Transition to this state should be triggered by the CharacterMovementComponent's 'IsFalling' check.
	 */
	Jump = 3 UMETA(DisplayName = "Jump"),

	/** * Maximum velocity locomotion. 
	 * @note Often consumes stamina and restricts certain actions (like Firing) in the WeaponSystem.
	 */
	Sprint = 4 UMETA(DisplayName = "Sprint",Tooltip="Maximum velocity locomotion."),

	/** * Specialized state for climbing or vaulting over obstacles. 
	 * @note Typically utilizes Root Motion to ensure the mesh precisely follows the ledge geometry.
	 */
	Traversing = 5 UMETA(DisplayName = "Traversing",Tooltip = " Specialized state for climbing or vaulting over obstacles. ")
};

/**
 * @brief Represents the current weapon-related state of the player.
 *
 * This enum is used to track and manage the player's interaction with weapons. 
 * The default state is Unarmed (value = 0). It can be utilized both in C++ and Blueprints 
 * to control animations, gameplay logic, and weapon handling mechanics.
 *
 * States:
 * - Unarmed   : The player has no weapon equipped (default state).
 * - Armed     : The player has a weapon equipped but is not actively using it.
 * - Firing    : The player is currently firing the equipped weapon.
 * - Reloading : The player is reloading the equipped weapon.
 * - Aiming    : The player is aiming down sights or focusing aim with the weapon.
 */
UENUM(BlueprintType, Category="Weapons", meta=(ToolTip="Represents the current weapon-related state of the player."))
enum class EWeaponState : uint8
{
	/**
	 * Indicate that the  character doesn't hold any weapon , it has nothing to do with the player running or walking or Idle state 
	 */
	Unarmed UMETA(DisplayName = "Unarmed",Tooltip = "Indicate that the  character doesn't hold any weapon , it has nothing to do with the player running or walking or Idle state "),
	Armed UMETA(DisplayName = "Armed"),
	Firing UMETA(DisplayName = "Firing"),
	Reloading UMETA(DisplayName = "Reloading"),
	Aiming UMETA(DisplayName = "Aiming"),
};

/**
 * represents the type/size of the weapon ,used in animation to choose the proper animation for the weapon
 */
UENUM(BlueprintType)
enum class EWeaponType:uint8
{
	Pistol=0 UMETA(DisplayName="Pistol"),
	Rifle=1 UMETA(DisplayName="Rifle"),
	Smg=2 UMETA(DisplayName="SMG"),
};