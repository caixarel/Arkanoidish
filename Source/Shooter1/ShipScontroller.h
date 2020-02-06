// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipScontroller.generated.h"

UCLASS()
class SHOOTER1_API AShipScontroller : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipScontroller();

protected:
	//AShipScontroller();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionBox;//cria uma opcao no menu do unreal com o nome CollisionBox onde se pode escolher o tipo de collider.UShapeComponent serve para defenir a forma do componente

	UPROPERTY(EditAnywhere)
	float Speed = 10.0f;//cria uma opcao publica no menu unreal onde podes alterar a velocidade sem modificar o codigo

	UPROPERTY(EditAnywhere, Category = "Spawning")//cria uma categoria chamada Spawing
	TSubclassOf<class ABulletController>BulletBlueprint;//nessa categoria vai ser possivel escolher a blueprint da bala 

	void Move_XAxis(float AxisValue);
	void Move_yAxis(float AxisValue);
	void OnShoot();
	void OnRestart();

	FVector CurrentVelocity;

	bool Died;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
