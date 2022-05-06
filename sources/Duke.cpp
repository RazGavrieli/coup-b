#include "Duke.hpp"

using namespace coup;

void Duke::tax() {  
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (isMaxCoins()) {
        throw std::runtime_error("Player must coup!");
    }
    incrementCoins(3);
    getCurrGame()->nextTurn();
}

std::string Duke::role() const {     return "Duke";}

void Duke::block(Player &blockedPlayer) {
    if (!isInGame(blockedPlayer)) {
        throw std::runtime_error("Player not in game!");
    }
    if (!blockedPlayer.didForeign()) {
        throw std::runtime_error("this player didn't foreign aid!");
    }
    blockedPlayer.incrementCoins(-2);
 }