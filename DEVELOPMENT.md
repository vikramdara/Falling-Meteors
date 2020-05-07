# Development

---
**4/19/2020** Changed library from Chipmunk to Box2D because
it was easier to implement. Added in Box2D library. Added
some logic to draw a meteor.

**4/23/2020** Added logic for bodies for ground and meteor.
Have to add logic for making the meteor fall.

**4/28/2020** Moved around all the code from the app class into their own separate
classes. Fixed a lot of bugs regarding position of bodies. Have to fix major bug
regarding lack of collision.

**4/29/2020** Tried creating smart pointers, moving code around, changing position
coordinates, making constructors for the objects, etc... nothing is fixing the bug.

**4/30/2020** Finally was able to fix bug by seeing what happens when I add a meteor
upon a mouse click. Bug was caused by a really weird scaling issue unique to
specific computers. Added logic for meteors falling from random spots in the sky
and created the sprite and made it move.

**5/1/2020** Working on collision behavior between meteor and player. All code is
Setup, just have to fix some issues regarding contact listeners.

**5/1/2020** Fixed bugs collisions effects work fine.

**5/3/2020** Added code to delete the meteor bodies from 
the screen once it is out of the window. Planning on getting rid of the
ground body as it doesn't make much sense in my project.

**5/4/2020** Added the GameOver screen and made replay logic so users can now replay the game.
Next step is to remove the ground body.

**5/5/2020** Got rid of the groundbody and refactored code accordingly. I was also make mechanics for the user to
move with the mouse. Unfortunately key movements have a delay on drag. For now the basic mechanics of the first level is
done, now I have to add new levels.

**5/6/2020** Started adding barrier logic. Unfortunately dealing with memory for the barrier is very difficult. 

**5/6/2020** Made a wave, conversions, and direction class. Conversion class allows me to bypass 
ridiculous errors regarding constants.

**5/6/2020** Finally finished mechanics of the game and fixed bugs. I also added texture refs and music
to make the game a lot more appealing.

**5/6/2020** Finished ReadMe.md