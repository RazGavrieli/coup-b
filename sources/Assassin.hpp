#include "Player.hpp"
#include "Game.hpp"

#include <iostream>

namespace coup
{
    class Assassin : public Player
    {
        /* private fields */
        bool didCoup;
        Player *coupedPlayer;

    public:
        /* --- constructors --- */
        Assassin(Game &, std::string);
        //using Player::Player;

        /* --- getters --- */
        std::string role() const override;
        bool isCouped() const;
        Player *getCoupedPlayer() const;

        /* --- setters --- */
        void resetPlayer() override;

        /* --- functions --- */
        void coup(Player &) override;
    };

}