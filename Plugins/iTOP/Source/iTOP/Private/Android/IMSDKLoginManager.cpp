 
#include "../iTOP/Public/IMSDKLoginManager.h"
#include "../iTOP/Public/IMSDKDefine.h" 
 
static jclass s_IMSDKLoginClass;

IMSDKLoginManager::IMSDKLoginManager() {
    m_pInst = NULL;
    m_LoginListener = NULL;
    m_pVM = NULL;
    m_channel = "";
    m_reportChannel = "";
    m_logintype = "";
    m_extraJson = "";
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKLoginListener *>();
}

IMSDKLoginManager::~IMSDKLoginManager() {
    listenerMap->clear();
}

IMSDKLoginManager *IMSDKLoginManager::m_pInst;

IMSDKLoginManager *IMSDKLoginManager::getInstance() {
    if (m_pInst == NULL) {
        m_pInst = new IMSDKLoginManager();
    } 
    return m_pInst;
}

void IMSDKLoginManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_LOGIN_API_CLASSPATH);
    s_IMSDKLoginClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}

void IMSDKLoginManager::setLoginListener(const IMSDKLoginListener *pLoginListener) {
    if (pLoginListener == NULL) {
        iTOPLOGI("LoginListener is NULL");
        return;
    }
    m_LoginListener = pLoginListener;
}

const IMSDKLoginListener *IMSDKLoginManager::getLoginListener() const {
    return m_LoginListener;
}

void OnLoginRawParse(std::string result, int tag, ResultDelegate callBack) {
    iTOPLOGD("OnLoginRawParse raw data result = %s", result.c_str());
    IMSDKLoginResult imsdkLoginResult = convertiTOPLoginResult(result);

    std::map<int, const IMSDKLoginListener *> listenerMap = IMSDKLoginManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKLoginListener *imLoginListener = const_cast<IMSDKLoginListener *>(listenerMap.at(
                    tag));
            listenerMap.erase(tag);
            imLoginListener->OnLoginNotify(imsdkLoginResult);
        }
    } 
}

void OnQuickLoginRawParse(std::string result, int tag, ResultDelegate callBack) {
    iTOPLOGD("OnQuickLoginRawParse raw data result = %s", result.c_str());
    IMSDKLoginResult imsdkLoginResult = convertiTOPQuickLoginResult(result);
    
    std::map<int, const IMSDKLoginListener *> listenerMap = IMSDKLoginManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKLoginListener *imLoginListener = const_cast<IMSDKLoginListener *>(listenerMap.at(
                                                                                                  tag));
            listenerMap.erase(tag);
            imLoginListener->OnLoginNotify(imsdkLoginResult);
        }
    }
}

void OnBindRawParse(std::string result, int tag, ResultDelegate callBack) {
	iTOPLOGD("OnBindRawParse raw data result = %s", result.c_str());  
	IMSDKLoginResult imsdkLoginResult = convertiTOPBindResult(result); 
	std::map<int, const IMSDKLoginListener *> listenerMap = IMSDKLoginManager::getInstance()->getListenerMap();
	if (listenerMap.size() > 0) {
		if (listenerMap.end() != listenerMap.find(tag)) {
			IMSDKLoginListener *imLoginListener = const_cast<IMSDKLoginListener *>(listenerMap.at(
				tag));
			listenerMap.erase(tag);
			imLoginListener->OnLoginNotify(imsdkLoginResult);
		}
	}
}

void OnLogutRawParse(std::string result, int tag, ResultDelegate callBack) {
    iTOPLOGD("OnLogutRawParse raw data result = %s", result.c_str());
    IMSDKResult imsdkResult = convertiTOPResult(result);
    std::map<int, const IMSDKLoginListener *> listenerMap = IMSDKLoginManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKLoginListener *imLoginListener = const_cast<IMSDKLoginListener *>(listenerMap.at(
                    tag));
            listenerMap.erase(tag);
            imLoginListener->OnLogoutNotify(imsdkResult);
        }
    } 
}

void OnGetBindInfoRawParse(std::string result, int tag, ResultDelegate callBack) {
    iTOPLOGD("OnGetBindInfoRawParse raw data result = %s", result.c_str());
    IMSDKBindInfo imBindInfo  = convertiTOPGetBindResult(result);

    std::map<int, const IMSDKLoginListener *> listenerMap = IMSDKLoginManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKLoginListener *imLoginListener = const_cast<IMSDKLoginListener *>(listenerMap.at(
                    tag));
            listenerMap.erase(tag);
            imLoginListener->OnGetBindInfoNotify(imBindInfo);
        }
    }  
}
 

