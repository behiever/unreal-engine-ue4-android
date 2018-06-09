
#include "iTOPWidget.h" 
#include "LogHelp.h"

#if PLATFORM_MAC
	#include <GuestSimulator.h>
#endif

class PrintLoginListener : public IMSDKLoginListener{
public:
	void OnLoginNotify(IMSDKLoginResult loginResult)
	{
#if PLATFORM_IOS
		LogDebug(FString("Login result:"));
		LogDebug(FString(loginResult.toJsonString().c_str()));
		NSLog(@ "= == == == == result json : %s", loginResult.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("OnLoginNotify imsdkRetCode ... %d", loginResult.imsdkRetCode);
		iTOPLOGD("OnLoginNotify imsdkRetMsg ... %s", loginResult.imsdkRetMsg.c_str());
		iTOPLOGD("OnLoginNotify thirdRetCode. %d", loginResult.thirdRetCode);
		iTOPLOGD("OnLoginNotify thirdRetMsg %s", loginResult.thirdRetMsg.c_str());
		iTOPLOGD("OnLoginNotify retExtraJson %s", loginResult.retExtraJson.c_str());
		iTOPLOGD("OnLoginNotify innerToken %s", loginResult.guid_token.c_str());
		iTOPLOGD("OnLoginNotify channelToken %s", loginResult.channel_token.c_str());
		iTOPLOGD("OnLoginNotify openid %s", loginResult.guid_open_id.c_str());
		iTOPLOGD("OnLoginNotify guidUserNick %s", loginResult.guid_user_nick.c_str());
		iTOPLOGD("OnLoginNotify channelUserId %s", loginResult.channel_userid.c_str());
		iTOPLOGD("OnLoginNotify channel %s", loginResult.channel.c_str());
		iTOPLOGD("OnLoginNotify method_tag %s", loginResult.method_tag.c_str());
#endif
#if PLATFORM_MAC
		UE_LOG(LogTemp, Warning, TEXT("====printLoginResult===="));
		UE_LOG(LogTemp, Warning, TEXT("| retCode : %d"), loginResult.retCode);
		UE_LOG(LogTemp, Warning, TEXT("| imsdkRetCode : %d"), loginResult.imsdkRetCode);
		UE_LOG(LogTemp, Warning, TEXT("| thirdRetCode : %d"), loginResult.thirdRetCode);
		UE_LOG(LogTemp, Warning, TEXT("| guid_channel_id : %d"), loginResult.guid_channel_id);
		UE_LOG(LogTemp, Warning, TEXT("| guid_game_id : %d"), loginResult.guid_game_id);
		UE_LOG(LogTemp, Warning, TEXT("===================="));
#endif
	} 

	void OnGetBindInfoNotify(IMSDKBindInfo loginRet)
	{
#if PLATFORM_IOS
		NSLog(@ "= == == == == bind info count : %lu", loginRet.channel_info.size());
		NSLog(@ "= == == == == bind info login_info : %s", loginRet.login_info.toJsonString().c_str());
		 
#endif

#if PLATFORM_ANDROID 
		iTOPLOGD("OnGetBindInfoNotify imsdkRetCode ... %d", loginRet.login_info.imsdkRetCode);
		iTOPLOGD("OnGetBindInfoNotify imsdkRetMsg ... %s", loginRet.login_info.imsdkRetMsg.c_str());
		iTOPLOGD("OnGetBindInfoNotify thirdRetCode. %d", loginRet.login_info.thirdRetCode);
		iTOPLOGD("OnGetBindInfoNotify thirdRetMsg %s", loginRet.login_info.thirdRetMsg.c_str());
		for (IMSDKChannelInfo Finfo : loginRet.channel_info)
		{
			iTOPLOGD("OnGetBindInfoNotify callback  nick = %s", Finfo.nick.c_str()); 
		}
#endif
	} 

	void OnLogoutNotify(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "= == == == == logout info count : %s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
#endif
	}
};
PrintLoginListener iTOPLoginListener;

class PrintFriendListener : public IMSDKFriendListener {
	void OnFriendNotify(IMSDKFriendResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "= == == == == result OnFriendNotify : %s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
        iTOPLOGD("Friend-OnShareNotify callback %d , retMsg = %s", result.imsdkRetCode, result.imsdkRetMsg.c_str());
        iTOPLOGD("Friend-OnFriendNotify callback %d , thirdMsg = %s", result.thirdRetCode, result.thirdRetMsg.c_str());
        for(IMSDKFriendInfo friendInfo : result.friends){
            iTOPLOGD("Friend-OnFriendNotify FriendInfo guid_open_id = %s , channel_userid = %s, guid_user_nick = %s, guid_user_portrait = %s, guid_user_gender = %d", friendInfo.guid_open_id.c_str(), friendInfo.channel_userid.c_str(), friendInfo.guid_user_nick.c_str(), friendInfo.guid_user_portrait.c_str(), friendInfo.guid_user_gender);
        }
#endif
	}


