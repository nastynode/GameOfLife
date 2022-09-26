## Conway's Game of life

For more info on the game, it's creator, and the rules, check out https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

## Compile
Makefile uses g++ cpp compiler. Also requires ncurses package. You can try running the bash setup script to check for required resources.
To compile, run
    ```make```
in your command line, then
    ```./life```
If you want to use a different compiler, make sure you link the dependencies (especially ncurses).

## How to play
Run the game and use the arrow keys to move your cursor and the space bar to place your "starter cells". Then press enter to begin the simulation!
Clicking any key will iterate to the next generation. Holding down a key will iterate generations quickly.

Rules:
    1) Each cell with  <= 1 neighbors dies
    2) each cell with >= 4 neighbors dies
      - therefore, each cell with 2 or 3 neighbors survives
    3) each cell with 3 neighbors becomes alive
