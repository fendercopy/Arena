// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


DECLARE_LOG_CATEGORY_EXTERN(Arena, Log, All);

#define A_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define A_LOG_CALLONLY(Verbosity) UE_LOG(Arena, Verbosity, TEXT("%s"), *A_LOG_CALLINFO)
#define A_LOG(Verbosity, Format, ...) UE_LOG(Arena, Verbosity, TEXT("%s %s"), *A_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))