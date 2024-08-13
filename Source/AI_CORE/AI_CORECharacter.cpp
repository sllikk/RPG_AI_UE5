// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_CORECharacter.h"

#include "NavigationInvokerComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Team.h"

AAI_CORECharacter::AAI_CORECharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	pCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	pCameraBoom->SetupAttachment(RootComponent);
	pCameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	pCameraBoom->TargetArmLength = 1100.f;
	pCameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	pCameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	pCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	pCameraComponent->SetupAttachment(pCameraBoom, USpringArmComponent::SocketName);
	pCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	pNavigationInvokerComponent = CreateDefaultSubobject<UNavigationInvokerComponent>(TEXT("Player_NavInvoker"));
	pNavigationInvokerComponent->SetGenerationRadii(4000.0f, 6000.0f);
	pPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Player_PERCEPTION_STIMUL"));
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

void AAI_CORECharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (pPerceptionStimuliSourceComponent->IsValidLowLevelFast())
	{
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Hearing::StaticClass());
		pPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Team::StaticClass());
	}
	
}

void AAI_CORECharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AAI_CORECharacter::BeginPlay()
{
	Super::BeginPlay();

}

