#pragma once
#ifndef _ENGINE_APP_HPP_
#define _ENGINE_APP_HPP_

#include "IO/Window.hpp"
#include "Loader/Loader.hpp"
#include "Scene/Scene.hpp"

#include <string>

class EngineApp {
    public:
        EngineApp();

<<<<<<< HEAD
        Scene scene;
=======
        Scene *scene;
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6

        int init();
        void run();
        void terminate();

        Loader loader;              /* Used to load in files and GPU memory */

        std::string RESOURCE_DIR;   /* Static resource directory */
        std::string APP_NAME;       /* Name of application */
        double timeStep;            /* Delta time */
        bool verbose;               /* Log things or not */

    private:
        double fps;                 /* Frames per second */
        double lastFpsTime;         /* Time at which last FPS was calculated */
        int nFrames;                /* Number of frames in current second */
        double lastFrameTime;       /* Time at which last frame was rendered */
        double runTime;             /* Global timer */

        Window windowHandler;       /* GLFW window */
};

#endif