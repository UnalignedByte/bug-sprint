#include <android_native_app_glue.h>


bool isSetup = false;

void processAppCommands(android_app *app, int cmd);
void setup();
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
    if(isSetup)
        return;

    isSetup = true;
}


void executeLoop()
{
    if(!isSetup)
        return;
}
