// Fill out your copyright notice in the Description page of Project Settings.


#include "Amunition/weapon_base.h"

// Sets default values
Aweapon_base::Aweapon_base(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.Get()), pWeaponMeshComponent(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pWeaponMeshComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponSkeletalMesh"));
	RootComponent = pWeaponMeshComponent;
}

void Aweapon_base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called when the game starts or when spawned
void Aweapon_base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aweapon_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

