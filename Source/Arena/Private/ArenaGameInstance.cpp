// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaGameInstance.h"
#include "Arena.h"

/*Unreal 객채의 Class Constructor 는 UC의 defaultproperty 처럼쓰자*/
UArenaGameInstance::UArenaGameInstance()
{
	A_LOG(Warning, TEXT("Gameinstance Constructor CALL START"));	
	/**
	CreateDefaultSubobject 는 Constructor에서만 사용
	이제 ArenaGameInstance의 Instance 는 WebConnection의 Outer 가 되고
	WebConnection은 ArenaGameInstance 의 Instance의 Subobject가 된다.
	**/
	WebConnection = CreateDefaultSubobject<UWebConnection>(/*HASH Seed*/TEXT("Webconnection"));
	A_LOG(Warning, TEXT("Gameinstance Constructor CALL END"));
}

void UArenaGameInstance::Init(void)
{
	Super::Init();

	//LogCatagory : 로그의 카테고리 LogClass, LogTemp 등이 기본 제공됨, 모듈별로 설정 가능, 커스텀도 가능
	//Vervosity : Log, Warning, Error, Fatal, Display 등이 제공됨
	UE_LOG(/*LogCatagory*/LogClass, /*Vervosity*/Warning, /*Format*/TEXT("%s"), TEXT("GameInstance Init"));

	//Compile Time에 Class 정보가 필요하다면 UObject::StaticClass()로 가져올 수 있다
	UClass* MetaClassAtCompileTime = UWebConnection::StaticClass();
	//Run Time에 Class 정보가 필요하다면 UObjectInstance->GetClass()로 가져올 수 있다
	UClass* MetaClassAtRunTime = WebConnection->GetClass();
	if (MetaClassAtCompileTime == MetaClassAtRunTime)
	{
		//Compile Time 에나 RunTime 에나 Class 정보는 동일하다
		A_LOG(Warning, TEXT("ClassInfo At Compile-Time is same with Run-Time"));
	}

	//UProperty와 UFunction 의 상위 클래스인 UField를 TFieldIterator로 검색 할 수 있다.
	for (TFieldIterator<UProperty> It(MetaClassAtCompileTime); It; ++It)
	{
		A_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName());

		//MetaClass에서 찾은 속성, 이름으로 WebConnection 인스턴스의 값을 조회 해봄
		UStrProperty* StrProp = FindField<UStrProperty>(MetaClassAtCompileTime, *It->GetName());
		if (StrProp)
		{
			A_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnection));
		}
	}

	//만약 UFunction을 찾고 싶다면 TfieldIterator<UFunction>으로 위와 같이 찾아 볼 수도 있다.
	//찾으려는 Function의 이름을 알고 있다면 FindFunctionByName(FString) 으로 찾아 볼 수 있다.
	//C++로 구현된 Native Function 이라면 Function Lookup Table을 검색 해 볼 수도 있다. (블프 함수도 되는지는 나중에 테스트 해보자)
	for (const auto& Entry : MetaClassAtCompileTime->NativeFunctionLookupTable)
	{
		A_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
		UFunction* FuncProp = MetaClassAtCompileTime->FindFunctionByName(Entry.Name);

		//MetaClass의 Function 정보를 가지고 인스턴스의 Function을 Call 해봄
		if (FuncProp->ParmsSize == 0)
		{
			WebConnection->ProcessEvent(FuncProp, NULL);
		}
	}
}
