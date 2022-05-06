#include "Player.hpp"
#include "Game.hpp"

#include <iostream>
namespace coup {
    class Contessa : public Player {
        public:
                /* --- constructors --- */
            using Player::Player;

                /* --- getters --- */
            std::string role() const override;
                /* --- setters --- */
                
                /* --- functions --- */
            void block(Player&) override;

    };

}