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

Summary
------
Overall, this was a fun, but frustrating, project to work on. I think my snake, Pathon, does do alright, but definitley is not
living up to what I set out to achieve. All of my ideas did not turn out as I expected them to and they all scored fairly low.
If I were to do this project again, I would probably focus more on keeping track of the tail like I have been trying for the
past couple of days. Tail management is definitely the most important aspect of this program if you want any sort of high scoring
snake.
