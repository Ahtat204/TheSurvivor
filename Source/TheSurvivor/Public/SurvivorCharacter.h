// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorCharacter.generated.h"

class USoundCue;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class THESURVIVOR_API ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()
#pragma region Components
	/** Camera boom for positioning the follow camera behind the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	/** Follow camera providing the player's first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma endregion
	#pragma region Inputs
	/** Input mapping context used when the player is in a challenge. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ChallengeMappingContext;
	/** Input mapping context used when the player is free-roaming (not in a challenge). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* FreeMappingContext;
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
	UInputAction* Interact;
	/** Input action for aiming with a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	/** Input action for firing a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	/** Input action for reloading a weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
#pragma endregion
#pragma region Effects
	/** Sound to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds", meta = (AllowPrivateAccess = "true"))
	USoundCue* ReloadSound;
	/** Animation montage to play when reloading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadAnimMontage;
	/** Reference to the underlying APlayerState associated with this character. */
#pragma endregion
public:
	// Sets default values for this character's properties
	explicit ASurvivorCharacter(const FObjectInitializer& ObjectInitialize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma region InputsFunctions
	/** Handles reloading input. */
	void Reload(const FInputActionValue& Value);
	/** Handles shooting input. */
	void Shoot(const FInputActionValue& Value);
	/** Handles aiming input. */
	void Aim(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	/** Handles looking input (camera rotation). */
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#pragma region Getters&setters
	/** @return The camera boom subObject. */
	[[nodiscard]] FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** @return The follow camera subObject. */
	[[nodiscard]] FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion

	// Called to bind functionality to input
};
