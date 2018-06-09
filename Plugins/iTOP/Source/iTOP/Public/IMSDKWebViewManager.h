/*!
 *  @header    IMSDKWebViewManager.h
 *  @abstract  WebView Manager
 *  @author    Created by Hillson Song on 8/10/15.
 *  @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#ifndef __IMSDK__IMSDKWebViewManager__
#define __IMSDK__IMSDKWebViewManager__
 
#include "IMSDKWebViewListener.h"

/*!
 *  @class IMSDKWebViewManager*
 *  @abstract IMSDK内置浏览器，支持是否全屏以及是否显示工具栏
 */
class IMSDKWebViewManager {
private:
    static IMSDKWebViewManager* m_pInst;
    const IMSDKWebViewListener* m_pListener;
    int m_listenerTag;
    std::map<int,const IMSDKWebViewListener *> *m_pListenerMap;
    
    std::string m_channel;
    IMSDKWebViewManager();
    virtual ~IMSDKWebViewManager();
    
public:
    
    /*!
     *  @brief 获取IMSDKWebViewManager单例
     *
     *  @return 单例
     */
    static IMSDKWebViewManager* getInstance();
    
    /*!
     *  @brief 设置回调处理监听类
     *
     *  @param pListener 回调处理实例
     */
    void setListener(const IMSDKWebViewListener* pListener);
    
    /*!
     *  @brief 获取回调处理类
     *
     *  @return 回调处理实例
     */
    const IMSDKWebViewListener* getListener() const;
    
    /*!
     *  @brief 设置WebView的渠道，默认为IMSDK
     *
     *  @param channel 渠道名
     */
    void setChannel(const std::string channel="IMSDK");
    

    /*!
     *  @brief 打开指定链接
     *  未设置尺寸的情况下将调用游戏内置浏览器IMSDKWebViewController（width或者height为0）。可调用setPosition或者setSize设置尺寸
     *  @param url 目标链接
     *  @param toolBar 是否需要工具栏
     *  @param browser 是否使用外部浏览器
     *  @param isfullScreen 是否全屏
     */
    void openURL(std::string url, bool toolBar = false, bool browser = false , bool isfullScreen = false, std::string extraJSON = "{}");
    
    /*!
     *  @brief 调用JS函数
     *  @param parasJson 传递给JS的参数
     */
    void callJS(std::string parasJson);
    
    /*!
     *  @brief 设置webview位置与大小
     *  @param x x轴坐标
     *  @param y y轴坐标
     *  @param w 宽
     *  @param h 高
     */
    void setPosition(int x, int y, int w, int h);
    
    /*!
     *  @brief  判断是否可见
     *
     *  @return 是否可见
     */
    bool isWebViewActivated();
    
    /*!
     *  @brief 关闭webview
     */
    void closeWebView();
    
    /*!
     *  @brief 判断是否可后退
     *
     *  @return 是否可回退
     */
    bool canGoBack();
    
    /*!
     *  @brief 后退
     */
    void backWebView();
    
    /*!
     *  @brief 判断是否可前进
     *
     *  @return 是否可前进
     */
    bool canGoForward();
    
    /*!
     *  @brief 前进
     */
    void forwardWebView();
    
    /*!
     *  @brief 重载
     */
    void reloadWebView();
    
    /*!
     *  @brief 获取当前登录态对应的webview票据信息
     */
    void getTicket();
    
    /*!
     *  @brief 返回是否全屏
     *
     *  @return 是否全屏
     */
    bool isFullScreen();

#ifdef ANDROID
private:
	JavaVM* m_pVM;

public:
	void init(JavaVM* pVM);
	void setVM(JavaVM* pVM);
	JavaVM* getVM();

	void setWebViewActionCallback();
	const std::map<int, const IMSDKWebViewListener*> getListenerMap() {
		return *m_pListenerMap;
	}


#endif
    
};

#endif /* defined(__IMSDK__IMSDKWebViewManager__) */
