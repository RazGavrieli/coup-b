#include "Assassin.hpp"
using namespace coup;
#include <iostream>
const short COUP_PRICE = 7;
const short ASSASSINATION_PRICE = 3;

Assassin::Assassin(Game & game, std::string name) : Player(game, std::move(name)) {
    didCoup = false;
    coupedPlayer = nullptr;
}

void Assassin::coup(Player &coup) {
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (coins()<ASSASSINATION_PRICE) {
        throw std::runtime_error("Not enough coins");
    }
    if (!isInGame(coup)) {
        throw std::runtime_error("Player not in game!");
    }
    if (coins()>=COUP_PRICE) {
        Player::coup(coup);
        return;
    }
    getCurrGame()->removePlayer(&coup);
    didCoup = true;
    coupedPlayer = &coup;
    incrementCoins(-3);
    getCurrGame()->nextTurn();
}
std::string Assassin::role() const {     return "Assassin";}

bool Assassin::isCouped() const{      return didCoup;}

Player* Assassin::getCoupedPlayer() const{    return coupedPlayer;}

void Assassin::resetPlayer () {
    didCoup = false;
    coupedPlayer = nullptr;
}