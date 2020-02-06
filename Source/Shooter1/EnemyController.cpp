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
	ShootBullet();
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocarion = GetActorLocation();
	NewLocarion.X += Speed * DeltaTime;
	SetActorLocation (NewLocarion);

	/*if (NewLocarion.X > -600.0f)
	{
		this->Destroy();
	}*/
}

void AEnemyController::ShootBullet()
{
	GetWorldTimerManager().ClearTimer(BulletTimer);
	UWorld* World = GetWorld();//Getter for the cached world pointer, will return null if the actor is not actually spawned in a level

	if (World)
	{
		FVector Location = GetActorLocation();
		Location.X -= 100;

		World->SpawnActor<AEnemy_bullet>(BulletBlueprint, Location, FRotator::ZeroRotator);//vai gerar uma bala no local onde se encontra o actor(neste caso o shipController), axo ke ABulletController è o codigo da bala. e BulletBlueprint è o menu no Unreal onde podemos escolher o local para leter a buller blueprint
	}
	GetWorldTimerManager().SetTimer(BulletTimer, this, &AEnemyController::ShootBullet, 3.f, false);
}

