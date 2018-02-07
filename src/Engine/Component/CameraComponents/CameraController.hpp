/* Controls camera using mouse and keyboard */
#pragma once
#ifndef _CAMERA_CONTROLLER_HPP_
#define _CAMERA_CONTROLLER_HPP_

#include "Component/Component.hpp"
#include "CameraComponent.hpp"

class CameraController : public Component {
    public:
        CameraController(CameraComponent *cc, float ls, float ms, int f, int b, int l, int r, int u, int d) :
            camera(cc),
            lookSpeed(ls),
            moveSpeed(ms),
            front(f),
            back(b),
            left(l),
            right(r),
            up(u),
            down(d)
        {}

        void init();

        void update(float dt);

        void lookAround(float dt, float dx, float dy);
        void moveFront(float dt);
        void moveBack(float dt);
        void moveLeft(float dt);
        void moveRight(float dt);
        void moveUp(float dt);
        void moveDown(float dt);
    private:
        CameraComponent* camera;
        float lookSpeed, moveSpeed;
        int front, back, left, right, up, down;
};

#endif
