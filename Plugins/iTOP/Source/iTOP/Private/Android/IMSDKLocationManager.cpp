//
// Created by SHIBIN HUANG on 2018/4/19.
//

#include "../iTOP/Public/IMSDKLocationManager.h"
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKLbsClass;

void OnLbsRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnLbsRawParse raw data result = %s", result.c_str());
    IMSDKLocationInfo lbsResult = convertiTOPLbsResult(result);
    std::map<int, const IMSDKLocationListener*> listenerMap = IMSDKLocationManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKLocationListener *imLbsListener = const_cast<IMSDKLocationListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imLbsListener->OnGetLocationInfo(lbsResult);
        }
    }
}


IMSDKLocationManager::IMSDKLocationManager() { 
    m_pInst = NULL;
    m_pListener = NULL;
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKLocationListener*>();
}

IMSDKLocationManager::~IMSDKLocationManager() {
    listenerMap->clear();
}

IMSDKLocationManager* IMSDKLocationManager::m_pInst;
IMSDKLocationManager* IMSDKLocationManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKLocationManager();
        m_pInst->init();
    }
    return m_pInst;
}

void IMSDKLocationManager::init() {
    JNIEnv *env = IMSDKJni::getJniEnv();
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_LBS_API_CLASSPATH);
    s_IMSDKLbsClass = (jclass) env->NewGlobalRef(cls);
    DEL_LOCAL_REF(cls);
}

void IMSDKLocationManager::setListener(const IMSDKLocationListener *pNoticeListener) {
    if (pNoticeListener == NULL) {
        iTOPLOGI("pNoticeListener is NULL");
        return;
    }
    m_pListener = pNoticeListener;
}

const std::string IMSDKLocationManager::getChannel() const {
    return m_channel;
}

void IMSDKLocationManager::setChannel(const std::string channel) {
    JNIEnv *env = IMSDKJni::getJniEnv();
    iTOPLOGD("IMSDKiTOPLOGI(nManager::setChannel enter %s", "");
    jmethodID jSetChannelMethod = env->GetStaticMethodID(s_IMSDKLbsClass, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    env->CallStaticBooleanMethod(s_IMSDKLbsClass, jSetChannelMethod, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
}

void IMSDKLocationManager::getLocationInfo(){
    JNIEnv *env = IMSDKJni::getJniEnv();
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnLbsRawParse), resultPointer, tag);
    jmethodID jLocationInfo = env->GetStaticMethodID(s_IMSDKLbsClass, "getLocationInfo", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKLbsClass, jLocationInfo, jListener); 
    env->DeleteLocalRef(jListener);
}
