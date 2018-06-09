// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <IMSDKAdjustManager.h>
#include "iTopStatsSample.generated.h"

/**
 * 
 */
UCLASS()
class ITOPSAMPLE_API UiTopStatsSample : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Get Adjust Deep link")
    void GetAdjustDeepLink();
	
	
};
