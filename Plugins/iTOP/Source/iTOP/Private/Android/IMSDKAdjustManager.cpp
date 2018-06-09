//
// Created by SHIBIN HUANG on 2018/4/19.
//

#include "../iTOP/Public/IMSDKAdjustManager.h"
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKAdjustClass;

IMSDKAdjustManager::IMSDKAdjustManager() {
    m_adjustInst = NULL;
}

IMSDKAdjustManager::~IMSDKAdjustManager() {
    
}

IMSDKAdjustManager* IMSDKAdjustManager::m_adjustInst;

IMSDKAdjustManager* IMSDKAdjustManager::getInstance() {
    if (m_adjustInst == NULL){
        m_adjustInst = new IMSDKAdjustManager();
        m_adjustInst->init();
    }
    return m_adjustInst;
}

void IMSDKAdjustManager::init() {
    JNIEnv *env = IMSDKJni::getJniEnv();
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_ADJUST_EXTEND_CLASSPATH);
    s_IMSDKAdjustClass = (jclass) env->NewGlobalRef(cls);
    DEL_LOCAL_REF(cls);
}

bool IMSDKAdjustManager::addStandardDeepLink(std::string uri) {
    iTOPLOGD("in addStandardDeepLink %s" , uri.c_str());
    JNIEnv *env = IMSDKJni::getJniEnv();
    bool ret = false;
    jclass localRef = IMSDKJni::holdWeakGlobalClass(env,s_IMSDKAdjustClass,IMSDK_ADJUST_EXTEND_CLASSPATH);
    jmethodID jAddStandardDeepLink = env->GetStaticMethodID(s_IMSDKAdjustClass, "addStandardDeepLink", "(Ljava/lang/String;)Z");
    if (jAddStandardDeepLink != NULL) {
        jstring jUri = env->NewStringUTF(uri.c_str());
        jboolean jRet = env->CallStaticBooleanMethod(s_IMSDKAdjustClass, jAddStandardDeepLink, jUri);
        if (jRet == JNI_TRUE) {
            ret = true;
        }
        DEL_LOCAL_REF(jUri);
    }
    DEL_LOCAL_REF(localRef);
    return ret;
}

std::string IMSDKAdjustManager::pollStandardDeepLink() {
    iTOPLOGD("in pollStandardDeepLink %s", "");
    JNIEnv *env = IMSDKJni::getJniEnv();
    std::string ret = "";
    jclass localRef = IMSDKJni::holdWeakGlobalClass(env,s_IMSDKAdjustClass,IMSDK_ADJUST_EXTEND_CLASSPATH);
    jmethodID jPollStandardDeepLink = env->GetStaticMethodID(s_IMSDKAdjustClass, "pollStandardDeepLink", "()Ljava/lang/String;");
    if (jPollStandardDeepLink != NULL) {
        jstring jRet = (jstring) env->CallStaticObjectMethod(s_IMSDKAdjustClass, jPollStandardDeepLink);
        ret = env->GetStringUTFChars(jRet, NULL);
        DEL_LOCAL_REF(jRet);
    }
    DEL_LOCAL_REF(localRef);
    return ret;
}

bool IMSDKAdjustManager::addDeferredDeepLink(std::string uri) {
    iTOPLOGD("in addDeferredDeepLink %s" , uri.c_str());
    JNIEnv *env = IMSDKJni::getJniEnv();
    bool ret = false;
    jclass localRef = IMSDKJni::holdWeakGlobalClass(env,s_IMSDKAdjustClass,IMSDK_ADJUST_EXTEND_CLASSPATH);
    jmethodID jAddDeferredDeepLink = env->GetStaticMethodID(s_IMSDKAdjustClass, "addDeferredDeepLink", "(Ljava/lang/String;)Z");
    if (jAddDeferredDeepLink != NULL) {
        jstring jUri = env->NewStringUTF(uri.c_str());
        jboolean jRet = env->CallStaticBooleanMethod(s_IMSDKAdjustClass, jAddDeferredDeepLink, jUri);
        if (jRet == JNI_TRUE) {
            ret = true;
        }
        DEL_LOCAL_REF(jUri);
    }
    DEL_LOCAL_REF(localRef);
    return ret;
}

std::string IMSDKAdjustManager::pollDeferredDeepLink() {
    iTOPLOGD("in pollDeferredDeepLink %s", "");
    JNIEnv *env = IMSDKJni::getJniEnv();
    std::string ret = "";
    jclass localRef = IMSDKJni::holdWeakGlobalClass(env,s_IMSDKAdjustClass,IMSDK_ADJUST_EXTEND_CLASSPATH);
    jmethodID jPollDeferredDeepLink = env->GetStaticMethodID(s_IMSDKAdjustClass, "pollDeferredDeepLink", "()Ljava/lang/String;");
    if (jPollDeferredDeepLink != NULL) {
        jstring jRet = (jstring) env->CallStaticObjectMethod(s_IMSDKAdjustClass, jPollDeferredDeepLink);
        ret = env->GetStringUTFChars(jRet, NULL);
    }
    DEL_LOCAL_REF(localRef);
    return ret;
}

