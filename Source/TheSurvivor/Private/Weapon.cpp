#include <Weapon.h>
#include <Components/CapsuleComponent.h>
#include "Niagara/Public/NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AWeapon::AWeapon(const FObjectInitializer& FObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMeshComponent;
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(RootComponent);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupSphere->SetSphereRadius(50.f);
	FireSound = CreateDefaultSubobject<USoundCue>("FireSound");
	NiagraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagraComponent->SetupAttachment(SkeletalMeshComponent);

}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::FireBullet()
{
	if (CurrentAmmo==0 && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Out Of Ammo , Please press R to Reload");
	}
	const auto SpawnLocation = this->SkeletalMeshComponent->GetSocketLocation("Muzzle"); //TODO:since I plan to add more weapons,I should remove this bad hardcoding
	const auto SpawnRotation = this->SkeletalMeshComponent->GetSocketRotation("Muzzle");//TODO:here too

	if (CurrentAmmo > 0)
	{
		if (BulletClass)
		{
			const FActorSpawnParameters SpawnParams;
			auto Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation(), 3,5);
			CurrentAmmo--;
		}
	}
}

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

ABullet::ABullet(const FObjectInitializer& FObjectInitializer)
{
	SetActorRelativeRotation(FRotator(0, 0, 0));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	if (StaticMeshComponent)
	{
		RootComponent = StaticMeshComponent;
	}
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->InitialSpeed = 10000.f;
		ProjectileMovementComponent->MaxSpeed = 0.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = false;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	}
	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule");
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleHalfHeight(81.08f);
	CapsuleComponent->SetCapsuleRadius(30.944208f);
}

