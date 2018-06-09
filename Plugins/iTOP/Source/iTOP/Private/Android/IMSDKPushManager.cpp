//
// Created by dandiliu on 17/10/11.
//

#include "../iTOP/Public/IMSDKPushManager.h" 
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKPushManager;

void OnRegisterPushRawParse(std::string result, int tag, ResultDelegate callBack){
   iTOPLOGD("OnRegisterPushRawParse raw data result = %s", result.c_str());
  IMSDKResult imsdkResult= convertiTOPResult(result);
    std::map<int, const IMSDKPushListener*> listenerMap = IMSDKPushManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKPushListener *imFriendListener = const_cast<IMSDKPushListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnRegister(imsdkResult);
        }
    } 
}

void OnUnregisterPushRawParse(std::string result, int tag, ResultDelegate callBack){
   iTOPLOGD("OnUnregisterPushRawParse raw data result = %s", result.c_str());
     IMSDKResult imsdkResult = convertiTOPResult(result);
    std::map<int, const IMSDKPushListener*> listenerMap = IMSDKPushManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKPushListener *imFriendListener = const_cast<IMSDKPushListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnUnregister(imsdkResult);
        }
    } 
}

void OnSetTagRawParse(std::string result, int tag, ResultDelegate callBack){
   iTOPLOGD("OnSetTagRawParse raw data result = %s", result.c_str());
    IMSDKResult imsdkResult = convertiTOPResult(result);
    std::map<int, const IMSDKPushListener*> listenerMap = IMSDKPushManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKPushListener *imFriendListener = const_cast<IMSDKPushListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnSetTag(imsdkResult);
        }
    }
}

void OnDelTagRawParse(std::string result, int tag, ResultDelegate callBack){
   iTOPLOGD("OnDelTagRawParse raw data result = %s", result.c_str());
    IMSDKResult imsdkResult = convertiTOPResult(result);
    std::map<int, const IMSDKPushListener*> listenerMap = IMSDKPushManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKPushListener *imFriendListener = const_cast<IMSDKPushListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnDelTag(imsdkResult);
        }
    }
}

void OnAddLocalNotification(std::string result, int tag, ResultDelegate callBack){
   iTOPLOGD("OnAddLocalNotification raw data result = %s", result.c_str());
    std::map<int, const IMSDKPushListener*> listenerMap = IMSDKPushManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKPushListener *imFriendListener = const_cast<IMSDKPushListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnNotification(result);
        }
    }
} 

IMSDKPushManager::IMSDKPushManager() {
    m_pInst = NULL;
    m_pVM = NULL;
    m_pInst = NULL;
    m_pPushListener = NULL;
    m_channel = "";
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKPushListener*>();
}

IMSDKPushManager::~IMSDKPushManager() {
    listenerMap->clear();
}

IMSDKPushManager* IMSDKPushManager::m_pInst;

IMSDKPushManager* IMSDKPushManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKPushManager();
    }
    return m_pInst;
}

void IMSDKPushManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_PUSH_API_CLASSPATH);
    s_IMSDKPushManager = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}
 

void IMSDKPushManager::setPushListener(const IMSDKPushListener *pPushListener) {
    if (pPushListener == NULL) {
        iTOPLOGI("pPushListener is NULL");
        return;
    }
    m_pPushListener = pPushListener;
}

const IMSDKPushListener* IMSDKPushManager::getPushListener() const {
    return m_pPushListener;
}


void IMSDKPushManager::setChannel(std::string channel) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
   iTOPLOGD("IMSDKFriendManager::setChannel enter %s", channel.c_str());
    jmethodID setChannel = env->GetStaticMethodID(s_IMSDKPushManager, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKPushManager, setChannel, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
}

std::string IMSDKPushManager::getChannel() {
    return m_channel;
}

