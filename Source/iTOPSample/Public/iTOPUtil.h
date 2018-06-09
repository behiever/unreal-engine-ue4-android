// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#ifndef IMSDK_ITOPUTIL_h
#define IMSDK_ITOPUTIL_h

#include "EngineMinimal.h" 
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <string>
#include <vector>
#include <map>
#include <IMSDKNoticeManager.h>

class iTOPUtil{
    
public:
   static IMSDKNoticePicInfo getFitPic(std::vector<IMSDKNoticePicInfo> pics);
   static IMSDKNoticeResult filterPic(IMSDKNoticeResult noticeResult);
};


#endif