	virtual void OnShareNotify(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "= == == == == result OnShareNotify : %s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("Friend-OnShareNotify callback %d , retMsg = %s", result.imsdkRetCode, result.imsdkRetMsg.c_str());
		iTOPLOGD("Friend-OnFriendNotify callback %d , thirdMsg = %s", result.thirdRetCode, result.thirdRetMsg.c_str());
#endif
	}
};
PrintFriendListener iTOPFriendListener;

 

class PrintPushListener : public IMSDKPushListener {
public:
	void OnRegister(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "OnRegister :%s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnRegister callback  retMsg = %s", result.imsdkRetMsg.c_str());
#endif
	}


	void OnUnregister(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "OnUnregister :%s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnUnregister callback  retMsg = %s", result.imsdkRetMsg.c_str());
#endif
	}


	void OnSetTag(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "OnSetTag :%s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnSetTag callback  retMsg = %s", result.imsdkRetMsg.c_str());
#endif
	}


	void OnDelTag(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "OnDelTag :%s", result.toJsonString().c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnDelTag callback  retMsg = %s", result.imsdkRetMsg.c_str());
#endif
	} 

	void OnNotification(std::string jsonMessage)
	{
#if PLATFORM_IOS
		NSLog(@ "OnNotification :%s", jsonMessage.c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnNotification callback  retMsg = %s", jsonMessage.c_str());
#endif
	} 

	void OnNotifactionClick(std::string jsonMessage)
	{
#if PLATFORM_IOS
		NSLog(@ "OnNotifactionClick :%s", jsonMessage.c_str());
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("PrintPushListener OnNotifactionClick callback  retMsg = %s", jsonMessage.c_str());
#endif
	}
};

PrintPushListener iTOPPushListener;

class PrintAuthListener {
public:
	static void OnAuth(IMSDKAuthResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnAuth: %s", result.toJsonString().c_str());
#endif
		
#if PLATFORM_ANDROID
		iTOPLOGD("OnAuth imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnAuth imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnAuth thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnAuth thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnAuth retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnAuth snsInfoVec.size  %d", result.snsInfoVec.size());

		iTOPLOGD("OnAuth channelId %d", result.channelId);
		iTOPLOGD("OnAuth gameId %d", result.gameId);
		iTOPLOGD("OnAuth openId %s", result.openId.c_str());
		iTOPLOGD("OnAuth innerToken %s", result.innerToken.c_str());
		iTOPLOGD("OnAuth deviceId %s", result.deviceId.c_str());

		iTOPLOGD("OnAuth tokenExpireTime %lld", result.tokenExpireTime);
		iTOPLOGD("OnAuth isFirstLogin %d", result.isFirstLogin);
#endif 
	} 

	static void OnConnect(IMSDKAuthConnectResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnConnect: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID 
		iTOPLOGD("OnConnect imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnConnect imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnConnect thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnConnect thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnConnect retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnConnect channelId %d", result.channelId); 
		iTOPLOGD("OnConnect openId %s", result.openId.c_str());
		iTOPLOGD("OnConnect confirmCode %s", result.confirmCode.c_str());
		iTOPLOGD("OnConnect userName %s", result.userName.c_str());
		iTOPLOGD("OnConnect pictureUrl %s", result.pictureUrl.c_str());
		iTOPLOGD("OnConnect gender. %d", result.gender);   
#endif
	} 

	static void OnReConnect(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnReConnect: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID 
		iTOPLOGD("OnReConnect imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnReConnect imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnReConnect thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnReConnect thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnReConnect retExtraJson %s", result.retExtraJson.c_str());
#endif
	} 

	static void OnRestore(IMSDKAuthResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnRestore: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnRestore imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnRestore imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnRestore thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnRestore thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnRestore retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnRestore channelId %d", result.channelId);
		iTOPLOGD("OnRestore gameId %d", result.gameId);
		iTOPLOGD("OnRestore openId %s", result.openId.c_str());
		iTOPLOGD("OnRestore innerToken %s", result.innerToken.c_str());
		iTOPLOGD("OnRestore deviceId %s", result.deviceId.c_str());

		iTOPLOGD("OnRestore tokenExpireTime %lld", result.tokenExpireTime);
		iTOPLOGD("OnRestore isFirstLogin %d", result.isFirstLogin);
#endif
	}


