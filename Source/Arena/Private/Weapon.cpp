// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SkeletalMeshComponent를 subobject로 한다
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	//SkeletalMeshComponent를 Root로 함
	RootComponent = Weapon;
	//사용할 SkeletalMesh를 찾아옴
	//ConstructorHelper를 사용하기 위해 UObject/ConstructorHelpers.h를 인클루드함, Constructor에서만 사용 가능(CDO생성시에만 실행 된다는 의미) --> 고로 엔진 기동시에 리소스 유무가 체크 됨
	//만약 게임 실행중에 리소스를 가져온다면 StaticLoadObject()등을 사용 해야한다
	//FObjectFinder는 해당 리소스의 인스턴스를 가져온다
	//FClassFinder는 해당 리소스의 클래스(타입)을 가져온다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_BlackNight(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));
	Weapon->SetSkeletalMesh(SK_BlackNight.Object);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

