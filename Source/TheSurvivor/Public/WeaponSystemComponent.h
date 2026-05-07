#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Components/ActorComponent.h"
#include "TheSurvivor/TheSurvivor.h"
#include "WeaponSystemComponent.generated.h"

class ASurvivorCharacter;
class AWeapon;

/**
 * @class UWeaponSystemComponent
 * @brief Orchestrates weapon lifecycle, inventory management, and state-driven combat logic.
 * * This component acts as a "Service Layer" for the character's combat capabilities. 
 * It manages a collection of AWeapon actors and reacts to changes in the player's 
 * state to execute firing or reloading sequences.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,
	DisplayName="Weapon Component",
	ToolTip=
	"this component is like an ASP.NET or Spring service,it is delegated to manage the interaction with Weapons for more flexibility instead of just one Weapon in the Character "
))
class THESURVIVOR_API UWeaponSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	/** Internal registry of all weapons currently possessed by the owner. */
	TArray<AWeapon*> Weapons;

public:
	/** Pointer to the currently active weapon in the character's hands. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<AWeapon> CurrentWeapon;

protected:
	virtual void BeginPlay() override;

	/**
	 * Cache the Owner without causing Circular reference
	 */
	TWeakObjectPtr<ASurvivorCharacter> Owner;

public:
	explicit UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Retrieves a weapon reference by its index in the inventory.
	 * @param Index The position in the Weapons array.
	 * @return A pointer to the weapon, or nullptr if the index is out of bounds.
	 * @note Uses NODISCARD to ensure the caller validates the returned pointer.
	 */

	_Ret_maybenull_ NODISCARD inline AWeapon* GetWeapon(_Const_ _In_ uint16 Index) const;

	/**  @brief Returns a non-owning, thread-safe view of the weapon list.
    @note This is high-performance (no copy, no allocation).
 */
	inline TArrayView<AWeapon* const> GetAllWeapons() const;

	/**
	 * @brief Adds a new weapon actor to the character's inventory.
	 * @param newWeapon The weapon actor to be registered.
	 * @return The updated weapon array reference.
	 */
	NODISCARD TArrayView<AWeapon* const> AddWeapon(_In_ AWeapon* newWeapon);

	/**
	 * @brief Removes a weapon from the registry, typically for dropping or destruction.
	 * @param Index The index of the weapon to remove.
	 * @return The resulting weapon array after removal.
	 */
	TArrayView<AWeapon* const> RemoveWeapon(_In_ int16 Index);

	/**
	 * @brief Observes the current WeaponState to trigger firing logic.
	 * @param WeaponState The observed state from the character/controller.
	 * @details This function acts as a reactor; if the state is 'Shooting', 
	 * it validates cooldowns and ammo before instructing the CurrentWeapon to fire.
	 */
	void FireAction(_In_ const EPlayerCharacterState WeaponState) const;

	/**
	 * @brief Observes the current WeaponState to trigger reloading logic.
	 * @param WeaponState The observed state from the character/controller.
	 * @details Synchronizes weapon reload animations and ammo pool deductions.
	 */
	void ReloadAction(_In_ EPlayerCharacterState WeaponState) const;

	/**
	 * @brief this method is used only as a wrapper on the Actor::AttachToComponent with additional validation checks(ex:nullptr checks)
	 */
	void AttachWeapon(AWeapon* pickUpWeapon) noexcept;
};