	static void OnRecover(IMSDKAuthResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnRecover: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnRecover imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnRecover imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnRecover thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnRecover thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnRecover retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnRecover channelId %d", result.channelId);
		iTOPLOGD("OnRecover gameId %d", result.gameId);
		iTOPLOGD("OnRecover openId %s", result.openId.c_str());
		iTOPLOGD("OnRecover innerToken %s", result.innerToken.c_str());
		iTOPLOGD("OnRecover deviceId %s", result.deviceId.c_str());

		iTOPLOGD("OnRecover tokenExpireTime %lld", result.tokenExpireTime);
		iTOPLOGD("OnRecover isFirstLogin %d", result.isFirstLogin);
#endif
	}


	static void OnGetMigrateCode(IMSDKAuthMigrateResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnGetMigrateCode: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnGetMigrateCode imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnGetMigrateCode imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnGetMigrateCode thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnGetMigrateCode thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnGetMigrateCode retExtraJson %s", result.retExtraJson.c_str()); 
		iTOPLOGD("OnGetMigrateCode validTime. %d", result.validTime);
		iTOPLOGD("OnGetMigrateCode migrateCode %s", result.migrateCode.c_str());
#endif
	}


	static void OnMigrate(IMSDKAuthResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnMigrate: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnMigrate imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnMigrate imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnMigrate thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnMigrate thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnMigrate retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnMigrate channelId %d", result.channelId);
		iTOPLOGD("OnMigrate gameId %d", result.gameId);
		iTOPLOGD("OnMigrate openId %s", result.openId.c_str());
		iTOPLOGD("OnMigrate innerToken %s", result.innerToken.c_str());
		iTOPLOGD("OnMigrate deviceId %s", result.deviceId.c_str());

		iTOPLOGD("OnMigrate tokenExpireTime %lld", result.tokenExpireTime);
		iTOPLOGD("OnMigrate isFirstLogin %d", result.isFirstLogin);
#endif
	}


	static void OnGetMigrateInfo(IMSDKAuthMigrateResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnGetMigrateInfo: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnGetMigrateCode imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnGetMigrateCode imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnGetMigrateCode thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnGetMigrateCode thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnGetMigrateCode retExtraJson %s", result.retExtraJson.c_str());
		iTOPLOGD("OnGetMigrateInfo validTime. %d", result.validTime);
		iTOPLOGD("OnGetMigrateInfo migrateCode %s", result.migrateCode.c_str());
#endif
		
	}


	static void OnDisconnect(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnDisconnect: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnDisconnect imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnDisconnect imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnDisconnect thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnDisconnect thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnDisconnect retExtraJson %s", result.retExtraJson.c_str());
#endif
	}


	static void OnDeleteDeviceAccount(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback deleteDeviceAccount: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnDeleteDeviceAccount imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnDeleteDeviceAccount imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnDeleteDeviceAccount thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnDeleteDeviceAccount thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnDeleteDeviceAccount retExtraJson %s", result.retExtraJson.c_str());
#endif
	}


	static void OnDeleteAllAccount(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnDeleteAllAccount: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnDeleteAllAccount imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnDeleteAllAccount imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnDeleteAllAccount thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnDeleteAllAccount thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnDeleteAllAccount retExtraJson %s", result.retExtraJson.c_str());
#endif
	} 

	static void OnSignOut(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnSignOut: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnSignOut imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnSignOut imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnSignOut thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnSignOut thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnSignOut retExtraJson %s", result.retExtraJson.c_str());
#endif
	}


	static void OnAllBind(IMSDKAuthResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnAllBind: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnMigrate imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnMigrate imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnMigrate thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnMigrate thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnMigrate retExtraJson %s", result.retExtraJson.c_str());

		iTOPLOGD("OnMigrate channelId %d", result.channelId);
		iTOPLOGD("OnMigrate gameId %d", result.gameId);
		iTOPLOGD("OnMigrate openId %s", result.openId.c_str());
		iTOPLOGD("OnMigrate innerToken %s", result.innerToken.c_str());
		iTOPLOGD("OnMigrate deviceId %s", result.deviceId.c_str());

		iTOPLOGD("OnMigrate tokenExpireTime %lld", result.tokenExpireTime);
		iTOPLOGD("OnMigrate isFirstLogin %d", result.isFirstLogin);
#endif
	}


