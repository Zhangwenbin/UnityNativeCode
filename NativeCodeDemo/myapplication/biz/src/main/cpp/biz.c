#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include "xhook.h"

 float myAddFloatHook(float x,float y)
{
    __android_log_print(ANDROID_LOG_ERROR, "hook", "xxxxyyy");
    return x*y;
}

JNIEXPORT void JNICALL Java_com_qiyi_biz_BizNativeHandler_start(JNIEnv* env, jobject obj)
{
    (void)env;
    (void)obj;
    __android_log_print(ANDROID_LOG_ERROR, "hook", "hook start ");
   // xhook_register("^/system/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
  //  xhook_register("^/vendor/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
   int res= xhook_register(".*/libmathnativelib\\.so$", "myAddFloat", (float *)myAddFloatHook, NULL);

    if (res==0){
        __android_log_print(ANDROID_LOG_ERROR, "hook", "hook register success");
    }else{
        __android_log_print(ANDROID_LOG_ERROR, "hook", "hook register failed");
    }
    //just for testing
    //xhook_ignore(".*/liblog\\.so$", "__android_log_print"); //ignore __android_log_print in liblog.so
    //xhook_ignore(".*/libjavacore\\.so$", NULL); //ignore all hooks in libjavacore.so
}
