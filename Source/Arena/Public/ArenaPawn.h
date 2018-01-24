// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArenaPawn.generated.h"

UCLASS(Config=Game)
class ARENA_API AArenaPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArenaPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Collidion")
		class UCapsuleComponent* Body;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Visual")
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Helper")
		class UArrowComponent* Arrow;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Camera")
		class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Camera")
		class UCameraComponent* Camera;
	//config에서 수정 한 값을 적용 하려면 에디터를 재시작 해야함
	UPROPERTY(Config,BlueprintReadWrite,EditDefaultsOnly,Category="Stat")
		float MaxHP;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Stat")
		float CurrentHP;
	UPROPERTY(Config,BlueprintReadWrite, VisibleAnywhere, Category = "Stat")
		float BaseHP;

private:
	UPROPERTY(Config)
		TArray<FStringAssetReference> CharacterAssets;


};
