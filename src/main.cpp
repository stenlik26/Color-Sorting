#include "Utils.h"
#include "Game.h"
#include <time.h>
#include <iostream>
#include "Renderer.h"
int main()
{
    srand(time(NULL));
    
    Game game;
    game.init_game(Hard);

    Renderer renderer(&game);

    while (true)
    {
        if (!renderer.render())
            break;
    }

   /* while (true) {
        std::cout << "------------------------------------\n";

        for (size_t i = 0; i < game.get_stacks().size(); i++)
        {
            std::cout << i << ") ";
            for (size_t j = 0; j < game.get_stacks()[i].size(); j++)
            {
                std::cout << game.get_stacks()[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------------------\n";
        std::cin >> from >> to;

        if (from == -1) {
            game.restart_game();
        }

        std::cout << "Valid move: " << game.apply_move(from, to) << std::endl;
        std::cout << "Game state: " << (int)game.get_game_state() << std::endl;
        
        std::cout << "Stack locks: ";
        for (size_t i = 0; i < game.get_stacks_locks().size(); i++)
        {
            std::cout << game.get_stacks_locks()[i];
        }
        std::cout << "\n\n";

    }*/
    return 0;
}