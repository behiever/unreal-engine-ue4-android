
#include "iTOPUtil.h"

//从图片列表中获取对应的某一图片信息
IMSDKNoticePicInfo iTOPUtil::getFitPic(std::vector<IMSDKNoticePicInfo> pics) {
    IMSDKNoticePicInfo picResult;
    if (pics.size() == 0) {
        picResult = IMSDKNoticePicInfo();
        picResult.picUrl = "none";//返回空
        return picResult;
    }
    picResult = pics.at(0);
    if (pics.size() == 1) {
        return picResult;//只有一张图片，返回那一张，即第一张图片
    }
    int32 SMALL_VALUE_X = 550;
    int32 BIG_VALUE_X = 1050;
    int32 screenX = GEngine->GameViewport->Viewport->GetSizeXY().X;
    
    std::string screenSize;
    if (screenX < SMALL_VALUE_X) {//判断要取哪个尺寸类别的照片
        screenSize = "small";//屏幕宽度小于600用小图
    } else if ( screenX > BIG_VALUE_X ) {
        screenSize = "big";//屏幕宽度大于1050用大图
    } else {
        screenSize = "middle";//其他情况用中等大小的图
    }
    
#if PLATFORM_ANDROID
    iTOPLOGD("The current device width is X = %d", screenX);
    iTOPLOGD("The current device screen is screenSize = %s", screenSize.c_str());
#endif
    //遍历图片列表
    for (int i = 0; i < pics.size();i++)
    {
        IMSDKNoticePicInfo picInfo = pics.at(i);
        std::string::size_type idx = picInfo.picUrl.find(screenSize);
        if(idx != std::string::npos ) {//存在。
            return picInfo;//返回匹配的图片
        }
    }
    return picResult;//没找到，返回第一张图片
}

//过滤掉不需要的照片信息
IMSDKNoticeResult iTOPUtil::filterPic(IMSDKNoticeResult noticeResult) {
    if (noticeResult.number < 1) { //公告数为0，无需处理
        return noticeResult;
    }
    std::vector<IMSDKNoticeInfo> noticeList = noticeResult.list;//公告列表
    int count = noticeList.size();
    if (count < 1) {//没有公告，无需处理
        return noticeResult;
    }
    //遍历公告列表
    std::vector<IMSDKNoticeInfo> fitNoticeInfo;//重新组装公告列表
    for (int i = 0; i < count;i++)
    {
        IMSDKNoticeInfo noticeInfo = noticeList.at(i);
        IMSDKNoticePicInfo picInfo = getFitPic(noticeInfo.pics);
        std::vector<IMSDKNoticePicInfo> fitNoticePicInfo;//重新组装图片列表
        fitNoticePicInfo.push_back(picInfo);
        noticeInfo.pics = fitNoticePicInfo;
        fitNoticeInfo.push_back(noticeInfo);
    }
    noticeResult.list = fitNoticeInfo;
    return noticeResult;
}


 

