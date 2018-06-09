//
// Created by Administrator on 2018/1/4.
//

#include "../iTOP/Public/IMSDKGameServiceManager.h"
#include "../iTOP/Public/IMSDKDefine.h"

static jclass  s_IMSDKGameServiceClass;

IMSDKGameServiceManager::IMSDKGameServiceManager() {
    m_pVM = NULL;
    m_pInst = NULL;
    m_pGameServiceListener = NULL;
    m_channel = "";
    listenerTag = -1;
    listenerMap = new std::map<int, const IMSDKGameServiceListener*>();
}

IMSDKGameServiceManager::~IMSDKGameServiceManager() {
    listenerMap->clear();
}

IMSDKGameServiceManager* IMSDKGameServiceManager::m_pInst;

IMSDKGameServiceManager* IMSDKGameServiceManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKGameServiceManager();
    }
    return m_pInst;
}

void IMSDKGameServiceManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_GAMESERVICE_API_CLASSPATH);
    s_IMSDKGameServiceClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
}
 
void IMSDKGameServiceManager::setGameServiceListener(const IMSDKGameServiceListener *listener) {
    if (listener == NULL) {
        iTOPLOGI("FriendListener is NULL %s", "");
        return;
    }
    m_pGameServiceListener = listener;
}

const IMSDKGameServiceListener* IMSDKGameServiceManager::getGameServiceListener() const {
    return m_pGameServiceListener;
}

bool IMSDKGameServiceManager::setChannel(const std::string channel) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKGameServiceManager::setChannel enter %s", channel.c_str());
    jmethodID setChannel = env->GetStaticMethodID(s_IMSDKGameServiceClass, "setChannel", "(Ljava/lang/String;)Z");
    jstring jChannel = env->NewStringUTF(channel.c_str());
    jboolean jret = env->CallStaticBooleanMethod(s_IMSDKGameServiceClass, setChannel, jChannel);
    m_channel = channel;
    env->DeleteLocalRef(jChannel);
    return jret;
}

const std::string IMSDKGameServiceManager::getChannel() {
    return m_channel;
}

void OnGameserviceResultParse(std::string result, int tag, ResultDelegate callback){
    iTOPLOGD("OnShareRawParse raw data result = %s", result.c_str());
    IMSDKResult imsdkResult = convertiTOPResult(result);;
    std::map<int, const IMSDKGameServiceListener*> listenerMap = IMSDKGameServiceManager::getInstance()->getListenerMap();
    if (listenerMap.size() > 0) {
        if (listenerMap.end() != listenerMap.find(tag)) {
            IMSDKGameServiceListener *imGameServiceListener = const_cast<IMSDKGameServiceListener *>(listenerMap.at(tag));
            listenerMap.erase(tag);
            imGameServiceListener->OnGameServiceNotify(imsdkResult);
        }
    }
}

void IMSDKGameServiceManager::setup() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jSetupMethod = env->GetStaticMethodID(s_IMSDKGameServiceClass, "setup", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jSetupMethod,jListener,NULL);
    env->DeleteLocalRef(jListener);
}

void IMSDKGameServiceManager::setScore(std::string board ,int score) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jSetScoreMethod = env->GetStaticMethodID(s_IMSDKGameServiceClass, "setScore", "(Ljava/lang/String;ILcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jBoard = env->NewStringUTF(board.c_str());
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jSetScoreMethod,  jBoard, score, jListener,NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jBoard);
}

void IMSDKGameServiceManager::showLeaderBoard(std::string board) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jShowLeaderBoard = env->GetStaticMethodID(s_IMSDKGameServiceClass, "showLeaderBoard", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jBoard = env->NewStringUTF(board.c_str());
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jShowLeaderBoard,jBoard,jListener,NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jBoard);
}

void IMSDKGameServiceManager::unlockAchieve(std::string achieve) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jUnlockAchieveMethod = env->GetStaticMethodID(s_IMSDKGameServiceClass, "unlockAchieve", "(Ljava/lang/String;Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jAchieve = env->NewStringUTF(achieve.c_str());
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jUnlockAchieveMethod, jAchieve, jListener,NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jAchieve);
}

void IMSDKGameServiceManager::increaseAchieve(std::string achieve,int step) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jIncreaseAchieveMethod = env->GetStaticMethodID(s_IMSDKGameServiceClass, "increaseAchieve", "(Ljava/lang/String;ILcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    jstring jAchieve = env->NewStringUTF(achieve.c_str());
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jIncreaseAchieveMethod, jAchieve,  step, jListener,NULL);
    env->DeleteLocalRef(jListener);
    env->DeleteLocalRef(jAchieve);
}

void IMSDKGameServiceManager::showAchievement() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    int tag = ++listenerTag;
    listenerMap->insert(std::make_pair(tag, m_pGameServiceListener));
    long resultPointer=0;
    jobject jListener = initListener(env, (long)(&OnGameserviceResultParse), resultPointer, tag);
    jmethodID jShowAchievementMethod = env->GetStaticMethodID(s_IMSDKGameServiceClass, "showAchievement", "(Lcom/tencent/imsdk/android/api/IMSDKResultListener;[Ljava/lang/Object;)V");
    env->CallStaticVoidMethod(s_IMSDKGameServiceClass, jShowAchievementMethod, jListener,NULL);
    env->DeleteLocalRef(jListener);
}

