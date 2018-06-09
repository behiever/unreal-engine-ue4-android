/*!
 @header IMSDKExtendToolManager.h
 @abstract IMSDKExtendToolManager.h in IMSDK
 @author Created by yuanchengsu on 16/4/27.
 @versino 1.0.0
   Copyright © 2016年 Tencent. All rights reserved.
 */
#ifndef IMSDKExtendToolsListener_h
#define IMSDKExtendToolsListener_h

#include "IMSDKExtendToolListener.h"
#include <cstring>

class IMSDKExtendToolManager{
    
private:
    static IMSDKExtendToolManager *m_instance;
    IMSDKExtendToolListener *m_listener;
    IMSDKExtendToolManager();
    ~IMSDKExtendToolManager();
public:
    
    /*!
     *  @brief the extendtools singleton
     *
     *  @return the instance of extend tools
     */
    static IMSDKExtendToolManager* getInstance();
    
    /*!
     *  @brief set the listener of extend tools
     *
     *  @param listener the listener of extend tools
     */
    void setListener(IMSDKExtendToolListener *listener);
    
    /*!
     *  @brief get the listener of extend tools
     *
     *  @return the listener of extend tools
     */
    IMSDKExtendToolListener *getListener();
    
    /*!
     *  @brief initial url scheme, get the key-value parameters of url querystring when app called through another app
     *
     *  @param keys get the values of the keys from url querystring
     */
    void initUrlShceme(std::vector<std::string>keys);
    
    /*!
     *  @brief check tha app of the channel is installed
     *
     *  @param channel  the channel
     */
    bool isChannelInstalled(std::string channel);
#ifdef ANDROID
private:
	JavaVM* m_pVM;
public:
	void init(JavaVM* pVM);
    std::string  jstring2str(JNIEnv *env, jstring jStr);
    std::string  getPackageChannelId(std::string path);
#endif
};
#endif
