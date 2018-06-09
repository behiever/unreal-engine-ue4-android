
#include "../iTOP/Public/IMSDKJson.h"    
std::string convertFstring2string(FString str) {
	std::string msg(TCHAR_TO_UTF8(*str));
	return msg;
}

template <typename StructType>
void  GetStructFromJsonString(FString content, StructType& StructOutput) {
	StructType StructData;
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(content, &StructOutput, 0, 0);
}

IMSDKResult convertiTOPResult(std::string _jsonData) {
	IMSDKLoginResult iTOPResult; 
	FString fResult(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPResult iTOPResultStruct;
	GetStructFromJsonString<FiTOPResult>(fResult, iTOPResultStruct);
	iTOPResult.imsdkRetCode = iTOPResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPResultStruct.imsdkRetMsg));
	iTOPResult.imsdkRetMsg = imsdkRetMsg;

	iTOPResult.thirdRetCode = iTOPResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPResultStruct.thirdRetMsg));
	iTOPResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPResultStruct.retExtraJson));
	iTOPResult.retExtraJson = retExtraJson;
 
	return iTOPResult; 
} 
 

IMSDKLoginResult convertiTOPBaseLoginResult(std::string _jsonData) {
	IMSDKLoginResult loginResult;
	FString fResult(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPLoginResult iTOPLoginResultStruct;
	GetStructFromJsonString<FiTOPLoginResult>(fResult, iTOPLoginResultStruct);
	loginResult.imsdkRetCode = iTOPLoginResultStruct.imsdkRetCode;
	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPLoginResultStruct.imsdkRetMsg));
	loginResult.imsdkRetMsg = imsdkRetMsg;

	loginResult.thirdRetCode = iTOPLoginResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPLoginResultStruct.thirdRetMsg));
	loginResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPLoginResultStruct.retExtraJson));
	loginResult.retExtraJson = retExtraJson;

	std::string channel(TCHAR_TO_UTF8(*iTOPLoginResultStruct.channel));
	loginResult.channel = channel;

	loginResult.guid_channel_id = iTOPLoginResultStruct.channelId;

	std::string channelToken(TCHAR_TO_UTF8(*iTOPLoginResultStruct.channelToken));
	loginResult.channel_token = channelToken;

	loginResult.channel_expire = iTOPLoginResultStruct.channelTokenExpire;

	std::string channelUserId(TCHAR_TO_UTF8(*iTOPLoginResultStruct.channelUserId));
	loginResult.channel_userid = channelUserId;

	loginResult.guid_game_id = iTOPLoginResultStruct.gameId;

	std::string guid(TCHAR_TO_UTF8(*iTOPLoginResultStruct.guid));
	loginResult.guid = guid;

	std::string guidUserBirthday(TCHAR_TO_UTF8(*iTOPLoginResultStruct.guidUserBirthday));
	loginResult.guid_user_birthday = guidUserBirthday;

	std::string guidUserNick(TCHAR_TO_UTF8(*iTOPLoginResultStruct.guidUserNick));
	loginResult.guid_user_nick = guidUserNick;

	std::string guidUserPortrait(TCHAR_TO_UTF8(*iTOPLoginResultStruct.guidUserPortrait));
	loginResult.guid_user_portrait = guidUserBirthday;

	loginResult.guid_user_gender = iTOPLoginResultStruct.guidUserSex;

	std::string innerToken(TCHAR_TO_UTF8(*iTOPLoginResultStruct.innerToken));
	loginResult.guid_token = innerToken;

	loginResult.guid_token_expire = iTOPLoginResultStruct.innerTokenExpire;

	std::string openId(TCHAR_TO_UTF8(*iTOPLoginResultStruct.openId));
	loginResult.guid_open_id = openId; 
 
	return loginResult;
}

IMSDKLoginResult convertiTOPBindResult(std::string _jsonData) { 
	IMSDKLoginResult loginResult = convertiTOPBaseLoginResult(_jsonData);
	loginResult.method_tag = "bind";
	return loginResult;
}

IMSDKLoginResult convertiTOPLoginResult(std::string _jsonData) {
	IMSDKLoginResult loginResult = convertiTOPBaseLoginResult(_jsonData);
	loginResult.method_tag = "login";
	return loginResult;
}

IMSDKLoginResult convertiTOPQuickLoginResult(std::string _jsonData) {
    IMSDKLoginResult loginResult = convertiTOPBaseLoginResult(_jsonData);
    loginResult.method_tag = "quicklogin";
    return loginResult;
}


