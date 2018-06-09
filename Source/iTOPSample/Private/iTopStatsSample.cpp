// Fill out your copyright notice in the Description page of Project Settings.

#include "iTopStatsSample.h"
#include "LogHelp.h"


void UiTopStatsSample::GetAdjustDeepLink()
{
    LogDebug(FString("handleLoadNoticeButtonClick"));
#if PLATFORM_ANDROID

    
#endif
    
#if PLATFORM_IOS
    NSLog(@ "= == == = click handleLoadNoticeButtonClick");
    dispatch_async(dispatch_get_main_queue(), ^
                   {
                       IMSDKAdjustManager* manager = IMSDKAdjustManager::getInstance();
                       
                       std::string link = "";
                       do {
                           link = manager->pollStandardDeepLink();
                           NSLog(@"get StandardDeepLink = %s", link.c_str());
                       }while (link.length() > 0);
                       
                       do {
                           link = manager->pollDeferredDeepLink();
                           NSLog(@"get DeferredDeepLink = %s", link.c_str());
                       }while (link.length() > 0);
                       
                        });
#endif
}