	static void OnBindSendCode(IMSDKResult result)
	{
#if PLATFORM_IOS
		NSLog(@ "callback OnBindSendCode: %s", result.toJsonString().c_str());
#endif
#if PLATFORM_ANDROID
		iTOPLOGD("OnSignOut imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnSignOut imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnSignOut thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnSignOut thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnSignOut retExtraJson %s", result.retExtraJson.c_str());
#endif
	}
};

PrintAuthListener iTOPAuthListener;

 

class PrintGameServiceListener : public IMSDKGameServiceListener {
public:
	virtual void OnGameServiceNotify(IMSDKResult result) {
#if PLATFORM_ANDROID
		iTOPLOGD("OnGameServiceNotify imsdkRetCode ... %d", result.imsdkRetCode);
		iTOPLOGD("OnGameServiceNotify imsdkRetMsg ... %s", result.imsdkRetMsg.c_str());
		iTOPLOGD("OnGameServiceNotify thirdRetCode. %d", result.thirdRetCode);
		iTOPLOGD("OnGameServiceNotify thirdRetMsg %s", result.thirdRetMsg.c_str());
		iTOPLOGD("OnGameServiceNotify retExtraJson %s", result.retExtraJson.c_str());
#endif
	} 
};
PrintGameServiceListener iTOPGameServiceListener;

//webview回调
class PrintWebViewListener : public IMSDKWebViewListener{
public:
    void OnGetTicket(IMSDKWebViewTicketResult &ticketRet) {
#if PLATFORM_IOS
    	NSLog(@"override OnGetTicket");
#endif

#if PLATFORM_ANDROID
			iTOPLOGD("WebView-OnGetTicket callback %d , retMsg = %s", ticketRet.retCode, ticketRet.retMsg.c_str());

#endif
    }
    
    void OnWebviewAction(IMWebViewStatusResult statuResult) {
#if PLATFORM_IOS
	NSLog(@"in OnWebviewAction :%s", statuResult.toJsonString().c_str());
	if(statuResult.stateCode ==3){
	    IMSDKWebViewManager::getInstance()->callJS("{\"k1\":\"v1\"}");
	}
	NSLog(@"OnWebviewAction done");
#endif

#if PLATFORM_ANDROID
		iTOPLOGD("WebView-OnWebviewAction callback %d , retMsg = %s", statuResult.retCode, statuResult.retMsg.c_str()); 
#endif
        
    }
};
PrintWebViewListener demoWebViewListener;

class PrintNoticeListener : public IMSDKNoticeListener {
    void OnLoadNotice(IMSDKNoticeResult result)
    {
        IMSDKNoticeResult suitableResult = iTOPUtil::filterPic(result);
#if PLATFORM_ANDROID
        iTOPLOGD("IMSDKNoticeResult imsdkRetCode ... %d", suitableResult.imsdkRetCode);
        iTOPLOGD("IMSDKNoticeResult imsdkRetMsg ... %s", suitableResult.imsdkRetMsg.c_str());
        iTOPLOGD("IMSDKNoticeResult thirdRetCode. %d", suitableResult.thirdRetCode);
        iTOPLOGD("IMSDKNoticeResult thirdRetMsg %s", suitableResult.thirdRetMsg.c_str());
        iTOPLOGD("IMSDKNoticeResult retExtraJson %s", suitableResult.retExtraJson.c_str());
        
        for (IMSDKNoticeInfo Finfo : suitableResult.list)
        {
            for (IMSDKNoticePicInfo picInfo : Finfo.pics)
            {
                     iTOPLOGD("PrintNoticeListener picurl = %s", picInfo.picUrl.c_str());
            }
        }
#endif
        
#if PLATFORM_IOS
	LogDebug(FString(result.toJsonString().c_str()));
	NSLog(@ "notice result:%s", result.toJsonString().c_str());
	//===
	IMSDKNoticeResult result2 = iTOPUtil::filterPic(result);
	LogDebug(FString(result2.toJsonString().c_str()));
	NSLog(@ "notice result2:%s", result2.toJsonString().c_str());
#endif

    }
};

PrintNoticeListener demoNoticeListener;

