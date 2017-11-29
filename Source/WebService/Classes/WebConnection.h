// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h" //이헤더는 UBT에 의해 Intermediate/Build/Win64 안에 생성됨, 메타 데이터를 생성하도록 UBT가 코드를 추가하는것으로 보임, 고로 모든 include후 가장 마지막에 include 함

/**
 * 
 */

 //WEBSERVICE_API 매크로는 Development 구성에서 __declspec(dllexport) 로 치환되어 모듈의 DLL 로 빌드가된다, shipping 에서는 NULL로 치환되어 .exe로 정적 빌드된다

UCLASS()
class WEBSERVICE_API UWebConnection : public UObject 
{
	GENERATED_BODY()

public:
	UWebConnection();
	
	UPROPERTY()
		FString Host;
	UPROPERTY()
		FString URI;

	//UPROPERTY() 매크로를 사용하지 않으면 메타정보가 생성 되지 않는다.
	//고로 UWebConnection 의 메타클래스는 메타클래스대로 인스턴스 되고
	//UWebConnection의 인스턴스(CDO)는 코드의 클래스로 인스턴스 된다는 말인데....
	//Constructor가 호출 되는 시점을 보자면 기동할때 메타클래스와 CDO가 각각 생성 된다고 보는 쪽이 맞을 것 같다.
	FString Token;

	UFUNCTION()
		void RequestToken();
	
};
DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);