std::vector<IMSDKNoticePicInfo> convertiTOPNoticePicInfoList(TArray<FiTOPNoticePicInfo> picList) {
	std::vector<IMSDKNoticePicInfo> iTOPNoticeInfoPicList;

	for (FiTOPNoticePicInfo Finfo : picList)
	{
		IMSDKNoticePicInfo iTOPNoticeInfo;

		iTOPNoticeInfo.noticeId = Finfo.noticeId;

		iTOPNoticeInfo.picUrl = convertFstring2string(Finfo.picUrl);

		iTOPNoticeInfo.screenDir = Finfo.screenDir;

		iTOPNoticeInfo.mPicHash = convertFstring2string(Finfo.picHash);

		iTOPNoticeInfo.picTitle = convertFstring2string(Finfo.picTitle);

		iTOPNoticeInfo.picSize = convertFstring2string(Finfo.picSize);

		iTOPNoticeInfo.extraJson = convertFstring2string(Finfo.extraJson);

		iTOPNoticeInfoPicList.push_back(iTOPNoticeInfo);
	}

	return iTOPNoticeInfoPicList;
}

std::vector<IMSDKNoticeInfo> convertiTOPNoticeInfoList(TArray<FiTOPNoticeInfo> noticelist) {

	std::vector<IMSDKNoticeInfo> iTOPNoticeInfoList;

	for (FiTOPNoticeInfo Finfo : noticelist)
	{
		IMSDKNoticeInfo iTOPNoticeInfo;
		std::string stateCode(TCHAR_TO_UTF8(*Finfo.stateCode));
		iTOPNoticeInfo.stateCode = stateCode;

		iTOPNoticeInfo.noticeId = Finfo.noticeId;

		std::string appId(TCHAR_TO_UTF8(*Finfo.appId));
		iTOPNoticeInfo.appId = appId;

		std::string openId(TCHAR_TO_UTF8(*Finfo.openId));
		iTOPNoticeInfo.openId = openId;

		std::string noticeUrl(TCHAR_TO_UTF8(*Finfo.noticeUrl));
		iTOPNoticeInfo.url = noticeUrl;

		iTOPNoticeInfo.scene = Finfo.noticeScene;

		iTOPNoticeInfo.startTime = Finfo.noticeStartTime;

		iTOPNoticeInfo.endTime = Finfo.noticeEndTime;

		iTOPNoticeInfo.updateTime = Finfo.noticeUpdateTime;

		iTOPNoticeInfo.screenName = convertFstring2string(Finfo.screenName);

		iTOPNoticeInfo.language = convertFstring2string(Finfo.noticeLanguage);

		iTOPNoticeInfo.contentType = Finfo.noticeContentType;

		iTOPNoticeInfo.title = convertFstring2string(Finfo.noticeTitle);

		iTOPNoticeInfo.content = convertFstring2string(Finfo.noticeContent);

		iTOPNoticeInfo.contentWebUrl = convertFstring2string(Finfo.noticeContentWebUrl);

		iTOPNoticeInfo.extraJson = convertFstring2string(Finfo.extraJson);

		iTOPNoticeInfo.pics = convertiTOPNoticePicInfoList(Finfo.noticePics);
		iTOPNoticeInfoList.push_back(iTOPNoticeInfo);
	}
	return iTOPNoticeInfoList;
}

IMSDKNoticeResult convertiTOPNoticeResult(std::string _jsonData) {
	IMSDKNoticeResult iTOPNoticeResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPNoticeResult iTOPNoticeResultStruct;
	GetStructFromJsonString<FiTOPNoticeResult>(fResult, iTOPNoticeResultStruct);
	iTOPNoticeResult.imsdkRetCode = iTOPNoticeResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPNoticeResultStruct.imsdkRetMsg));
	iTOPNoticeResult.imsdkRetMsg = imsdkRetMsg;

	iTOPNoticeResult.thirdRetCode = iTOPNoticeResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPNoticeResultStruct.thirdRetMsg));
	iTOPNoticeResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPNoticeResultStruct.retExtraJson));
	iTOPNoticeResult.retExtraJson = retExtraJson;

	iTOPNoticeResult.number = iTOPNoticeResultStruct.noticesNum;

	iTOPNoticeResult.list = convertiTOPNoticeInfoList(iTOPNoticeResultStruct.noticesList);

	return iTOPNoticeResult;
}


