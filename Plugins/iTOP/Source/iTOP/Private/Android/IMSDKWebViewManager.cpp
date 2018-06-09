//
// Created by dandiliu on 17/9/28.
//
 
#include "../iTOP/Public/IMSDKWebViewManager.h" 
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKWebViewClass;

void OnGetTicketRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnGetTicketRawParse raw data result = %s", result.c_str());
    IMSDKWebViewTicketResult ticketResult =  convertiTOPWebViewTicketResult(result);
    std::map<int, const IMSDKWebViewListener*> listenerMap = IMSDKWebViewManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKWebViewListener *imFriendListener = const_cast<IMSDKWebViewListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnGetTicket(ticketResult);
        }
    } 
}

void OnWebViewActionRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnWebViewActionRawParse raw data result = %s", result.c_str());
    IMWebViewStatusResult actionResult = convertiTOPWebViewStatusResult(result);
    std::map<int, const IMSDKWebViewListener*> listenerMap = IMSDKWebViewManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKWebViewListener *imFriendListener = const_cast<IMSDKWebViewListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnWebviewAction(actionResult);
        }
    } 
}

IMSDKWebViewManager::IMSDKWebViewManager(){
    m_pVM = NULL;
    m_pInst = NULL;
    m_pListener = NULL;
    m_channel = "";
    m_listenerTag = -1;
    m_pListenerMap = new std::map<int, const IMSDKWebViewListener*>();
}

IMSDKWebViewManager::~IMSDKWebViewManager() {
    m_pListenerMap->clear();
    delete m_pListenerMap;
}

IMSDKWebViewManager* IMSDKWebViewManager::m_pInst;

IMSDKWebViewManager* IMSDKWebViewManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKWebViewManager();
    }
    return m_pInst;
}

void IMSDKWebViewManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_WEBVIEW_API_CLASSPATH);
    s_IMSDKWebViewClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}

JavaVM* IMSDKWebViewManager::getVM() {
    return m_pVM;
}

void IMSDKWebViewManager::setVM(JavaVM *pVM) {
    m_pVM = pVM;
}

void IMSDKWebViewManager::setChannel(const std::string channel) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::setChannel enter %s", channel.c_str());
    jmethodID setChannel = env->GetStaticMethodID(s_IMSDKWebViewClass, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKWebViewClass, setChannel, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
}

void IMSDKWebViewManager::setListener(const IMSDKWebViewListener *pListener) {
    if (pListener == NULL){
        iTOPLOGI("pNoticeListener is NULL");
        return;
    }
    m_pListener = pListener;
}

void IMSDKWebViewManager::callJS(std::string parasJson) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID  jCallJS = env->GetStaticMethodID(s_IMSDKWebViewClass, "callJs", "(Ljava/lang/String;)V");
    jstring jParasJson = env->NewStringUTF(parasJson.c_str());
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jCallJS, jParasJson);
}

void IMSDKWebViewManager::getTicket() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++m_listenerTag;
    m_pListenerMap->insert(std::make_pair(tag, m_pListener));
    long resultPointer = 0;
    jobject jListener = initListener(env, (long)(&OnGetTicketRawParse), resultPointer, tag);
    jmethodID jGetTicket = env->GetStaticMethodID(s_IMSDKWebViewClass, "getTicket", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jGetTicket, jListener);
    env->DeleteLocalRef(jListener);
}


void IMSDKWebViewManager::openURL(std::string url,
                                  bool toolBar,
                                  bool browser,
                                  bool isfullScreen,
                                  std::string extraJSON) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jOpenURL = env->GetStaticMethodID(s_IMSDKWebViewClass, "openURL", "(Ljava/lang/String;ZZLjava/lang/String;)V");
    jstring jUrl = env->NewStringUTF(url.c_str());
    jstring jExtraJSON = env->NewStringUTF(extraJSON.c_str());
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jOpenURL, jUrl, toolBar, browser, jExtraJSON);
    env->DeleteLocalRef(jUrl);
    env->DeleteLocalRef(jExtraJSON);
}

void IMSDKWebViewManager::backWebView() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jBack = env->GetStaticMethodID(s_IMSDKWebViewClass, "back", "()V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jBack);
}

void IMSDKWebViewManager::closeWebView() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jCloseWebView = env->GetStaticMethodID(s_IMSDKWebViewClass, "close", "()V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jCloseWebView);
}

void IMSDKWebViewManager::forwardWebView() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jForwardWebView = env->GetStaticMethodID(s_IMSDKWebViewClass, "forward", "()V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jForwardWebView);
}

void IMSDKWebViewManager::reloadWebView() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jReloadWebView =env->GetStaticMethodID(s_IMSDKWebViewClass, "reload", "()V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jReloadWebView);
}

void IMSDKWebViewManager::setPosition(int x, int y, int w, int h) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jSetPosition = env->GetStaticMethodID(s_IMSDKWebViewClass, "setPosition", "(IIII)V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jSetPosition, x, y, w, h);
}

void IMSDKWebViewManager::setWebViewActionCallback() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++m_listenerTag;
    m_pListenerMap->insert(std::make_pair(tag, m_pListener));
    long resultPointer = 0;
    jobject jListener = initListener(env, (long)(&OnWebViewActionRawParse), resultPointer, tag);
    jmethodID jSetWebViewActionCallback = env->GetStaticMethodID(s_IMSDKWebViewClass, "registerActionObserver", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKWebViewClass, jSetWebViewActionCallback, jListener);
    env->DeleteLocalRef(jListener);
}


