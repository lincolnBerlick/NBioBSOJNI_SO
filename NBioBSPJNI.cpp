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



// chamar metodo para captura da digital e aponta espaco na memoria
JNIEXPORT void JNICALL Java_NBioBSPJNI_NBioBSPJNI_capture(JNIEnv *env, jobject thisObj, NBioAPI_FIR_HANDLE param1) {

    NBioAPI_FIR_HANDLE fir;
    NBioAPI_FIR_HANDLE hCapturedFIR1;

    NBioAPI_Capture(m_hNBioBSP, NBioAPI_FIR_PURPOSE_VERIFY, &hCapturedFIR1, 3000,NULL,NULL);



   cout << "capturado" << endl;
   return;
}




