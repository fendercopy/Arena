// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WebConnection.h"
#include "ArenaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UArenaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:	
	UArenaGameInstance();

	virtual void Init() override;
	
	UPROPERTY()
	class UWebConnection* WebConnection;
};
