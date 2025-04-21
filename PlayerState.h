#pragma once
#include "IState.h"
#include "Common.h"
#include "Player.h"
#include <memory> 

namespace astro
{
    class PlayerState : public IState
    {
    public:
        static PlayerState& Instance()
        {
            static PlayerState instance;
            return instance;
        }

        void Update(std::shared_ptr<Player> player) { this->player = player; }
        std::shared_ptr<Player> GetPlayer() const { return player; }

    private:
        std::shared_ptr<Player> player;
    };
}
