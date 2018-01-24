// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaGameInstance.h"
#include "Arena.h"
//#include "Runtime/Engine/Public/EngineUtils.h"
//#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
//#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/UObjectIterator.h"
#include "Engine/StreamableManager.h"

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

	//UObject를 dynamic 하게 할당 해본다. NewObject<>로 할당하는 것은 subobject가 아니다
	//NewObject<UObject>(Outer) 를 사용 함
	//WebConnection 돠 WebConnection_New 의 기능상 차이는 없다. 코드적으로는 생성 시점의 차이가 있을뿐이고
	//의도 상으로는 WebConnection의 경우 이 객체를 변경 하지 않겠다는 전제가 있어야 한다, WebConnection_New의 경웅는 상황에 따라 변경 가능하다는 의도가 들어 있어야 한다
	//그리고 defaultSubobject로 지정하면 런타임에 이 값이 null이 아님을 보장 함
	WebConnection_New = NewObject<UWebConnection>(/*Outer*/this);	//새로 할당하는 UWebConnection 오브젝트의 Outer를 따로 지정 할 수 있다.
	A_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnection_New->GetOuter()->GetClass()->GetName());

	//현재 Actor의 모든 서브오브젝트의 default 값을를 검색해본다.
	//WebConnection_New 는 Subobject가 아니므로 검색 되지 않음
	TArray<UObject*> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects)
	{
		A_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		A_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetName());		
	}

	//World내의 모든 Actor 순회 ranged for 를 써보자
	//FActorRange 클래스는 "Runtime/Engine/Public/EngineUtils.h" 를 인클루드 해야함
	UWorld* CurrentWorld = GetWorld();
	for (const auto& Entry : FActorRange(CurrentWorld))
	{
		A_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
		TArray<UObject*> Components;
		Entry->GetDefaultSubobjects(Components);
		for (const auto& Component : Components)
		{
			A_LOG(Warning, TEXT("---Component : %s"), *Component->GetName());
		}
	}
	//World내의 모든 Actor 순회 TActorIterator<> 를 써보자
	for (TActorIterator<AStaticMeshActor> iter(CurrentWorld); iter; ++iter)
	{
		A_LOG(Warning, TEXT("StaticMeshActor : %s"), *iter->GetName());
	}
	//World내에 로딩된 언리얼 오브젝트 순회
	WebConnection->Host = TEXT("localhost");
	WebConnection_New->Host = TEXT("127.0.0.1");
	 
	for (TObjectIterator<UWebConnection> iter; iter; ++iter)
	{
		UWebConnection* Comp = *iter;
		A_LOG(Warning, TEXT("WebConnection Host is a %s"), *Comp->Host);
	}

	//WebConnection::TokenCompleteDeligate에 함수 바인딩
	//바인딩 할 함수(여기서는 UArenaGameInstance::TokenRequestComplete()에 따라 다른 function을 사용 하여 바인딩한다.
	//전역C++함수 : BindStatic
	//전역C++람다 : BindRambda
	//C++클래스멤버 : BindRaw
	//공유포인터 클래스의 멤버(스레드미지원) : BindSP
	//공유포인터 클래스의 멤버(스레드 지원) : BindThreadSafeSP
	//UFUNCTION 멤버 : BindUFunction
	//언리얼오브젝트의 멤버 : BIndUObject
	WebConnection->TokenCompleteDeligate.BindUObject(this, &UArenaGameInstance::TokenRequestComplete);

	//Deligate 실험해보자..
	WebConnection->RequestToken(TEXT("BaeBuRee"));


}

void UArenaGameInstance::TokenRequestComplete(const FString & Token)
{
	A_LOG(Warning, TEXT("Token = %s"), *Token);
}
