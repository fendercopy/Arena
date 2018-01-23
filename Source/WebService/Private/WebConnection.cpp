// Fill out your copyright notice in the Description page of Project Settings.

#include "WebConnection.h"

DEFINE_LOG_CATEGORY(WebConnection);

UWebConnection::UWebConnection()
{
	UE_LOG(WebConnection, Warning, TEXT("WebConnection Constructor CALL"));

	Host = TEXT("localhost:8000");
	URI = TEXT("/");

	Token = TEXT("");
}

void UWebConnection::RequestToken(const FString& UserID)
{
	UE_LOG(WebConnection, Warning, TEXT("Request Token CALL"));
	SendRequestPacket(UserID);
}

void UWebConnection::SendRequestPacket(const FString & Packet)
{
	FString Str;
	Str = TEXT("Token") + Packet;
	//서버로부터 받았다고 치고 여기서 Answer 호출
	ReceiveAnswerPacket(Str);

}

void UWebConnection::ReceiveAnswerPacket(const FString & Packet)
{
	UE_LOG(WebConnection, Warning, TEXT("ReceivePacket"));
	//ExecuteIfBound는 바인딩된 함수가 있다면 호출 해줌
	TokenCompleteDeligate.ExecuteIfBound(Packet);

}




