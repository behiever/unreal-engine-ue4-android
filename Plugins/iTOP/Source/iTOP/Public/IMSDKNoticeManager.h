/*!
 @header IMSDKNoticeManager.h
 @abstract IMSDKNoticeManager.h in IMSDK
 @author Created by yuanchengsu on 16/6/16.
 @versino 1.0.0
 @copyright Copyright © 2016年 Tencent. All rights reserved.
 */
#ifndef IMSDKNoticeManager_h
#define IMSDKNoticeManager_h

#include"IMSDKNoticeListener.h"
 

/*!
 @class IMSDKNoticeManager
 @abstract Notice 管理类，对外接口
 */
class IMSDKNoticeManager {
private:
    static IMSDKNoticeManager* m_pInst;
    const IMSDKNoticeListener* m_Listener;
    std::string m_channel;
    
    int listenerTag;
    std::map<int,const IMSDKNoticeListener*> *listenerMap;

    IMSDKNoticeManager();
    virtual ~IMSDKNoticeManager();
    
public:
    
    /*!
     *  @breif 获取公告类单例
     *
     *  @return IMSDKLoginManager单例
     */
    static IMSDKNoticeManager* getInstance();
    
    /*!
     *  @breif 设置公告回调
     *
     *  @param pNoticeListener 公告回调
     */
    void setListener(const IMSDKNoticeListener* pNoticeListener);
    
    /*!
     *  @breif 获取公告回调指针
     *
     *  @return 公告回调指针
     */
    const IMSDKNoticeListener* getListener() const;
    
    /*!
     *  @breif 设置渠道
     *
     *  @param channel 渠道名称
     */
    void setChannel(const std::string channel);
    
    /*!
     *  @breif 获取公告渠道
     *
     *  @return 渠道
     */
    const std::string getChannel() const;

    /*!
     *  @brief 展示公告
     *
     *  @param noticeId    指定需要获取的notice ID(可选,如不指定将按loadDataType自动获取)
     *  @param noticeType  公告类型
     *                       <li> 1 : 登录前公告</li>
     *                       <li> 2 : 登录后公告</li>
     *                       <li> 3 : 标题公告</li>
     *                       <li> 4 : 底部标题公告</li>
     *                       <li> 5 : 用户协议</li>
     *                       <li> 6 : 更新信息</li>
     *  @param scene       指定的场景
     *  @param extraJson 附加参数
     */
    void showNotice(std::string noticeId, int noticeType, std::string scene,std::string extraJson);
    
    /*!
     *  @brief 获取公告数据
     *
     *  @param noticeId     指定需要获取的notice ID(可选,如不指定将按loadDataType自动获取)
     *  @param loadDataType 1:从第三方渠道获取数据 2:从deepLink获取数据 3：预留：从imsdk自研平台获取数据（返回的是IMNoticeInfo）4...
     *  @param scene        指定的场景
     *  @param noticeType    公告类型
     *                       <li> 1 : 登录前公告</li>
     *                       <li> 2 : 登录后公告</li>
     *                       <li> 3 : 标题公告</li>
     *                       <li> 4 : 底部标题公告</li>
     *                       <li> 5 : 用户协议</li>
     *                       <li> 6 : 更新信息</li>
     *  @param extraJson    附加参数
     */
    void loadNoticeData(std::string noticeId, int loadDataType , std::string scene, int noticeType,std::string extraJson );

    /*!
     *  @brief 获取多语言公告
     *
     *  @param version    app版本
     *  @param language   需要的语言环境
     *  @param region     地区
     *  @param partition  游戏大区
     *  @param isUseCache 如果有图片是否使用本地缓存图片
     *  @param noticeType    公告类型
     *                       <li> 1 : 登录前公告</li>
     *                       <li> 2 : 登录后公告</li>
     *                       <li> 3 : 标题公告</li>
     *                       <li> 4 : 底部标题公告</li>
     *                       <li> 5 : 用户协议</li>
     *                       <li> 6 : 更新信息</li>
     *  @param extraJson  扩展字段
     */
    void loadNoticeData(std::string version, std::string language, int region, int partition, bool isUseCache,int noticeType, std::string extraJson);
    
    /*!
     *  @brief 设置用户唯一标识码及标签
     *
     *  @param targetingJsonData 设置json数据
     *  @param extraJson         附加参数
     */
    void setUserTargetingData(std::string targetingJsonData, std::string extraJson);
   
    /*!
     *  @brief 将SetUserTargetingData的数据同步至服务器
     *
     *  @param extraJson 附加参数
     */
    void updateUserTargetingDataToSvr(std::string extraJson);
    
    /*!
     *  @brief 强制关闭广告
     *
     *  @param noticeId     指定需要关闭的notice ID(可选,如不指定将按closeType值关闭)
     *  @param closeType    1：关闭最上端弹窗 2：关闭所有弹窗，包括等待中的弹窗
     *  @param extraJson    附加参数
     */
    void closeNotice(std::string noticeId , int closeType , std::string extraJson);

#ifdef ANDROID
private:
	JavaVM* m_pVM;

public:
	void init(JavaVM* pVM);
	void setVM(JavaVM* pVM);
	JavaVM* getVM();

	const std::map<int, const IMSDKNoticeListener*> getListenerMap() {
		return *listenerMap;
	}
#endif
};

#endif