std::vector<IMSDKAuthSNSInfo> convertiTOPSnsInfoList(TArray<FiTOPAuthSNSInfo> snsInfoList) {

	std::vector<IMSDKAuthSNSInfo> iTOPAuthSnsInfoList;

	for (FiTOPAuthSNSInfo Finfo : snsInfoList)
	{
		IMSDKAuthSNSInfo iTOPAuthSnsInfo;

		iTOPAuthSnsInfo.channelId = Finfo.channelId;

		iTOPAuthSnsInfo.openId = convertFstring2string(Finfo.openId);

		iTOPAuthSnsInfo.userName = convertFstring2string(Finfo.userName);

		iTOPAuthSnsInfo.gender = Finfo.gender;

		iTOPAuthSnsInfo.pictureUrl = convertFstring2string(Finfo.pictureUrl);

		iTOPAuthSnsInfoList.push_back(iTOPAuthSnsInfo);
	}
	return iTOPAuthSnsInfoList;
}

IMSDKAuthResult convertiTOPAuthResult(std::string _jsonData) {
	IMSDKAuthResult iTOPAuthResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPAuthResult iTOPAuthResultStruct;
	GetStructFromJsonString<FiTOPAuthResult>(fResult, iTOPAuthResultStruct);
	iTOPAuthResult.imsdkRetCode = iTOPAuthResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.imsdkRetMsg));
	iTOPAuthResult.imsdkRetMsg = imsdkRetMsg;

	iTOPAuthResult.thirdRetCode = iTOPAuthResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.thirdRetMsg));
	iTOPAuthResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPAuthResultStruct.retExtraJson));
	iTOPAuthResult.retExtraJson = retExtraJson;

	iTOPAuthResult.channelId = iTOPAuthResultStruct.channelId;

	iTOPAuthResult.gameId = iTOPAuthResultStruct.gameId;

	std::string deviceId(TCHAR_TO_UTF8(*iTOPAuthResultStruct.deviceId));
	iTOPAuthResult.deviceId = deviceId;

	std::string innerToken(TCHAR_TO_UTF8(*iTOPAuthResultStruct.innerToken));
	iTOPAuthResult.innerToken = innerToken;

	iTOPAuthResult.isFirstLogin = iTOPAuthResultStruct.isFirstLogin;

	std::string openId(TCHAR_TO_UTF8(*iTOPAuthResultStruct.openId));
	iTOPAuthResult.openId = openId;

	iTOPAuthResult.tokenExpireTime = iTOPAuthResultStruct.tokenExpireTime;
	iTOPAuthResult.snsInfoVec = convertiTOPSnsInfoList(iTOPAuthResultStruct.snsInfoList);
	return iTOPAuthResult;
}

IMSDKAuthMigrateResult convertiTOPAuthMigrateResult(std::string _jsonData) {
	IMSDKAuthMigrateResult iTOPAuthResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPAuthMigrateResult iTOPAuthResultStruct;
	GetStructFromJsonString<FiTOPAuthMigrateResult>(fResult, iTOPAuthResultStruct);
	iTOPAuthResult.imsdkRetCode = iTOPAuthResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.imsdkRetMsg));
	iTOPAuthResult.imsdkRetMsg = imsdkRetMsg;

	iTOPAuthResult.thirdRetCode = iTOPAuthResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.thirdRetMsg));
	iTOPAuthResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPAuthResultStruct.retExtraJson));
	iTOPAuthResult.retExtraJson = retExtraJson;


	std::string migrateCode(TCHAR_TO_UTF8(*iTOPAuthResultStruct.migrateCode));
	iTOPAuthResult.migrateCode = migrateCode;


	iTOPAuthResult.validTime = iTOPAuthResultStruct.validTime;
	iTOPAuthResult.snsInfoVec = convertiTOPSnsInfoList(iTOPAuthResultStruct.snsInfoList);

	return iTOPAuthResult;
}


