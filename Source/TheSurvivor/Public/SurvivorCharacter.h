#pragma once
#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "TheSurvivor/TheSurvivor.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "SurvivorCharacter.generated.h"

class USurvivorAttributeSet;
class UGameplayAbility;
class AWeapon;
class UWeaponSystemComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class USurvivorAbilitySystemComponent;

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
class THESURVIVOR_API ASurvivorCharacter : public ACharacter, public IAbilitySystemInterface
{
public:
	/** 
	 * Overridden to track overlapped actors. Mainly used to detect pickable weapons.
	 * @param OtherActor The actor that intersected with this character's collision bounds.
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	GENERATED_BODY()
	
	/** Used to specify the exact weapon to pick up inside the {@code AActor::NotifyActorBeginOverlap} */
	TWeakObjectPtr<AWeapon> DetectedWeapon;

#pragma region Components
	/** Camera boom for positioning the follow camera behind the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera providing the player's first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Core Gameplay Ability System component managing the character's abilities, tags, and effects. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	USurvivorAbilitySystemComponent* AbilitySystemComponent;

	/** The Component responsible for Weapons functionalities, such as storing weapons, showing player weapons, choosing weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UWeaponSystemComponent* WeaponSystemComponent;

	/** Array of default gameplay abilities granted to the player character on initialization. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlayAbility, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> PlayerAbilities;

	/** The attribute set object representing the character's stats (e.g., Health, Stamina). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlayAttribute, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USurvivorAttributeSet> AttributeSet;

	/** Default gameplay effect applied during initialization to establish baseline attribute values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlayAttribute, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
#pragma endregion

#pragma region Inputs
	/** This the main mapping context that will be used the majority of the time. */
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
	 * @remark It's bound to mouse right click. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	/** Input action for firing a weapon.
	 *  @remark It's bound to mouse left click.	
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** Input action for reloading a weapon.
	 * @remark It's bound to the R key. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	/** Input Action for arming the player with a weapon, whether pick up or from weapon inventory. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextWeapon;
#pragma endregion

#pragma region StateMachine
#pragma message(__FILE__ ": there's a 7 byte wasted memory padding in this variable")
	/** Bitmask tracking active structural states of the player character. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", BitMask))
	EPlayerCharacterState CharacterState;

	/** 
	 * Checks if specific state flags are currently set on the character.
	 * @param Bitmask Bitmask of EPlayerCharacterState flags to evaluate.
	 * @return True if the specified state flags match or are active.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="IsActive")
	inline bool IsActive(UPARAM(meta = (Bitmask, BitmaskEnum = EPlayerCharacterState)) uint8 Bitmask);
#pragma endregion

public:
	/** 
	 * Customized object initializer constructor. Sets up default subobjects like components.
	 * @param ObjectInitializer Framework utility structure used to instantiate subobjects.
	 */
	explicit ASurvivorCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/** Called when the game starts or when the actor is spawned. */
	virtual void BeginPlay() override;

#pragma region InputsFunctions
	/** Handles reloading input. */
	void Reload(const FInputActionValue& Value);

	/** Handles shooting input. */
	void Shoot(const FInputActionValue& Value);

	/** Handles aiming input. */
	void Aim(const FInputActionValue& Value);

	/** Handles Movements inputs. */
	void Move(const FInputActionValue& Value);

	/** Handles looking input (camera rotation). */
	void Look(const FInputActionValue& Value);

	/** Handles pickups, mainly weapon pickup. */
	void Pickup(const FInputActionValue& Value);

	/** @note This function is just the first idea of implementing interaction, maybe will be moved to a dedicated Component. */
	MAYBE_UNUSED void Interact(const FInputActionValue& Value) const;

	/** 
	 * Allows the character to bind functionality to input component setups.
	 * @param PlayerInputComponent Subobject acting as an abstraction layer for raw hardware inputs.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Getters&setters
	/** @return The camera boom subObject. */
	NODISCARD FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** @return The follow camera subObject. */
	NODISCARD FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** @return The reference pointer to the AttributeSet subObject. */
	NODISCARD FORCEINLINE USurvivorAttributeSet* GetAttributeSet() const { return AttributeSet; }
#pragma endregion
	
	/** Interface implementation tracking the underlying ASC object instance. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** 
	 * Called on the Server when a controller takes ownership of this character.
	 * @param NewController The controller taking ownership.
	 */
	virtual void PossessedBy(AController* NewController) override;

	/** Client-side replication notification triggered when the PlayerState assignment completes. */
	virtual void OnRep_PlayerState() override;

	/** Handles initializing and binding internal caching hooks for the AbilitySystemComponent. */
	void InitAbilitySystemComponent();

	/** Iterates through the PlayerAbilities asset configuration array and registers them to the local ASC. */
	NOINLINE void GiveAbilities() const;

	/** Applies the default attribute calculation effects to establish standard health, speed, or utility attributes. */
	void InitDefaultAttributes() const;
};

