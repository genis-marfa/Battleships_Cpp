#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Matrix.h"

// Set up a "random device" that generates a new random number each time the program is run.
std::random_device rand_dev;
// Set up a pseudo-random number generater "rnd", seeded with a random number
std::mt19937 rnd(rand_dev());


class ship {
    private:
        unsigned size{};
        std::string orientation{};
        std::string type{};
    
    public:
    // Param. constructor:
        ship (std::string type_, bool rand) ;
        
        // Function to verify if a ship can be placed (defined outside). Placed if possible.
        bool place(board &player_board, int x, int y, bool rand);
        
        // Get ship type:
        std::string get_type(){return type;}
};

ship :: ship(std::string type_, bool rand) {
    
    std::vector<std::string> valid_types {"aircraft carrier", "battleship", "cruiser", "submarine", "patrol boat"};
    std::vector<std::string>::iterator it = std::find(valid_types.begin(), valid_types.end(), type_);
    
    type = type_;
    
    while (it == valid_types.end()) {
        std::cerr << "Invalid ship type " << type_ << ", please enter a valid type: ";
        std::cin >> type_;
        it = std::find(valid_types.begin(), valid_types.end(), type_);
        type=type_;
    }
    
    if       (type == "aircraft carrier") size = 5;
    else if  (type == "battleship") size = 4;
    else if  (type == "cruiser") size = 3;
    else if  (type == "submarine") size = 2;
    else if  (type == "patrol boat") size = 1;
    
    if (type == "patrol boat") orientation = "v";
    
    else {
        if(!rand){
            while (orientation != "v"  && orientation != "h"
                   && orientation != "ld" && orientation != "rd")
                {
                    std::cout << "Please specify the orientation ( h / v / rd / ld ) for your " << type << ": ";
                    std::cin >> orientation;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.clear();
                }
        }
        else {
            std::vector<std::string> orientations = {"h", "v", "ld", "rd"};
            int i = rnd()% 4;
            orientation = orientations[i];
            }
        }
}



bool ship :: place(board &player_board, int x, int y, bool rand)
{
    int board_side = sqrt(player_board.size());
    
    if (orientation == "v")
    {
        // Verify ship can be placed:
        if (x+size > board_side) {
            if (!rand) std::cerr << "Out of range" << std::endl;
            return false;
        }
        for (unsigned i{0}; i< size; i++) {
            if (player_board(x+i,y) > 0 )
            {
                if (!rand) std::cerr << "You already have a ship there" << std::endl;
                return false;
            }
        }
        // If it did not return false, place ship:
        for (unsigned i{0}; i< size; i++) player_board(x+i,y) = 1.;
    }
    
    else if (orientation == "h")
    {
        // Verify ship can be placed:
        if (y+size > board_side) {
            if (!rand) std::cerr << "Out of range" << std::endl;
            return false;
        }
        for (unsigned i{0}; i< size; i++) {
            if (player_board(x,y+i) > 0 )
            {
                if (!rand) std::cerr << "You already have a ship there" << std::endl;
                return false;
            }
        }
        // If it did not return false, place ship:
        for (unsigned i{0}; i< size; i++) player_board(x,y+i) = 1.;
        
    }
    
    else if (orientation == "rd")
    {
        // Verify ship can be placed:
        if (y+size > board_side || x+size > board_side) {
            if (!rand) std::cerr << "Out of range" << std::endl;
            return false;
        }
                      
        for (unsigned i{0}; i< size; i++) {
            if (player_board(x+i,y+i) > 0 )
            {
                if (!rand) std::cerr << "You already have a ship there" << std::endl;
                return false;
            }
        }
        
        // If it did not return false, place ship:
        for (unsigned i{0}; i< size; i++) player_board(x+i,y+i) = 1.;
    }
    
    else if (orientation == "ld")
    {
        // Verify ship can be placed:
        if (y-size > board_side || x+size > board_side) {
            if (!rand) std::cerr << "Out of range" << std::endl;
            return false;
        }
                      
        for (unsigned i{0}; i< size; i++) {
            if (player_board(x+i,y-i) > 0 )
            {
                if (!rand) std::cerr << "You already have a ship there" << std::endl;
                return false;
            }
        }
        
        // If it did not return false, place ship:
        for (unsigned i{0}; i< size; i++) player_board(x+i,y-i) = 1.;
    }
    
    std::cout << "Successfully placed your " << type <<"." << std::endl;
    return true;
}
