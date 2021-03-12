#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "ship.h"


class player {
    private:
        board ship_board;
        board attack_board;
        std::string player_name;
    
    public:
    
    // Constructor:
    player()
    {
            std::cout << "Enter your name: ";
            std::cin >> player_name;
            
            // Create a 10 by 10 board:
            board size_10_board (10,10);
            ship_board = size_10_board;
            
            for (int i{1}; i<=10; i++){
                for (int j{1}; j<=10; j++) {
                    size_10_board(i,j) = 2;
                }
            }
            attack_board = size_10_board;
    }
    
    // Place on board:
    void place(ship ship) {
        std::cout << "Attempting to place your " << ship.get_type() << ":" << std::endl;
        int x, y;
        std::cout << "Enter the row: ";
        std::cin >> x;
        std::cout << "Enter the column: ";
        std::cin >> y;
        
        bool succesful_placement;
        succesful_placement = ship.place(ship_board, x, y, false);
        
        while (succesful_placement != true)
           {
               std::cout << "Try again:" << std::endl;
               std::cout << "Enter the row: ";
               std::cin >> x;
               std::cout << "Enter the column: ";
               std::cin >> y;
               succesful_placement = ship.place(ship_board, x, y, false);
           }
        std::cout << '\n';
        std::cout << player_name <<"'s ship board:" << std::endl;
        std::cout << ship_board << std::endl;
    }
    
    void random_place(ship ship){
        std::cout << "Attempting to place your " << ship.get_type() << ":" << std::endl;
            int x, y;
            x = rand() % 9 + 1;
            y = rand() % 9 + 1;
        
            bool succesful_placement;
            succesful_placement = ship.place(ship_board, x, y, true);
            
            while (succesful_placement != true)
               {
                   x = rnd() % 9 + 1;
                   y = rnd() % 9 + 1;
                   succesful_placement = ship.place(ship_board, x, y, true);
               }
            std::cout << '\n';
        }
        
    
    void manual_setup(){
        // Typical Fleet:
        //      1x Aircraft Carrier     (size 5)
        //      1x Battleship           (size 4)
        //      1x Cruiser              (size 3)
        //      2x Submarine            (size 2)
        //      2x Patrol Boat          (size 1)
        
        ship ac1("aircraft carrier", false);
        place(ac1);
             
        ship battle("battleship", false);
        place(battle);
             
        ship cruise("cruiser", false);
        place(cruise);
             
        ship submarine1("submarine", false);
        place(submarine1);
             
        ship submarine2("submarine", false);
        place(submarine2);
             
        ship patrol1 ("patrol boat", false);
        place(patrol1);
             
        ship patrol2 ("patrol boat", false);
        place(patrol2);
        
    }
    
    void random_setup(){
        ship ac1("aircraft carrier", true);
        random_place(ac1);
             
        ship battle("battleship", true);
        random_place(battle);
             
        ship cruise("cruiser", true);
        random_place(cruise);
             
        ship submarine1("submarine", true);
        random_place(submarine1);
             
        ship submarine2("submarine", true);
        random_place(submarine2);
             
        ship patrol1 ("patrol boat", true);
        random_place(patrol1);
             
        ship patrol2 ("patrol boat", true);
        random_place(patrol2);
        
        std::cout << player_name <<"'s ship board:" << std::endl;
        std::cout << ship_board << std::endl;
    }
    
    bool hit(int x, int y){
        if (ship_board(x,y) == 1) return true;
        else return false;
    }
    
    std::string get_name(){return player_name;}
    
    void update_board(int x, int y, player opponent){
        if (opponent.hit(x, y)) {
            std::cout << "You hit your opponent's ship!" << std::endl;
            attack_board(x,y) = 1;
        }
        else {
            std::cout << "You hit the water." << std::endl;
            attack_board(x,y) = 0;
        }
    }
    
    void display_attack_board() {
        std::cout << '\n' << player_name << "'s attack board:" << std::endl;
        std::cout << attack_board << std::endl;}
   
};

