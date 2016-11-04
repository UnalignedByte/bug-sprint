#include <android_native_app_glue.h>

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "CoreAdapter.h"


bool isSetup = false;
CoreAdapter *coreAdapter = nullptr;

EGLDisplay eglDisplay;
EGLContext eglContext;
EGLSurface eglSurface;

void processAppCommands(android_app *app, int cmd);
void setup(android_app *app);
void setupEGL(android_app *app);
void setupCoreAdapter();


void android_main(android_app *app)
{
    app_dummy();

    app->onAppCmd = processAppCommands;

    int events;
    android_poll_source *source;

    while(true) {
        while(ALooper_pollAll(0, NULL, &events, (void **) &source) >= 0) {
            if(source != NULL)
                source->process(app, source);

            if(app->destroyRequested)
                return;
        }

        if(isSetup)
            coreAdapter->executeLoop();
    }
}


void processAppCommands(android_app *app, int cmd)
{
    switch(cmd) {
        case APP_CMD_INIT_WINDOW:
            setup(app);
            break;
        default:
            break;
    }
}


void setup(android_app *app)
{
    if (!isSetup) {
        setupEGL(app);
        setupCoreAdapter();

        isSetup = true;
    }
}


void setupEGL(android_app *app)
{
    EGLint attributes[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 1,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE};

    EGLint contextAttributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(eglDisplay, NULL, NULL);

    int configsCount;
    EGLConfig  config;
    eglChooseConfig(eglDisplay, attributes, &config, 1, &configsCount);

    eglSurface = eglCreateWindowSurface(eglDisplay, config, app->window, NULL);
    eglContext = eglCreateContext(eglDisplay, config, NULL, contextAttributes);
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
}


void setupCoreAdapter()
{
    EGLint width;
    EGLint  height;
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &height);

    coreAdapter = new CoreAdapter(width, height);
}