class PrintLocationListener : public IMSDKLocationListener {
    void OnGetLocationInfo(IMSDKLocationInfo &locationInfo) {
#if PLATFORM_IOS
        NSLog(@"Location result country_no:%d", locationInfo.country_no);
        NSLog(@"Location result country_name:%s", locationInfo.country_name.c_str());
        NSLog(@"Location result province_no:%d", locationInfo.province_no);
        NSLog(@"Location result province_name:%s", locationInfo.province_name.c_str());
        NSLog(@"Location result city_no:%d", locationInfo.city_no);
        NSLog(@"Location result city_name:%s", locationInfo.city_name.c_str());
        
        LogDebug(FString("Location result country_no:") + FString::FromInt(locationInfo.country_no));
        LogDebug(FString("Location result country_name:") + FString(locationInfo.country_name.c_str()));
        LogDebug(FString("Location result province_no:") + FString::FromInt(locationInfo.province_no));
        LogDebug(FString("Location result province_name:") + FString(locationInfo.province_name.c_str()));
        LogDebug(FString("Location result city_no:") + FString::FromInt(locationInfo.city_no));
        LogDebug(FString("Location result city_name:") + FString(locationInfo.city_name.c_str()));
#endif
        
#if PLATFORM_ANDROID
        iTOPLOGD("IMSDKLocationInfo imsdkRetCode ... %d", locationInfo.imsdkRetCode);
        iTOPLOGD("IMSDKLocationInfo imsdkRetMsg ... %s", locationInfo.imsdkRetMsg.c_str());
        iTOPLOGD("IMSDKLocationInfo thirdRetCode. %d", locationInfo.thirdRetCode);
        iTOPLOGD("IMSDKLocationInfo thirdRetMsg %s", locationInfo.thirdRetMsg.c_str());
        
              iTOPLOGD("IMSDKLocationInfo city_no. %d", locationInfo.city_no);
              iTOPLOGD("IMSDKLocationInfo province_no. %d", locationInfo.province_no);
              iTOPLOGD("IMSDKLocationInfo country_no. %d", locationInfo.country_no);
           iTOPLOGD("IMSDKLocationInfo province_name %s", locationInfo.province_name.c_str());
        iTOPLOGD("IMSDKLocationInfo city_name %s", locationInfo.city_name.c_str());
           iTOPLOGD("IMSDKLocationInfo country_name %s", locationInfo.country_name.c_str());
        
#endif
    }
};

PrintLocationListener lbsListener;

/************* 以下是接口调用示例 **********/

/* Guest Login */
void UiTOPWidget::handleGuestLoginButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleGuestLoginButtonClick")); 
#if PLATFORM_IOS
	NSLog(@ "= == == = click handleGuestLoginButtonClick");
	NSLog(@ "Current Thread is %@ (%d)", [NSThread currentThread].name, [NSThread currentThread].isMainThread);

	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
		manager->setChannel("Guest");
		manager->login();
	});
#endif

#if PLATFORM_ANDROID
	IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
	manager->init(GJavaVM); //该初始化可只执行一次
	manager->setLoginListener(&iTOPLoginListener);
    manager->setChannel("Twitter");
    manager->login();
#endif

#if PLATFORM_MAC
	// GuestSimulator::getInstance()->setLoginListener(new PrintLoginListener());
	// GuestSimulator* manager = GuestSimulator::getInstance();
	// manager->login();
#endif
}
 
//guangji - FBlogin
void UiTOPWidget::handleFBLoginButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleFBLoginButtonClick"));
#if PLATFORM_IOS
	NSLog(@ "= == == = click handleFBLoginButtonClick");
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
		manager->setChannel("Facebook");//Twitter
		manager->login();
	});
#endif

#if PLATFORM_ANDROID
	IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
	manager->init(GJavaVM); //该初始化可只执行一次
	manager->setLoginListener(&iTOPLoginListener);
	manager->setChannel("Twitter");
    std::vector<std::string> permissions;
//    permissions.push_back("public_profile");
//    permissions.push_back("user_friends");
    manager->login(&permissions, false);
#endif
} 

  void OnReconnect1(IMSDKResult &result) { 
#if PLATFORM_ANDROID
	iTOPLOGD("PrintAuthListener OnAllBind callback  retMsg = %s", result.imsdkRetMsg.c_str());
#endif
}

  //bind facebook
void UiTOPWidget::handleFBBindButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleBindFacebookButtonClick")); 

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
        
		manager->bind("Facebook");
	});
#endif 

#if PLATFORM_ANDROID   
	IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
	manager->init(GJavaVM);
    manager->setLoginListener(&iTOPLoginListener);
    //android fb bind示例代码
    manager->bind("Facebook", "", "{\"permissions\" : [\"user_friends\", \"email\"]}");
    //android wechat bind示例代码
   // manager->bind("WeChat", "", "{\"permissions\" : [\"snsapi_userinfo\", \"snsapi_friend\",\"snsapi_message\"]}");
#endif
} 

void UiTOPWidget::handleGcGpLoginButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleGcGpLoginButtonClick"));
	 
