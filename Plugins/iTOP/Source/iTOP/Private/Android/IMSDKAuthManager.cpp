//
// Created by dandiliu on 17/9/28.
// 
#include "../iTOP/Public/IMSDKAuthManager.h"
#include "../iTOP/Public/IMSDKDefine.h"

static jclass s_IMSDKAuthClass;

static jobject initListener(JNIEnv *env, long metadataPointer, long resultPointer) {
	jclass jCls = FAndroidApplication::FindJavaClass("com/tencent/imsdk/cpphelper/IMSDKCppListener");
	jmethodID jInit = env->GetMethodID(jCls, "<init>", "(JJ)V");
	if (jInit == NULL) {
		return NULL;
	}
	jlong jMetadataPointer = (jlong)metadataPointer;
	jlong jResultPointer = (jlong)resultPointer;
	jobject jListener = env->NewObject(jCls, jInit, jMetadataPointer, jResultPointer);
    env->DeleteLocalRef(jCls);
	return jListener;
}

IMSDKAuthManager::IMSDKAuthManager() {
    m_authInst = NULL;
    m_pVM = NULL;
}

IMSDKAuthManager::~IMSDKAuthManager() {

}

IMSDKAuthManager* IMSDKAuthManager::m_authInst;

IMSDKAuthManager* IMSDKAuthManager::getInstance() {
    if (m_authInst == NULL){
        m_authInst = new IMSDKAuthManager();
    }
    return m_authInst;
}

void IMSDKAuthManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_AUTH_API_CLASSPATH);
    s_IMSDKAuthClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}

JavaVM* IMSDKAuthManager::getVM() {
    return m_pVM;
}

void IMSDKAuthManager::setVM(JavaVM *pVM) {
    m_pVM = pVM;
}

void OnAuthRawParse(std::string result, int tag, ResultDelegate callBack) {
	iTOPLOGD("OnAuthRawParse raw data result = %s", result.c_str());
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
	callBack(authResult);
}

void OnConnectRawParse(std::string result, int tag, ResultDelegate callBack){
	iTOPLOGD("OnConnectRawParse raw data result = %s", result.c_str());
	IMSDKAuthConnectResult connectResult = convertiTOPAuthConnectResult(result);
	callBack(connectResult);
}

void OnReConnectRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnReConnectRawParse raw data result = %s", result.c_str() );
	IMSDKResult imsdkResult = convertiTOPResult(result);
    callBack(imsdkResult);
}

void OnRestoreRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnRestoreRawParse raw data result = %s", result.c_str() );
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult);
}

void OnRecoverRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnRestoreRawParse raw data result = %s", result.c_str() );
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult); 
}

void OnDeleteAllAccountRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnDeleteAllAccountRawParse raw data result = %s", result.c_str() );
	IMSDKResult imsdkResult = convertiTOPResult(result); 
    callBack(imsdkResult);
}

void OnDeleteDeviceAccountRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnDeleteDeviceAccountRawParse raw data result = %s", result.c_str() );
	IMSDKResult imsdkResult = convertiTOPResult(result);
    callBack(imsdkResult);
}

void OnDisconnectRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnDisconnectRawParse raw data result = %s", result.c_str() );
	
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult);
}

void OnGetConncetInfo(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnGetConncetInfo raw data result = %s", result.c_str() );  
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult);
}

void OnGetMigrateCodeRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnGetMigrateCodeRawParse raw data result = %s", result.c_str() ); 
	IMSDKAuthMigrateResult migrateResult = convertiTOPAuthMigrateResult(result);
    callBack(migrateResult); 
}

void OnGetMigrateInfoRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnGetMigrateInfoRawParse raw data result = %s", result.c_str() );
	IMSDKAuthMigrateResult migrateResult = convertiTOPAuthMigrateResult(result);
    callBack(migrateResult);  
}

void OnMigrateRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnMigrateRawParse raw data result = %s", result.c_str() );
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult); 
}

void OnSignOutRawParse(std::string result, int tag, ResultDelegate callBack){
    iTOPLOGD("OnSignOutRawParse raw data result = %s", result.c_str() ); 
	IMSDKAuthResult authResult = convertiTOPAuthResult(result);
    callBack(authResult);
} 
 
