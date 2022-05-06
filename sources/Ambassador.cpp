#include "Ambassador.hpp"
#include "Captain.hpp"

using namespace coup;

// Ambassador::Ambassador(Game & game, std::string name) : Player(game, std::move(name)) {
//         payer = nullptr;
//         receiver = nullptr;
//         didTransfer = false;
// }

void Ambassador::transfer(Player &payer, Player &receiver) {
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (isMaxCoins()) {
        throw std::runtime_error("Player must coup!");
    }
    if (!isInGame(payer)||!isInGame(receiver)) {
        throw std::runtime_error("Player not in game!");
    }
    if (payer.coins()<1) {
        throw std::runtime_error("Payer Player does not have enough coins!");
    }
    payer.incrementCoins(-1);
    receiver.incrementCoins(1);
    
        /* the following data is for blocking system to the transfer function
        it is not needed for this assigment though it was written for future proofing the code */
    // this->payer = &payer;
    // this->receiver = &receiver;
    // didTransfer = true;
        /* ------- */

    getCurrGame()->nextTurn();
}

std::string Ambassador::role() const {     return "Ambassador";}

// void Ambassador::resetPlayer() {
    /**
     * @brief NOT NEEDED BLOCKING IMPLEMENTATION
     * 
     */
//     didTransfer = false;
//     payer = receiver = nullptr;
// }

void Ambassador::block(Player &blockedPlayer) {
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
