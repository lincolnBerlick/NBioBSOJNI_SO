// Save as "HelloJNI.c"

/*
 * Class:     NBioBSPJNI
 * Method:    JNI
 * Author:    Lincoln Berlick
 *
 */


#include <iostream>
#include <string>
#include <jni.h>
#include "NBioBSPJNI.h"   // Generated
#include "NBioAPI.h"
#include <cstring>

using namespace std;



NBioAPI_HANDLE m_hNBioBSP;

bool isOpen = false;


    void IniciarSDK(){

        if(!isOpen){
            NBioAPI_Init(&m_hNBioBSP);
            cout << "open" << endl;
            isOpen = true;
        }

    }

NBioAPI_RETURN MyCaptureCallback(NBioAPI_WINDOW_CALLBACK_PARAM_PTR_0 pCallbackParam, NBioAPI_VOID_PTR pUserParam)
{

    return NBioAPIERROR_NONE;
}


JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeOpenDevice(JNIEnv *env, jobject thisObj) {

    IniciarSDK();

    NBioAPI_RETURN nRet;
    NBioAPI_DEVICE_ID deviceID = NBioAPI_GetOpenedDeviceID(m_hNBioBSP); //pega o id do dispositivo

    if(NBioAPI_DEVICE_ID_NONE != deviceID){
        NBioAPI_CloseDevice(m_hNBioBSP,deviceID);
    }

    nRet = NBioAPI_OpenDevice(m_hNBioBSP,NBioAPI_DEVICE_ID_AUTO);
    if(NBioAPIERROR_NONE == nRet){

        //nRet = NBioAPI_GetDeviceInfo(m_hNBioBSP, deviceID, 0, &m_hNBioBSP);
    }
    return nRet;
}



JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_TesteObject
  (JNIEnv *env, jobject thisObj, jobject iLevel) {
    jfieldID fid; /* store the field ID */
    jobject i;

    /* Get a reference to obj's class */
    //jclass thisClass = env->GetObjectClass(thisObj);
    jclass thisClass = env->FindClass("NBioBSPJNI/NBioBSPJNI$Items");

    jfieldID field = env->GetFieldID(thisClass, "idade","I"); // Type int

    if (NULL == field) return;

    //get int value given by FieldID
    int number = env->GetIntField(iLevel, field);

    jfieldID field2 = env->GetFieldID(thisClass, "nome", "Ljava/lang/String;");

    jstring nome = (jstring) env->GetObjectField(iLevel, field2);

    const char *nativeFileString = env->GetStringUTFChars(nome, NULL);

   cout << "capturado " << number << endl;
   cout << "capturado " << nativeFileString << endl;

   env->SetIntField (iLevel,field, 5);


   return;


  }



JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeCapture
  (JNIEnv *env, jobject thisObj,jobject fir_handle) {



    NBioAPI_WINDOW_OPTION winOption;
    NBioAPI_FIR_HANDLE hCapturedFIR1 = NBioAPI_INVALID_HANDLE;
    NBioAPI_RETURN nRet;



    nRet = NBioAPI_Capture(m_hNBioBSP, NBioAPI_FIR_PURPOSE_VERIFY, &hCapturedFIR1, -1, NULL, &winOption);
    jclass thisClass = env->FindClass("NBioBSPJNI/NBioBSPJNI$FIR_HANDLE");
    jfieldID field = env->GetFieldID(thisClass, "Handle", "J");

    jlong number = env->GetLongField(fir_handle, field);
    env->SetLongField (fir_handle,field, hCapturedFIR1);


   return;

  }




JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerify  (JNIEnv *env,jobject thisObj, NBioAPI_HANDLE_PTR hHandle,  NBioAPI_FIR_HANDLE_PTR piStoredTemplate,
     NBioAPI_BOOL* pbResult,NBioAPI_FIR_PAYLOAD_PTR pPayload, NBioAPI_FIR_HANDLE_PTR  phAuditData,  NBioAPI_WINDOW_OPTION_PTR pWindowOption) {


    NBioAPI_RETURN nRet;
    NBioAPI_FIR_PAYLOAD payload;        // Windows Option setting
    NBioAPI_WINDOW_OPTION winOption;


    NBioAPI_BOOL resultado;

    NBioAPI_FIR_HANDLE digi = *piStoredTemplate;
    NBioAPI_INPUT_FIR inputFIR;
    inputFIR.Form = NBioAPI_FIR_FORM_HANDLE;
    inputFIR.InputFIR.FIRinBSP =  &digi;

     nRet = NBioAPI_Verify(m_hNBioBSP, &inputFIR, &resultado, &payload, -1, NULL, &winOption);
     cout << "resultado C++ " << resultado << endl;
     pbResult = &resultado;


    return nRet;




     }

JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerify2
    (JNIEnv *env,jobject thisObj, NBioAPI_FIR_HANDLE hHandle, jstring *strin) {
    NBioAPI_RETURN nRet;
    jboolean blnIsCopy;



    return 0;

/*
        NBioAPI_FIR_PAYLOAD payload;
        // Windows Option setting
        NBioAPI_WINDOW_OPTION winOption;

        NBioAPI_FIR_HANDLE *hCapturedFIR1;


        //NBioAPI_Capture(m_hNBioBSP, NBioAPI_FIR_PURPOSE_VERIFY, &hCapturedFIR1, 3000,NULL,NULL);


        NBioAPI_INPUT_FIR inputFIR;
        inputFIR.Form = NBioAPI_FIR_FORM_HANDLE;
        inputFIR.InputFIR.FIRinBSP = &hHandle;

        NBioAPI_BOOL resultado;


        nRet = NBioAPI_Verify(m_hNBioBSP, &inputFIR, &resultado, &payload, -1, NULL, &winOption);

        cout << "resultado C++ " << resultado << endl;

    return nRet;

    */






    }




