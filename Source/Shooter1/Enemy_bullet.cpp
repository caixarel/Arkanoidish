// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_bullet.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include"EnemyController.h"
#include"SpaceShooterGameMode.h"
#include"ShipScontroller.h"
#include"TimerManager.h"

// Sets default values
AEnemy_bullet::AEnemy_bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->SetGenerateOverlapEvents(true);
}



void AEnemy_bullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AShipScontroller::StaticClass()))
	{
		this->Destroy();
		OtherActor->Destroy();
	}
}

void AEnemy_bullet::BulletDestroy()
{
	Destroy();
}

// Called when the game starts or when spawned
void AEnemy_bullet::BeginPlay()
{
	Super::BeginPlay();
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_bullet::OnOverlap);
	GetWorldTimerManager().SetTimer(DestroyBullet, this, &AEnemy_bullet::BulletDestroy, 5.f, false);
}

// Called every frame
void AEnemy_bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

