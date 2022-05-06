#include "Player.hpp"
#include "Game.hpp"

#include <iostream>
using namespace coup;

const short INIT_COINS = 0;
const short MAX_COINS = 10;
const short COUP_PRICE = 7;

// Player::Player() { 
//     // for default constructor of a game
// }
Player::Player(Game & game, std::string name) {
    nickname = std::move(name);
    amountOfCoins = INIT_COINS;
    alive = true;
    didForeign_aid = false;
    id = game.addPlayer(this);
    currGame = &game;
}

void Player::incrementCoins(int increment) {
    this->amountOfCoins+=increment;
}

Game* Player::getCurrGame() const  { return currGame;}

std::string Player::getNickname() const  {  return nickname;}

bool Player::isAlive() const {  return alive;}
bool Player::didForeign() const {  return didForeign_aid;}
bool Player::isPlaying() const{    
    if (!currGame->isRunning()&&currGame->players().size()<2) {
        throw std::runtime_error("not enough players to start the game!");
    } 
    return currGame->turnPlayer()==this;
    }
bool Player::isMaxCoins() const{    return coins()>=MAX_COINS;}
std::string Player::role() const  {     return "This player still has no role";}
int Player::coins()const {  return amountOfCoins;}
size_t Player::getid() const {  return id;}

void Player::setAlive(bool isAlive) {
    alive = isAlive;
}
void Player::resetPlayer() {
    didForeign_aid = false;
}

void Player::income() {
    /**
     * @brief Initiates "income" move to the player
     * 
     */
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (isMaxCoins()) {
        throw std::runtime_error("Player must coup!");
    }
    
    incrementCoins(1);
    resetPlayer();
    currGame->nextTurn();
}

void Player::foreign_aid() {
    /**
     * @brief Initiates "foreign aid" move to the player (blockable by duke)
     * 
     */
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (isMaxCoins()) {
        throw std::runtime_error("Player must coup!");
    }

    incrementCoins(2);
    resetPlayer();
    didForeign_aid = true;
    currGame->nextTurn();
}
bool Player::isInGame(Player &coup) {
    return !(coup.currGame!=currGame||!coup.alive);
}

void Player::coup(Player &coup) {
    /**
     * @brief Initiates "coup" move to the Player that is being couped.
     * 
     */
    if (!isPlaying()) {
        throw std::runtime_error("this isn't the player's turn!");
    }
    if (amountOfCoins<COUP_PRICE) {
        throw std::runtime_error("Not enough coins");
    }
    if (!isInGame(coup)) {
        throw std::runtime_error("Player not in game!");
    }
    currGame->removePlayer(&coup);
    resetPlayer();
    incrementCoins(-COUP_PRICE);
    currGame->nextTurn();
}

void Player::transfer(Player &payer, Player &receiver) {
    throw std::runtime_error("This Player can't transfer");
}

void Player::tax() {
    throw std::runtime_error("This Player can't tax");
}

void Player::steal(Player &a) {
    throw std::runtime_error("This Player can't steal");
}

void Player::block(Player &a) {
    throw std::runtime_error("This Player can't block "); 
}