// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WebConnection.h"
#include "Engine/StreamableManager.h"
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

	UPROPERTY()
	class UWebConnection* WebConnection_New;

	FStreamableManager AssetLoader;

	//WebConnection::TokenCompleteDeligate에 바인딩 할 함수 정의
	UFUNCTION()
	void TokenRequestComplete(const FString& Token);

};
