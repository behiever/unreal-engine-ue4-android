/*!
 *  @header    IMSDKGameService.h
 *  @abstract  游戏服务类
 *  @author    Created by shibinhuang on 04/01/18.
 *  @Copyright (c) 2018 Tencent. All rights reserved.
 */

#ifndef IMSDK_ANDROID_IMSDKGAMESERVICE_H
#define IMSDK_ANDROID_IMSDKGAMESERVICE_H

#include "IMSDKGameServiceListener.h"

class IMSDKGameServiceManager {
public:
    static IMSDKGameServiceManager* getInstance();

    /*!
     *  @abstract  设置回调
     *
     *  @param listener 回调
     */
    void setGameServiceListener(const IMSDKGameServiceListener* listener);

    /*!
     *  @abstract  获取回调实例
     *
     *  @return 回调实例
     */
    const IMSDKGameServiceListener* getGameServiceListener() const;

    /*!
     *  @abstract  设置渠道
     *
     *  @param channel 渠道名称（Facebook、WeChat等）
     */
    bool setChannel(const std::string channel);

    /*!
     *  @abstract  获取当前渠道
     *
     *  @return 渠道名称
     */
    const std::string getChannel();

    void setup() ;

    void setScore(std::string board ,int score);

    void showLeaderBoard(std::string board);

    void unlockAchieve(std::string achieve);

    void increaseAchieve(std::string achieve,int step);

    void showAchievement();

#ifdef ANDROID
private:
    JavaVM* m_pVM;

public:
    void init(JavaVM* pVM);
    const std::map<int, const IMSDKGameServiceListener*> getListenerMap(){
        return *listenerMap;
    }
#endif

private:
    static IMSDKGameServiceManager* m_pInst;
    const IMSDKGameServiceListener* m_pGameServiceListener;
    std::string m_channel;

    int listenerTag;
    std::map<int, const IMSDKGameServiceListener*> *listenerMap;

    IMSDKGameServiceManager();
    virtual ~IMSDKGameServiceManager();


};

#endif //IMSDK_ANDROID_IMSDKGAMESERVICE_H
