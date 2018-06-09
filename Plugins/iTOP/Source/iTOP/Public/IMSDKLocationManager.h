/*!
 @header    IMSDKLocationManager.h
 @abstract  IMSDK位置信息处理类声明文件
 @author    Created by Hillson Song on 9/8/15.
 @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef __IMSDK__IMSDKLocationManager__
#define __IMSDK__IMSDKLocationManager__

#include "IMSDKLocationListener.h"

/*!
 @class IMSDKLocationManager
 @abstract IMSDK位置信息处理类
 */
class IMSDKLocationManager {
private:
    static IMSDKLocationManager* m_pInst;
    const IMSDKLocationListener* m_pListener;
    int language_tag;//语言标记
    bool m_enableGPS;//GPS权限
    IMSDKLocationManager();
    virtual ~IMSDKLocationManager(); 
    std::string m_channel;
    int listenerTag;
    std::map<int,const IMSDKLocationListener*> *listenerMap;
    
public:
    /*!
     *  @brief 获取位置信息处理单例
     *
     *  @return 单例
     */
    static IMSDKLocationManager* getInstance();
    
    void setChannel(const std::string channel);
    
    /*!
     *  @brief 设置回调监听
     *
     *  @param pListener 监听类实例
     */
    void setListener(const IMSDKLocationListener* pListener);
    
    /*!
     *  @brief 获取回调监听
     *
     *  @return 监听类实例
     */
    const IMSDKLocationListener* getListener();
    
    
    /*!
     *  @breif 获取lbs渠道
     *
     *  @return 渠道
     */
    const std::string getChannel() const;

    /*!
     *  @brief 设置语言标记（不设置默认中文）
     *
     *  @param tag 语言标记
     */
    void setLanguageTag(int tag);
    
    /*!
     *  @brief 获取当前语言标记
     *
     *  @return 当前语言标记
     */
    int getLanguageTag();
    
    /*!
     *  @brief 设置是否需要开启GPS定位
     *
     *  @param enableGPS GPS定位权限
     */
    void enableGPS(bool enableGPS);
    
    /*!
     *  @brief 获取是否允许GPS定位
     *
     *  @return 是否允许
     */
    bool getGPSEnable();
    
    /*!
     * @brief 获取地理位置信息
     *
     */
    void getLocationInfo();
    
#ifdef ANDROID  
public:
    void init();
    const std::map<int, const IMSDKLocationListener*> getListenerMap() {
        return *listenerMap;
    }
#endif
};

#endif /* defined(__IMSDK__IMSDKLocationManager__) */
