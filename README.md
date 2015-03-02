TLB - The Left Behind (Working Title)
===

TLB is a game I am developing as an educational exercise to learn game development and get game development experience. When I began the project, my main objective was to learn how things are done at each layer of game and so I decided to develop the game from scratch, without using a preexisting engine. 

The game is developed in C++ using the SDL graphics library to render 2D graphics and is cross-platform Windows and Linux.

Since this is a personal project for my own enjoyment and growth, I can only work on it in my freetime and so development progresses slowly, especially since it is also a solo project.

The game is a real-time strategy game presented in a top-down/three-quarter view where the player selects units and issues orders. It's designed to be a compromise between fast-paced RTS and strict turn based games, so it is real-time but the player may pause at any time and queue up their commands. Currently it is planned to be single player only.

Here are the things that are currently in and working:
- Game state classes independent from the main game loop
- Tile based map system that reads in XML defined map files
- Sprite animation system that reads in XML defined sprite sheets and renders based on entity's current action
- A* algorithm pathfinding for player characters and enemies
- State machine driven AI behavior for enemies and player characters
- Mouse and keyboard controls
- Event handling system
- Basic real-time combat system

The graphics are merely placeholders and made up of free art I have found available on the internet.

Finally, since I am building the engine from scratch, all of my work so far as been getting the basic mechanics of the game functioning and thus the game lacks gameplay content at the moment (such as levels, missions, quests, story, etc). I am designing it such a way that once even features are working, content can be written in external files (such as XML) and loaded in. Therefore, the demo is extremely basic and currently consists of controlling a single character against a single zombie. The demo can be downloaded at https://dl.dropboxusercontent.com/u/10397390/TLB%20Demo.zip . Simply extract the folder and run the EXE.

Here is a current screenshot. ![alt tag](http://i.imgur.com/naYMgTq.png)


