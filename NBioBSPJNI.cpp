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


NBioAPI_FIR_HANDLE getFIR_HANDLE(JNIEnv *env, jobject fir_handle){

    NBioAPI_FIR_HANDLE firhandle; // retorno

    jclass thisclass = env->GetObjectClass(fir_handle);

    jfieldID field_inputfir =  env->GetFieldID(thisclass, "Handle", "I");
    long digital = env->GetLongField(fir_handle, field_inputfir);

    firhandle = digital;

    return firhandle;



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


int a = 0;

static jclass classInteger;
static jmethodID midIntegerInit;


JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_TesteObject
  (JNIEnv *env, jobject thisObj, jobject  b) {
    jfieldID fid; /* store the field ID */

   jclass c = env->GetObjectClass(b);

   fid = env->GetFieldID(c,"value", "Z");
   jbyte old = env->GetBooleanField(b,fid);
   cout << "capturado " << old << endl;

   env->SetBooleanField(b,fid,0);


   return ;


  }



JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeCapture
  (JNIEnv *env,jobject thisObj, jint proposito,jobject fir_handle, jint timeout, jobject fir_handleaudit, jobject winoption)  {


    NBioAPI_WINDOW_OPTION winOption;
    NBioAPI_FIR_HANDLE hCapturedFIR1;
    NBioAPI_RETURN nRet;

    nRet = NBioAPI_Capture(m_hNBioBSP, NBioAPI_FIR_PURPOSE_VERIFY, &hCapturedFIR1, -1, NULL, &winOption);
    jclass thisClass = env->GetObjectClass(fir_handle);
    jfieldID field = env->GetFieldID(thisClass, "Handle", "J");

    //long number = env->GetLongField(fir_handle, field);
    env->SetLongField(fir_handle,field, hCapturedFIR1);


   return;

  }


void getINPUT_FIR(JNIEnv *env, jobject input_fir, NBioAPI_INPUT_FIR &fir, long &id){

    jclass thisClass = env->FindClass("NBioBSPJNI/NBioBSPJNI$INPUT_FIR");
    jfieldID field_FIRHandle = env->GetFieldID(thisClass, "FIRHandle", "J");
    jfieldID field_Form = env->GetFieldID(thisClass, "Form", "I");


    return;



    }

JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerify  (JNIEnv *env,jobject thisObj, jobject INPUT_FIR, jobject paramBoolean, jobject PAY_LOAD, jint inteiro ) {


    NBioAPI_RETURN nRet;
    NBioAPI_FIR_PAYLOAD payload;        // Windows Option setting
    NBioAPI_WINDOW_OPTION winOption;
    NBioAPI_BOOL resultado;
    NBioAPI_INPUT_FIR inputFIR;


//recebe objecto de java e adiciona a objeto nativo
    jclass thisClass = env->GetObjectClass(INPUT_FIR);
    jfieldID field_FIRHandle = env->GetFieldID(thisClass, "FIRHandle", "J");

    jfieldID field_Form = env->GetFieldID(thisClass, "Form", "I");

    jlong digital = env->GetLongField(INPUT_FIR, field_FIRHandle);
    int form = env->GetIntField(INPUT_FIR, field_Form);

    inputFIR.InputFIR.FIR = &digital;
    inputFIR.Form = form;


    nRet = NBioAPI_Verify(m_hNBioBSP, &inputFIR, &resultado, &payload, -1, NULL, &winOption);
//fim objeto nativo

    if(resultado == true){


    //devolve valor booleano
   jfieldID fid; /* store the field ID */
   jclass c = env->GetObjectClass(paramBoolean);
   fid = env->GetFieldID(c,"value", "Z");
   jbyte old = env->GetBooleanField(paramBoolean,fid);

   env->SetBooleanField(paramBoolean,fid,1);

    }





    return 1;


     }





