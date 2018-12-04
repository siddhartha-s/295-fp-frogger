# IPD Homework 7: Hexapawn

  - **Due: Tuesday, November 27 at 11:59 PM**

## Summary

For this homework, you will write an interactive program implementing
the two-player abstract strategy game
[Hexapawn](https://en.wikipedia.org/wiki/Hexapawn).

## Goals

To design a whole program from scratch, while maintaining good style and
logical factoring.

## Specification

The rules of Hexapawn are available in [the Hexapawn Wikipedia
article](https://en.wikipedia.org/wiki/Hexapawn), and your program
should implement these rules.

Unlike traditional 3×3 Hexapawn, your game should support board
dimensions from 3×3 to 8×8. Changing a dimension should be as easy as
changing a constant (or you can integrate dimension selection into your
UI).

You must implement a graphical user interface, using the [`ge211`]
library. At each turn, your game should display the state of the board
and somehow indicate which player’s turn it is. (I’ve indicated that
below by rotating the board so that the player who is moving is at the
bottom, moving up; you could indicate it another way, though.) The UI
should then allow the player to select a move. Here is an example of
what that display might look like (approximated textually) for a 5×3
game, when it is the player B’s turn:

`ge211`: https://tov.github.io/ge211/

````
+---+---+---+---+---+
| W |   | W | W | W |
+---+---+---+---+---+
|   | W |   |   |   |
+---+---+---+---+---+
| B | B | B | B | B |
+---+---+---+---+---+
````

At this point, the player B can move by first clicking which piece
to move, and then clicking where to move it to.

When a player wins, either by reaching the other side or leaving the
other player with no available moves, a messages to this effect should
be displayed, and it should not be possible to make further moves.

## Deliverables

Your deliverables are:

  - The source code of the `hexapawn` program as described
    above.

  - Automated tests for your model. (You do not needs tests for the
    view and controller.)

  - A plain text file `EVALUATION.md` (which can use
    [Markdown](https://help.github.com/articles/github-flavored-markdown/)
    formatting if you like) in which you describe the design of your
    program. In particular please discuss, briefly:

      - how you tested your programs to ensure correctness and

      - anything that surprised you while doing this assignment.

    When discussing your code, please provide file and line number
    references.

## How to submit

Please submit a ZIP or TAR archive of your whole project. Your project
should build in CLion using the configuration in CMakeLists.txt. Before
creating the archive, be sure to clean your project (*Run* menu /
*Clean*).
