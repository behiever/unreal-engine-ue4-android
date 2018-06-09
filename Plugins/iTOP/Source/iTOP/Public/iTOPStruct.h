//// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "IMSDKDefine.h"
#include "IMSDKComm.h"
#include "CoreMinimal.h"  
#include "iTOPStruct.generated.h" 
  
USTRUCT()
struct FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() int imsdkRetCode;
	UPROPERTY() FString imsdkRetMsg;
	UPROPERTY() int thirdRetCode;
	UPROPERTY() FString thirdRetMsg;
	UPROPERTY() FString retExtraJson; 
};  


USTRUCT()
struct FiTOPWebViewTicketResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() FString ticket;
	UPROPERTY() FString domain;
};

USTRUCT()
struct FiTOPWebViewStatusResult : public FiTOPResult {
	GENERATED_BODY()
public: 
	UPROPERTY() int stateCode; 
};


USTRUCT()
struct FiTOPAuthSNSInfo {
	GENERATED_BODY()
public:
	UPROPERTY() FString openId;
	UPROPERTY() int channelId;
	UPROPERTY() FString userName;
	UPROPERTY() int gender;
	UPROPERTY() FString pictureUrl;
};

USTRUCT()
struct FiTOPAuthConnectResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() FString confirmCode;
	UPROPERTY() int channelId;
	UPROPERTY() FString openId;
	UPROPERTY() int gender;
	UPROPERTY() FString userName;
	UPROPERTY() FString pictureUrl;
};


USTRUCT()
struct FiTOPAuthResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() FString channel;
	UPROPERTY() int channelId;
	UPROPERTY() FString deviceId;
	UPROPERTY() int gameId;
	UPROPERTY() FString innerToken;
	UPROPERTY() int isFirstLogin;
	UPROPERTY() FString openId;
	UPROPERTY() int tokenExpireTime;   
	UPROPERTY() TArray<FiTOPAuthSNSInfo> snsInfoList;
};  

USTRUCT()
struct FiTOPLbsResult : public FiTOPResult {
    GENERATED_BODY()
public:
    UPROPERTY() int channelId;
    UPROPERTY() FString cityName;
    UPROPERTY() int cityNumber;
    UPROPERTY() FString countryName;
    UPROPERTY() int countryNumber;
    UPROPERTY() int gameId;
    UPROPERTY() FString guid;
    UPROPERTY() FString guidToken;
    UPROPERTY() int guidTokenExpire;
    UPROPERTY() FString guidUserBirthday;
    UPROPERTY() FString guidUserNick;
    UPROPERTY() FString guidUserPortrait;
    UPROPERTY() int guidUserSex;
    UPROPERTY() FString provinceName;
    UPROPERTY() FString openId;
    UPROPERTY() int provinceNumber;
};

USTRUCT()
struct FiTOPAuthMigrateResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() FString migrateCode;
	UPROPERTY() int validTime; 
	UPROPERTY() TArray<FiTOPAuthSNSInfo> snsInfoList;
};
 
USTRUCT()
struct FiTOPLoginResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() FString channel;
	UPROPERTY() int channelId; 
	UPROPERTY() FString channelToken;
	UPROPERTY() int channelTokenExpire;
	UPROPERTY() FString channelUserId;
	UPROPERTY() int gameId;
	UPROPERTY() FString guid;
	UPROPERTY() FString guidUserBirthday;
	UPROPERTY() FString guidUserNick;
	UPROPERTY() FString guidUserPortrait;
	UPROPERTY() int guidUserSex;
	UPROPERTY() int innerTokenExpire;
	UPROPERTY() int isFirstLogin;
	UPROPERTY() FString innerToken;
	UPROPERTY() FString openId;
}; 

USTRUCT()
struct FiTOPNoticePicInfo {
	GENERATED_BODY()
public:
	UPROPERTY() int noticeId;
	UPROPERTY() int screenDir;
	UPROPERTY() FString picUrl;
	UPROPERTY() FString picHash;
	UPROPERTY() FString picTitle;
	UPROPERTY() FString picSize;
	UPROPERTY() FString extraJson;
};


USTRUCT()
struct FiTOPNoticeInfo {
	GENERATED_BODY()
public:
	UPROPERTY() FString stateCode;
	UPROPERTY() int noticeId;
	UPROPERTY() FString appId;
	UPROPERTY() FString openId;
	UPROPERTY() FString noticeUrl;
	UPROPERTY() int noticeScene;

	UPROPERTY() int noticeUpdateTime;
	UPROPERTY() int noticeEndTime;
	UPROPERTY() int noticeStartTime;

	UPROPERTY() FString screenName;
	UPROPERTY() FString noticeLanguage;

	UPROPERTY() int noticeContentType;
	UPROPERTY() FString noticeTitle;
	UPROPERTY() FString noticeContent;

	UPROPERTY() TArray<FiTOPNoticePicInfo> noticePics;

	UPROPERTY() FString noticeContentWebUrl;
	UPROPERTY() FString extraJson;
};

USTRUCT()
struct FiTOPNoticeResult : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() TArray<FiTOPNoticeInfo> noticesList;
	UPROPERTY() int noticesNum;
};
 

USTRUCT()
struct FiTOPChannelInfo : public FiTOPResult {
	GENERATED_BODY()
public:
	UPROPERTY() int channelId;
	UPROPERTY() int gender;
	UPROPERTY() FString pictureUrl;
	UPROPERTY() FString userName;
};

USTRUCT()
struct FiTOPBindResult : public FiTOPLoginResult {
	GENERATED_BODY()
public: 
	UPROPERTY() TArray<FiTOPChannelInfo> bindInfoList;
};

USTRUCT()
struct FiTOPFriendInfo {
    GENERATED_BODY()
public:
    UPROPERTY() FString openId;
    UPROPERTY() FString channelUserId;
    UPROPERTY() FString channelId;
    UPROPERTY() FString userName;
    UPROPERTY() int gender;
    UPROPERTY() FString pictureUrl;
    UPROPERTY() FString email;
    UPROPERTY() FString phone;
};

USTRUCT()
struct FiTOPFriendResult : public FiTOPResult{
    GENERATED_BODY()
public:
    UPROPERTY() TArray<FiTOPFriendInfo> sameGameFriendList;
};

