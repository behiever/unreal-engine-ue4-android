 
#include "../iTOP/Public/IMSDKFriendManager.h"
#include "../iTOP/Public/IMSDKDefine.h"
 

 
static jclass  s_IMSDKFriendClass;
void IMSDKFriendManager::init(JavaVM *pVM) {
	m_pVM = pVM;
	JNIEnv *env;
	m_pVM->AttachCurrentThread(&env, NULL);
	jclass cls = FAndroidApplication::FindJavaClass(IMSDK_FRIEND_API_CLASSPATH);
	s_IMSDKFriendClass = (jclass)env->NewGlobalRef(cls);
	env->DeleteLocalRef(cls);
}

IMSDKFriendManager::IMSDKFriendManager() {
    m_pVM = NULL;
    m_pInst = NULL;
    m_pFriendListener = NULL;
    m_channel = "";
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKFriendListener*>();
}

IMSDKFriendManager::~IMSDKFriendManager() {
    listenerMap->clear();
}

IMSDKFriendManager* IMSDKFriendManager::m_pInst;
IMSDKFriendManager* IMSDKFriendManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKFriendManager();
    }
    return m_pInst;
}
 

void IMSDKFriendManager::setFriendListener(const IMSDKFriendListener *listener) {
    if (listener == NULL) {
        iTOPLOGD("FriendListener is NULL %s", "");
        return;
    }
    m_pFriendListener = listener;
}

const IMSDKFriendListener* IMSDKFriendManager::getFriendListener() const {
    return m_pFriendListener;
}

bool IMSDKFriendManager::setChannel(const std::string channel) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::setChannel enter %s", channel.c_str());
    jmethodID setChannel = env->GetStaticMethodID(s_IMSDKFriendClass, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKFriendClass, setChannel, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
    return jret;
}

const std::string IMSDKFriendManager::getChannel() {
    return m_channel;
}

jobject convertRequestInfo(JNIEnv *env, IMSDKFriendRequestInfo requestInfo){
    jclass jCls = FAndroidApplication::FindJavaClass("com/tencent/imsdk/android/api/relation/IMSDKFriendReqInfo");
    jmethodID jInit = env->GetMethodID(jCls, "<init>", "()V");
    if (jInit == NULL){
        return NULL;
    }
    jobject jRequestInfo = env->NewObject(jCls, jInit);
    if (jRequestInfo == NULL){
        return NULL;
    }
    //将本地对象的字段，赋值给Java对应的对象的字段
    JniSetIntField(jCls, jRequestInfo, type, "type", requestInfo.type);
    JniSetStringField(jCls, jRequestInfo, user, "user", requestInfo.user);
    JniSetStringField(jCls, jRequestInfo, title, "title", requestInfo.title);
    JniSetStringField(jCls, jRequestInfo, content, "content", requestInfo.content);
    JniSetStringField(jCls, jRequestInfo, link, "link", requestInfo.link);
    JniSetStringField(jCls, jRequestInfo, thumbPath, "thumbPath", requestInfo.thumb_path);
    JniSetStringField(jCls, jRequestInfo, imagePath, "imagePath", requestInfo.image_path);
    JniSetStringField(jCls, jRequestInfo, extraJson, "extraJson", requestInfo.extra_json);
    env->DeleteLocalRef(jCls);
    return jRequestInfo;
}

void OnFriendRawParse(std::string result, int tag, ResultDelegate callBack) {
    iTOPLOGD("OnFriendRawParse raw data result = %s", result.c_str() );
    IMSDKFriendResult friendResult = convertFriendResultFromJson(result);
    std::map<int, const IMSDKFriendListener*> listenerMap = IMSDKFriendManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKFriendListener *imFriendListener = const_cast<IMSDKFriendListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnFriendNotify(friendResult);
        }
    }
}

void OnShareRawParse(std::string result, int tag, ResultDelegate callback){
    iTOPLOGD("OnShareRawParse raw data result = %s", result.c_str()); 
	IMSDKResult imsdkResult = convertiTOPResult(result);
    std::map<int, const IMSDKFriendListener*> listenerMap = IMSDKFriendManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKFriendListener *imFriendListener = const_cast<IMSDKFriendListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imFriendListener->OnShareNotify(imsdkResult);
        }
    }
} 

void IMSDKFriendManager::invite(IMSDKFriendRequestInfo requestInfo) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::invite enter %s, %s", requestInfo.user.c_str(), requestInfo.content.c_str());
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pFriendListener));
    long resultPointer =0;
    jobject jListener = initListener(env, (long)(&OnFriendRawParse), resultPointer, tag);
    jobject jRequestInfo = convertRequestInfo(env, requestInfo);
    jmethodID jInvite = env->GetStaticMethodID(s_IMSDKFriendClass, "invite", "(Lcom/tencent/imsdk/android/api/relation/IMSDKFriendReqInfo;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKFriendClass, jInvite, jRequestInfo, jListener, NULL);
    env->DeleteLocalRef(jRequestInfo);
    env->DeleteLocalRef(jListener);
}

void IMSDKFriendManager::getFriends(int page, int count, int type, std::string extend) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::getFriends enter %d, %d", page, count);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pFriendListener));
    long resultPointer =0;
    jobject jListener = initListener(env, (long)(&OnFriendRawParse), resultPointer, tag);
    jmethodID jGetFriendsMethod = env->GetStaticMethodID(s_IMSDKFriendClass, "getFriendList", "(Ljava/lang/String;IIILjava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jExtend = env->NewStringUTF(extend.c_str());
    jstring jSubChannel = env->NewStringUTF("");
    env->CallStaticVoidMethod(s_IMSDKFriendClass, jGetFriendsMethod, jSubChannel,  page, count, type, jExtend, jListener);
    env->DeleteLocalRef(jExtend);
    env->DeleteLocalRef(jListener);
}

void IMSDKFriendManager::sendMessage(IMSDKFriendRequestInfo requestInfo) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::invite enter %s, %s", requestInfo.user.c_str(), requestInfo.content.c_str());
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pFriendListener));
    long resultPointer =0;
    jobject jListener = initListener(env, (long)(&OnFriendRawParse), resultPointer, tag);
    jobject jRequestInfo = convertRequestInfo(env, requestInfo);
    jmethodID jSendMessage = env->GetStaticMethodID(s_IMSDKFriendClass, "sendMessage", "(Lcom/tencent/imsdk/android/api/relation/IMSDKFriendReqInfo;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKFriendClass, jSendMessage, jRequestInfo, jListener, NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jRequestInfo);
}

void IMSDKFriendManager::share(IMSDKFriendRequestInfo requestInfo) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKFriendManager::share enter %s, %s", requestInfo.user.c_str(), requestInfo.content.c_str());
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pFriendListener));
    long resultPointer =0;
    jobject jListener =  initListener(env, (long)(&OnShareRawParse), resultPointer, tag);
    jobject jRequestInfo = convertRequestInfo(env, requestInfo);
    jmethodID jShare = env->GetStaticMethodID(s_IMSDKFriendClass, "share", "(Lcom/tencent/imsdk/android/api/relation/IMSDKFriendReqInfo;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKFriendClass, jShare, jRequestInfo, jListener, NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jRequestInfo);
}  
