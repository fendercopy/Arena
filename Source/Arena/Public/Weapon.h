// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

//BlueprintType :: �� C++Ŭ������ �������Ʈ���� ������ ������ ������ Ÿ���̴�
//Blueprintable : �������Ʈ���� �� C++ Ŭ������ �왜�޾Ƽ� ���Ӱ� Ŭ������ ��ӹ޾� ���Ӱ� Ȯ���Ҽ� �ִ�)
//������ �̹� Actor�ּ� ���� �Ķ���Ͱ� �����Ǿ� �����Ƿ� �߰��� ���ص��ʿ�� ������ ������� �غ�
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
////�������(UPROPERTY)
	//1.Blueprint ������ ���� ����
	//BlueprintReadOnly : �������Ʈ������ �б� �� ����
	//BluepeiintReadWrite : �������Ʈ���� �б� ���Ⱑ��

	//2.�����Ϳ����� �� ��������
	//Edit~ : ��������
	//Visible~ : �����Ұ�, Ȯ���� ����
	//~DefaultsOnly : �������� �������Ʈ���� �� Ŭ���� ���������� ��������
	//~InstanceOnly : �������� ������ ��ġ �Ѱ�� (�ν��Ͻ��� ���� �Ѱ��) �� �ν��Ͻ� ���������� ��������
	//~AnyWhere : �Ѵ�
	//�ٸ� InstanceOnly�� �Ѱ�� �������Ʈ Ŭ���� �ֵ��Ϳ����� ��������(DefaultsOnly) ����......

	//3.��Ÿ������
	//���������� ����
	//AllowPrivateAccess : 
	//		BlueprintŬ������ NativeClass�� ����ϴ� ��� NativeClass�� Private �����ھֵ� �ұ��ϰ� �������Ʈ���� ���ٰ����ϰ� ��(Getter�� Setter�� �ڵ����� ���شٰ� ��������)
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
//����Լ�(UFUNCTION)
	//1.BlueprintCallable : �������Ʈ���� ȣ�Ⱑ�� �ٸ�, ī�װ��� �� ����������
	//2.BlueprintImplementableEvent : �� �Լ��� ������ Blueprint���� �Ѵ�
	//3.BlueprintNativeEvent : �� �Լ��� ������ Native�� ������ Blueprint���� override �� �� �ִ�
	UFUNCTION(BlueprintCallable,Category="Weapon|Damage")
	float GetCalcDamage()
	{
		return BaseDamage;
	}
};
