//
// Created by Rafal Grodzinski on 04/11/2016.
//

#include "SystemUtils.h"

using namespace std;


android_app *SystemUtils::app = nullptr;


string SystemUtils::pathForFileName(const std::string &fileName)
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    /*JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, NULL);

    jclass nativeActivityClass = env->FindClass("android/app/NativeActivity");
    jmethodID getExternalFilesDirId = env->GetMethodID(nativeActivityClass, "getExternalFilesDir",
        "(Ljava/lang/String;)Ljava/io/File;");
    jobject externalFilesDirObj = env->CallObjectMethod(app->activity->clazz, getExternalFilesDirId, nullptr);

    jclass fileClass = env->FindClass("java/io/File");
    jmethodID getPathId = env->GetMethodID(fileClass, "getPath", "()Ljava/lang/String;");
    jstring pathStringObj = (jstring)env->CallObjectMethod(externalFilesDirObj, getPathId);

    const char *cFilePath = env->GetStringUTFChars(pathStringObj, nullptr);
    string filePath = string(cFilePath);

    env->ReleaseStringUTFChars(pathStringObj, cFilePath);
    env->DeleteLocalRef(pathStringObj);

    app->activity->vm->DetachCurrentThread();

    if(filePath.length() > 0) {
        filePath = filePath + "/" + fileName;

        return filePath;
    }*/

    return fileName;
}


FileBuffer SystemUtils::bufferForFileName(const std::string &fileName)
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    AAsset *fileAsset = AAssetManager_open(app->activity->assetManager, fileName.c_str(), AASSET_MODE_BUFFER);

    long fileDataLength = AAsset_getLength(fileAsset);
    const void *fileData = AAsset_getBuffer(fileAsset);

    FileBuffer fileBuffer(const_cast<void *>(fileData), fileDataLength);

    AAsset_close(fileAsset);

    return fileBuffer;
}
