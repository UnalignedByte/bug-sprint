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

    //AAsset *fileAsset = AAssetManager_open(app->activity->assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);

    //AAsset_close(fileAsset);

    //JNIEnv *env;
    //app->activity->vm->AttachCurrentThread(&env, NULL);

    //jclass fileClass = env->FindClass("java/io/File");


    return "";
}