void IMSDKAuthManager::auth(IMSDKAuthCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnAuthRawParse), (long) callback);
    jmethodID auth = env->GetStaticMethodID(s_IMSDKAuthClass, "auth", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKAuthClass,auth, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::connect(std::string channel, IMSDKConnectCallBack callback,
                               const std::vector<std::string> &permissions,
                               std::string confirmCode) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnConnectRawParse), (long) callback);
    jmethodID connect = env->GetStaticMethodID(s_IMSDKAuthClass, "connect", "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jstring jConfirmCode = env->NewStringUTF(confirmCode.c_str());

    jclass jStringClass = env->FindClass("java/lang/Object");
    jobjectArray jArray = env->NewObjectArray((jsize)permissions.size(), jStringClass, 0);
    for(unsigned int i=0; i < permissions.size(); i++ )
    {
        jstring jPermission = (env)->NewStringUTF(permissions.at(i).c_str());
        (env)->SetObjectArrayElement(jArray, i, jPermission);
        env -> DeleteLocalRef(jPermission);
    } 
    env->CallStaticVoidMethod(s_IMSDKAuthClass, connect, jChannel, jConfirmCode, jListener, jArray);
    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jConfirmCode);
    env->DeleteLocalRef(jArray);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jStringClass);
}

void IMSDKAuthManager::reconnect(IMSDKCallBack callback, std::string confirmCode) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnReConnectRawParse),  (long) callback);
    jmethodID reconnect = env->GetStaticMethodID(s_IMSDKAuthClass, "reconnect", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jConfirmCode = env->NewStringUTF(confirmCode.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, reconnect, jConfirmCode, jListener, NULL);
    env->DeleteLocalRef(jConfirmCode);
    env->DeleteLocalRef(jListener);
}


void IMSDKAuthManager::restore(IMSDKAuthCallBack callback, std::string confirmCode) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnRestoreRawParse), (long) callback);
    jmethodID restore = env->GetStaticMethodID(s_IMSDKAuthClass, "restore", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jConfirmCode = env->NewStringUTF(confirmCode.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, restore, jConfirmCode, jListener, NULL);
    env->DeleteLocalRef(jConfirmCode);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::deleteAllAccount(IMSDKCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnDeleteAllAccountRawParse), (long) callback);
    jmethodID deleteAllAccount = env->GetStaticMethodID(s_IMSDKAuthClass, "deleteAllAccount", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKAuthClass, deleteAllAccount, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::deleteDeviceAccount(IMSDKCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnDeleteDeviceAccountRawParse), (long) callback);
    jmethodID deleteDeviceAccount = env->GetStaticMethodID(s_IMSDKAuthClass, "deleteDeviceAccount", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKAuthClass, deleteDeviceAccount, jListener);
    env->DeleteLocalRef(jListener);
}


void IMSDKAuthManager::disconnect(std::string channel, IMSDKCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnDisconnectRawParse), (long) callback);
    jmethodID disconnect = env->GetStaticMethodID(s_IMSDKAuthClass, "disconnect", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, disconnect, jChannel, jListener);
    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::recover(std::string channel, IMSDKAuthCallBack callback,
                               const std::vector<std::string> &permissions) {

    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnRecoverRawParse), (long) callback);
    jmethodID recover = env->GetStaticMethodID(s_IMSDKAuthClass, "recover", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, recover, jChannel, jListener);
    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jListener);
}


void IMSDKAuthManager::getConncetInfo(IMSDKAuthCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnGetConncetInfo), (long) callback);
    jmethodID getConnectInfo = env->GetStaticMethodID(s_IMSDKAuthClass, "getConnectInfo", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKAuthClass, getConnectInfo, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::getMigrateCode(IMSDKMigrateCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnGetMigrateCodeRawParse),  (long) callback);
    jmethodID getMigrateCode = env->GetStaticMethodID(s_IMSDKAuthClass, "getMigrateCode", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    env->CallStaticVoidMethod(s_IMSDKAuthClass, getMigrateCode, jListener);
    env->DeleteLocalRef(jListener);
}

void IMSDKAuthManager::getMigrateInfo(IMSDKMigrateCallBack callback, std::string code) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnGetMigrateInfoRawParse), (long) callback);
    jmethodID getMigrateInfo = env->GetStaticMethodID(s_IMSDKAuthClass, "getMigrateInfo", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jCode = env->NewStringUTF(code.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, getMigrateInfo, jCode, jListener);
    env->DeleteLocalRef(jCode);
    env->DeleteLocalRef(jListener);
}


void IMSDKAuthManager::migrate(IMSDKAuthCallBack callback, std::string code) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnMigrateRawParse), (long) callback);
    jmethodID migrate = env->GetStaticMethodID(s_IMSDKAuthClass, "migrate", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jCode = env->NewStringUTF(code.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, migrate, jCode, jListener);
    env->DeleteLocalRef(jCode);
    env->DeleteLocalRef(jListener);
}


