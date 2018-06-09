
#ifndef IMSDK_ANDROID_IMSDKJNI_H
#define IMSDK_ANDROID_IMSDKJNI_H

 
#include "Runtime/ApplicationCore/Public/Android/AndroidApplication.h" 
#include "Runtime/Launch/Public/Android/AndroidJNI.h" 

/**
 * jni内存原则：重复使用的对象抽取成对象,管理好对象的释放
 * 1. jclass是通过主线程的classloader获取到,因此采用全局弱引用缓存,防止被回收采用局部变量hold的方式
 * 2. jni里new出来的对象采用局部变量缓存,注意delete
 * 3. methodid和filedid用当前线程的jnienv即可获取,因为是int值,采用全局变量缓存
 */

/**创建和删除变量的宏定义**/
#define NEW_GLOBAL_REF(v) (env)->NewGlobalRef(v)
#define DEL_GLOBAL_REF(v) (env)->DeleteGlobalRef( v)
#define NEW_LOCAL_REF(v) (env)->NewLocalRef(v)
#define DEL_LOCAL_REF(v) (env)->DeleteLocalRef( v)
#define NEW_WEAK_GLOBAL_REF(v) (env)->NewWeakGlobalRef(v)
#define DEL_WEAK_GLOBAL_REF(v) (env)->DeleteWeakGlobalRef(v)

/**查找并将类置为全局变量的宏定义**/
#define FIND_GLOBAL_CLASS(name) NEW_GLOBAL_REF((env)->FindClass(name))
#define FIND_WEAKGLOBAL_CLASS(name) NEW_WEAK_GLOBAL_REF((env)->FindClass(name))
 
/**通用对象的宏定义**/
#define OBJECT_SIG 	"Ljava/lang/Object;"
#define STRING_SIG 	"Ljava/lang/String;"
#define CLASS_SIG 	"Ljava/lang/Class;"
#define TYPE_SIG 	"Ljava/lang/reflect/Type;"
#define METHOD_SIG 	"Ljava/lang/reflect/Method;"
#define ACTIVITY_SIG "android/app/ActivityThread"

class IMSDKJni {
private:
	static IMSDKJni* m_pInst;
	IMSDKJni();
	virtual ~IMSDKJni();

public:
    static jclass holdWeakGlobalClass(JNIEnv *env, jclass  weak_clz,  const char* name);
	static JNIEnv *getJniEnv(); 

#ifdef ANDROID
public:
	void init(JavaVM* vm, void* reserved);
	static jobject getGlobalContext(JNIEnv *env);
#endif

};

#endif 


