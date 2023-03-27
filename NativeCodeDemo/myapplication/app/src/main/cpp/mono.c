#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include "xh_log.h"
#include "dlfcn.h"
#include "xhook.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    MONO_IMAGE_OK,
    MONO_IMAGE_ERROR_ERRNO,
    MONO_IMAGE_MISSING_ASSEMBLYREF,
    MONO_IMAGE_IMAGE_INVALID
} MonoImageOpenStatus;
typedef uint32_t       guint32;
typedef int32_t        gboolean;
 typedef void* (*mono_image_open_from_data_with_name_type)(char *data, guint32 data_len, gboolean need_copy, MonoImageOpenStatus *status, gboolean refonly, const char *name);
mono_image_open_from_data_with_name_type orign_mono_image_open_from_data_with_name = NULL;
char updated_assembly_csharp_path[260] = {0};

typedef float (*add_type)(float x,float y);
add_type orign_add = NULL;

float newAdd(float x,float y){
    __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hooknewadd to xy");
    return x*y;
}

void *hook_mono_image_open_from_data_with_name(char *data, guint32 data_len, gboolean need_copy, MonoImageOpenStatus *status, gboolean refonly, const char *name)
{
    __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hook__mono_image_open_from_data_with_name");
    if (orign_mono_image_open_from_data_with_name == NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "orign_mono_image_open_from_data_with_name is null");
        return NULL;
    }
    void *ret = NULL;
    __android_log_print(ANDROID_LOG_ERROR, "hotupdate c ", "orign name is %s", name);

	char* file_name = strrchr(name, '/');
	char file_full_name[260] = {0};
	strcpy(file_full_name, updated_assembly_csharp_path);
	strncat(file_full_name, file_name, strlen(file_name));
    __android_log_print(ANDROID_LOG_ERROR, "hotupdate c ", "update name is %s", file_full_name);
	
    // if (updated_assembly_csharp_path[0] != 0 && strstr(name, assembly_csharp_dll) != NULL)
    // {
    FILE* pFile = NULL;
    pFile = fopen(file_full_name, "rb");
    if (pFile != NULL)
    {
    	fseek(pFile, 0L, SEEK_END);
        unsigned int sz = ftell(pFile);
		fseek(pFile, 0L, SEEK_SET);
		char *buffer = (char *)malloc(sz);
		if (buffer != NULL)
		{
			unsigned int result = fread(buffer, 1, sz, pFile);
			if (result == sz)
			{
				ret = orign_mono_image_open_from_data_with_name(buffer, sz, need_copy, status, refonly, file_full_name);
				__android_log_print(ANDROID_LOG_ERROR, "hotupdate", "update dll %s", file_full_name);
			}
			else
			{
				__android_log_print(ANDROID_LOG_ERROR, "hotupdate", "failed to fread");
			}
			free(buffer);
        }
        else
        {
        	__android_log_print(ANDROID_LOG_ERROR, "hotupdate", "failed to malloc");
        }
        fclose(pFile);
    }
    else 
    {
    	ret = orign_mono_image_open_from_data_with_name(data, data_len, need_copy, status, refonly, name);
		__android_log_print(ANDROID_LOG_ERROR, "hotupdate", "orign dll %s", name);
		// __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "cant open file %s", updated_assembly_csharp_path);
	}
	// }
    // else
    // {
    //     ret = orign_mono_image_open_from_data_with_name(data, data_len, need_copy, status, refonly, name);
    //     __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "orign dll %s", name);
    // }
    return ret;
}

JNIEXPORT void JNICALL Java_com_DefaultCompany_ScriptsBuildOnlyTest_HotUpdate_SetHotUpdatePath(JNIEnv* env, jobject obj, jstring path)
{
    (void)env;
    (void)obj;
    const char *pathChar = (*env)->GetStringUTFChars(env, path, JNI_FALSE);
    strncpy(updated_assembly_csharp_path, pathChar, strlen(pathChar));
    __android_log_print(ANDROID_LOG_ERROR, "hotupdate c", "set dll path %s", updated_assembly_csharp_path);
    (*env)->ReleaseStringUTFChars(env, path, pathChar);
}


JNIEXPORT void JNICALL Java_com_DefaultCompany_ScriptsBuildOnlyTest_HotUpdate_StartHook(JNIEnv* env, jobject obj)
{
    (void)env;
    (void)obj;

    __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "start hook");
    if (0 == xhook_register(".*/libmathnativelib\\.so$", "myNativeAdd", newAdd,  (float *)&orign_add))
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hook register success");
    }
    else 
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hook register failure");
    }
    if (0 == xhook_refresh(0))
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hook refresh success");
    }
    else 
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "hook refresh failure");
    }
    if (orign_add != NULL)
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "orign mono image open is not null");
    }
    else 
    {
        __android_log_print(ANDROID_LOG_ERROR, "hotupdate", "orign mono image open is null");
    }
}



#ifdef __cplusplus
}
#endif
