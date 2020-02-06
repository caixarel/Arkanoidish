// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Strong_Enemy.generated.h"

UCLASS()
class SHOOTER1_API AStrong_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrong_Enemy();
	UPROPERTY(EditAnywhere)
		class UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere)
		float Speed = -200.0f;
	UPROPERTY(EditAnywhere)
		int Lives = 3;

	UPROPERTY(EditAnywhere, Category = "Spawning")//cria uma categoria chamada Spawing
		TSubclassOf<class AEnemy_bullet>BulletBlueprint;

	FTimerHandle BulletTimer;

	UFUNCTION()
		void ShootBullet();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
