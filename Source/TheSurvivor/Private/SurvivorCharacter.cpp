
#include<SurvivorCharacter.h>

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon.h"
#include "WeaponSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


void ASurvivorCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (const auto Gun = Cast<AWeapon>(OtherActor))
	{
		LOG("Your log message here");
		DetectedWeapon = Gun;
	}
}


bool ASurvivorCharacter::IsActive(const uint8 Bitmask)
{
	return Bitmask & static_cast<uint8>(CharacterState);;
}

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
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}
	checkf(JumpAction, TEXT("JumpAction is null — assign in the editor"));
	checkf(MoveAction, TEXT("MoveAction is null — assign in the editor"));
	checkf(ReloadAction, TEXT("ReloadAction is null — assign in the editor"));
	checkf(LookAction, TEXT("LookAction is null — assign in the editor"));
	checkf(AimAction, TEXT("AimAction is null — assign in the editor"));
	checkf(NextWeapon, TEXT("NextWeapon InputAction Asset is not assigned"));
	checkf(MainMappingContext, TEXT("MainMappingContext is not assigned"));
	CharacterState=EPlayerCharacterState::Idle;
}

void ASurvivorCharacter::Reload(const FInputActionValue& Value)
{
	if (!Value.Get<bool>()) return;
	if (!ensureMsgf(WeaponSystemComponent, TEXT("WeaponSystemComponent missing"))) return;
	auto ReloadMontage = WeaponSystemComponent->CurrentWeapon->ReloadAnimMontage;

#if UE_BUILD_SHIPPING
	if (ReloadMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reload anim missing, reloading without animation"));
		ReloadWeapon();
		return;
	}
#else
	checkf(ReloadMontage, TEXT("Reload animation not assigned for %s"),
	       *WeaponSystemComponent->CurrentWeapon->GetName());
#endif
	PlayAnimMontage(ReloadMontage);
}


void ASurvivorCharacter::Shoot(const FInputActionValue& Value)
{
	
	if (!ensureMsgf(WeaponSystemComponent, TEXT("WeaponSystemComponent is null"))) return;
	if (WeaponSystemComponent->CurrentWeapon == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Player is aiming %hhd"), CharacterState)
	auto ammo=WeaponSystemComponent->CurrentWeapon->CurrentAmmo;
	if (ammo==0)
	{
		CharacterState &= ~EPlayerCharacterState::Firing;
		return;
	}
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
		WeaponSystemComponent->FireAction(CharacterState);
		
	}
	if (!bIsShooting)
	{
		CharacterState &= ~EPlayerCharacterState::Firing;
	}
}
void ASurvivorCharacter::Aim(const FInputActionValue& Value)
{
	if (!ensureMsgf(WeaponSystemComponent, TEXT("WeaponSystemComponent is null"))) return;
	if (WeaponSystemComponent->CurrentWeapon == nullptr) return;
	const auto bIsAiming = Value.Get<bool>();
	uint8 current = static_cast<uint8>(CharacterState) & static_cast<uint8>(EPlayerCharacterState::Armed);
	if (current == 0)return;
	bool active=IsActive(static_cast<uint8>(EPlayerCharacterState::Armed));
	if (bIsAiming)
	{
		CharacterState |= EPlayerCharacterState::Aiming;
		UE_LOG(LogTemp, Warning, TEXT("Player is aiming %hhd"), CharacterState)
		UE_LOG(LogTemp, Warning, TEXT("Player is aiming %hhd"), active)
	}
	if (!bIsAiming)
	{
		CharacterState &= ~EPlayerCharacterState::Aiming;
		UE_LOG(LogTemp, Warning, TEXT("Player is not aiming"))
	}
}

void ASurvivorCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr)return;
	const auto MovementVector = Value.Get<FVector2D>();
	if (MovementVector.Length() == 0)
	{
		CharacterState |= EPlayerCharacterState::Idle; // switch Idle to On
		CharacterState &= ~EPlayerCharacterState::Moving; //switch Moving to Off 
	}
	if (MovementVector.Length() > 0)
	{
		CharacterState &= ~EPlayerCharacterState::Idle; //switch Idle to off
		CharacterState |= EPlayerCharacterState::Moving; //switch moving to on
	}
	const auto Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
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

void ASurvivorCharacter::Pickup(const FInputActionValue& Value)
{
	if (DetectedWeapon == nullptr) return;
	if (Value.Get<bool>())
	{
		auto weapon = Cast<AWeapon>(DetectedWeapon);
		[[maybe_unused]] const auto Weapons = WeaponSystemComponent->AddWeapon(weapon);
		CharacterState |= EPlayerCharacterState::Armed;
		bool active = IsActive(static_cast<uint8>(EPlayerCharacterState::Armed));
		UE_LOG(LogTemp, Warning, TEXT("Player is aiming %d"), active);
	}
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
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Canceled, this, &ASurvivorCharacter::Shoot);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ASurvivorCharacter::Reload);
		EnhancedInputComponent->BindAction(NextWeapon, ETriggerEvent::Started, this, &ASurvivorCharacter::Pickup);
	}
}
