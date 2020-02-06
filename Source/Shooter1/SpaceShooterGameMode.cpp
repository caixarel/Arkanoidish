// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include"EnemyController.h"
#include "Engine/World.h"
#include "GameWidget.h"
#include"SpaceShooterGameMode.h"


void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	((UGameWidget*)CurrentWidget)->Load();
}

void ASpaceShooterGameMode::IncrementScore()
{
	Score += 100;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
	}
	if (NewWidgetClass!=nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
	}

	if (CurrentWidget!=nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTimer += DeltaTime;
	EnemyTimer -= DeltaTime;

	if (EnemyTimer<=0.0f)
	{
		float DifficultyPercentage = FMath::Min(GameTimer / TIME_TO_MINIMUN_INTERVAL, 1.0f);//return the lowest value with a maximun of 1
		EnemyTimer = MAXIMUN_INTERVAL - (MAXIMUN_INTERVAL - MINIMUN_INTERVAL) * DifficultyPercentage;//longer the game goes, higher becamos de difficulty wich will make the enemy timer smaller.
		//when the enemy timer reaches a minimun of 0.5 is on max level
		//each second gets 62*Deltatime, so enemys are spawned every 0.5seconds at max level
		UWorld* World = GetWorld();
		UE_LOG(LogTemp, Warning, TEXT("%f"), EnemyTimer);

		if (World)
		{
			FVector Location = FVector(2000.0f, FMath::RandRange(300.0f, 4400.0f),70.0f);
			World->SpawnActor<AEnemyController>(EnemyBlueprint, Location, FRotator::ZeroRotator);
		}
	}
}