void IMSDKAuthManager::signOut(std::string channel, IMSDKCallBack callback) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jobject jListener = initListener(env, (long)(&OnSignOutRawParse), (long) callback);
    jmethodID signOut = env->GetStaticMethodID(s_IMSDKAuthClass, "signOut", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;)V");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    env->CallStaticVoidMethod(s_IMSDKAuthClass, signOut, jChannel, jListener);
    env->DeleteLocalRef(jChannel);
    env->DeleteLocalRef(jListener);
}


IMSDKAuthResult IMSDKAuthManager::getAuthResult() {
    iTOPLOGD("getAuthResult %s" ,"");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKAuthManager::getAuthResult enter %s", "");
    jmethodID jGetAuthResultMethod = env->GetStaticMethodID(s_IMSDKAuthClass, "getAuthResult", "()Lcom/tencent/imsdk/android/api/auth/IMSDKAuthResult;");
    IMSDKAuthResult imAuthRet;
    if (jGetAuthResultMethod != NULL) {
        jobject jauthResultOjbect = env->CallStaticObjectMethod(s_IMSDKAuthClass, jGetAuthResultMethod);
        if (jauthResultOjbect != NULL) {
            jclass jauthResultClss = env->GetObjectClass(jauthResultOjbect);
            if (jauthResultClss != NULL) {
                imAuthRet = getAuthResultFromJava(env, jauthResultClss, jauthResultOjbect);
            }
        }
    }
    return imAuthRet;
}

//从Java侧获取到的AuthResult转换为C++可用，并一一对应的AuthResult
IMSDKAuthResult IMSDKAuthManager::getAuthResultFromJava(JNIEnv * env, jclass jclassResult, jobject jobjectResult) {
    IMSDKAuthResult imAuthRet;
    if (env == NULL || jclassResult == NULL || jobjectResult == NULL) {
        return imAuthRet;
    }
    JniGetAndSetIntField(imsdkRetCode, "imsdkRetCode", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetIntField(thirdRetCode, "thirdRetCode", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(imsdkRetMsg, "imsdkRetMsg", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(thirdRetMsg, "thirdRetMsg", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(retExtraJson, "retExtraJson", jclassResult, jobjectResult, imAuthRet);

    JniGetAndSetIntField(channelId, "channelId", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetIntField(gameId, "gameId", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(openId, "openId", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(innerToken, "innerToken", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetStringField(deviceId, "deviceId", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetIntField(isFirstLogin, "isFirstLogin", jclassResult, jobjectResult, imAuthRet);
    JniGetAndSetLongField(tokenExpireTime, "tokenExpireTime", jclassResult, jobjectResult, imAuthRet);

    iTOPLOGD("friendInfoList exchange start %s", "");
    jfieldID listId = env->GetFieldID(jclassResult, "snsInfoList", "Ljava/util/List;");
    if (listId != NULL) {
        jobject jfriendInfoListObj = env->GetObjectField(jobjectResult, listId);
        if (jfriendInfoListObj != NULL) {
            jclass jfriendInfoListClass = env->GetObjectClass(jfriendInfoListObj);
            if (jfriendInfoListClass != NULL) {
                jmethodID listSizeM = env->GetMethodID(jfriendInfoListClass, "size", "()I");
                jmethodID listGetM = env->GetMethodID(jfriendInfoListClass, "get", "(I)Ljava/lang/Object;");
                int len = (int) env->CallIntMethod(jfriendInfoListObj, listSizeM);

                iTOPLOGD("friendInfoList exchanging ... %d", len);
                for (int i = 0; i < len; i++) {
                    jobject jfriendInfoObj = env->CallObjectMethod(jfriendInfoListObj, listGetM, i);
                    jclass jfriendInfoClass = FAndroidApplication::FindJavaClass("com/tencent/imsdk/android/api/common/IMSDKFriendInfo");
                    IMSDKAuthSNSInfo authSNSInfo;
                    JniGetAndSetStringField(openId, "openId", jfriendInfoClass, jfriendInfoObj, authSNSInfo);
                    JniGetAndSetIntField(channelId, "channelId", jfriendInfoClass, jfriendInfoObj, authSNSInfo);
                    JniGetAndSetStringField(userName, "userName", jfriendInfoClass, jfriendInfoObj, authSNSInfo);
                    JniGetAndSetIntField(gender, "gender", jfriendInfoClass, jfriendInfoObj, authSNSInfo);
                    JniGetAndSetStringField(pictureUrl, "pictureUrl", jfriendInfoClass, jfriendInfoObj, authSNSInfo);
                    imAuthRet.snsInfoVec.push_back(authSNSInfo);
                }
            }
        }
    }
    iTOPLOGD("friendInfoList exchange end %s", "");
    return imAuthRet;
}



