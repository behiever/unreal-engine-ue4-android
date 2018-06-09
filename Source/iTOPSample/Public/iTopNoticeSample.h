// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <IMSDKNoticeListener.h>
#include <IMSDKNoticeManager.h>
#include "iTopNoticeSample.generated.h"

/**
 * 
 */
UCLASS()
class ITOPSAMPLE_API UiTopNoticeSample : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Notice")
	void LoadNotice();
	
	
	
};
