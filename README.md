GameOfLife
==========
Jon Gautsch
Lab 7 - Conway's Game of Life
10/29/12
CSE 20211

#Running the game of life. 

- compile the game of life by entering "gcc life.c -o life" in the terminal
- then run ./life
- enter 'a' to enter in a new "live" cell
- after entering in all the live cells you want, enter 'p' to run forever
- CTRL C to quit

##Running the game of life using scenes
- To run the game of life with pre made scence, run "./life < scene#.life"
- A description of the various scenes can be found below:

For scene1.life, there are 4 different static shapes. These shapes do not change with each iterat$
of the game of life.

For scence2.life, I made 4 different oscillating shapes. These shapes oscilate, but they never gr$
and never disappear either. They will oscilate onto infinity.

For scene3.life, I made 4 gliders that start fairly close to the center of the grid, but then gli$
off in 4 different directions.

For scene4.life, I implemedted one of the shapes described as a "methusela." This means that it g$
through very many itterations before settling. This particular methusela shape explodes into 633 $
cells before settling into static shapes and simply oscilations.

For scene5.life, I implemented Gosper's Glider Gun. The "gun" shoots off gliders infinitely. Conw$
bet $50 that an infinitely growing function couldn't be made, and Gosper from MIT was able to mak$
Since then, other infinitely growing functions have been made, but Gosper's Glider Gun was the fi$
Gosper won the $50. (source: wikipedia).