//
// Created by dandiliu on 17/9/28.
//
  
#include "../iTOP/Public/IMSDKStatManager.h"

static jclass s_IMSDKStatClass;

IMSDKStatManager::IMSDKStatManager() {
    m_pVM = NULL;
    m_pInst = NULL;
}

IMSDKStatManager::~IMSDKStatManager() {

}

IMSDKStatManager* IMSDKStatManager::m_pInst;
IMSDKStatManager* IMSDKStatManager::getInstance() {
    if (m_pInst == NULL){
        m_pInst = new IMSDKStatManager();
    }
    return m_pInst;
}

void IMSDKStatManager::init(JavaVM *pVM) {
    iTOPLOGD("IMSDKStatManager init start ");
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass cls = FAndroidApplication::FindJavaClass(IMSDK_STAT_API_CLASSPATH);
    s_IMSDKStatClass = (jclass) env->NewGlobalRef(cls);
    env->DeleteLocalRef(cls);
    iTOPLOGD("IMSDKStatManager init end ");
}

JavaVM* IMSDKStatManager::getVM() {
    return m_pVM;
}

void IMSDKStatManager::setVM(JavaVM *pVM) {
    m_pVM = pVM;
}


void IMSDKStatManager::clearFilter() {
    iTOPLOGD("IMSDKStatManager::clearFilter start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    iTOPLOGD("IMSDKStatManager::get clearFilter method start");
    jmethodID jClearMethod = env->GetStaticMethodID(s_IMSDKStatClass, "clearFilter", "()V");
    iTOPLOGD("IMSDKStatManager::call clearFilter start");
    env->CallStaticVoidMethod(s_IMSDKStatClass, jClearMethod);
    iTOPLOGD("IMSDKStatManager::clearFilter end ");
}

const std::vector<std::string> IMSDKStatManager::getChannelFilter() {
    iTOPLOGD("IMSDKStatManager::getChannelFilter start");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass jArrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID jInitMethod = env->GetMethodID(jArrayListClass, "<init>", "()V");
    jmethodID jSizeMethod = env->GetMethodID(jArrayListClass, "size", "()I");
    jmethodID jAddMethod = env->GetMethodID(jArrayListClass, "add","(Ljava/lang/Object;)Z");
    jmethodID jGetMethod = env->GetMethodID(jArrayListClass,"get","(I)Ljava/lang/Object;");
    jmethodID jgetChannelFilter = env->GetStaticMethodID(s_IMSDKStatClass, "getFilter", "()Ljava/util/List;");
    iTOPLOGD("IMSDKStatManager::getChannelFilter instance");
    jobject jChannelFilter = env->NewObject(jArrayListClass, jInitMethod);

    jChannelFilter = (jobject) env->CallStaticObjectMethod(s_IMSDKStatClass, jgetChannelFilter);
//    jobject jChannelFilterList = (jobject) env->CallStaticObjectMethod(s_IMSDKStatClass, jgetChannelFilter);
    iTOPLOGD("IMSDKStatManager::getChannelFilter instance end ");
    std::vector<std::string> listFilter;
    if (jChannelFilter == NULL){
        return listFilter;
    }
    int len = env->CallIntMethod(jChannelFilter,jSizeMethod);
    for (int i = 0; i < len; i++) {
        iTOPLOGD("IMSDKStatManager::getChannelFilter 2.1 ");
        jboolean isCopy;
        const char* cChannel = env->GetStringUTFChars((jstring)env->CallObjectMethod(jChannelFilter, jGetMethod, i), &isCopy);
        iTOPLOGD("IMSDKStatManager::getStatMID mid: %s", cChannel);
        listFilter.push_back(cChannel);
        iTOPLOGD("IMSDKStatManager::getChannelFilter 2.2 ");
        //env->DeleteLocalRef(jChannel);
    }
    iTOPLOGD("IMSDKStatManager::getChannelFilter 3.1 ");
    env->DeleteLocalRef(jChannelFilter);
    env->DeleteLocalRef(jArrayListClass);
    iTOPLOGD("IMSDKStatManager::getChannelFilter end ");
    return listFilter;
}
 

std::string IMSDKStatManager::getStatIMEI() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jGetStatIMEI = env->GetStaticMethodID(s_IMSDKStatClass, "getStatIMEI", "()Ljava/lang/String;");
    jstring jIMEI = (jstring) env->CallStaticObjectMethod(s_IMSDKStatClass, jGetStatIMEI);
    jboolean isCopy;
    const char* cIMEI = env->GetStringUTFChars(jIMEI, &isCopy);
    std::string imei = cIMEI;
    iTOPLOGD("IMSDKStatManager::getStatIMEI imei: %s", cIMEI);
    env->DeleteLocalRef(jIMEI);
    iTOPLOGD("IMSDKStatManager::getStatIMEI end ");
    return imei;
}

