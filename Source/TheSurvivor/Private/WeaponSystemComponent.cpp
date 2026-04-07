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
TArray<AWeapon*>& UWeaponSystemComponent::AddWeapon(AWeapon* newWeapon)
{
	UE_LOG(LogTemp, Warning, TEXT("AddWeapon is Fired,not from work but I mean it's on the stack frame"));
	if (newWeapon==nullptr){return Weapons;}
	if (Weapons.Num() >= 10)
	{
		Weapons[10]=newWeapon;
		return Weapons;
	}
	Weapons.Add(newWeapon);
	AttachWeapon(newWeapon);
	return Weapons;
}
void UWeaponSystemComponent::FireAction(const EWeaponState WeaponState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if (WeaponState==EWeaponState::Firing)
		{
			CurrentWeapon->FireBullet();
		}
	}
}

void UWeaponSystemComponent::ReloadAction(EWeaponState WeaponState) const
{
	if (CurrentWeapon!=nullptr)
	{
		if (WeaponState==EWeaponState::Reloading)
		{
			
		}
	}
}


void UWeaponSystemComponent::AttachWeapon( AWeapon* pickUpWeapon) 
{
	UE_LOG(LogTemp, Warning, TEXT("AttachWeapon is Fired,not from work but I mean it's on the stack frame"));
	if (Owner==nullptr) return;
	auto SkeletonMeshComponent=Owner->GetMesh();
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

TArray<AWeapon*> UWeaponSystemComponent::RemoveWeapon(int16 Index)
{
	
	if (Index >= Weapons.Num())
	{
		return Weapons;
	}
	Weapons.RemoveAt(Index);
	return Weapons;
}