IMSDKAuthConnectResult convertiTOPAuthConnectResult(std::string _jsonData) {
	IMSDKAuthConnectResult iTOPAuthResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPAuthConnectResult iTOPAuthResultStruct;
	GetStructFromJsonString<FiTOPAuthConnectResult>(fResult, iTOPAuthResultStruct);
	iTOPAuthResult.imsdkRetCode = iTOPAuthResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.imsdkRetMsg));
	iTOPAuthResult.imsdkRetMsg = imsdkRetMsg;

	iTOPAuthResult.thirdRetCode = iTOPAuthResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPAuthResultStruct.thirdRetMsg));
	iTOPAuthResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPAuthResultStruct.retExtraJson));
	iTOPAuthResult.retExtraJson = retExtraJson;

	std::string confirmCode(TCHAR_TO_UTF8(*iTOPAuthResultStruct.confirmCode));
	iTOPAuthResult.confirmCode = confirmCode;

	std::string openId(TCHAR_TO_UTF8(*iTOPAuthResultStruct.openId));
	iTOPAuthResult.openId = openId;

	std::string userName(TCHAR_TO_UTF8(*iTOPAuthResultStruct.userName));
	iTOPAuthResult.userName = userName;

	iTOPAuthResult.channelId = iTOPAuthResultStruct.channelId;

	iTOPAuthResult.gender = iTOPAuthResultStruct.gender;

	std::string pictureUrl(TCHAR_TO_UTF8(*iTOPAuthResultStruct.pictureUrl));
	iTOPAuthResult.pictureUrl = pictureUrl;

	return iTOPAuthResult;
}


IMWebViewStatusResult convertiTOPWebViewStatusResult(std::string _jsonData) {
	IMWebViewStatusResult iTOPWebViewStatusResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPWebViewStatusResult iTOPWebViewStatusResultStruct;
	GetStructFromJsonString<FiTOPWebViewStatusResult>(fResult, iTOPWebViewStatusResultStruct);
	iTOPWebViewStatusResult.imsdkRetCode = iTOPWebViewStatusResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPWebViewStatusResultStruct.imsdkRetMsg));
	iTOPWebViewStatusResult.imsdkRetMsg = imsdkRetMsg;

	iTOPWebViewStatusResult.thirdRetCode = iTOPWebViewStatusResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPWebViewStatusResultStruct.thirdRetMsg));
	iTOPWebViewStatusResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPWebViewStatusResultStruct.retExtraJson));
	iTOPWebViewStatusResult.retExtraJson = retExtraJson;

	iTOPWebViewStatusResult.stateCode = iTOPWebViewStatusResultStruct.stateCode;

	return iTOPWebViewStatusResult;
} 

