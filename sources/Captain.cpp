#include "Captain.hpp"
using namespace coup;

Captain::Captain(Game & game, std::string name) : Player(game, std::move(name)) {
    didSteal = 0;
    stolenPlayer = nullptr;
}

void Captain::steal(Player &stealFrom) {
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (!isInGame(stealFrom)) {
        throw std::runtime_error("Player not in game!");
    }
    if (isMaxCoins()) {
        throw std::runtime_error("Player must coup!");
    }
    if (stealFrom.coins()<=0) { 
        throw std::runtime_error("Stolen player does not have enough coins!");
    }
    if (stealFrom.coins()==1) { 
        //throw std::runtime_error("Stolen player does not have enough coins!");
        stealFrom.incrementCoins(-1);
        incrementCoins(1);
        didSteal = 1;
        stolenPlayer = &stealFrom;
        getCurrGame()->nextTurn();
        return;
    }
    stealFrom.incrementCoins(-2);
    incrementCoins(2);
    didSteal = 2;
    stolenPlayer = &stealFrom;
    getCurrGame()->nextTurn();
}

std::string Captain::role() const{     return "Captain";}

int Captain::isSteal() const{      return didSteal;}

Player* Captain::getStolenPlayer() const {      return stolenPlayer;}

void Captain::resetPlayer () {
    didSteal = 0;
    stolenPlayer = nullptr;
}

void Captain::block(Player &blockedPlayer) {
    if (!isInGame(blockedPlayer)) {
        throw std::runtime_error("Player not in game!");
    }
    if (blockedPlayer.role()!="Captain") {
        throw std::runtime_error("This Player can't block that!");
    }
    Captain *blockedCaptain = dynamic_cast<Captain*>(&blockedPlayer);
    if (blockedCaptain->isSteal()==0) {
        throw std::runtime_error("The blocked Player didn't steal!");
    }
    if (blockedCaptain->isSteal()==1) {
        //throw std::runtime_error("The blocked Player didn't steal!");
        blockedCaptain->incrementCoins(-1);
        if (isInGame(*blockedCaptain->getStolenPlayer())) {
            blockedCaptain->getStolenPlayer()->incrementCoins(1); 
        }
        blockedCaptain->resetPlayer();
        return;
    }
    blockedCaptain->incrementCoins(-2);
    if (isInGame(*blockedCaptain->getStolenPlayer())) {
        blockedCaptain->getStolenPlayer()->incrementCoins(2); 
    }
    blockedCaptain->resetPlayer();
    

}