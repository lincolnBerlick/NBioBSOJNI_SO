/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "NBioAPI.h"
/* Header for class NBioBSPJNI */

#ifndef _Included_NBioBSPJNI
#define _Included_NBioBSPJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     NBioBSPJNI
 * Method:    sayHello
 * Signature: ()V
 */


JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeOpenDevice
    (JNIEnv *env, jobject thisObj);

JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeCapture
    (JNIEnv *jenv,jobject thisObj, jint purpose,jobject fir_handle, jint timeout, jobject fir_handleaudit, jobject winoption);

JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_TesteObject
    (JNIEnv *env, jobject thisObj, jobject  b);

JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerify
    (JNIEnv *env,jobject thisObj, jobject INPUT_FIR, jobject result, jobject PAY_LOAD);

JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeCloseDevice
    (JNIEnv *env, jobject thisObj);

JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerifyMatch
  (JNIEnv *env, jobject thisObj, jobject  FIR_HANDLE1, jobject FIRHANDLE2, jobject booleano, jobject PAY_LOAD);

//indexsearch
 JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeInitIndexsearch  (JNIEnv *env,jobject thisObj) ;



#ifdef __cplusplus
}
#endif
#endif