std::string IMSDKStatManager::getStatMID() {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jGetStatMID = env->GetStaticMethodID(s_IMSDKStatClass, "getStatMID", "()Ljava/lang/String;");
    jstring jMID = (jstring) env->CallStaticObjectMethod(s_IMSDKStatClass, jGetStatMID);
    jboolean isCopy;
    const char* cMID = env->GetStringUTFChars(jMID, &isCopy);
    std::string mid = cMID;
    iTOPLOGD("IMSDKStatManager::getStatMID mid: %s", cMID);
    env->DeleteLocalRef(jMID);
    iTOPLOGD("IMSDKStatManager::getStatMID end ");
    return mid;
}

void IMSDKStatManager::reportAutoExceptionReport(bool flag) {
    iTOPLOGD("IMSDKStatManager::reportAutoExceptionReport start %s","");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jReportException = env->GetStaticMethodID(s_IMSDKStatClass, "reportException", "(Z)V");
    env->CallStaticVoidMethod(s_IMSDKStatClass, jReportException, flag);
    iTOPLOGD("IMSDKStatManager::reportAutoExceptionReport end ");
}

void IMSDKStatManager::reportCrash(bool flag) {
    iTOPLOGD("IMSDKStatManager::reportCrash start");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jReportEventMethod = env->GetStaticMethodID(s_IMSDKStatClass, "reportCrash", "(Z)V");
    env->CallStaticVoidMethod(s_IMSDKStatClass, jReportEventMethod, flag);
    iTOPLOGD("IMSDKStatManager::reportCrash end ");
}

void IMSDKStatManager::reportEvent(std::string event,
                                   std::map<std::string, std::string> params,
                                   bool isRealTime) {
    iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName,std::vector<KVPair> cEventList, bool isRealTime) start ");
    JNIEnv *env;
    if(params.empty() || params.size()==0) return;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID method = env->GetStaticMethodID(s_IMSDKStatClass, "reportEvent", "(Ljava/lang/String;Ljava/util/Map;Z)V");
    jstring jName = env->NewStringUTF(event.c_str());
    jclass jHashMapClass = env->FindClass("java/util/HashMap");
    jmethodID jInitMethod = env->GetMethodID(jHashMapClass, "<init>", "()V");
    jmethodID jPutMethod = env->GetMethodID(jHashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jobject jparams = env->NewObject(jHashMapClass, jInitMethod);

    std::map<std::string, std::string>::iterator it;
    for (it = params.begin(); it != params.end(); ++it) {
        jstring jKey = env->NewStringUTF((const char *) it->first.c_str());
        jstring jValue = env->NewStringUTF((const char *) it->second.c_str());
        env->CallObjectMethod(jparams, jPutMethod, jKey, jValue);
        env->DeleteLocalRef(jKey);
        env->DeleteLocalRef(jValue);
    }
    env->CallStaticVoidMethod(s_IMSDKStatClass, method, jName, jparams, isRealTime);
    env->DeleteLocalRef(jHashMapClass);
    env->DeleteLocalRef(jName);
    env->DeleteLocalRef(jparams);
    iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName,std::vector<KVPair> cEventList, bool isRealTime) end ");
}

void IMSDKStatManager::reportEvent(std::string event, std::string eventBody, bool isRealTime) {
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    if(!eventBody.empty()) {
        iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName,std::string eventBody, bool isRealTime) start ");
        jmethodID jReportEventMethod = env->GetStaticMethodID(s_IMSDKStatClass, "reportEvent", "(Ljava/lang/String;ZLjava/lang/String;)V");
        jstring jEventName = env->NewStringUTF(event.c_str());
        jstring jEventBody = env->NewStringUTF(eventBody.c_str());
        env->CallStaticVoidMethod(s_IMSDKStatClass, jReportEventMethod, jEventName, isRealTime, jEventBody);
        env->DeleteLocalRef(jEventName);
        env->DeleteLocalRef(jEventBody);
        iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName,std::string eventBody, bool isRealTime) end ");
    } else {
        iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName, bool isRealTime) start ");
        jmethodID jReportEventMethod = env->GetStaticMethodID(s_IMSDKStatClass, "reportEvent", "(Ljava/lang/String;Z)V");
        jstring jEventName = env->NewStringUTF(event.c_str());
        env->CallStaticVoidMethod(s_IMSDKStatClass, jReportEventMethod, jEventName, isRealTime);
        env->DeleteLocalRef(jEventName);
        iTOPLOGD("IMSDKStatManager::reportEvent(std::string eventName, bool isRealTime) end ");
    }
}

