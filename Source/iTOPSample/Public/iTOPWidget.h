// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <IMSDKFriendManager.h>
#include <IMSDKLoginManager.h>
#include <IMSDKAuthManager.h>
#include <IMSDKNoticeListener.h>
#include <IMSDKNoticeManager.h>
#include <IMSDKPushListener.h>
#include <IMSDKPushManager.h>
#include <IMSDKStatManager.h> 
#include <IMSDKGameServiceManager.h> 
#include <IMSDKGameServiceListener.h> 
#include <IMSDKExtendToolManager.h>
#include <IMSDKWebViewListener.h>
#include <IMSDKWebViewManager.h>
#include <IMSDKLocationManager.h>
#include <IMSDKAdjustManager.h>
#include "iTOPUtil.h"
#include "CoreMinimal.h" 
#include "Blueprint/UserWidget.h"
#include "iTOPWidget.generated.h" 

/**
 * 
 */
UCLASS()
class ITOPSAMPLE_API UiTOPWidget : public UUserWidget
{
	GENERATED_BODY() 
public:
	UFUNCTION(BlueprintCallable, Category = "guestLogin")
		void handleGuestLoginButtonClick();

	UFUNCTION(BlueprintCallable, Category = "FBLogin")
		void handleFBLoginButtonClick();

	UFUNCTION(BlueprintCallable, Category = "FBBind")
		void handleFBBindButtonClick();

	UFUNCTION(BlueprintCallable, Category = "GcGpLogin")
		void handleGcGpLoginButtonClick(); 

	UFUNCTION(BlueprintCallable, Category = "gcgpBind")
		void handleGcGpBindButtonClick();

	UFUNCTION(BlueprintCallable, Category = "getBindInfo")
		void handleGetBindInfoButtonClick();
		
	UFUNCTION(BlueprintCallable, Category = "logout")
        		void handleLogoutButtonClick();

	UFUNCTION(BlueprintCallable, Category = "fbShareFunction")
		void handleFBShareButtonClick();

	UFUNCTION(BlueprintCallable, Category = "TWShare")
		void handleTWShareButtonClick(); 

	UFUNCTION(BlueprintCallable, Category = "loadNotice")
		void handleLoadNoticeButtonClick(); 

	UFUNCTION(BlueprintCallable, Category = "pushRegister")
		void handlePushRegisterButtonClick(); 

	UFUNCTION(BlueprintCallable, Category = "pushUnregister")
		void handlePushUnregisterButtonClick(); 

	UFUNCTION(BlueprintCallable, Category = "statReport")
		void handleStatReportButtonClick(); 
	
	
    

};  
