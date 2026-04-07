#include<SurvivorCharacter.h>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon.h"
#include "WeaponSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASurvivorCharacter::ASurvivorCharacter(const FObjectInitializer& ObjectInitialize)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	WeaponSystemComponent=CreateDefaultSubobject<UWeaponSystemComponent>("WeaponSystemComponent");
	CameraBoom->SetupAttachment(GetMesh(),TEXT("head"));
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterState=ECharacterState::Idle;
	if (auto const PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}
    
}

void ASurvivorCharacter::Reload(const FInputActionValue& Value)
{
	const auto bIsReloading=Value.Get<bool>();
	if (WeaponSystemComponent->CurrentWeapon->ReloadAnimMontage!=nullptr)
	{
		if (bIsReloading)
		{
			CurrentWeaponState=EWeaponState::Reloading;
			PlayAnimMontage(WeaponSystemComponent->CurrentWeapon->ReloadAnimMontage);
		}
	}
	CurrentWeaponState=EWeaponState::Aiming;
}

void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivorCharacter::Shoot(const FInputActionValue& Value)
{
	const bool bIsShooting = Value.Get<bool>();

	if (bIsShooting && CurrentWeaponState == EWeaponState::Aiming)
	{
		CurrentWeaponState = EWeaponState::Firing;
		WeaponSystemComponent->FireAction(CurrentWeaponState);
	}
	else if (!bIsShooting && CurrentWeaponState == EWeaponState::Firing)
	{
		/** * Here is the "Magic": We check the persistent boolean 
		 * to see if the player is STILL holding Aim.
		 */
		CurrentWeaponState = bIsAimingInputActive ? EWeaponState::Aiming : EWeaponState::Armed;
        
		WeaponSystemComponent->FireAction(CurrentWeaponState);
	}
}

void ASurvivorCharacter::Aim(const FInputActionValue& Value)
{
	bIsAimingInputActive=Value.Get<bool>();
	if (bIsAimingInputActive && CurrentWeaponState==EWeaponState::Armed)
	{
		CurrentWeaponState=EWeaponState::Aiming;
	}
}

void ASurvivorCharacter::Move(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();
	if (MovementVector.Length()==0) CharacterState=ECharacterState::Idle;
	if (Controller != nullptr)
	{
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void ASurvivorCharacter::Look(const FInputActionValue& Value)
{
	const auto LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASurvivorCharacter::Interact(const FInputActionValue& Value)
{
	
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Look);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ASurvivorCharacter::Aim);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ASurvivorCharacter::Shoot);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this,&ASurvivorCharacter::Reload);

	}
}

