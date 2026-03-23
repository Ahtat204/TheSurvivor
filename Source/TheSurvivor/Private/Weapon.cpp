// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
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

// Called when the game starts or when spawned
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
}

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

ABullet::ABullet(const FObjectInitializer& FObjectInitializer)
{
}

