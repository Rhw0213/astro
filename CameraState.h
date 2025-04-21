#pragma once
#include "IState.h"
#include "Common.h"

namespace astro
{
    class CameraState : public IState
    {
    public:
        static CameraState& Instance()
        {
            static CameraState instance;
            return instance;
        }

        void Update(const Camera2D& camera) { this->camera = camera; }
        const Camera2D& GetCamera() const { return camera; }

    private:
        Camera2D camera{ 0 };
    };
} 