IMSDKWebViewTicketResult convertiTOPWebViewTicketResult(std::string _jsonData) {
	IMSDKWebViewTicketResult iTOPWebViewTicketResult;
	FString fResult = FString(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPWebViewTicketResult iTOPWebViewTicketResultStruct;
	GetStructFromJsonString<FiTOPWebViewTicketResult>(fResult, iTOPWebViewTicketResultStruct);
	iTOPWebViewTicketResult.imsdkRetCode = iTOPWebViewTicketResultStruct.imsdkRetCode;

	std::string imsdkRetMsg(TCHAR_TO_UTF8(*iTOPWebViewTicketResultStruct.imsdkRetMsg));
	iTOPWebViewTicketResult.imsdkRetMsg = imsdkRetMsg;

	iTOPWebViewTicketResult.thirdRetCode = iTOPWebViewTicketResultStruct.thirdRetCode;

	std::string thirdRetMsg(TCHAR_TO_UTF8(*iTOPWebViewTicketResultStruct.thirdRetMsg));
	iTOPWebViewTicketResult.thirdRetMsg = thirdRetMsg;

	std::string retExtraJson(TCHAR_TO_UTF8(*iTOPWebViewTicketResultStruct.retExtraJson));
	iTOPWebViewTicketResult.retExtraJson = retExtraJson;

	std::string ticket(TCHAR_TO_UTF8(*iTOPWebViewTicketResultStruct.ticket));
	iTOPWebViewTicketResult.ticket = ticket;
	 
	std::string domain(TCHAR_TO_UTF8(*iTOPWebViewTicketResultStruct.domain));
	iTOPWebViewTicketResult.domain = domain;

	return iTOPWebViewTicketResult;
}  



std::vector<IMSDKChannelInfo> convertiTOPBindInfoList(TArray<FiTOPChannelInfo> bindInfoList) {

	std::vector<IMSDKChannelInfo> iTOPChannelInfoList;

	for (FiTOPChannelInfo Finfo : bindInfoList)
	{
		IMSDKChannelInfo iTOPChannelInfo;

		iTOPChannelInfo.channel_id = Finfo.channelId;

		iTOPChannelInfo.portrait = convertFstring2string(Finfo.pictureUrl);

		iTOPChannelInfo.nick = convertFstring2string(Finfo.userName);

		iTOPChannelInfo.gender = Finfo.gender; 

		iTOPChannelInfoList.push_back(iTOPChannelInfo);
	}
	return iTOPChannelInfoList;
}  

IMSDKBindInfo convertiTOPGetBindResult(std::string _jsonData) {
	IMSDKBindInfo bindInfoResult;
	FString fResult(UTF8_TO_TCHAR(_jsonData.c_str()));
	FiTOPBindResult iTOPbindInfoResultStruct;
	GetStructFromJsonString<FiTOPBindResult>(fResult, iTOPbindInfoResultStruct);
	bindInfoResult.login_info = convertiTOPLoginResult(_jsonData);
	bindInfoResult.channel_info = convertiTOPBindInfoList(iTOPbindInfoResultStruct.bindInfoList);
	return bindInfoResult;
}
std::vector<IMSDKFriendInfo> convertiTOPFriendInfoList(TArray<FiTOPFriendInfo> friendInfoList){
    std::vector<IMSDKFriendInfo> iTOPFriendInfoList;
    for(FiTOPFriendInfo fInfo : friendInfoList){
        IMSDKFriendInfo iTopFriendInfo;
		std::string openId(TCHAR_TO_UTF8(*fInfo.openId));
        iTopFriendInfo.guid_open_id = openId;
		std::string channelUserId(TCHAR_TO_UTF8(*fInfo.channelUserId));
        iTopFriendInfo.channel_userid = channelUserId;
		std::string userName(TCHAR_TO_UTF8(*fInfo.userName));
        iTopFriendInfo.guid_user_nick = userName;
		std::string pictureUrl(TCHAR_TO_UTF8(*fInfo.pictureUrl));
        iTopFriendInfo.guid_user_portrait = pictureUrl;
        iTopFriendInfo.guid_user_gender = fInfo.gender;
        iTOPFriendInfoList.push_back(iTopFriendInfo);
    }
    return iTOPFriendInfoList;
}

IMSDKFriendResult convertFriendResultFromJson(std::string json){
    IMSDKFriendResult result;
    FString fr = FString(UTF8_TO_TCHAR(json.c_str()));
    FiTOPFriendResult friendResultStruct;
    GetStructFromJsonString<FiTOPFriendResult>(fr, friendResultStruct);
    
    result.imsdkRetCode = friendResultStruct.imsdkRetCode;
    
    std::string imsdkRetMsg(TCHAR_TO_UTF8(*friendResultStruct.imsdkRetMsg));
    result.imsdkRetMsg = imsdkRetMsg;
    
    result.thirdRetCode = friendResultStruct.thirdRetCode;
    
    std::string thirdRetMsg(TCHAR_TO_UTF8(*friendResultStruct.thirdRetMsg));
    result.thirdRetMsg = thirdRetMsg;
    
    std::string retExtraJson(TCHAR_TO_UTF8(*friendResultStruct.retExtraJson));
    result.retExtraJson = retExtraJson;
	
    result.friends = convertiTOPFriendInfoList(friendResultStruct.sameGameFriendList);
	iTOPLOGD("Friend FiTOPFriendResult %s", retExtraJson.c_str());
	return result;
}

IMSDKLocationInfo convertiTOPLbsResult(std::string json){
    IMSDKLocationInfo result;
    FString locationInfo = FString(UTF8_TO_TCHAR(json.c_str()));
    FiTOPLbsResult lbsStruct;
    GetStructFromJsonString<FiTOPLbsResult>(locationInfo, lbsStruct);
    
    result.imsdkRetCode = lbsStruct.imsdkRetCode;
    std::string imsdkRetMsg(TCHAR_TO_UTF8(*lbsStruct.imsdkRetMsg));
    result.imsdkRetMsg = imsdkRetMsg;
    result.thirdRetCode = lbsStruct.thirdRetCode;
    std::string thirdRetMsg(TCHAR_TO_UTF8(*lbsStruct.thirdRetMsg));
    result.thirdRetMsg = thirdRetMsg;

    result.city_no =lbsStruct.cityNumber;
    std::string cityName(TCHAR_TO_UTF8(*lbsStruct.cityName));
    result.city_name = cityName;
    
    result.province_no=lbsStruct.provinceNumber;
    std::string provinceName(TCHAR_TO_UTF8(*lbsStruct.provinceName));
    result.province_name = provinceName;
    
    result.country_no=lbsStruct.countryNumber;
    std::string countryName(TCHAR_TO_UTF8(*lbsStruct.countryName));
    result.country_name = countryName;
    
    return result;
}