#if PLATFORM_ANDROID 
    IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
    manager->init(GJavaVM); //该初始化可只执行一次
    manager->setLoginListener(&iTOPLoginListener);
    manager->setChannel("Google");
//    std::vector<std::string> permissions;
//    manager->login(&permissions, false);
    manager->quickLogin();
#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handleGcGpLoginButtonClick");

	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
		manager->setChannel("GameCenter");
		manager->login();
	});
#endif
} 

void UiTOPWidget::handleGcGpBindButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleGcGpBindButtonClick"));

#if PLATFORM_IOS
	NSLog(@ "= == == = click handleGcGpBindButtonClick");
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
		manager->bind("GameCenter");
	});
#endif

#if PLATFORM_ANDROID 
    IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
    manager->init(GJavaVM);
    manager->setLoginListener(&iTOPLoginListener);
    manager->bind("Google","","");
#endif
}

void UiTOPWidget::handleGetBindInfoButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleGetBindInfoButtonClick"));
#if PLATFORM_IOS
	NSLog(@ "= == == = click handleGetBindInfoButtonClick"); 
	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->setLoginListener(new PrintLoginListener());
		IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
		manager->getBindInfo();
	});
#endif

#if PLATFORM_ANDROID
	IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
	manager->init(GJavaVM); //该初始化可只执行一次
	manager->setLoginListener(&iTOPLoginListener); 
	manager->getBindInfo();
#endif
}

void UiTOPWidget::handleLogoutButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleLogoutButtonClick"));

#if PLATFORM_ANDROID 
    IMSDKLoginManager* manager = IMSDKLoginManager::getInstance();
    manager->init(GJavaVM); //该初始化可只执行一次
    manager->logout();
#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handleLogoutButtonClick");

	dispatch_async(dispatch_get_main_queue(), ^
	{
		IMSDKLoginManager::getInstance()->logout();
	});
#endif
} 

