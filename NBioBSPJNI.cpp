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

void getINPUT_FIR(JNIEnv *env, jobject input_fir, NBioAPI_INPUT_FIR *retorno){


    NBioAPI_INPUT_FIR inputFIR; //vai retornar


    jclass thisClass = env->FindClass("NBioBSPJNI/NBioBSPJNI$INPUT_FIR");
    jfieldID field_FIRHandle = env->GetFieldID(thisClass, "FIRHandle", "J");
    jfieldID field_Form = env->GetFieldID(thisClass, "Form", "I");
    long digital = env->GetLongField(input_fir, field_FIRHandle);
    long *dig = &digital;

    cout << "valor de  " << digital << endl;
    int form = env->GetIntField(input_fir, field_Form);

    retorno->InputFIR.FIR = &digital;
    //(*retorno).InputFIR.FIR = &dig;
    //*retorno.InputFIR.FIR = &dig;
    retorno->Form = form;

   // NBioAPI_INPUT_FIR* reetorno = inputFIR;

    return;



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
  (JNIEnv *env, jint proposito,jobject fir_handle, jint timeout, jobject fir_handleaudit, jobject winoption)  {


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




JNIEXPORT NBioAPI_RETURN JNICALL Java_NBioBSPJNI_NBioBSPJNI_NativeVerify  (JNIEnv *env,jobject thisObj, jobject INPUT_FIR, jboolean result, jobject PAY_LOAD ) {


    NBioAPI_RETURN nRet;
    NBioAPI_FIR_PAYLOAD payload;        // Windows Option setting
    NBioAPI_WINDOW_OPTION winOption;
    NBioAPI_BOOL resultado;
    NBioAPI_INPUT_FIR inputFIR;

    NBioAPI_INPUT_FIR inputFIR2;
    NBioAPI_INPUT_FIR fir;



    getINPUT_FIR(env, INPUT_FIR, &inputFIR2);

    fir = inputFIR2;

     nRet = NBioAPI_Verify(m_hNBioBSP, &inputFIR2, &resultado, &payload, -1, NULL, &winOption);
     cout << "resultado C++ " << resultado << endl;



    return nRet;


     }





