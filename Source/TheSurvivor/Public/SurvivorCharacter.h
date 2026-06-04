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
/**
 * \copydoc ACharacter
 * \class ASurvivorCharacter
 * \brief Main player character class for the game.
 * \author Ahtat204
 *
 * \details
 * This class extends ACharacter to represent the player in a first-person
 * shooter training environment. It defines camera setup, input bindings,
 * weapon handling, and state management for various gameplay mechanics such as
 * shooting, aiming, reloading, and interacting with the environment.
 *
 * Features:
 * - Provides a first-person camera setup using a spring arm and follow camera.
 * - Handles player input actions (movement, looking, jumping, aiming, shooting, reloading, interacting).
 * - Manages weapon states (Unarmed, Armed, Firing, Reloading, Aiming).
 * - Supports attaching and interacting with weapons (e.g., picking up a pistol).
 * - Integrates animations and sounds for weapon actions (reload montage, reload sound).
 *
 * Most properties are exposed to Blueprints to allow designers to modify and
 * extend the character’s behavior without modifying C++ code.
 *
 * \note This class is configured with `config=Game` and designed to be extended
 *       in both C++ and Blueprints.
 */
UCLASS()
class THESURVIVOR_API ASurvivorCharacter : public ACharacter
{
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	GENERATED_BODY()
	/** used to specify the exact weapon to pick up inside the {@code AActor::NotifyActorBeginOverlap} */
	TWeakObjectPtr<AWeapon> DetectedWeapon;
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
	UInputMappingContext* MainMappingContext;
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
	UInputAction* InteractAction;
	/** Input action for aiming with a weapon.
	 * @remark it's bound to mouse right click	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	/** Input action for firing a weapon.
	 *  @remark it's bound to mouse left click	
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	/** Input action for reloading a weapon.
	 * @remark it's bound to the R  key	
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
	/** Input Action for arming the player with a weapon , whether pick up or from weapon inventory  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextWeapon;

#pragma endregion
#pragma region StateMachine
#pragma message(__FILE__ ": there's a 7 byte wasted memory padding in this variable")
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	EPlayerCharacterState CharacterState;
	UFUNCTION(BlueprintCallable,DisplayName="IsActive")
	inline bool IsActive(UPARAM(meta = (Bitmask, BitmaskEnum = EPlayerCharacterState)) uint8 Bitmask);

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
	/** Handles pickups,Mainly weapon pickup ,since the  	 */
	void Pickup(const FInputActionValue& Value);
	/** @note this function is just the first idea of implementing interaction , maybe will be moved to a dedicated Component */
	MAYBE_UNUSED void Interact(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
#pragma region Getters&setters
	/** @return The camera boom subObject. */
	NODISCARD FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** @return The follow camera subObject. */
	NODISCARD FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion
	
};
