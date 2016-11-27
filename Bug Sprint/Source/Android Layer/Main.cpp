#include <android_native_app_glue.h>

#include <iostream>
#include <cstdlib>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <android/log.h>

#include "CoreAdapter.h"
#include "SystemUtils.h"

bool isSetup = false;
static bool isEglSetUp = false;

CoreAdapter *coreAdapter = nullptr;

EGLDisplay eglDisplay;
EGLContext eglContext;
EGLSurface eglSurface;

void processAppCommands(android_app *app, int cmd);
int processInput(android_app *app, AInputEvent *inputEvent);
void processTouchInput(AInputEvent *inputEvent);

void setup(android_app *app);
void shutdown(android_app *app);

void setupEGL(android_app *app);
void shutdownEGL(android_app *app);

void setupSystemUtils(android_app *app);
void setupCoreAdapter();


void android_main(android_app *app)
{
    app_dummy();

    app->onAppCmd = processAppCommands;
    app->onInputEvent = processInput;

    int events;
    android_poll_source *source;

    while(true) {
        while(ALooper_pollAll(0, NULL, &events, (void **) &source) >= 0) {
            if(source != NULL)
                source->process(app, source);

            if(app->destroyRequested)
                return;
        }

        if(isSetup) {
            coreAdapter->executeLoop();
            eglSwapBuffers(eglDisplay, eglSurface);
        }
    }
}


void processAppCommands(android_app *app, int cmd)
{
    switch(cmd) {
        case APP_CMD_INIT_WINDOW:
            setup(app);
            break;
        case APP_CMD_TERM_WINDOW:
            shutdownEGL(app);
            break;
        case APP_CMD_DESTROY:
            shutdown(app);
            break;
        default:
            break;
    }
}


int processInput(android_app *app, AInputEvent *inputEvent)
{
    switch(AInputEvent_getType(inputEvent)) {
        case AINPUT_EVENT_TYPE_MOTION:
            switch(AInputEvent_getSource(inputEvent)) {
                case AINPUT_SOURCE_TOUCHSCREEN:
                    processTouchInput(inputEvent);
                    break;
            }
            break;
    }

    return 0;
}


void setup(android_app *app)
{
    setupEGL(app);
    setupSystemUtils(app);
    setupCoreAdapter();

    isSetup = true;
}


void shutdown(android_app *app)
{
    if(!isSetup)
        return;

    shutdownEGL(app);
}


void setupEGL(android_app *app)
{
    if(isEglSetUp)
        return;

    EGLint attributes[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 1,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE};

    EGLint contextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(eglDisplay == EGL_NO_DISPLAY) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not get EGL Display");
        abort();
    }

    if(!eglInitialize(eglDisplay, NULL, NULL)) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not initialize EGL");
        abort();
    }

    int configsCount;
    EGLConfig  config;
    eglChooseConfig(eglDisplay, attributes, &config, 1, &configsCount);
    if(configsCount <= 0) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not get EGL configs");
        abort();
    }

    eglSurface = eglCreateWindowSurface(eglDisplay, config, app->window, NULL);
    if(eglSurface == EGL_NO_SURFACE) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not create EGL Surface");
        abort();
    }

    eglContext = eglCreateContext(eglDisplay, config, NULL, contextAttributes);
    if(eglSurface == EGL_NO_CONTEXT) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not create EGL Context");
        abort();
    }

    if(!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        __android_log_print(ANDROID_LOG_ERROR, "App", "Could not initialize EGL Context");
        abort();
    }

    isEglSetUp = true;
}


void shutdownEGL(android_app *app)
{
    if(!isEglSetUp)
        return;

    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);

    eglDisplay = EGL_NO_DISPLAY;
    eglContext = EGL_NO_CONTEXT;
    eglSurface = EGL_NO_SURFACE;

    isEglSetUp = false;
}


void setupSystemUtils(android_app *app)
{
    SystemUtils::app = app;
}


void setupCoreAdapter()
{
    EGLint width;
    EGLint height;
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &height);

    coreAdapter = new CoreAdapter(width, height);
}


void processTouchInput(AInputEvent *inputEvent)
{
    int x = AMotionEvent_getX(inputEvent, 0);
    int y = AMotionEvent_getY(inputEvent, 0);

    switch(AMotionEvent_getAction(inputEvent)) {
        case AMOTION_EVENT_ACTION_DOWN:
            coreAdapter->touchDown(x, y);
            break;
        case AMOTION_EVENT_ACTION_UP:
            coreAdapter->touchUp(x, y);
            break;
        case AMOTION_EVENT_ACTION_MOVE:
            coreAdapter->touchMove(x, y);
            break;
        case AMOTION_EVENT_ACTION_CANCEL:
            coreAdapter->touchCancel();
            break;
        default:break;
    }
}
