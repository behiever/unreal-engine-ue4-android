 
#include "../iTOP/Public/IMSDKExtendToolManager.h"    

static jclass s_IMSDKToolClass;
static jclass s_IMSDKTClass;
static jclass s_IMSDKAPKToolClass;

IMSDKExtendToolManager::IMSDKExtendToolManager() {
    m_instance = NULL;
    m_pVM = NULL;
}

IMSDKExtendToolManager::~IMSDKExtendToolManager() {

}

IMSDKExtendToolManager *IMSDKExtendToolManager::m_instance;


IMSDKExtendToolManager* IMSDKExtendToolManager::getInstance() {
    if (m_instance == NULL) {
        m_instance = new IMSDKExtendToolManager();
    }

    return m_instance;
}

void IMSDKExtendToolManager::init(JavaVM *pVM) {
    m_pVM = pVM;
    JNIEnv *env;
    m_pVM->AttachCurrentThread(&env, NULL);

    jclass clsTool = FAndroidApplication::FindJavaClass(IMSDK_TOOL_API_CLASSPATH);
    s_IMSDKToolClass = (jclass) env->NewGlobalRef(clsTool);

    jclass clsT = FAndroidApplication::FindJavaClass(IMSDK_T_API_CLASSPATH);
    s_IMSDKTClass = (jclass) env->NewGlobalRef(clsT);

    jclass clsApkTool = FAndroidApplication::FindJavaClass(IMSDK_APK_TOOL_API_CLASSPATH);
    s_IMSDKAPKToolClass =(jclass) env->NewGlobalRef(clsApkTool);
    
    env->DeleteLocalRef(clsTool);
    env->DeleteLocalRef(clsT);
    env->DeleteLocalRef(clsApkTool);
}

bool IMSDKExtendToolManager::isChannelInstalled(std::string channel) {
	JNIEnv *env;
	m_pVM->AttachCurrentThread(&env, NULL);

	jfieldID jActivityField = env->GetStaticFieldID(s_IMSDKTClass, "mGlobalActivityUpToDate", "Landroid/app/Activity;");
	jobject jActivityObj = env->GetStaticObjectField(s_IMSDKTClass, jActivityField);

	jmethodID jIsLoginMethod = env->GetStaticMethodID(s_IMSDKToolClass, "isAppInstalled", "(Landroid/content/Context;Ljava/lang/String;)Z");
	jstring jPackageName = env->NewStringUTF(channel.c_str());
	jboolean jret = env->CallStaticBooleanMethod(s_IMSDKToolClass, jIsLoginMethod, jActivityObj, jPackageName);
	env->DeleteLocalRef(jActivityObj);
	env->DeleteLocalRef(jPackageName);
	return jret;
}

std::string IMSDKExtendToolManager::jstring2str(JNIEnv *env, jstring jstr)
{
    jboolean * f = JNI_FALSE;
    if (jstr == NULL) {
        return "";
    }
    const char* string = env->GetStringUTFChars(jstr, f);
    if (string == NULL){
        return "";
    }
    std::string str(string);
    iTOPLOGD("jstring2str str is : %s", str.c_str());
    return str;
}

std::string IMSDKExtendToolManager::getPackageChannelId(std::string path){
    JNIEnv *env = FAndroidApplication::GetJavaEnv();
    jmethodID jGetPackageChannelId = env->GetStaticMethodID(s_IMSDKAPKToolClass, "getPackageChannelId", "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;");
    jfieldID jActivityField = env->GetStaticFieldID(s_IMSDKTClass, "mGlobalActivityUpToDate", "Landroid/app/Activity;");
    jobject jActivityObj = env->GetStaticObjectField(s_IMSDKTClass, jActivityField);
    jstring jPathName = env->NewStringUTF(path.c_str());
    jstring jChannelId = (jstring) env->CallStaticObjectMethod(s_IMSDKAPKToolClass, jGetPackageChannelId, jActivityObj, jPathName);
    std::string channelID = jstring2str(env,jChannelId);
    env->DeleteLocalRef(jPathName);
    env->DeleteLocalRef(jActivityObj);
    env->DeleteLocalRef(jChannelId);
    return channelID;
}
