// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_bullet.generated.h"

UCLASS()
class SHOOTER1_API AEnemy_bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_bullet();
	UPROPERTY(EditAnyWhere)
		UShapeComponent* RootBox;// cria uma opcao no menu unreal para escolher a shape do component

	UPROPERTY(EditAnyWhere)
		float Speed = 600.0f;//cria a opcao de mudar a velocidade da bala no menu unreal

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	FTimerHandle DestroyBullet;
	void BulletDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
