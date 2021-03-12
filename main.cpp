//  BATTLESHIPS:
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "player.h"

int convert_char_to_num(char a){
    if (a=='A' || a == 'a') return 1;
    if (a=='B' || a == 'b') return 2;
    if (a=='C' || a == 'c') return 3;
    if (a=='D' || a == 'd') return 4;
    if (a=='E' || a == 'e') return 5;
    if (a=='F' || a == 'f') return 6;
    if (a=='G' || a == 'g') return 7;
    if (a=='H' || a == 'h') return 8;
    if (a=='I' || a == 'i') return 9;
    if (a=='J' || a == 'j') return 10;
    
    return 0;
}

void attack_opponent(player &player1, player &player2){
    std::cout << player1.get_name() << ", it's your turn to attack " << player2.get_name() << std::endl;
    player1.display_attack_board();
    
    char letter; int number;
    std::cout << "What position do you wish to attack?: ";
    std::cin >> letter >> number;
        
    player1.update_board(convert_char_to_num(letter), number, player2);
   }


void play(){
    
    // First players must set up their battleship positions.
    //     This can be done either manually or randomly
    player player1;
    player1.random_setup();
    
    player player2;
    player2.random_setup();
    
    while (true) {
    attack_opponent(player1, player2);
    attack_opponent(player2, player1);
   }
   
}



int main() {
    
    
    play();
    
    

    return 0;
}
