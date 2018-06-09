
#include "../iTOP/Public/IMSDKJni.h"

IMSDKJni::IMSDKJni() {
   
}

IMSDKJni::~IMSDKJni() {
    
}

/**
 * 获取当前线程的jnienv
 * @return
 */
JNIEnv *IMSDKJni::getJniEnv() {
    JNIEnv *env = FAndroidApplication::GetJavaEnv();
    return env;
}

/**
 * 该方法的作用在于避免软全局引用被GC回收导致空指针异常，采用局部变量hold住软引用避免回收
 * @param env  当前线程的jni环境
 * @param weak_clz  软全局引用
 * @param local_clz  局部引用
 * @return
 */
jclass IMSDKJni::holdWeakGlobalClass(JNIEnv *env, jclass weak_clz, const char *name) {
    jclass localClazz;
    while (weak_clz == NULL ||
           (localClazz = (jclass) NEW_LOCAL_REF(weak_clz)) == NULL) {
        weak_clz = (jclass) FIND_WEAKGLOBAL_CLASS(name);
    }
    return localClazz;
}
 
static jclass s_ActivityThread;
/**
 * 从activity实例对象获取applicationcontext
 * @param env
 * @return
 */
jobject IMSDKJni::getGlobalContext(JNIEnv *env)
{
    jclass localRef = IMSDKJni::holdWeakGlobalClass(env,s_ActivityThread,ACTIVITY_SIG);
    jmethodID currentActivityThread = env->GetStaticMethodID(s_ActivityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject at = env->CallStaticObjectMethod(s_ActivityThread, currentActivityThread);
    //获取Application，也就是全局的Context
    jmethodID getApplication = env->GetMethodID(s_ActivityThread, "getApplication", "()Landroid/app/Application;");
    jobject context = env->CallObjectMethod(at, getApplication);
    DEL_LOCAL_REF(localRef);
    return context;
}
