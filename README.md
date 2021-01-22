# alienInvasion

This is just a prototype of game with very simple mechanic.

Scenes:
1. Main menu
Just lobby with configs and other objects. Every clickable button change colour because of cursor collisions.
New game - open game scene.
Options - open config setup.
Level editor - open level editor.
Exit - go out.

2. Level Editor
You can place some objects (wall, doorIn, doorOut, spawnPoint) using left mouse button.
RBM - to destroy object.
W,A,S,D - to move camera.
Q - to  change active object (that would be placed after mouse clicking)
Mouse scrolling - to looping scale map.
Button "Clear" - to clear all level.
Button "Save" - to save level and exit (program saves in resource file and loads after reloading game).

Wall - just a wall, nothing more.
DoorIn - input place of player.
DoorOut - output place of player (after stepping there you would win level).
SpawnPoint - place of spawning alians.

3. Game
W,A,S,D - to move player. Camera moves automaticly.
Mouse scrolling - to looping scale map.
LBM - shoot.
LBM + scrolling - you can exchange your damage and attack speed (damage per second are constant).