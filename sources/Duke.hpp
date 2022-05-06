#include "Player.hpp"
#include "Game.hpp"

#include <iostream>

namespace coup {
    class Duke : public Player{
        
        public:
                /* --- constructors --- */
            using Player::Player;

                /* --- getters --- */
            std::string role() const override;

                /* --- setters --- */

                /* --- functions --- */
            void tax() override; 
            void block(Player&) override;

    };

}