void UiTOPWidget::handleFBShareButtonClick()
{
	static int index = 1;
	UE_LOG(LogTemp, Warning, TEXT("handleFBShareButtonClick"));
#if PLATFORM_IOS
	NSLog(@ "= == == = click handleFBShareButtonClick");
	NSLog(@ "= == == = is facebook app installed: %d.", IMSDKExtendToolManager::getInstance()->isChannelInstalled("facebook"));

	IMSDKFriendRequestInfo requestInfo = IMSDKFriendRequestInfo();
	requestInfo.type = IMSDKShareImageDialog;
	requestInfo.title = "FBshare";
	requestInfo.content = "facebook deeplink";
	requestInfo.link = "https://www.qq.com";
	if (index %2 == 0) {
		requestInfo.image_path = "https://ossweb-img.qq.com/images/game/ieg/web201404/logo.png";
	} else {
		NSString *nsImagePath = [NSString  stringWithFormat:@"%@/Saved/TestImage.png", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
		requestInfo.image_path = [nsImagePath UTF8String];
	}
	index++;
	IMSDKFriendManager* manager = IMSDKFriendManager::getInstance();
	manager->setChannel("Facebook");
	manager->setFriendListener(new PrintFriendListener());
	dispatch_async(dispatch_get_main_queue(), ^
	{
		manager->share(requestInfo);
	});
#endif

#if PLATFORM_ANDROID
//    IMSDKFriendRequestInfo requestInfo;
//    requestInfo.title = "FBshare";
//    requestInfo.content = "facebook deeplink";
//    requestInfo.link = "https://www.qq.com";
//    requestInfo.extra_json =  "{\"invitetype\":\"batch\",\"userlist\":[\"1559763867446298\",]}";
//    IMSDKFriendManager* manager = IMSDKFriendManager::getInstance();
//    manager->init(GJavaVM);
//    manager->setChannel("Facebook");
//    manager->setFriendListener(&iTOPFriendListener);
//    manager->invite(requestInfo);
    
    //getfriendlist接口
//    IMSDKFriendManager *manager = IMSDKFriendManager::getInstance();
//    manager->init(GJavaVM);
//    manager->setChannel("Facebook");
//    manager->setFriendListener(&iTOPFriendListener);
//    manager->getFriends(1, 10, 0, "");
    
    //sendmessage和invite接口
    IMSDKFriendManager *manager = IMSDKFriendManager::getInstance();
    manager->init(GJavaVM);
    manager->setChannel("Facebook");
    manager->setFriendListener(&iTOPFriendListener);
     
    IMSDKFriendRequestInfo requestInfo = IMSDKFriendRequestInfo();
    requestInfo.type = IMSDKShareImageDialog;
    requestInfo.title = "FBshare";
    requestInfo.content = "facebook deeplink";
    requestInfo.link = "https://www.qq.com";
     manager->sendMessage(requestInfo);
//    manager->invite(requestInfo);
#endif
}  

void UiTOPWidget::handleTWShareButtonClick()
{
	static int index = 1;
	UE_LOG(LogTemp, Warning, TEXT("handleTWShareButtonClick"));
#if PLATFORM_IOS
	NSLog(@ "= == == = click handleTWShareButtonClick");

	IMSDKFriendRequestInfo requestInfo = IMSDKFriendRequestInfo();
	requestInfo.type = IMSDKShareImageDialog;
	requestInfo.title = "TWshare";
	requestInfo.content = "twitter content";
	requestInfo.link = "https://www.qq.com";
	if (index %2 == 0) {
		requestInfo.image_path = "https://ossweb-img.qq.com/images/game/ieg/web201404/logo.png";
	} else {
		NSString *nsImagePath = [NSString  stringWithFormat:@"%@/Saved/TestImage.png", [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
		requestInfo.image_path = [nsImagePath UTF8String];
	}
	index++;
	IMSDKFriendManager* manager = IMSDKFriendManager::getInstance();
	manager->setChannel("Twitter");
	manager->setFriendListener(new PrintFriendListener());
	dispatch_async(dispatch_get_main_queue(), ^
	{
		manager->share(requestInfo);
	});
#endif

#if PLATFORM_ANDROID
    IMSDKFriendRequestInfo requestInfo;
    
    requestInfo.title = "FBshare";
    requestInfo.content = "facebook deeplink";
    requestInfo.link = "https://www.qq.com";
    requestInfo.extra_json = {};
    
    IMSDKFriendManager* manager = IMSDKFriendManager::getInstance();
    manager->init(GJavaVM);
    manager->setChannel("Facebook");
    manager->setFriendListener(&iTOPFriendListener);
    manager->invite(requestInfo);
#endif
}  


void UiTOPWidget::handleLoadNoticeButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("openURL"));
#if PLATFORM_ANDROID
    
//    webview代码
//    IMSDKWebViewManager *manager = IMSDKWebViewManager::getInstance();
//    manager->init(GJavaVM);
//    manager->setChannel("QQ");
//    manager->setListener(&demoWebViewListener);
//    manager->openURL("http://www.facebook.com/", true, false, true);
    
    //notice代码
//    IMSDKNoticeManager *manager = IMSDKNoticeManager::getInstance();
//    manager->init(GJavaVM);
//    manager->setChannel("IMSDK");
//    manager->setListener(&demoNoticeListener);
//    manager->loadNoticeData("1.0.0","en-US", 1, 0, 0,1,"");
    
       //lbs代码
     IMSDKLocationManager *manager = IMSDKLocationManager::getInstance();
     manager->setListener(&lbsListener);
     manager->getLocationInfo();
#endif

#if PLATFORM_IOS
	// //webview
	// NSLog(@ "==== openURL");
	
 //            dispatch_async(dispatch_get_main_queue(), ^
	// {
	// 	IMSDKWebViewManager::getInstance()->setChannel("IMSDK");//初始化必须放在主线程，否则会crash
	//     	if (!IMSDKWebViewManager::getInstance()->getListener()) {
	//         		PrintWebViewListener *webListener = new PrintWebViewListener();
	//         		IMSDKWebViewManager::getInstance()->setListener(webListener);
	//     	}
	//     	NSLog(@ "==== openURL2");
	//     	IMSDKWebViewManager *manager = IMSDKWebViewManager::getInstance();
	// 	manager->openURL("http://www.facebook.com/", true,false,true);//设置全屏
	// }); 

//    //notice
//    dispatch_async(dispatch_get_main_queue(), ^{
//        IMSDKNoticeManager *manager = IMSDKNoticeManager::getInstance();
//        manager->setChannel("IMSDK");
//        manager->setListener(&demoNoticeListener);
//        manager->loadNoticeData("1.0.0","en-US", 1, 0, 0,1,"");
//    });

    //location
    dispatch_async(dispatch_get_main_queue(), ^{
        PrintLocationListener *listener = new PrintLocationListener();
        IMSDKLocationManager::getInstance()->setListener(listener);
        IMSDKLocationManager::getInstance()->getLocationInfo();
    });
#endif
} 

void UiTOPWidget::handlePushRegisterButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handlePushRegisterButtonClick"));
#if PLATFORM_ANDROID
	IMSDKPushManager* manager = IMSDKPushManager::getInstance();
	manager->init(GJavaVM);
	PrintPushListener *pushListener = new PrintPushListener();
	manager->setPushListener(pushListener);
	manager->setChannel("XG");
	manager->registerPush("iMSDK123456789");
#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handlePushRegisterButtonClick");
	IMSDKPushManager	* manager = IMSDKPushManager::getInstance();
	manager->setPushListener(&iTOPPushListener);
	manager->setChannel("XG");
	dispatch_async(dispatch_get_main_queue(), ^
	{
		manager->registerPush("ue4jacky");
	});

#endif
}

 
void UiTOPWidget::handlePushUnregisterButtonClick()
{ 

	UE_LOG(LogTemp, Warning, TEXT("handlePushUnregisterButtonClick"));
#if PLATFORM_ANDROID
	 
    IMSDKPushManager* manager = IMSDKPushManager::getInstance();
	manager->init(GJavaVM);
	PrintPushListener    *pushListener = new PrintPushListener();
	manager->setPushListener(pushListener);
	manager->setChannel("XG");
	manager->unregisterPush(); 
	 

#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handlePushUnregisterButtonClick");
	IMSDKPushManager	* manager = IMSDKPushManager::getInstance();
	manager->setPushListener(&iTOPPushListener);
	dispatch_async(dispatch_get_main_queue(), ^
	{
		manager->unregisterPush();
	});
#endif
}
 
 
void UiTOPWidget::handleStatReportButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("handleStatReportButtonClick"));
#if PLATFORM_ANDROID
    // adjust Deeplink test
    IMSDKAdjustManager* manager = IMSDKAdjustManager::getInstance(); 
    manager->addDeferredDeepLink("https://www.baidu.com");
    manager->addStandardDeepLink("https://www.qq.com");
    
    std::string link = "";
    do {
        link = manager->pollStandardDeepLink();
        iTOPLOGD("get StandardDeepLink = %s", link.c_str());
    }while (link.length() > 0);
    
    do {
        link = manager->pollDeferredDeepLink();
        iTOPLOGD("get DeferredDeepLink = %s", link.c_str());
    }while (link.length() > 0);
    
    
    
    //stat test
