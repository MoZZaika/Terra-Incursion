#pragma once
#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"
#include "Containers/UnrealString.h"

DEFINE_LOG_CATEGORY_STATIC(Terra, All, All)

#define CHECK_ERROR(expression, errorMsg) if(CheckError(static_cast<bool>(expression), errorMsg, __FILE__, __LINE__)) { return; }

inline bool CheckError(bool expressionValue, const FString& errorMsg, const char* fileName, uint32 fileLine)
{
	if (expressionValue)
		return false;

	UE_LOG(Terra, Error, TEXT("%s:%d: \"%s\""), *FString(fileName), fileLine, *errorMsg);
	
	if (GEngine)
	{
		const int32 idKey = -1;
		const int32 time = 100;
		GEngine->AddOnScreenDebugMessage(idKey, time, FColor::Red, errorMsg);
	}

	return true;
}