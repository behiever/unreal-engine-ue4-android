//
// Created by dandiliu on 17/9/28.
//

#include "../iTOP/Public/IMSDKNoticeManager.h"
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKNoticeClass;

void OnLoadRawParse(std::string result, int tag, ResultDelegate callBack){
  iTOPLOGD("OnLoadRawParse raw data result = %s", result.c_str()); 
    
  IMSDKNoticeResult noticeResult= convertiTOPNoticeResult(result);
    std::map<int, const IMSDKNoticeListener*> listenerMap = IMSDKNoticeManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKNoticeListener *imFriendListener = const_cast<IMSDKNoticeListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnLoadNotice(noticeResult);
        }
    } 
}

void OnShowRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnShowRawParse raw data result = %s", result.c_str());
    IMSDKNoticeResult noticeResult;
    std::map<int, const IMSDKNoticeListener*> listenerMap = IMSDKNoticeManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKNoticeListener *imFriendListener = const_cast<IMSDKNoticeListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnLoadNotice(noticeResult);
        }
    }
}

IMSDKNoticeManager::IMSDKNoticeManager() {
    m_pVM = NULL;
    m_pInst = NULL;
    m_Listener = NULL;
    m_channel = "";
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKNoticeListener*>();
}

IMSDKNoticeManager::~IMSDKNoticeManager() {
    listenerMap->clear();
}

IMSDKNoticeManager* IMSDKNoticeManager::m_pInst;
IMSDKNoticeManager* IMSDKNoticeManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKNoticeManager();
    }
    return m_pInst;
}

void IMSDKNoticeManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_NOTICE_API_CLASSPATH);
    s_IMSDKNoticeClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}

JavaVM* IMSDKNoticeManager::getVM() {
    return m_pVM;
}

void IMSDKNoticeManager::setVM(JavaVM *pVM) {
    m_pVM = pVM;
}

void IMSDKNoticeManager::setListener(const IMSDKNoticeListener *pNoticeListener) {
    if (pNoticeListener == NULL) {
        iTOPLOGI("pNoticeListener is NULL");
        return;
    }
    m_Listener = pNoticeListener;
}

const IMSDKNoticeListener* IMSDKNoticeManager::getListener() const {
    return m_Listener;
}

const std::string IMSDKNoticeManager::getChannel() const {
    return m_channel;
}

void IMSDKNoticeManager::setChannel(const std::string channel) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    iTOPLOGD("IMSDKiTOPLOGI(nManager::setChannel enter %s", "");
    jmethodID jSetChannelMethod = env->GetStaticMethodID(s_IMSDKNoticeClass, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    env->CallStaticBooleanMethod(s_IMSDKNoticeClass, jSetChannelMethod, jChannel);
    m_channel = channel; // channel , Facebook, WeChat, GameCenter, Guest...
    env->DeleteLocalRef(jChannel);
} 
  
void IMSDKNoticeManager::loadNoticeData(std::string noticeId,
                                        int loadDataType,
                                        std::string scene,
                                        int noticeType,
                                        std::string extraJson) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_Listener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnLoadRawParse), resultPointer, tag);
    jmethodID jLoadNoticeData = env->GetStaticMethodID(s_IMSDKNoticeClass, "loadNoticeData", "(Ljava/lang/String;ILjava/lang/String;ILcom/tencent/imsdk/android/api/IMSDKResultListener;Ljava/lang/String;)V");
    jstring jNoticeId = env->NewStringUTF(noticeId.c_str());
    jstring jScene = env->NewStringUTF(scene.c_str());
    jstring jExtraJson = env->NewStringUTF(extraJson.c_str());
    env->CallStaticVoidMethod(s_IMSDKNoticeClass, jLoadNoticeData, jNoticeId, loadDataType, jScene, noticeType, jListener, jExtraJson);
    env->DeleteLocalRef(jNoticeId);
    env->DeleteLocalRef(jScene);
    env->DeleteLocalRef(jExtraJson);
    env->DeleteLocalRef(jListener);
}

void IMSDKNoticeManager::loadNoticeData(std::string version,
                                        std::string language,
                                        int region,
                                        int partition,
                                        bool isUseCache,
                                        int noticeType,
                                        std::string extraJson) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_Listener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnLoadRawParse), resultPointer, tag);
    jstring jVersion = env->NewStringUTF(version.c_str());
    jstring jLanguage = env->NewStringUTF(language.c_str());
    jstring jExtraJson = env->NewStringUTF(extraJson.c_str());
    jmethodID jLoadNoticeData = env->GetStaticMethodID(s_IMSDKNoticeClass, "loadNoticeData", "(Ljava/lang/String;Ljava/lang/String;IIZILcom/tencent/imsdk/android/api/IMSDKResultListener;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(s_IMSDKNoticeClass, jLoadNoticeData, jVersion, jLanguage, region, partition, isUseCache, noticeType, jListener, jExtraJson);
    env->DeleteLocalRef(jVersion);
    env->DeleteLocalRef(jLanguage);
    env->DeleteLocalRef(jExtraJson);
    env->DeleteLocalRef(jListener);
}

void IMSDKNoticeManager::closeNotice(std::string noticeId,
                                     int closeType,
                                     std::string extraJson) {
}

void IMSDKNoticeManager::showNotice(std::string noticeId,
                                    int noticeType,
                                    std::string scene,
                                    std::string extraJson) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_Listener));

    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnShowRawParse), resultPointer, tag);

    jmethodID jShowNotice = env->GetStaticMethodID(s_IMSDKNoticeClass, "showNotice", "(Ljava/lang/String;ILjava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;Ljava/lang/String;)V");
    jstring jNoticeId = env->NewStringUTF(noticeId.c_str());
    jstring jScene = env->NewStringUTF(scene.c_str());
    jstring jExtraJson = env->NewStringUTF(extraJson.c_str());

    env->CallStaticVoidMethod(s_IMSDKNoticeClass, jShowNotice, jNoticeId, noticeType, jScene, jListener, jExtraJson);
    env->DeleteLocalRef(jNoticeId);
    env->DeleteLocalRef(jScene);
    env->DeleteLocalRef(jExtraJson);
    env->DeleteLocalRef(jListener);
}

void IMSDKNoticeManager::setUserTargetingData(std::string targetingJsonData,
                                              std::string extraJson) {
}

void IMSDKNoticeManager::updateUserTargetingDataToSvr(std::string extraJson) {

}
