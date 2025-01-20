#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"

#include "DynamicArray.h"
#include "HashTable.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920;
    int screenHeight = 1000;



    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------



    srand(time(NULL));

    // Setting Upo the Critter Textures;
    
    // Setting The Textures
    Texture2D JellyFish = LoadTexture("res/10.png");
    Texture2D Squids = LoadTexture("res/9.png");

    // Adding the Textures to a Hash Table
    HashTable TableHash;
    TableHash["JellyFish"] = &JellyFish;
    TableHash["Squids"] = &Squids;


    DynamicArray jellies(50);
   // Critter critters[1000]; 











    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100+(rand()%200), -100+(rand()%200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);




        // create a critter in a random location
        Critter critter;
        critter[i].Init(
            { (float)(5+rand() % (screenWidth-10)), (float)(5+(rand() % screenHeight-10)) },
            velocity,
            12, "res/10.png");
        jellies.PushBack(critter);
    }








    Critter destroyer;
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, "res/9.png");



    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        float delta = GetFrameTime();

        // update the destroyer
        destroyer.Update(delta);
        // check each critter against screen bounds
        if (destroyer.GetX() < 0) {
            destroyer.SetX(0);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetX() > screenWidth) {
            destroyer.SetX(screenWidth);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() < 0) {
            destroyer.SetY(0);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() > screenHeight) {
            destroyer.SetY(screenHeight);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }

        // update the critters
        // (dirty flags will be cleared during update)
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            jellies[i].Update(delta);

            // check each critter against screen bounds
            if (jellies[i].GetX() < 0) {
                jellies[i].SetX(0);
                jellies[i].SetVelocity(Vector2{ -jellies[i].GetVelocity().x, jellies[i].GetVelocity().y });
            }
            if (jellies[i].GetX() > screenWidth) {
                jellies[i].SetX(screenWidth);
                jellies[i].SetVelocity(Vector2{ -jellies[i].GetVelocity().x, jellies[i].GetVelocity().y });
            }
            if (jellies[i].GetY() < 0) {
                jellies[i].SetY(0);
                jellies[i].SetVelocity(Vector2{ jellies[i].GetVelocity().x, -jellies[i].GetVelocity().y });
            }
            if (jellies[i].GetY() > screenHeight) {
                jellies[i].SetY(screenHeight);
                jellies[i].SetVelocity(Vector2{ jellies[i].GetVelocity().x, -jellies[i].GetVelocity().y });
            }

            // kill any critter touching the destroyer
            // simple circle-to-circle collision check
            float dist = Vector2Distance(jellies[i].GetPosition(), destroyer.GetPosition());

            if (dist < jellies[i].GetRadius() + destroyer.GetRadius())
            {
                jellies[i].Destroy();
                // this would be the perfect time to put the critter into an object pool
            }
        }
                
        // check for critter-on-critter collisions
        for (int i = 0; i < CRITTER_COUNT; i++)
        {            
            for (int j = 0; j < CRITTER_COUNT; j++){
                if (i == j || jellies[i] .IsDirty()) // note: the other critter (j) could be dirty - that's OK
                    continue;
                // check every critter against every other critter
                float dist = Vector2Distance(jellies[i].GetPosition(), jellies[j].GetPosition());
                if (dist < jellies[i].GetRadius() + jellies[j].GetRadius())
                {
                    // collision!
                    // do math to get critters bouncing
                    Vector2 normal = Vector2Normalize( Vector2Subtract(jellies[j].GetPosition(), jellies[i].GetPosition()));

                    // not even close to real physics, but fine for our needs
                    jellies[i].SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));

                    // set the critter to *dirty* so we know not to process any more collisions on it
                    jellies[i].SetDirty();

                    // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                    // to make sure the other critter is clean before we do the collision response
                    if (!jellies[j].IsDirty()) {
                        jellies[j].SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        jellies[j].SetDirty();
                    }
                    break;
                }
            }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            // find any dead critters and spit them out (respawn)
            for (int i = 0; i < CRITTER_COUNT; i++)
            {
                if (JellyFish[i].IsDead())
                {
                    Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

                    // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                    Vector2 pos = destroyer.GetPosition();
                    pos = Vector2Add(pos, Vector2Scale(normal, -50));
                    // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
                    jellies[i].Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");
                    break;
                }
            }
            nextSpawnPos = destroyer.GetPosition();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKPURPLE);

        // draw the critters
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            jellies[i].Draw();
        }
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!)
        destroyer.Draw();

        DrawFPS(10, 10);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        jellies[i].Destroy();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}