//    IMSDKStatManager* manager = IMSDKStatManager::getInstance();
//    manager->init(GJavaVM);
//    std::map<std::string, std::string> params;
//    params.insert(std::make_pair("test1key", "test1value"));
//    params.insert(std::make_pair("test2key", "test2value"));
//    manager->reportEvent("99zml2", "我是body from UE4 android", 1);
//    // firebase, Event Name must start with a letter
//    manager->reportEvent("testFB", params, true);

#endif

#if PLATFORM_IOS
	NSLog(@ "= == == = click handleStatReportButtonClick");
	std::vector<std::string> eventChannel;
	eventChannel.push_back("Adjust");
	eventChannel.push_back("Beacon");
	eventChannel.push_back("Firebase");

	/* crash report */
	std::vector<std::string> crashChannel;
	crashChannel.push_back("Bugly");

	IMSDKStatChannelInterface myInterFace;
	myInterFace.eventReportChannels = eventChannel;
	myInterFace.trackEventChannels = eventChannel;
	myInterFace.crashReportChannels = crashChannel;
	myInterFace.testSpeedChannels = eventChannel;

	IMSDKStatManager::getInstance()->setChannelInterface(myInterFace);
	IMSDKStatManager::getInstance()->clearFilter();
	IMSDKStatManager::getInstance()->reportCrash(true);

	dispatch_async(dispatch_get_main_queue(), ^
	{
		 IMSDKStatManager::getInstance()->reportEvent("IMSDK_Event", "我是body from UE4-Adjust4.12.1", true);
		 IMSDKStatManager::getInstance()->reportEvent("27b0zz", "IMSDK_Event 4 Adjust from UE4-Adjust4.12.1", true);

		 //Firebase
		 NSLog(@ "==== Firebase");
		 std::map<std::string, std::string> params;
		 params["fb_test"] = "9";
		 params["fb_score"] = "100";
		 IMSDKStatManager::getInstance()->reportEvent("level_achieved_ue4", params);
	});	
#endif
} 

void OnGameServiceResult(IMSDKResult &result) {

#if PLATFORM_ANDROID
	iTOPLOGD("OnGameServiceResult code =  %d", result.imsdkRetCode );
	iTOPLOGD("OnGameServiceResult msg =  %s", result.imsdkRetMsg.c_str());
#endif 
}

 

