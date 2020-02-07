// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "BulletController.h"
#include "Kismet/GameplayStatics.h"
#include"TimerManager.h"
#include"Enemy_bullet.h"


// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	//shoots a bullet when spawned
	ShootBullet();
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//actor will move in a determined directio
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation (NewLocation);
}

void AEnemyController::ShootBullet()
{
	GetWorldTimerManager().ClearTimer(BulletTimer);
	UWorld* World = GetWorld();//Getter for the cached world pointer, will return null if the actor is not actually spawned in a level

	if (World)
	{
		FVector Location = GetActorLocation();
		Location.X -= 100;
		// actor will spawn a bullet
		World->SpawnActor<AEnemy_bullet>(BulletBlueprint, Location, FRotator::ZeroRotator);
	}
	//timer to control when the bullets are spawned.in this case every 3 seconds
	GetWorldTimerManager().SetTimer(BulletTimer, this, &AEnemyController::ShootBullet, 3.f, false);
}

