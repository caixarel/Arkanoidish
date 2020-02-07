// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletController.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include"EnemyController.h"
#include"SpaceShooterGameMode.h"
#include"ShipScontroller.h"
#include"Strong_Enemy.h"
#include"Boss.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootBox->SetGenerateOverlapEvents ( true);
	
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	RootBox->OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnOverlap);
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//actor will move in determinded direction
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);
	
}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if this actor hits a "weak" enemy that enemy will be destroyed and the player gains 1 point
	if (OtherActor->IsA(AEnemyController::StaticClass()))
	{
		this->Destroy();
		OtherActor->Destroy();
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
	//if this actor hits a "strong" enemy that enemy will be lose 1 life until he gets destroyed and the player gains 
	//1 point for each time he hits this enemy
	else if (OtherActor->IsA(AStrong_Enemy::StaticClass()))
	{
		AStrong_Enemy* enemy = Cast<AStrong_Enemy>(OtherActor);
		this->Destroy();
		enemy->Lives--;
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
		if (enemy->Lives == 0)
		{
			OtherActor->Destroy();
		}
	}
	//if this actor hits a "strong" enemy that enemy will be lose 1 life until he gets destroyed and the player gains 
	//1 point for each time he hits this enemy
	else if (OtherActor->IsA(ABoss::StaticClass()))
	{
		ABoss* boss = Cast<ABoss>(OtherActor);
		this->Destroy();
		boss->lives--;
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
		if (boss->lives == 0)
		{
			OtherActor->Destroy();
		}
	}
}

