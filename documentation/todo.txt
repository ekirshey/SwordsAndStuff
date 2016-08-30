Cannon Game - Version 0.02

Author: Erik Kirshey

3/17/15: Began initial project. Moved the KCS(Component System) into the project and started working on the
Game State Management.

3/18/15: Ended up really bulking up the state management system before adding in SDL Stuff

TODO:
    1) First major task is to add in the SDL support, so you can more accurately describe
       the game states
       3/18/15: added basic support
            1a) Add an Image Manager of some sort
                3/19/15: Bumped to 0.017 and added in texturemanager and texture class. hasnt been tested yet
                3/19/15: Had to dynamically allocate the texture inside the manager. I think the SDL_Texture* pointer
                         was being lost somehow. It is loading the image properly but I seem to have a potential memory leak.
                         Update: Memory usage seems to level off at 18,316 K - 18320 K. Takes a while to get to that point and I'm not
                         sure if it's a consistent plateau.
                         Images Work! Have background and buttons working! woo (bumped to 0.018)
    2) Finish Game State Management
        3/18/15: Need a good way to add a new state, such as pause, that will be removed when you leave and added when you enter
        3/19/15: Seems to be good at this point. Bumping to 0.02
    3) Begin work on adding in objects and evaluate KCS.
        3a) Revise KCS if/as needed
            3/19/15: Background and button objects are in. Need to figure out how I want to do callbacks in a component system
            3/20/15: Had to pass the system component bits to the add entity function in the system. It was using the interface bits
                     and not the correct system bits (i.e System::BITs not CallbackSystem::BITs)
            3/22/15: Need to seriously consider adding a tagging system. This way I can add entities to systems based on tags and not
                     just the component/system ids.
     4) Add Shooting System.
            3/22/15: Basic system implemented. Need to fix bounding boxes so they rotate.
     5) Add "Monster" Spawner
            5/31/15: Done
     6) Adding Item Manager and item system to game. To facilitate this need to wrap ECSManager in an object manager.
     7) Add some sort of mechanism to detect duplicate component ids.
            6/2/15: Initial Attempt Done. Just added a bit mask when adding a component to an entity. If UUID & COMPONENTID != 0 then
                    a component with that id is already there.
     8) Added RPGStatsComponent and InventoryComponent. THe RPGStatsComponent needs to be fleshed out with what I actually want in the game. Also
        How do I calculate stats in a component based on other stats? I think I'll just do it in the functions.
     9) Periodic crash. I'm not sure when it happens. I tried some things that I thought stopped it but after putting them back in the crash isnt happening.
        Leaning towards the way the movement system removes off screen objects.
            6/4/15: I think i fixed it. I was messing with the objects bounding box AFTER I removed it. I have no idea why that didnt crash the cannongame version.
     10) You need to add systems in the right order with the right indices or it crashes. That is kind of dumb. You should make it better.
     11) Basic HUD system in place. I've added a fillbar for health and mana and I just need to add customization and such to them, then eventually
         make them look pretty.

Misc:
    1) Tag system for systems outside of the normal process loop
    2) Double check verification so a system cant try to access a component that isn't there
    3) Mouse response isn't good as needed. You can get into a state where the button is held down but no considered held down
        3/20/15: Seems fixed but keep an eye on it. Had to add checks for released mouse
    4) Tidy Magic Numbers
    5) Why are the entity manager and system manager unique pointers?
