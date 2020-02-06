// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER1_API ASpaceShooterGameMode : public AGameMode
{
	GENERATED_BODY()

	float MINIMUN_INTERVAL = 0.5f;
	float MAXIMUN_INTERVAL = 2.0f;
	float TIME_TO_MINIMUN_INTERVAL = 30.0f;


	// Called when the game starts or when spawned
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyController>EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

	void IncrementScore();
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass);
protected:
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget>StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