void IMSDKLoginManager::setChannel(const std::string channel) {
    iTOPLOGD("IMSDKLoginManager::setChannel enter %s", channel.c_str());
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jSetChannel = env->GetStaticMethodID(s_IMSDKLoginClass, "setChannel",
                                                   "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKLoginClass, jSetChannel, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
}

void IMSDKLoginManager::setLoginType(std::string loginType) {
    iTOPLOGD("IMSDKLoginManager::setLoginType enter %s", loginType.c_str());
    m_logintype = loginType;
}

const std::string IMSDKLoginManager::getLoginType() {
    return m_logintype;
}

void IMSDKLoginManager::quickLogin() {
    iTOPLOGD("IMSDKLoginManager::quickLogin enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer =0;
    jobject jListener = initListener(env, (long) (&OnQuickLoginRawParse), resultPointer, tag);

    jmethodID jQuickLoginMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "quickLogin",
                                                         "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jQuickLoginMethod, jListener);

    env->DeleteLocalRef(jListener);
}

/**
 * @param permissions
 * @param needGuid iOS 暂时没有使用
 */
void IMSDKLoginManager::login(const std::vector<std::string> *permissions, bool needGuid) {
    iTOPLOGD("IMSDKLoginManager::login enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

	jobject jAddrList = NULL;
	jclass jArrayListClass = NULL;
	if (permissions != NULL) {
		jArrayListClass = env->FindClass("java/util/ArrayList");
		jmethodID jInitMethod = env->GetMethodID(jArrayListClass, "<init>", "()V");
		jmethodID jAddMethod = env->GetMethodID(jArrayListClass, "add", "(Ljava/lang/Object;)Z");
		jAddrList = env->NewObject(jArrayListClass, jInitMethod);

		for (int i = 0; i < (*permissions).size(); i++) {
			jstring jTag = env->NewStringUTF((const char *)(*permissions).at(i).c_str());
			env->CallBooleanMethod(jAddrList, jAddMethod, jTag);
			env->DeleteLocalRef(jTag);
		}
	}

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer = 0;
    jobject jListener = initListener(env, (long) (&OnLoginRawParse), resultPointer, tag);

    jmethodID jLoginMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "login",
                                                    "(Ljava/util/List;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jLoginMethod, jAddrList, jListener);

	if (jAddrList != NULL) {
		env->DeleteLocalRef(jAddrList);
	}
	if (jArrayListClass != NULL) {
		env->DeleteLocalRef(jArrayListClass);
	}
	env->DeleteLocalRef(jListener);
}

void IMSDKLoginManager::loginWithConfirmCode(std::string code) {
    iTOPLOGD("IMSDKLoginManager::login enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer = 0;
    jobject jListener = initListener(env, (long) (&OnLoginRawParse), resultPointer, tag);

    jstring jCode = env->NewStringUTF(code.c_str());
    jstring jSubChannel = env->NewStringUTF("");
    jstring jExtras = env->NewStringUTF(m_extraJson.c_str());

    jmethodID jLoginMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "login",
                                                    "(Ljava/lang/String;Ljava/lang/String;ZLjava/util/List;Lcom/tencent/imsdk/android/api/IMSDKResultListener;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jLoginMethod, jCode, jSubChannel, true, NULL,
                              jListener, jExtras);

    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jCode);
    env->DeleteLocalRef(jSubChannel);
    env->DeleteLocalRef(jExtras);
}

bool IMSDKLoginManager::isLogin() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jIsLoginMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "isLogin", "()Z");
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKLoginClass, jIsLoginMethod);
    return jret;
}

