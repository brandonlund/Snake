Log
------
April 5-9
------
Read the assignment thoroughly.

Think of various methods to make Pathon score high. So far I'm thinking DFS because it generally takes a longer
path allowing for a little bit of self tail management.

April 10
------
Created repository and push inital, given, files.

Tried DFS path finding. This did not work because it was getting stuck in a loop between two vertices since I was
recalculating the path for each time I moved Pathon.

Tried BFS path finding. This method is working good so far except for the expected lack of tail management.

Worked on some light tail management. So far so good except Pathon gets caught in self-made cut edges as well as
wrapping in on itself.

April 11-22
------
It seems like not a lot went on throughout this time, but I did some research into how other people created their
players outside of this class. I found a pretty neat "reverse A*" algorithm by Code Bullet on YouTube that I may
try to implement.

April 23
------
Work on A* pathfinding. Pathon scores slightly better. Have to figure out reverse A* to mimick Code Bullet's player.

April 26
------
Try to implement obstacles where there are cut edges to prevent the snake from
trapping itself. This didn't work well at all. Not much improvement.

April 27-29
------
Everything is not really working as I have expected it to at this point. I've given up on trying to implement Code 
Bullet's "reverse A*" algorithm, I cannot figure it out at this point. These past couple of days I've made it such 
that obstacles are placed next to the snakes tail so that it will not travel next to itself while pathing to the food. 
It seems like it does exactly how I want it to in the beginning stages, but continues to trap itself.

April 30 - May 1
------
During this time I worked on keeping track of the tail. This method involved having a "base node" in/near the top left corner.
I ultimately ended up switching back to my previous astar-bfs algorithm because that's the best scoring algorithm I have.
The "base node" algorithm is a pretty simple idea. Grab food then go back to the base node and start coiling the snake.
The snake will be coiled once the head passes through the base node and then the end of the tail passes through the base node.
Once the snake is done coiling it will repeat the process of grabbing the food, returning to the base node and coiling again, repeat.
This algorithm seemed to not work because the snake was still trapping itself in it's tail. I could probably write a fix for this but,
sadly, I am out of time.

August 3
------
Implemented feature to see the path generated per every move.

Summary
------
Overall, this was a fun, but frustrating, project to work on. I think my snake, Pathon, does do alright, but definitley is not
living up to what I set out to achieve. All of my ideas did not turn out as I expected them to and they all scored fairly low.
If I were to do this project again, I would probably focus more on keeping track of the tail like I have been trying for the
past couple of days. Tail management is definitely the most important aspect of this program if you want any sort of high scoring
snake.

Compilation Instructions
------
When adding files (and you should) to your player, modify the Makefile such that the files required for your Player are added to the PLAYER_SOURCE group in the Makefile.
Example:

PLAYER_SOURCE = player.cpp graph.cpp dfsPaths.cpp logicFunctions.cpp
Of course, your file names will likely be different. You are welcome to modify the Makefile to suit your preference but it must create a shared library by the name libPlayer.so regardless of anything else you change it to do. In its original state, it does this using only the player.cpp file (and associated .h file).
The included Makefile can build the graphic version of the game snake or the bulk testing version of the game driver:

Build the bulk version of the game and run it 100 times collecting the results:

% make driver
% for count in $(seq 1 100)
do
echo $count
./driver >> Out.dat
done
1
2
3
4
...
The commands (above) are bash shell commands. The first line is a for loop which says, for each number in a sequence from 1 to 100, assign the variable count to the number. The do is like the opening brace for a block of code. The echo just echos the index of the loop currently running. This is so you know your player isn't hung. The driver >> Out.dat says, run the driver executable and append the output to the file named Out.dat. The done is like the closing brace for the for loop.
After running the (above) bash script, you'll have a file named Out.dat which contains the results of 100 runs concatenated together. You can use this script to total and average those runs as follows:

% ./avgScores.pl < Out.dat
Number Items : 100
Average Score: 31.864
Maximum Score: 72
The script is a perl script which just grabs each result, sums, and averages the results. If you are going to run it, make sure to change its execute flag so it will run:
% chmod +x avgScores.pl
Build the graphic version of the game and run it setting the width, height, and whether or not obstacles should be placed in the playfield
% make snake
% snake 40 33 [true|FALSE]
You can change the playfield so that it will add obstacles by adding a true as the third command line parameter. If you leave the third parameter off, the default value is false
The first time running in a shell you will need to set the LD_LIBRARY_PATH environment variable. This allows the driver and graphics part of the code to find your player's shared library (libPlayer.so), even if it's not in the local directory, at runtime. We'll talk more about the benefits of shared libraries in the coming weeks.

% export LD_LIBRARY_PATH=.
% make driver           // build the bulk testing / no graphic driver
% make snake            // build the graphic version
If you do not do this, you will get an error which looks something like this:
$ snake
snake: error while loading shared libraries: libPlayer.so: cannot open shared object file: No such file or directory

Compilation Instructions Author: Dr. Paul Hinker

Emscripten Compilation Instructions and to Host on the Web
------
export LD_LIBRARY_PATH=.

em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 application.cpp main.cpp playfield.cpp snakeGraph.cpp biconnected.cpp cc.cpp game.cpp player.cpp dfsPaths.cpp bfsPaths.cpp bridges.cpp astar.cpp -o snake.html

emrun snake.html --port 4000
port forward to port 4000

