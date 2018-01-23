// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

//BlueprintType :: 이 C++클래스는 블루프린트에서 변수로 선언이 가능한 타입이다
//Blueprintable : 블루프린트에서 이 C++ 클래스를 살솢받아서 새롭게 클래스를 살속받아 새롭개 확장할수 있다)
//하지만 이미 Actor애서 위의 파라메터가 생성되어 있으므로 추가로 더해듈필요는 없지만 예를들어 해봄
//UCLASS(BlueprintType, Blueprintable, config = Engine, meta = (ShortTooltip = "An Actor is an object that can be placed or spawned in the world."))

UCLASS(Config=Game,BlueprintType, Blueprintable)
class ARENA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
////멤버변수(UPROPERTY)
	//1.Blueprint 에서의 접근 권한
	//BlueprintReadOnly : 블루프린트에서는 읽기 만 가능
	//BluepeiintReadWrite : 블루프린트에서 읽기 쓰기가능

	//2.에디터에서의 겂 편집권한
	//Edit~ : 수정가능
	//Visible~ : 수정불가, 확인은 가능
	//~DefaultsOnly : 에디터의 블루프린트에서 그 클래스 스코프에서 수정가능
	//~InstanceOnly : 에디터의 레벨에 배치 한경우 (인스턴스를 생성 한경우) 그 인스턴스 스코프에서 수정가능
	//~AnyWhere : 둘다
	//다만 InstanceOnly로 한경우 블루프린트 클래스 애디터에서도 수정가능(DefaultsOnly) 혔음......

	//3.메타지정자
	//여러가지가 있음
	//AllowPrivateAccess : 
	//		Blueprint클래스가 NativeClass를 상속하는 경우 NativeClass의 Private 지정자애도 불구하고 블루프린트에서 접근가능하게 함(Getter와 Setter를 자동생성 해준다고 생각하자)
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class USkeletalMeshComponent* Weapon;
	UPROPERTY(Config,BlueprintReadWrite, EditDefaultsOnly,Category="Weapon|Damage")
	float MaxDamage;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Category="Weapon|Damage")
	float BaseDamage;
	UPROPERTY(Config,BlueprintReadWrite, VisibleAnyWhere,Category="Weapon|Damage")
	float TotalDamage;
private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon|Damage", meta=(AllowPrivateAccess="true"))
	bool bNoDamage;

public:
//멤버함수(UFUNCTION)
	//1.BlueprintCallable : 블루프린트에서 호출가능 다만, 카테고리를 꼭 지정해주자
	//2.BlueprintImplementableEvent : 이 함수의 구헌은 Blueprint에서 한다
	//3.BlueprintNativeEvent : 이 함수의 구현은 Native에 있지만 Blueprint에서 override 할 수 있다
	UFUNCTION(BlueprintCallable,Category="Weapon|Damage")
	float GetCalcDamage()
	{
		return BaseDamage;
	}
};
