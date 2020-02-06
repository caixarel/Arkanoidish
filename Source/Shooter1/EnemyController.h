// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class SHOOTER1_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere)
	float Speed = -200.0f;

	UPROPERTY(EditAnywhere, Category = "Spawning")//cria uma categoria chamada Spawing
		TSubclassOf<class AEnemy_bullet>BulletBlueprint;

	FTimerHandle BulletTimer;

	UFUNCTION()
		void ShootBullet();
};
