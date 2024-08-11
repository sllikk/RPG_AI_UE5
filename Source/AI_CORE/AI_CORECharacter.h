// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_CORECharacter.generated.h"

/** Forward declaration to improve compiling times */
class UCameraComponent;
class USpringArmComponent;
class UNavigationInvokerComponent;

UCLASS(Blueprintable)
class AAI_CORECharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* pCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* pCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UNavigationInvokerComponent* pNavigationInvokerComponent;
	
public:
	AAI_CORECharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UCameraComponent* GetTopDownCameraComponent() const;
	USpringArmComponent* GetCameraBoom() const;

private:


	
};


FORCEINLINE USpringArmComponent* AAI_CORECharacter::GetCameraBoom() const
{
	return pCameraBoom;
}

FORCEINLINE UCameraComponent* AAI_CORECharacter::GetTopDownCameraComponent() const
{
	return pCameraComponent;
}
