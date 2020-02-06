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
	FVector NewLocation = GetActorLocation();
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);
	

	/*if (NewLocation.X > 600)
	{
		this->Destroy();
	}*/
}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass()))
	{
		this->Destroy();
		OtherActor->Destroy();
		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
	else if (OtherActor->IsA(AStrong_Enemy::StaticClass()))
	{
		AStrong_Enemy* enemy = Cast<AStrong_Enemy>(OtherActor);
		this->Destroy();
		enemy->Lives--;
		if (enemy->Lives == 0)
		{
			OtherActor->Destroy();
		}
	}
	else if (OtherActor->IsA(ABoss::StaticClass()))
	{
		ABoss* boss = Cast<ABoss>(OtherActor);
		this->Destroy();
		boss->lives--;
		if (boss->lives == 0)
		{
			OtherActor->Destroy();
		}
	}
}

