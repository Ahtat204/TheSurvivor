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
	WeaponSystemComponent = CreateDefaultSubobject<UWeaponSystemComponent>("WeaponSystemComponent");
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
	// TODO:replace  CharacterState = ECharacterState::Idle with EPlayerCharacterState::Idle;
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
	const bool bIsReloading = Value.Get<bool>();
	uint8 current = static_cast<uint8>(CharacterState) &
		(static_cast<uint8>(EPlayerCharacterState::Aiming) |
		 static_cast<uint8>(EPlayerCharacterState::Armed) |
		 static_cast<uint8>(EPlayerCharacterState::Firing));
	if (current == 0) return;

	if (WeaponSystemComponent->CurrentWeapon->ReloadAnimMontage != nullptr)
	{
		if (bIsReloading)
		{
			CharacterState |= EPlayerCharacterState::Reloading;
			PlayAnimMontage(WeaponSystemComponent->CurrentWeapon->ReloadAnimMontage);
		}
		else
		{
			CharacterState &= ~EPlayerCharacterState::Reloading;
		}
	}
}


void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivorCharacter::Shoot(const FInputActionValue& Value)
{
	const bool bIsShooting = Value.Get<bool>();
	uint8 current = static_cast<uint8>(CharacterState) &
		(static_cast<uint8>(EPlayerCharacterState::Aiming) | static_cast<uint8>(EPlayerCharacterState::Armed));
	/*bitwise AND has higher precedence than OR , thus it's the correct way to check both is by isolating them, if we just did*
	 * uint8 current=(uint8)CharacterState & (uint8)EPlayerCharacterState::Aiming | (uint8)EPlayerCharacterState::Armed;
	 * the OR will never be checked since AND higher precedence that OR
	 */

	if (current == 0) return;
	if (bIsShooting)
	{
		CharacterState |= EPlayerCharacterState::Firing;
	}
	if (!bIsShooting)
	{
		CharacterState &= ~EPlayerCharacterState::Firing;
	}
}

void ASurvivorCharacter::Aim(const FInputActionValue& Value)
{
	const auto bIsAiming = Value.Get<bool>();
	uint8 current = static_cast<uint8>(CharacterState) & static_cast<uint8>(EPlayerCharacterState::Armed);
	if (current == 0)return;
	if (bIsAiming)
	{
		CharacterState |= EPlayerCharacterState::Aiming;
	}
	if (!bIsAiming)
	{
		CharacterState &= ~EPlayerCharacterState::Aiming;
	}
}

void ASurvivorCharacter::Move(const FInputActionValue& Value)
{
	const auto MovementVector = Value.Get<FVector2D>();
	if (MovementVector.Length() == 0) CharacterState |= EPlayerCharacterState::Idle;
	if (MovementVector.Length() > 0) CharacterState &= ~EPlayerCharacterState::Idle;
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
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ASurvivorCharacter::Reload);
	}
}
