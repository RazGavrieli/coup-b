#include "Contessa.hpp"
#include "Assassin.hpp"
using namespace coup;

std::string Contessa::role() const {     return "Contessa";}

void Contessa::block(Player &blockedPlayer) {
    if (!isInGame(blockedPlayer)) {
        throw std::runtime_error("Player not in game!");
    }
    if (blockedPlayer.role()!="Assassin") {
        throw std::runtime_error("This Player can't block that!");
    }
    Assassin *blockedAssassin = dynamic_cast<Assassin*>(&blockedPlayer); 
    if (!blockedAssassin->isCouped()) {
        throw std::runtime_error("The blocked Player didn't steal!");
    }

    getCurrGame()->revivePlayer(blockedAssassin->getCoupedPlayer()); 
    blockedAssassin->resetPlayer();
}