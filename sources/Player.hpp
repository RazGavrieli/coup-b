#ifndef Player_H
#define Player_H


#include <iostream>
namespace coup
{
    class Game;
    class Player {
                /*private fields*/
        int amountOfCoins;
        size_t id; // (0-5)
        std::string nickname;
        Game *currGame;
        bool didForeign_aid;
        bool alive;    
        
        public:   
                /* --- constructors --- */
            Player(Game &, std::string);

                /* --- getters --- */
            Game* getCurrGame() const;
            std::string getNickname() const;
            bool isPlaying() const;
            bool didForeign() const;
            bool isInGame(Player &);
            bool isMaxCoins() const;
            bool isAlive() const;
            virtual std::string role() const;
            int coins() const;
            size_t getid() const;
                /* --- setters --- */
            void setAlive(bool);
            void incrementCoins(int);
            virtual void resetPlayer();
            
            
                /* --- functions --- */
            void income();
            void foreign_aid();
            virtual void coup(Player&);

            virtual void transfer(Player&, Player&);
            virtual void tax();
            virtual void steal(Player&);
            virtual void block(Player&);
        


    };
} 
#endif