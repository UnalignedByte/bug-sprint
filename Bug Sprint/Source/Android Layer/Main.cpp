#include <android_native_app_glue.h>

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>


bool isSetup = false;

EGLDisplay eglDisplay;
EGLContext eglContext;
EGLSurface eglSurface;

void processAppCommands(android_app *app, int cmd);
void setup();
void setupEGL();
void executeLoop();


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

        executeLoop();
    }
}


void processAppCommands(android_app *app, int cmd)
{
    switch(cmd) {
        case APP_CMD_INIT_WINDOW:
            setup();
            break;
        default:
            break;
    }
}


void setup()
{
    if (!isSetup) {
        setupEGL();

        isSetup = true;
    }
}


void setupEGL()
{
    EGLConfig  config;
    int configsCount;

    EGLint attributes[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
        EGL_RED_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_BLUE_SIZE, 5,
        EGL_DEPTH_SIZE, 1,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE};

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(eglDisplay, NULL, NULL);
    eglChooseConfig(eglDisplay, attributes, &config, 1, &configsCount);
    eglContext = eglCreateContext(eglDisplay, config, EGL_NO_CONTEXT, NULL);

    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

    glClearColor(0.0, 0.2, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    eglSwapBuffers(eglDisplay, eglSurface);
}


void executeLoop()
{
    if(!isSetup)
        return;
}