void IMSDKPushManager::registerPush() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnRegisterPushRawParse), resultPointer, tag);
    jmethodID jRegisterPush = env->GetStaticMethodID(s_IMSDKPushManager, "registerPush", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKPushManager, jRegisterPush, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::registerPush(std::string account) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnRegisterPushRawParse), resultPointer, tag);

    jmethodID jRegisterPush = env->GetStaticMethodID(s_IMSDKPushManager, "registerPush", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jAccount = env->NewStringUTF(account.c_str());
    env->CallStaticVoidMethod(s_IMSDKPushManager, jRegisterPush, jAccount, jListener);
    env->DeleteLocalRef(jAccount);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::unregisterPush() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnUnregisterPushRawParse), resultPointer, tag);
    jmethodID jUnregisterPush = env->GetStaticMethodID(s_IMSDKPushManager, "unregisterPush", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKPushManager, jUnregisterPush, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::setTag(std::string pushTag) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnSetTagRawParse), resultPointer, tag);

    jmethodID jSetPushTag = env->GetStaticMethodID(s_IMSDKPushManager, "setTag", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jPushTag = env->NewStringUTF(pushTag.c_str());
    env->CallStaticVoidMethod(s_IMSDKPushManager, jSetPushTag, jPushTag, jListener);
    env->DeleteLocalRef(jPushTag);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::delTag(std::string pushTag) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnDelTagRawParse), resultPointer, tag);
    jmethodID jDelTag = env->GetStaticMethodID(s_IMSDKPushManager, "deleteTag", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jPushTag = env->NewStringUTF(pushTag.c_str());
    env->CallStaticVoidMethod(s_IMSDKPushManager, jDelTag, jPushTag, jListener);
    env->DeleteLocalRef(jPushTag);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::delTag(std::vector<std::string> tagList) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnDelTagRawParse), resultPointer, tag);

    jmethodID jDelTag = env->GetStaticMethodID(s_IMSDKPushManager, "deleteTags", "(Ljava/util/List;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");

    jclass jArrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID jInitMethod = env->GetMethodID(jArrayListClass, "<init>", "()V");
    jmethodID jSizeMethod = env->GetMethodID(jArrayListClass, "size", "()I");
    jmethodID jAddMethod = env->GetMethodID(jArrayListClass, "add", "(Ljava/lang/Object;)Z");
    jobject jAddrList = env->NewObject(jArrayListClass, jInitMethod);

    for (int i = 0; i < tagList.size(); i++) {
        jstring jTag = env->NewStringUTF((const char *) tagList.at(i).c_str());
        env->CallBooleanMethod(jAddrList, jAddMethod, jTag);
        env->DeleteLocalRef(jTag);
    }
    env->CallStaticVoidMethod(s_IMSDKPushManager, jDelTag, jAddrList, jListener);
    env->DeleteLocalRef(jAddrList);
    env->DeleteLocalRef(jArrayListClass);
    env->DeleteLocalRef(jListener);
    iTOPLOGD("IMSDKPushManager::deleteTagWithList end ");
}

void IMSDKPushManager::addLocalNotification(IMSDKLocalNotification notification) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer =0;
    jobject jListener = initListener(env, (long)(&OnAddLocalNotification), resultPointer, tag);

    jclass jNotificationCls = FAndroidApplication::FindJavaClass("com/tencent/imsdk/android/api/push/IMSDKLocalMessage");
    jmethodID _initNotification = env->GetMethodID(jNotificationCls, "<init>", "()V");
    if (_initNotification == NULL){
        return;
    }
    jobject jNotification = env->NewObject(jNotificationCls, _initNotification);
    if (jNotification == NULL){
        return;
    }
    JniSetIntField(jNotificationCls, jNotification, type, "type", notification.type);
    JniSetStringField(jNotificationCls, jNotification, title, "title", notification.title);
    JniSetStringField(jNotificationCls, jNotification, content, "content", notification.content);
    JniSetIntField(jNotificationCls, jNotification, actionType, "actionType", notification.actionType);
    JniSetStringField(jNotificationCls, jNotification, actionContent, "actionContent", notification.actionContent);
    JniSetBooleanField(jNotificationCls, jNotification, isRinging, "isRinging", notification.isRinging);
    JniSetStringField(jNotificationCls, jNotification, ringRaw, "ringRaw", notification.ringRaw);
    JniSetBooleanField(jNotificationCls, jNotification, isVibrate, "isVibrate", notification.isVibrate);
    JniSetIntField(jNotificationCls, jNotification, light, "light", notification.light);
    JniSetStringField(jNotificationCls, jNotification, iconRes, "iconRes", notification.iconRes);
    JniSetStringField(jNotificationCls, jNotification, apkDownloadUrl, "apkDownloadUrl", notification.apkDownloadUrl);
    JniSetLongField(jNotificationCls, jNotification, builderId, "builderId", notification.builderId);
    JniSetIntField(jNotificationCls, jNotification, styleId, "styleId", notification.styleId);
    JniSetLongField(jNotificationCls, jNotification, fireTime, "fireTime", notification.fireTime);


    jmethodID jAddLocalNotification = env->GetStaticMethodID(s_IMSDKPushManager, "addLocalNotification", "(Lcom/tencent/imsdk/android/api/push/IMSDKLocalMessage;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKPushManager, jAddLocalNotification, jNotification, jListener);
    env->DeleteLocalRef(jNotification);
    env->DeleteLocalRef(jNotificationCls);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::clearLocalNotification() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pPushListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnDelTagRawParse), resultPointer, tag);
    jmethodID jClearLocalNotification = env->GetStaticMethodID(s_IMSDKPushManager, "clearLocalNotifications", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKPushManager, jClearLocalNotification, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKPushManager::deleteLocalNotification(std::string key) {
    iTOPLOGW("not support");
}
