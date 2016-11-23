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

    jobject assetsManagerObj = getAssetsManager();

    // inputStreamObj = assetsManagerObj.open(fileNameStringObj);
    jclass assetsManagerClass = env->FindClass("android/content/res/AssetManager");
    jmethodID openId = env->GetMethodID(assetsManagerClass, "open", "(Ljava/lang/String;)Ljava/io/InputStream;");
    jstring fileNameStringObj = env->NewStringUTF(fileName.c_str());
    jobject inputStreamObj = env->CallObjectMethod(assetsManagerObj, openId, fileNameStringObj);

    // bitmapObj = BitmapFactory.decodeStream(inputStreamObj)
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

    size_t bytesCount = size_t(imageData.width * imageData.height * 4);
    imageData.rgbaImageData = (unsigned char *)calloc(bytesCount, sizeof(unsigned char));
    memcpy(imageData.rgbaImageData, bitmapData, bytesCount * sizeof(unsigned char));

    AndroidBitmap_unlockPixels(env, bitmapObj);

    return imageData;
}


ImageData SystemUtils::imageDataForText(const std::string &text, const std::string &fontFileName,
    float fontSize, float red, float green, float blue)
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    ImageData imageData;

    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, NULL);

    // paintObj = new Paint()
    jclass paintClass = env->FindClass("android/graphics/Paint");
    jmethodID paintConstructor = env->GetMethodID(paintClass, "<init>", "(I)V");
    jobject paintObj = env->NewObject(paintClass, paintConstructor, 1);

    // paintObj.setTextSize(fontSize)
    jmethodID setTextSizeMethod = env->GetMethodID(paintClass, "setTextSize", "(F)V");
    env->CallVoidMethod(paintObj, setTextSizeMethod, fontSize * getScale());

    // paintObj.setColor(color)
    jmethodID setColorMethod = env->GetMethodID(paintClass, "setColor", "(I)V");
    uint32_t color = 0;
    color |= 255 << 24; // Alpha
    color |= int(red * 255) << 16; // Red
    color |= int(green * 255) << 8; //Green
    color |= int(blue * 255); // Blue
    env->CallVoidMethod(paintObj, setColorMethod, color);

    // typefaceObj = Typeface.createFromAssets(assetsManagerObj, fontFileNameStringObj)
    jclass typefaceClass = env->FindClass("android/graphics/Typeface");
    jmethodID createFromAssetMethod = env->GetStaticMethodID(typefaceClass, "createFromAsset",
                                                             "(Landroid/content/res/AssetManager;Ljava/lang/String;)Landroid/graphics/Typeface;");
    jobject assetsManagerObj = getAssetsManager();
    jstring fontFileNameStringObj = env->NewStringUTF(fontFileName.c_str());
    jobject typefaceObj = env->CallStaticObjectMethod(typefaceClass, createFromAssetMethod, assetsManagerObj, fontFileNameStringObj);

    // paintObj.setTypeface(typefaceObj)
    jmethodID setTypefaceMethod = env->GetMethodID(paintClass, "setTypeface", "(Landroid/graphics/Typeface;)Landroid/graphics/Typeface;");
    env->CallObjectMethod(paintObj, setTypefaceMethod, typefaceObj);

    // textWidth = paintObj.meassureText(textStringObj)
    jmethodID meassureTextMethod = env->GetMethodID(paintClass, "measureText", "(Ljava/lang/String;)F");
    jstring textStringObj = env->NewStringUTF(text.c_str());
    float textWidth = env->CallFloatMethod(paintObj, meassureTextMethod, textStringObj);

    // textAscent = paintObj.ascent()
    jmethodID ascentMethod = env->GetMethodID(paintClass, "ascent", "()F");
    float textAscent = env->CallFloatMethod(paintObj, ascentMethod);

    // textDescent = paintObj.descent()
    jmethodID descentMethod = env->GetMethodID(paintClass, "descent", "()F");
    float textDescent = env->CallFloatMethod(paintObj, descentMethod);

    imageData.width = int(textWidth);
    imageData.height = int(-textAscent + textDescent);

    // bitmapObj = Bitmap.createBitmap(imageData.width, imageData.height, ARGB_8888)
    jclass bitmapClass = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapMethod = env->GetStaticMethodID(bitmapClass, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOfMethod = env->GetStaticMethodID(bitmapConfigClass, "valueOf", "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
    jstring configStringObj = env->NewStringUTF("ARGB_8888");
    jobject argba8888FieldObj = env->CallStaticObjectMethod(bitmapConfigClass, valueOfMethod, configStringObj);

    jobject bitmapObj = env->CallStaticObjectMethod(bitmapClass, createBitmapMethod, imageData.width, imageData.height, argba8888FieldObj);

    // canvasObj = new Canvas(bitmapObj)
    jclass canvasClass = env->FindClass("android/graphics/Canvas");
    jmethodID canvasConstructor = env->GetMethodID(canvasClass, "<init>", "(Landroid/graphics/Bitmap;)V");
    jobject canvasObj = env->NewObject(canvasClass, canvasConstructor, bitmapObj);

    // canvasObj.drawText(textStringObj, -textAscent, paintObj)
    jmethodID drawTextMethod = env->GetMethodID(canvasClass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
    env->CallVoidMethod(canvasObj, drawTextMethod, textStringObj, 0.0, -textAscent, paintObj);

    // Copy image data
    void *bitmapData;
    AndroidBitmap_lockPixels(env, bitmapObj, &bitmapData);

    size_t bytesCount = size_t(imageData.width * imageData.height * 4);
    imageData.rgbaImageData = (unsigned char *)calloc(bytesCount, sizeof(unsigned char));
    memcpy(imageData.rgbaImageData, bitmapData, bytesCount * sizeof(unsigned char));

    AndroidBitmap_unlockPixels(env, bitmapObj);

    return imageData;
}


float SystemUtils::getScale()
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    static float density = 0.0;
    if(density > 0.0)
        return density;

    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    jobject resourcesObj = getResources();

    // resourcesObj.getDisplayMetrics()
    jclass resourcesClass = env->FindClass("android/content/res/Resources");
    jmethodID getDisplayMetricsMethod = env->GetMethodID(resourcesClass, "getDisplayMetrics", "()Landroid/util/DisplayMetrics;");
    jobject displayMetricsObj = env->CallObjectMethod(resourcesObj, getDisplayMetricsMethod);

    // displayMetricsObj.density
    jclass displayMetricsClass = env->FindClass("android/util/DisplayMetrics");
    jfieldID densityField = env->GetFieldID(displayMetricsClass, "density", "F");
    density = env->GetFloatField(displayMetricsObj, densityField);

    return density;
}


jobject SystemUtils::getAssetsManager()
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    // activity.getApplication()
    jclass nativeActivityClass = env->GetObjectClass(app->activity->clazz);
    jmethodID getApplicationId = env->GetMethodID(nativeActivityClass, "getApplication", "()Landroid/app/Application;");
    jobject applicationObj = env->CallObjectMethod(app->activity->clazz, getApplicationId);

    // applicationObj.getAssets()
    jclass applicationClass = env->FindClass("android/app/Application");
    jmethodID getAssetsId = env->GetMethodID(applicationClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assetsManagerObj = env->CallObjectMethod(applicationObj, getAssetsId);

    return assetsManagerObj;
}


jobject SystemUtils::getResources()
{
    if(app == nullptr)
        throw string("SystemUtils is not initialized");

    JNIEnv *env;
    app->activity->vm->AttachCurrentThread(&env, nullptr);

    // activity.getApplication()
    jclass nativeActivityClass = env->GetObjectClass(app->activity->clazz);
    jmethodID getApplicationId = env->GetMethodID(nativeActivityClass, "getApplication", "()Landroid/app/Application;");
    jobject applicationObj = env->CallObjectMethod(app->activity->clazz, getApplicationId);

    // applicationObj.getResources()
    jclass applicationClass = env->FindClass("android/app/Application");
    jmethodID getResourcesMethod = env->GetMethodID(applicationClass, "getResources", "()Landroid/content/res/Resources;");
    jobject resourcesObj = env->CallObjectMethod(applicationObj, getResourcesMethod);

    return resourcesObj;
}
