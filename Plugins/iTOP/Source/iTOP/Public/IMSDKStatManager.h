/*!
 @header    IMSDKStatManager.h
 @abstract  IMSDK数据上报模块处理类声明文件
 @author    Created by Hillson Song on 6/23/15.
 @copyright Copyright (c) 2015 Tencent. All rights reserved.
 */

#include "IMSDKComm.h"
#include "IMSDKJson.h"
#ifndef IMSDK_IMSDKStatManager_h
#define IMSDK_IMSDKStatManager_h

/*!
 @class IMSDKStatManager
 @abstract MSDK数据上报模块处理类
 */
class IMSDKStatManager {
private:
    static IMSDKStatManager* m_pInst;
    std::vector<std::string> channelFilter;
    IMSDKStatChannelInterface channelInterface;
    IMSDKStatManager();
    virtual ~IMSDKStatManager();
    
public:
    /*!
     *  @brief 获取数据上报处理类单例
     *
     *  @return 单例
     */
    static IMSDKStatManager* getInstance();
    
    /*!
     *  @brief 设置数据上报平台结构体，并初始化
     *
     *  @param interface 数据上报平台初始化结构体
     */
    void setChannelInterface(IMSDKStatChannelInterface interface);
    
    /*!
     *  @brief 获取数据上报平台结构体
     *
     *  @return 数据上报平台结构体
     */
    const IMSDKStatChannelInterface getChannelInterface();
    
    /*!
     *  @brief  设置上报渠道渠道过滤器。初始化渠道和过滤器的并集为实际上报渠道。
     *
     *  @param filter   渠道过滤器
     */
    void setChannelFilter(const std::vector<std::string> filter);
    
    /*!
     *  @brief 获取当前渠道过滤器，若无返回空。
     *
     *  @return 过滤器
     */
    const std::vector<std::string> getChannelFilter();
    
    /*!
     *  @brief 清空渠道过滤器
     */
    void clearFilter();
    
    /*!
     *  @brief 事件上报，包括事件名称（事件key）和事件体
     *  @param event      时间名称（或者事件key）
     *  @param eventBody  事件体
     *  @param isRealTime 是否实时
     */
    void reportEvent(std::string event, std::string eventBody, bool isRealTime=true);
    
    /*!
     *  @brief 事件上报，包括事件名称（事件key）和事件体
     *  @param event      时间名称（或者事件key）
     *  @param params  事件体
     *  @param isRealTime 是否实时
     */
    void reportEvent(std::string event, std::map<std::string, std::string> params,bool isRealTime=true);
    
    /*!
     *  @brief 购买事件上报
     *  @param purchaseName 购买事件名称
     *  @param currencyCode 货币类型
     *  @param expense      费用
     *  @param isRealTime   是否实时上报
     */
    void reportPurchase(std::string purchaseName, std::string currencyCode, std::string expense, bool isRealTime=true);
    
    /*!
     *  @brief 事件跟踪开始
     *  @param event     时间名称（或者事件key）
     *  @param eventBody 事件体,如需上报多个参数，请用英文逗号分开。例如"key1,value1,key2,value2……key_n,value_n"
     */
    void trackEventBegin(std::string event, std::string eventBody);

    /*!
     *  @brief 事件跟踪结束(事件名称必须成对出现，且参数列表完全相同，才能正常上报事件。)
     *  @param event     事件名称（或者事件key）。
     *  @param eventBody 事件体,如需上报多个参数，请用英文逗号分开。例如"key1,value1,key2,value2……key_n,value_n"
     */
    void trackEventEnd(std::string event, std::string eventBody);
    
    /*!
     *  @brief 页面跟踪开始
     *  @param pageName 页面名称
     */
    void trackPageBegin(std::string pageName);
    
    /*!
     *  @brief 页面跟踪结束(页面名称要成对匹配使用才能正常统计页面情况)
     *  @param pageName 页面名称
     */
    void trackPageEnd(std::string pageName);
    
    /*!
     *  @brief 网速测量
     *  @param hostMap 带端口的host
     */
    void speedTest(std::map<std::string, int> hostMap);
    
    /*!
     *  @brief 网络测速
     *  @param domainList 域名
     */
    void speedTest(std::string domainList[]);
    
    /*!
     *  @brief Crash 上报
     *  @param flag crash是否上报的标志位
     */
    void reportCrash(bool flag);
    
    /*!
     *  @brief Exception 上报
     *  @param flag Exception是否上报的标志位
     */
    void reportAutoExceptionReport(bool flag);
    
#ifdef ANDROID
    /*!
     *  @brief 上报捕获的异常
     *  @param exception 捕获的异常内容
     */
	public:
    //void reportException(Throwable exception);
    /*!
     *  @brief 获取移动设备的唯一识别码IMEI
     *  @return 移动设备的唯一识别码QIMEI
     */
    std::string getStatIMEI();
    
    /*!
     *  @brief 获取移动设备的唯一识别码MID
     *  @return 移动设备的唯一识别码MID
     */
    std::string getStatMID();

 
		JavaVM* m_pVM; 


	void init(JavaVM* pVM);
	void setVM(JavaVM* pVM);
	JavaVM* getVM();
#endif
};

#endif
