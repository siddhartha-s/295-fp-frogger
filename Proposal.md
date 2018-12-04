# Proposal
I will be making a game similar to Frogger:

- The screen consists of two halves, the road and the river. The objective of the game is to get the user-controlled frog to cross from the bottom to the top without getting hit by traffic and without following into the river. (Image below for reference)
-  The player moves the frog using the arrow keys on the keyboard.
- The bottom half, (hereon referred to as the `road section`), will have different vehicles of different lengths moving through the screen periodically, in their respective rows. Each vehicle type would be represented by a unique sprite.
- The top half, (hereon referred to as the `river section`), has different objects (eg: logs, boxes, turtles) moving in the opposite as the traffic in the road section. Each object would be of different lengths and have different sprites.
- The player must cross the river section by moving the frog across the section by having the frog land on the moving objects.
- While the frog is on an object in the `river section`, the frog moves along with the object.
7. If the vehicle and the frog collide in the `road section`, the player loses a life and restarts at the bottom of the screen.
- In the `river section`, the player loses a life if the frog lands in the river (the player moves the frog in a cell which does not have an object on it).
- If the frog reaches the right or left end of the screen (by staying on an object while it’s crossing the screen) and in the next frame, the object moves off the screen, the frog falls into the river and the player loses a life.
- The player will receive 10 points every time he crosses one row of the screen.
- There will be a time limit (represented by a countdown timer) set within which the player attempts to move the frog from the bottom of the screen to the top of the screen, while avoiding collisions and not falling into the river. If the counter reaches zero and the player has not reached the top of the screen, the player loses the game.
- The player has 3 lives.
- The player wins the game if he is able to get a frog into the top row of the screen.
