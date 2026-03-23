#pragma once
#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "TheSurvivor/TheSurvivor.h"
#include "SurvivorCharacter.generated.h"


class AWeapon;
class UWeaponSystemComponent;
class USoundCue;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;



UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle = 0 UMETA(DisplayName = "Idle"),
	Walk=1 UMETA(DisplayName = "Walk"),
	Run=2 UMETA(DisplayName = "Run"),
	Jump=3 UMETA(DisplayName = "Jump"),
	Sprint=4 UMETA(DisplayName = "Sprint"),
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
	Unarmed UMETA(DisplayName = "Unarmed"),
	Armed UMETA(DisplayName = "Armed"),
	Firing UMETA(DisplayName = "Firing"),
	Reloading UMETA(DisplayName = "Reloading"),
	Aiming UMETA(DisplayName = "Aiming"),
};
/**
 * @class ASurvivorCharacter
 * @brief Main player character class for the  game.
 *
 * This class extends ACharacter to represent the player in a first-person
 * shooter training environment. It defines camera setup, input bindings,
 * weapon handling, and state management for various gameplay mechanics such as
 * shooting, aiming, reloading, and interacting with the environment.
 *
 * ### Responsibilities:
 * - Provides a first-person camera setup using a spring arm and follow camera.
 * - Handles player input actions (movement, looking, jumping, aiming, shooting, reloading, interacting).
 * - Manages weapon states (Unarmed, Armed, Firing, Reloading, Aiming).
 * - Supports attaching and interacting with weapons (e.g., picking up a pistol).
 * - Integrates animations and sounds for weapon actions (reload montage, reload sound).
 *
 * ### Blueprint Integration:
 * Most properties are exposed to Blueprints to allow designers to modify and
 * extend the character’s behavior without modifying C++ code.
 *
 * @note This class is configured with `config=Game` and designed to be extended in both
 *       C++ and Blueprints.
 */
UCLASS()
class THESURVIVOR_API ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()
#pragma region Components
	/** Camera boom for positioning the follow camera behind the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	/** Follow camera providing the player's first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	/** the Component responsible for Weapons functionalities ,such as storing weapons , showing player weapons , choosing weapon*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UWeaponSystemComponent* WeaponSystemComponent;
#pragma endregion
#pragma region Inputs
	/** this the main mapping context that will be used tha majority of the time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MainMappginContext;
	/** Input action for jumping. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	/** Input action for player movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Input action for camera look/rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	/** Input action for interacting with objects (e.g., picking up weapons). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Interact;
	/** Input action for aiming with a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	/** Input action for firing a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	/** Input action for reloading a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
#pragma endregion
#pragma region Effects
	/** Sound to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds", meta = (AllowPrivateAccess = "true"))
	USoundCue* ReloadSound;
	/** Animation montage to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimMontage;
	/** Reference to the underlying APlayerState associated with this character. */
#pragma endregion
#pragma region StateMachine
	/** Current weapon state of the player (e.g., Armed, Firing, Reloading). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EWeaponState CurrentWeaponState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;
#pragma endregion
public:
	explicit ASurvivorCharacter(const FObjectInitializer& ObjectInitialize);
protected:
	virtual void BeginPlay() override;
#pragma region InputsFunctions
	/** Handles reloading input. */
	void Reload(const FInputActionValue& Value);
	/** Handles shooting input. */
	void Shoot(const FInputActionValue& Value);
	/** Handles aiming input. */
	void Aim(const FInputActionValue& Value);
	/** handles Movements inputs */
	void Move(const FInputActionValue& Value);
	/** Handles looking input (camera rotation). */
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

public:
	virtual void Tick(float DeltaTime) override;

#pragma region Getters&setters
	/** @return The camera boom subObject. */
	NODISCARD FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** @return The follow camera subObject. */
	NODISCARD FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion

	UFUNCTION(BlueprintImplementableEvent)
	void AttachWeapon(AWeapon* Weapon);
};
