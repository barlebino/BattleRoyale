#include "EngineApp.hpp"

#include <time.h>
#include <iostream>

EngineApp::EngineApp() {
    srand(time(0));
    RESOURCE_DIR = "../resources/";
    APP_NAME = "";
    verbose = false;
    nFrames = 0;
    timeStep = lastFrameTime = runTime = 0.f;
}

int EngineApp::init() {
    if (windowHandler.init(APP_NAME)) {
        return 1;
    }

<<<<<<< HEAD
    loader.init(verbose, RESOURCE_DIR);

    lastFrameTime = runTime = (float)windowHandler.getTime();

=======
    scene = new Scene();
    loader.init(verbose, RESOURCE_DIR);

    lastFrameTime = runTime = (float)windowHandler.getTime();
   
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6
    return 0;
}

void EngineApp::run() {

    // TODO : call all active component init functions

    while (!windowHandler.shouldClose()) {
        /* Update time and FPS */
        runTime = (float)windowHandler.getTime();
        timeStep = (runTime - lastFrameTime);
        lastFrameTime = runTime;
        nFrames++;
        if (runTime - lastFpsTime >= 1.0) {
            fps = (double)nFrames;
            nFrames = 0;
            lastFpsTime = runTime;
        }

        /* Update display, mouse, and keyboard */
        windowHandler.update();

        /* Update all game objects and components */
<<<<<<< HEAD
        scene.update(timeStep);
=======
        scene->update(timeStep);
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6
    }
}

void EngineApp::terminate() {
    windowHandler.shutDown();
<<<<<<< HEAD
    scene.shutDown();
=======
    scene->shutDown();
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6
}
