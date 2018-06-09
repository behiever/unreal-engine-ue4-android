// Fill out your copyright notice in the Description page of Project Settings.

#include "iTopNoticeSample.h"
#include "LogHelp.h"


class PrintNoticeListener : public IMSDKNoticeListener {
	void OnLoadNotice(IMSDKNoticeResult result)
	{
#if PLATFORM_IOS
		LogDebug(FString(result.toJsonString().c_str()));
		NSLog(@ "notice result:%s", result.toJsonString().c_str());
#endif
		 

#if PLATFORM_ANDROID
		iTOPLOGD("Friend-IMSDKNoticeListener callback  retMsg = %s", result.imsdkRetMsg.c_str());

		iTOPLOGD("Friend-IMSDKNoticeListener callback  list size = %d", result.list.size());

		iTOPLOGD("Friend-IMSDKNoticeListener callback  retMsg = %s", result.imsdkRetMsg.c_str());

		for (IMSDKNoticeInfo Finfo : result.list)
		{ 
			iTOPLOGD("Friend-IMSDKNoticeListener callback  noticeContent = %s", Finfo.content.c_str()); 
			iTOPLOGD("Friend-IMSDKNoticeListener callback  noticeLanguage = %s", Finfo.language.c_str()); 
			iTOPLOGD("Friend-IMSDKNoticeListener callback  noticeLanguage = %s", Finfo.openId.c_str());
			iTOPLOGD("Friend-IMSDKNoticeListener callback  noticeLanguage = %s", Finfo.openId.c_str()); 
		} 
#endif
	}
};

PrintNoticeListener iTOPNoticeListener;

void UiTopNoticeSample::LoadNotice()
{
	UE_LOG(LogTemp, Warning, TEXT("handleLoadNoticeButtonClick"));
	LogDebug(FString("handleLoadNoticeButtonClick"));
#if PLATFORM_ANDROID
	 IMSDKNoticeManager* manager = IMSDKNoticeManager::getInstance();
	manager->init(GJavaVM);
	manager->setChannel("imsdk");
	manager->setListener(&iTOPNoticeListener);
	manager->loadNoticeData("1.0.0", "en-US", 1, 2, 1, 1, "");  

#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handleLoadNoticeButtonClick");
	PrintNoticeListener *listener = new PrintNoticeListener();
	IMSDKNoticeManager::getInstance()->setListener(listener);
	IMSDKNoticeManager::getInstance()->setChannel("imsdk");
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKNoticeManager::getInstance()->loadNoticeData("1.0.0", "en-US", 1, 2, YES, 1, "");
	}); 
#endif
}
