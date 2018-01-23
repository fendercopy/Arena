// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaPawn.h"
#include "Arena.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "ArenaGameInstance.h"

// Sets default values
AArenaPawn::AArenaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	RootComponent = Body;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Body);
	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Body);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Body);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Body->SetCapsuleSize(34.0f, 88.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Warrior(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	Mesh->SetSkeletalMesh(SK_Warrior.Object);
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 650.0f;

	A_LOG(Warning, TEXT("INI ------> MaxHp=%d BaseHP=%d"));

}

// Called when the game starts or when spawned
void AArenaPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	//GameInstance에 접근해보자.. 궂이 이렇게 할 필요는 없지만....
	//Asset을 런타임에 동적으로 로드 하기위해 FStreamableManager를 사용한다. DefaultSubobject를 만들기 위해 Constructor에서 Asset 검증을 하고 로드 하려면 ConstructorHelpers를 사용함
	//전자를 소프트 레퍼런싱, 후자를 하드 래퍼런싱 이라고 한다.
	UArenaGameInstance* ArenaGameInstance = Cast<UArenaGameInstance>(GetGameInstance());
	int32 NewCharacterIndex = FMath::RandRange(0, CharacterAssets.Num());
	A_LOG(Warning, TEXT("NewCharancterIndex ------>%d"), NewCharacterIndex);
	if (ArenaGameInstance)
	{
		A_LOG(Warning, TEXT("NewCharancterIndex ------>%d"), NewCharacterIndex);

		//TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ArenaGameInstance->AssetLoader.SynchronousLoad(ChatacterAssets[NewCharancterIndex])); //단 이것은 게임로직에 동기적으로 로드한다. 즉, 로드 될동안 대기함
		//AssetLoader.SynchronousLoad()가 deprecated 되었음
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ArenaGameInstance->AssetLoader.LoadSynchronous(CharacterAssets[NewCharacterIndex], true)); //단 이것은 게임로직에 동기적으로 로드한다. 즉, 로드 될동안 대기함
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
	
}

// Called every frame
void AArenaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArenaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

