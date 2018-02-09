#include "EngineApp/EngineApp.hpp"

#include <string>
#include <iostream>

void printUsage() {
    std::cout << "Valid arguments: " << std::endl;

    std::cout << "\t-h\n\t\tPrint help" << std::endl;
    
    std::cout << "\t-v\n\t\tSet verbose nature logging" << std::endl;

    std::cout << "\t-r <resource_dir>" << std::endl;
    std::cout << "\t\tSet the resource directory" << std::endl;

    std::cout << "\t-n <application_name>" << std::endl;
    std::cout << "\t\tSet the application name" << std::endl;
}

int parseArgs(EngineApp *engine, int argc, char **argv) {
    /* Process cmd line args */
    for (int i = 0; i < argc; i++) {
        /* Help */
        if (!strcmp(argv[i], "-h")) {
            printUsage();
            return 1;
        }
        /* Verbose */
        if (!strcmp(argv[i], "-v")) {
            engine->verbose = true;
        }
        /* Set resource dir */
        if (!strcmp(argv[i], "-r")) {
            if (i + 1 >= argc) {
                printUsage();
                return 1;
            }
            engine->RESOURCE_DIR = argv[i + 1];
        }
        /* Set application name */
        if (!strcmp(argv[i], "-n")) {
            if (i + 1 >= argc) {
                printUsage();
                return 1;
            }
            engine->APP_NAME = argv[i + 1];
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    /* Singular engine */
    EngineApp engine;
<<<<<<< HEAD
    Scene *scene = &engine.scene;

    if (parseArgs(&engine, argc, argv)) {
        return 1;
    }

    /* Initialize engine */
    if (engine.init()) {
        return 1;
    }
=======

    if (parseArgs(&engine, argc, argv) || engine.init()) {
        return 1;
    }

    /* Scene reference for QOL */
    Scene *scene = engine.scene;
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6

    /* Create camera and camera controller components */
    GameObject *camera = scene->createGameObject();
    CameraComponent *cc = scene->createComponent<Scene::GAMELOGIC, CameraComponent>(45.f, 1280.f / 960.f, 0.01f, 250.f);
    camera->addComponent(cc);
<<<<<<< HEAD
    camera->addComponent(scene->createComponent<Scene::GAMELOGIC, CameraController>(cc, 20.f, 30.f, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_R));
=======
    camera->addComponent(scene->createComponent<Scene::GAMELOGIC, CameraController>(cc, 20.f, 30.f, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_R, GLFW_KEY_E));
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6

    /* Create diffuse shader */
    glm::vec3 lightPos(100.f, 100.f, 100.f);
    // TODO : user shouldn't need to specify resource dir here
    scene->renderer->addShader<DiffuseShader>("diffuse",                                    /* Shader name */
                                              engine.RESOURCE_DIR + "diffuse_vert.glsl",    /* Vertex GLSL file */
                                              engine.RESOURCE_DIR + "diffuse_frag.glsl",    /* Fragment GLSL file*/
                                              cc,                                           /* Shader-specific uniforms */
                                              &lightPos);                                   /*                          */

    /* Create bunny */
    GameObject *bunny = scene->createGameObject();
<<<<<<< HEAD
=======
    bunny->transform.position = glm::vec3(5.f, 0.f, 0.f);
>>>>>>> 0e67de0abf23004c8fb7a042626f3befc15a79a6
    bunny->transform.scale = glm::vec3(1.f);
    bunny->addComponent(scene->createComponent<Scene::RENDERABLE, DiffuseRenderableComponent>(
        scene->renderer->shaders.find("diffuse")->second->pid,
        engine.loader.getMesh("bunny.obj"),
        ModelTexture(0.3f, glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f))));
                            

    /* Main loop */
    engine.run();

    return 0;
}