void IMSDKStatManager::reportPurchase(std::string purchaseName,
                                      std::string currencyCode,
                                      std::string expense,
                                      bool isRealTime) {
    iTOPLOGD("IMSDKStatManager::reportPurchase(std::string purchaseName,std::string currencyCode, std::string expense, bool isRealTime) start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jReportEventMethod = env->GetStaticMethodID(s_IMSDKStatClass, "reportPurchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    jstring jPurchaseName = env->NewStringUTF(purchaseName.c_str());
    jstring jCurrencyCode = env->NewStringUTF(currencyCode.c_str());
    jstring jExpense = env->NewStringUTF(expense.c_str());
    env->CallStaticVoidMethod(s_IMSDKStatClass,
                              jReportEventMethod,
                              jPurchaseName,
                              jCurrencyCode,
                              jExpense,
                              isRealTime);
    env->DeleteLocalRef(jPurchaseName);
    env->DeleteLocalRef(jCurrencyCode);
    env->DeleteLocalRef(jExpense);
    iTOPLOGD("IMSDKStatManager::reportPurchase(std::string purchaseName,std::string currencyCode, std::string expense, bool isRealTime) end ");
}

void IMSDKStatManager::setChannelFilter(const std::vector<std::string> filter) {
    iTOPLOGD("IMSDKStatManager::setChannelFilter start ");
    JNIEnv * env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jclass jArrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID jInitMethod = env->GetMethodID(jArrayListClass, "<init>", "()V");
    jmethodID jSizeMethod = env->GetMethodID(jArrayListClass, "size", "()I");
    jmethodID jAddMethod = env->GetMethodID(jArrayListClass, "add",
                                            "(Ljava/lang/Object;)Z");
    iTOPLOGD("IMSDKStatManager::setChannelFilter 1 ");
    jobject jChannelList = env->NewObject(jArrayListClass, jInitMethod);
    iTOPLOGD("IMSDKStatManager::setChannelFilter 2 ");
    for (int i = 0; i < filter.size(); i++) {
        iTOPLOGD("IMSDKStatManager::setChannelFilter 2.1 ");
        jstring jAddr = env->NewStringUTF(
                (const char *) filter.at(i).c_str());
        env->CallBooleanMethod(jChannelList, jAddMethod, jAddr);
        iTOPLOGD("IMSDKStatManager::setChannelFilter 2.2 ");
        env->DeleteLocalRef(jAddr);
    }
    iTOPLOGD("IMSDKStatManager::setChannelFilter 3 ");
    jmethodID jmsetChannelFilter = env->GetStaticMethodID(s_IMSDKStatClass, "setFilter", "(Ljava/util/List;)V");
    env->CallStaticVoidMethod(s_IMSDKStatClass, jmsetChannelFilter, jChannelList);
    iTOPLOGD("IMSDKStatManager::setChannelFilter 4 ");
    env->DeleteLocalRef(jChannelList);
    env->DeleteLocalRef(jArrayListClass);
    iTOPLOGD("IMSDKStatManager::setChannelFilter end ");
}

void IMSDKStatManager::speedTest(std::map<std::string, int> hostMap) {

}

void IMSDKStatManager::speedTest(std::string *domainList) {

}

void IMSDKStatManager::trackEventBegin(std::string event, std::string eventBody) {
    iTOPLOGD("IMSDKStatManager::trackEventBegin start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jTrackEventBegin = env->GetStaticMethodID(s_IMSDKStatClass, "trackEventBegin", "(Ljava/lang/String;Ljava/lang/String;)V");
    jstring jEventName = env->NewStringUTF(event.c_str());
    jstring jEventBody = env->NewStringUTF(eventBody.c_str());
    env->CallStaticVoidMethod(s_IMSDKStatClass, jTrackEventBegin, jEventName, jEventBody);
    env->DeleteLocalRef(jEventName);
    env->DeleteLocalRef(jEventBody);
    iTOPLOGD("IMSDKStatManager::trackEventBegin end ");
}

void IMSDKStatManager::trackEventEnd(std::string event, std::string eventBody) {
    iTOPLOGD("IMSDKStatManager::trackEventEnd start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jTrackEventEnd = env->GetStaticMethodID(s_IMSDKStatClass,
                                                          "trackEventEnd", "(Ljava/lang/String;Ljava/lang/String;)V");
    jstring jEventName = env->NewStringUTF(event.c_str());
    jstring jEventBody = env->NewStringUTF(eventBody.c_str());
    env->CallStaticVoidMethod(s_IMSDKStatClass, jTrackEventEnd, jEventName, jEventBody);
    env->DeleteLocalRef(jEventName);
    env->DeleteLocalRef(jEventBody);
    iTOPLOGD("IMSDKStatManager::trackEventEnd end ");
}


void IMSDKStatManager::trackPageBegin(std::string pageName) {
    iTOPLOGD("IMSDKStatManager::trackPageBegin start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jTrackPageBegin = env->GetStaticMethodID(s_IMSDKStatClass, "trackPageBegin", "(Ljava/lang/String;)V");
    jstring jPageName = env->NewStringUTF(pageName.c_str());
    env->CallStaticVoidMethod(s_IMSDKStatClass, jTrackPageBegin, jPageName);
    env->DeleteLocalRef(jPageName);
    iTOPLOGD("IMSDKStatManager::trackPageBegin end ");
}

void IMSDKStatManager::trackPageEnd(std::string pageName) {
    iTOPLOGD("IMSDKStatManager::trackPageEnd start ");
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);
    jmethodID jTrackPageEnd = env->GetStaticMethodID(s_IMSDKStatClass, "trackPageEnd", "(Ljava/lang/String;)V");
    jstring jPageName = env->NewStringUTF(pageName.c_str());
    env->CallStaticVoidMethod(s_IMSDKStatClass, jTrackPageEnd, jPageName);
    env->DeleteLocalRef(jPageName);
    iTOPLOGD("IMSDKStatManager::trackPageEnd end ");
}


