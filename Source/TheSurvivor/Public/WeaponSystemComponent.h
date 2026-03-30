#pragma once

#include "CoreMinimal.h"
#include "SurvivorCharacter.h"
#include "Components/ActorComponent.h"
#include "TheSurvivor/TheSurvivor.h"
#include "WeaponSystemComponent.generated.h"

class AWeapon;

/**
 * @class UWeaponSystemComponent
 * @brief Orchestrates weapon lifecycle, inventory management, and state-driven combat logic.
 * * This component acts as a "Service Layer" for the character's combat capabilities. 
 * It manages a collection of AWeapon actors and reacts to changes in the player's 
 * state to execute firing or reloading sequences.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESURVIVOR_API UWeaponSystemComponent : public UActorComponent
{
    GENERATED_BODY()

    /** Internal registry of all weapons currently possessed by the owner. */
    TArray<AWeapon*> Weapons;

    /** Pointer to the currently active weapon in the character's hands. */
    TObjectPtr<AWeapon> CurrentWeapon;

protected:
    virtual void BeginPlay() override;

public: 
    explicit UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer);

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /**
     * @brief Retrieves a weapon reference by its index in the inventory.
     * @param Index The position in the Weapons array.
     * @return A pointer to the weapon, or nullptr if the index is out of bounds.
     * @note Uses NODISCARD to ensure the caller validates the returned pointer.
     */
    NODISCARD AWeapon* GetWeapon(uint16 Index) const; 

    /** @brief Returns a reference to the entire internal weapon registry. */
    TArray<AWeapon*>& GetAllWeapons();

    /**
     * @brief Adds a new weapon actor to the character's inventory.
     * @param newWeapon The weapon actor to be registered.
     * @return The updated weapon array reference.
     */
    TArray<AWeapon*>& AddWeapon(AWeapon* newWeapon);

    /**
     * @brief Removes a weapon from the registry, typically for dropping or destruction.
     * @param Index The index of the weapon to remove.
     * @return The resulting weapon array after removal.
     */
    TArray<AWeapon*> RemoveWeapon(int16 Index);

    /**
     * @brief Observes the current WeaponState to trigger firing logic.
     * @param WeaponState The observed state from the character/controller.
     * @details This function acts as a reactor; if the state is 'Shooting', 
     * it validates cooldowns and ammo before instructing the CurrentWeapon to fire.
     */
    void FireAction(EWeaponState WeaponState) const;

    /**
     * @brief Observes the current WeaponState to trigger reloading logic.
     * @param WeaponState The observed state from the character/controller.
     * @details Synchronizes weapon reload animations and ammo pool deductions.
     */
    void ReloadAction(EWeaponState WeaponState);

    /**
     * @brief Deterministic check to see if the system is ready for a new command.
     * @return True if the component is in an 'Idle' state and not currently locked by an animation or cooldown.
     */
    bool CanPerformAction() const;
};