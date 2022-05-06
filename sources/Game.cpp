#include "Game.hpp"
#include "Player.hpp"
using namespace coup;

const int MAX_PLAYERS = 6;

Game::Game() {
    gameStarted = false;
    gameFinished = false;
    playerTurn = nullptr;
    playerTurnID = 0;

}

void Game::revivePlayer(Player *revivedPlayer) {
    /**
     * @brief This function is called when contessa blocks a coup made by an assassin for 3 coins. 
     * It sets the isAlive field of the player to True, and adds it back to it's slot of the turn system.
     */
    if (onlinePlayers.at(revivedPlayer->getid())==nullptr) {
        //std::cout << "\t\tGAME MESSAGE: Reviving " << revivedPlayer->getNickname() << "\n";
        onlinePlayers[revivedPlayer->getid()] = revivedPlayer;
        revivedPlayer->setAlive(true);
        return;
    } 
    if (onlinePlayers.at(revivedPlayer->getid())==revivedPlayer) {
        throw std::runtime_error("player already alive");
    }
    throw std::runtime_error("fatal error, slot taken");

}

size_t Game::addPlayer(Player *newPlayer) {
    /**
     * @brief This function is called by the constructor of a Player object.
     * It adds the player to the game (adds it to the turn system i.e vector) and returns the ID of the player (0-5).
     */
    if(gameStarted||gameFinished) {
        throw std::runtime_error("can't add new players, game already initiated!");
    }
    if (onlinePlayers.size()==MAX_PLAYERS) {
        throw std::runtime_error("can't add new players, game full!");
    }
    if (onlinePlayers.empty()) {
        playerTurn = newPlayer;
    }
    onlinePlayers.push_back(newPlayer);
    return onlinePlayers.size()-1;
}

bool Game::checkForWin() {
    size_t numOfplayers = 0;
    for (size_t i = 0; i < onlinePlayers.size(); i++)
    {
        if (onlinePlayers.at(i)!=nullptr) {
            numOfplayers++;
        }
    }
    
    if (numOfplayers == 1) {
        gameFinished = true;
        return true;
    } 
    return false;
    
}

void Game::removePlayer(Player *losingPlayer) {
    /**
     * @brief This function is called when a player is couped. 
     * It also checks if the game is finished. (If only one player remaining)
     */
    for (size_t i = 0; i < onlinePlayers.size(); i++)
    {
        if (onlinePlayers.at(i)!=nullptr) {
            if (onlinePlayers.at(i)==losingPlayer) {
                //std::cout << "\t\t GAME MESSAGE: Removing " << losingPlayer->getNickname() << " from the game!\n";
                onlinePlayers[i] = nullptr;
                break;
            }
        }
    }
    losingPlayer->setAlive(false);
    if (checkForWin()) {
        gameFinished = true;
    }
}

std::vector<std::string> Game::players() const{
    std::vector<std::string> playerNicknames; 
    for (size_t i = 0; i < onlinePlayers.size(); i++)
    {
        if (onlinePlayers.at(i)!=nullptr) {
             playerNicknames.push_back(onlinePlayers.at(i)->getNickname());
        }
    }
    return playerNicknames;
}

std::string Game::turn() const{
    return playerTurn->getNickname();;
}

Player* Game::turnPlayer() const{
    return playerTurn;
}

bool Game::isRunning() const{
    if (gameFinished) {
        return !gameFinished;
    }
    return gameStarted;
}

void Game::nextTurn() {
    /**
     * @brief This function is responsible for the turn system in the game. 
     * It is called at the end of every move that satisfy a complete turn of a Player. 
     * 
     * The way it works is iterating over the vector of players until we find the current player and adding one to the iterating index.
     * We then initialize the pointer of the current playing Player to the (Player located at the new index) % (amount of players).
     * 
     * If the new Player is not playing (couped, for example) we then call the function again to calculate the next player. (recursion)
     */
    gameStarted = true; 
    if (checkForWin()) {
        gameFinished = true;
    }
    playerTurnID++;
    playerTurn = onlinePlayers.at(playerTurnID%onlinePlayers.size());
    if (playerTurn==nullptr&&!gameFinished) {
        nextTurn();
        return;
    } 
    if (gameFinished) {
        for (size_t i = 0; i < onlinePlayers.size(); i++)
        {
            if (onlinePlayers.at(i)!=nullptr) {
                playerTurn = onlinePlayers.at(i);
                break;
            }
        }
    }
    if (playerTurn!=nullptr) {
        //std::cout << "\t\tGAME MESSAGE: " << playerTurn->getNickname() << "'s(" << playerTurn->role() << ") turn\n";
    }
}

std::string Game::winner() {
    /**
     * @brief returns the winner of the game
     * 
     */
    if (!gameFinished) {
        throw std::runtime_error("game did not finish");
    }
    for (size_t i = 0; i < onlinePlayers.size(); i++)
    {
        if (onlinePlayers.at(i)!=nullptr) {
            return onlinePlayers.at(i)->getNickname();
        }
    }
    
    return "fatal error";
}