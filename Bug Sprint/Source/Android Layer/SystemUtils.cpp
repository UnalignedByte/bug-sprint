//
// Created by Rafal Grodzinski on 04/11/2016.
//

#include "SystemUtils.h"

#include <android/bitmap.h>

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


ImageData SystemUtils::imageDataForFileName(const std::string &fileName)
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    ImageData imageData;

    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, NULL);

    // activity.getApplication()
    jclass nativeActivityClass = env->GetObjectClass(app->activity->clazz);
    jmethodID getApplicationId = env->GetMethodID(nativeActivityClass, "getApplication", "()Landroid/app/Application;");
    jobject applicationObj = env->CallObjectMethod(app->activity->clazz, getApplicationId);

    // application.getAssets()
    jclass applicationClass = env->FindClass("android/app/Application");
    jmethodID getAssetsId = env->GetMethodID(applicationClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assetsManagerObj = env->CallObjectMethod(applicationObj, getAssetsId);

    // assetsManager.open()
    jclass assetsManagerClass = env->FindClass("android/content/res/AssetManager");
    jmethodID openId = env->GetMethodID(assetsManagerClass, "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
    jstring fileNameStringObj = env->NewStringUTF(fileName.c_str());
    jobject inputStreamObj = env->CallObjectMethod(assetsManagerObj, openId, fileNameStringObj);

    // BitmapFactory.decodeStream()
    jclass bitmapFactoryClass = env->FindClass("android/graphics/BitmapFactory");
    jmethodID decodeStreamId = env->GetStaticMethodID(bitmapFactoryClass, "decodeStream",
                                                    "(Ljava/io/InputStream;)Landroid/graphics/Bitmap;");
    jobject bitmapObj = env->CallStaticObjectMethod(bitmapFactoryClass, decodeStreamId, inputStreamObj);

    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmapObj, &bitmapInfo);
    if(bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
        return imageData;

    imageData.width = bitmapInfo.width;
    imageData.height = bitmapInfo.height;

    // Copy image data
    void *bitmapData;
    AndroidBitmap_lockPixels(env, bitmapObj, &bitmapData);

    int bytesCount = imageData.width * imageData.height * 4;
    imageData.rgbaImageData = (unsigned char *)calloc(bytesCount, sizeof(unsigned char));
    memcpy(imageData.rgbaImageData, bitmapData, bytesCount * sizeof(unsigned char));

    AndroidBitmap_unlockPixels(env, bitmapObj);

    return imageData;
}
