#include"WeaponSystemComponent.h"
#include<Weapon.h>
#include "Kismet/GameplayStatics.h"
#include <SurvivorCharacter.h>

#include "MovieSceneTracksComponentTypes.h"

//TODO:use Animation Layer Interface to make Animation blueprint flexible for each weapon type 
UWeaponSystemComponent::UWeaponSystemComponent(const FObjectInitializer& FObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UWeaponSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner =CastChecked<ASurvivorCharacter>(GetOwner());
}
void UWeaponSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
AWeapon* UWeaponSystemComponent::GetWeapon(const uint16 Index) const
{
	if (Index >= Weapons.Num() )
	{
		return nullptr;
	}
	return Weapons[Index];
}
 TArrayView<AWeapon* const> UWeaponSystemComponent::GetAllWeapons() 
{
	return Weapons;
}
TArrayView<AWeapon* const> UWeaponSystemComponent::AddWeapon(AWeapon* newWeapon)
{
	UE_LOG(LogTemp, Warning, TEXT("AddWeapon is Fired"));
	if (newWeapon==nullptr){return Weapons;}
	if (Weapons.Num() < 10)
	{
		Weapons.Add(newWeapon);
		return Weapons;
	}
	Weapons.Add(newWeapon);
	AttachWeapon(newWeapon);
	UE_LOG(LogTemp, Display, TEXT("Your log message here"));
	return Weapons;
}
void UWeaponSystemComponent::FireAction(const EPlayerCharacterState CharacterState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if ((static_cast<uint8>(CharacterState) & static_cast<uint8>(EPlayerCharacterState::Firing))==1)
		{
			CurrentWeapon->FireBullet();
		}
	}
}

void UWeaponSystemComponent::ReloadAction(EPlayerCharacterState CharacterState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if ((static_cast<uint8>(CharacterState) & (static_cast<uint8>(EPlayerCharacterState::Armed) | static_cast<uint8>(EPlayerCharacterState::Reloading)))==1)
		{
			
		}
	}
}


void UWeaponSystemComponent::AttachWeapon( AWeapon* pickUpWeapon) 
{
	if (Owner==nullptr) return;
	auto SkeletonMeshComponent=Owner.Get()->GetMesh();
	if (!IsValid(SkeletonMeshComponent)) return;
	if (pickUpWeapon==nullptr) return;
	auto weaponType=pickUpWeapon->WeaponType;
	if (weaponType==EWeaponType::Rifle)
	{
		if (CurrentWeapon==nullptr)
		{
			this->CurrentWeapon=pickUpWeapon;
		}
		CurrentWeapon->AttachToComponent(SkeletonMeshComponent,  FAttachmentTransformRules::KeepWorldTransform,TEXT("AR4XSocket"));
	}
	
}

TArrayView<AWeapon* const> UWeaponSystemComponent::RemoveWeapon(int16 Index)
{
	
	if (Index >= Weapons.Num())
	{
		return Weapons;
	}
	Weapons.RemoveAt(Index);
	return Weapons;
}
