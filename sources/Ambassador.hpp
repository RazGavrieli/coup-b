#include "Player.hpp"
#include "Game.hpp"

#include <iostream>
namespace coup
{
    class Ambassador : public Player
    {
        /* private fields */
        // Player *payer;
        // Player *receiver; NOT NEEDED FOR BLOCKING IMPLEMENTATION
        // bool didTransfer;

    public:
        /* --- constructors --- */
        using Player::Player;
        // Ambassador(Game &, std::string);

        /* --- getters --- */
        std::string role() const override;

        /* --- setters --- */
        // void resetPlayer() override;

        /* --- functions --- */
        void transfer(Player &, Player &) override;
        void block(Player &) override;
    };

}