void IMSDKLoginManager::logout() {
    iTOPLOGD("IMSDKLoginManager::logout enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long) (&OnLogutRawParse), resultPointer, tag);
    jmethodID jLogoutMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "logout",
                                                     "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jLogoutMethod, jListener);

    env->DeleteLocalRef(jListener);
}

/**
 * @param channel
 * @param subChannel
 * @param extraJson 透传到插件包
 */
void IMSDKLoginManager::bind(std::string channel, std::string subChannel, std::string extraJson) {
	iTOPLOGD("PrintAuthListener OnAllBind callback  ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    jstring jChannel = env->NewStringUTF(channel.c_str());
    jstring jSubChannel = env->NewStringUTF(subChannel.c_str());
    jstring jExtras = env->NewStringUTF(extraJson.c_str());

    jclass jStringClass = env->FindClass("java/lang/Object");
    jobjectArray jArray = env->NewObjectArray(1, jStringClass, 0);
    (env)->SetObjectArrayElement(jArray, 0, jExtras);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long) (&OnBindRawParse), resultPointer, tag);

    jmethodID jBindMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "bind",
                                                   "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jBindMethod, jChannel, jSubChannel, jListener,
                              jArray);
    env->DeleteLocalRef(jStringClass);
    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jSubChannel);
    env->DeleteLocalRef(jExtras);
    env->DeleteLocalRef(jArray);
    env->DeleteLocalRef(jListener);

}

void IMSDKLoginManager::getBindInfo() {
    iTOPLOGD("IMSDKLoginResult::getBindInfo enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_LoginListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long) (&OnGetBindInfoRawParse), resultPointer, tag);

    jstring jChannel = env->NewStringUTF(m_channel.c_str());
    jmethodID jLoginMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "getBindInfo",
                                                    "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKLoginClass, jLoginMethod, jChannel, jListener);

    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jListener);
}

const IMSDKLoginResult IMSDKLoginManager::getLoginResult() {
    iTOPLOGD("IMSDKLoginResult::getLoginResult enter %s", "");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jGetLoginResultMethod = env->GetStaticMethodID(s_IMSDKLoginClass, "getLoginResult",
                                                             "()Lcom/tencent/imsdk/android/api/login/IMSDKLoginResult;");
    IMSDKLoginResult imLoginRet;
    if (jGetLoginResultMethod != NULL) {
        jobject jloginResultOjbect = env->CallStaticObjectMethod(s_IMSDKLoginClass,
                                                                 jGetLoginResultMethod);
        if (jloginResultOjbect != NULL) {
            jclass jLoginResultClss = env->GetObjectClass(jloginResultOjbect);
            if (jLoginResultClss != NULL) {
                imLoginRet = getLoginResultFromJava(env, jLoginResultClss, jloginResultOjbect);
            }
        }
    }
    return imLoginRet;
}

void IMSDKLoginManager::setExtraJson(std::string extraJson) {
    iTOPLOGD("IMSDKLoginManager::setExtraJson enter %s", extraJson.c_str());
    m_extraJson = extraJson;
}

std::string IMSDKLoginManager::getExtraJson() {
    return m_extraJson;
}

IMSDKLoginResult IMSDKLoginManager::getLoginResultFromJava(JNIEnv *env, jclass jclassResult,
                                                           jobject jobjectResult) {
    IMSDKLoginResult imLoginRet;
    if (env == NULL || jclassResult == NULL || jobjectResult == NULL) {
        return imLoginRet;
    }

    JniGetAndSetIntField(imsdkRetCode, "imsdkRetCode", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetIntField(thirdRetCode, "thirdRetCode", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(imsdkRetMsg, "imsdkRetMsg", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(thirdRetMsg, "thirdRetMsg", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(retExtraJson, "retExtraJson", jclassResult, jobjectResult, imLoginRet);

    JniGetAndSetIntField(guid_channel_id, "channelId", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetIntField(guid_game_id, "gameId", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(guid, "guid", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(guid_open_id, "openId", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(guid_token, "innerToken", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetLongField(guid_token_expire, "innerTokenExpire", jclassResult, jobjectResult,
                          imLoginRet);
	JniGetAndSetStringField(guid_user_nick,"guidUserNick", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetIntField(guid_user_gender, "guidUserSex", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(guid_user_birthday, "guidUserBirthday", jclassResult, jobjectResult,
                            imLoginRet);
    JniGetAndSetStringField(guid_user_portrait, "guidUserPortrait", jclassResult, jobjectResult,
                            imLoginRet);
    JniGetAndSetStringField(channel, "channel", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetStringField(channel_userid, "channelUserId", jclassResult, jobjectResult,
                            imLoginRet);
    JniGetAndSetStringField(channel_token, "channelToken", jclassResult, jobjectResult, imLoginRet);
    JniGetAndSetLongField(channel_expire, "channelTokenExpire", jclassResult, jobjectResult,
                          imLoginRet);

    // std::vector<IMSDKAuthSNSInfo> snsInfoVec;
    // std::vector<std::string> channel_permissions;
    
    iTOPLOGD("IMSDKLoginResult exchange end");
    return imLoginRet;
}  
