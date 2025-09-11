#include <iostream>
#include <string>
#include <math.h>
#include "raygui.h"
#include <raylib.h>

const float PLAYER_RADIUS = 0.1f;

using namespace std;

struct PlayerData
{
    float directionOfView; // Direction of view in radians
    float speedOfPlayer; // Speed of player movement
    float positionOfPlayerX; // X position of player
    float positionOfPlayerY; // Y position of player
};

int gameLoop();
Vector2 getPlayerPositionXY();   
float percent(int integer); // Function to calculate percentage of an integer
void controlForward(PlayerData& p); // Function to control player movement forward
void controlBackward(PlayerData& p); // Function to control player movement backward
void controlLeft(float viewDirect); // Function to control player movement left
void controlRight(float viewDirect); // Function to control player movement right
bool isCollision(float x, float y); // Function to check for collision with walls
float castRay(float angle, float playerX, float playerY); // Function to cast a ray in a specified angle from the player's position
void castWalls(PlayerData p); // Function to cast rays and draw walls
void castFloar(PlayerData p); // Function to cast rays and draw the floor
void castRoof(PlayerData p); // Function to cast rays and draw the roof

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// meterials for field:
// @ = wall
// . = empty space
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

const int MAP_MAX_SIZE = 11; 
char field[MAP_MAX_SIZE][MAP_MAX_SIZE] = {
    {'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@'},
    {'@', '.', '.', '.', '.', '.', '.', '.', '.', '.', '@'},
    {'.', '.', '@', '@', '@', '.', '@', '@', '.', '.', '@'},
    {'@', '.', '.', '.', '.', '.', '.', '.', '.', '.', '@'},
    {'@', '.', '@', '@', '@', '.', '@', '@', '.', '.', '@'},
    {'@', '.', '.', '.', '.', '.', '.', '.', '.', '.', '@'},
    {'@', '.', '@', '@', '.', '.', '.', '.', '.', '.', '.'},
    {'@', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'@', '.', '@', '@', '.', '.', '.', '.', '.', '.', '.'},
    {'@', '.', '.', '.', '.', '.', '.', '.', '.', '.', '@'},
    {'@', '@', '@', '@', '@', '@', '@', '@', '@', '@', '@'}
};



    PlayerData player; // Player data structure
    // player.directionOfView = 0.0f; // Initialize direction of view
    // player.speedOfPlayer = 0.1f; // Initialize speed of player movement
    // player.positionOfPlayerX = getPlayerPositionXY.first; // Initialize X position of player
    // player.positionOfPlayerY = getPlayerPositionXY.second; // Initialize Y position of player








int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "BDe2 - Bad Engine 2.0 - Raylib Edition - by Vito");
    SetTargetFPS(60); 

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    Font font = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (GuiButton({
            (percent(GetScreenWidth()) * 10), 
            (percent(GetScreenHeight()) * 40),
            (percent(GetScreenWidth()) * 20),
            (percent(GetScreenHeight()) * 20)
        }, "PLAY")) {
            
             gameLoop();
         }

        DrawTextEx(font, "BDe2!", {
            (percent(GetScreenWidth()) * 40), 
            (percent(GetScreenHeight()) * 10) },
            (percent(GetScreenWidth()) * 20), 20,
            DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;   
}

int gameLoop() {
   
    player.directionOfView = 0.0f; // Initialize direction of view
    player.speedOfPlayer = 0.05f; // Initialize speed of player movement
    player.positionOfPlayerX = 5.0f; // Initialize X position of player
    player.positionOfPlayerY = 6.0f; // Initialize Y position of player


    



    
    while (!WindowShouldClose()) {

        // Handle player input
        if (IsKeyDown(KEY_W)) {
        controlForward(player); // Call function to control player movement forward
        } if (IsKeyDown(KEY_S)) {
        controlBackward(player); // Call function to control player movement backward
        } if (IsKeyDown(KEY_A)) {
        controlLeft(player.directionOfView); // Call function to control player movement left
        } if (IsKeyDown(KEY_D)) {
        controlRight(player.directionOfView); // Call function to control player movement right
        }






        BeginDrawing();
        ClearBackground(RAYWHITE);
        /*
        // Draw the field
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (field[i][j] == '@') {
                    DrawRectangle(j * 10, i * 10, 10, 10, DARKGRAY); // Draw wall
                } else if (field[i][j] == '.') {
                    DrawRectangle(j * 10, i * 10, 10, 10, LIGHTGRAY); // Draw empty space
                }
            }
        }
         DrawCircle(player.positionOfPlayerX * 10, player.positionOfPlayerY * 10, 5, BLUE);// Draw player
        */
        castFloar(player); // Cast rays and draw the floor
        castRoof(player); // Cast rays and draw the roof
        castWalls(player); // Cast rays and draw walls
       
        
        EndDrawing();
    }

    return 1; // Success
}


Vector2 getPlayerPositionXY() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            if (field[i][j] == 'p') {
                float x = j;
                float y = i;
                return {x, y}; // Return the coordinates of the player
            }
        }
    }
    return { -1.0f, -1.0f }; // Player not found
}

 float percent(int integer) {
     float percentt = integer / 100.0f;
     return percentt;
 }

 bool isCollision(float x, float y) {
    // We check 4 corners around the position taking into account the player's radius
    // If at least one cell is a wall, return "true"

    int left = (int)floor(x - PLAYER_RADIUS);
    int right = (int)floor(x + PLAYER_RADIUS);
    int top = (int)floor(y - PLAYER_RADIUS);
    int bottom = (int)floor(y + PLAYER_RADIUS);

    // Iterate through all cells within the player's radius
    for (int i = top; i <= bottom; i++) {
        for (int j = left; j <= right; j++) {
            if (i < 0 || i >= 11 || j < 0 || j >= 11) return true; // за границей - считаем стеной
            if (field[i][j] == '@') return true;
        }
    }
    return false;
}


void controlForward(PlayerData& p) {
    float newX = p.positionOfPlayerX + cosf(p.directionOfView) * p.speedOfPlayer;
    float newY = p.positionOfPlayerY + sinf(p.directionOfView) * p.speedOfPlayer;

    if (!isCollision(newX, p.positionOfPlayerY)) {
        p.positionOfPlayerX = newX;
    }

    if (!isCollision(p.positionOfPlayerX, newY)) {
        p.positionOfPlayerY = newY;
    }
}


void controlBackward(PlayerData& p) {
    float newX = p.positionOfPlayerX - cosf(p.directionOfView) * p.speedOfPlayer;
    float newY = p.positionOfPlayerY - sinf(p.directionOfView) * p.speedOfPlayer;

    if (!isCollision(newX, p.positionOfPlayerY)) {
        p.positionOfPlayerX = newX;
    }

    if (!isCollision(p.positionOfPlayerX, newY)) {
        p.positionOfPlayerY = newY;
    }
}

void controlLeft(float viewDirect) {
    viewDirect -= (PI/180);
    if (viewDirect < 0) {
        viewDirect += 2 * PI; // Wrap around to keep the angle positive
    }
    player.directionOfView = viewDirect; // Update player's direction of view
    
}

void controlRight(float viewDirect) {
    viewDirect += (PI/180);
    if (viewDirect >= 2 * PI) {
        viewDirect -= 2 * PI; // Wrap around to keep the angle within bounds
    }
    player.directionOfView = viewDirect; // Update player's direction of view
}


float castRay (float angle, float playerX, float playerY) {
    // Cast a ray in the specified angle from the player's position
    // Return the distance to the first wall hit or -1 if no wall is hit
    float stepSize = 0.01f; // Step size for ray casting
    float distance = 0.0f;
    

    while (distance < 15.0f) { // Limit the maximum distance to check
        float rayX = playerX + cosf(angle) * distance;
        float rayY = playerY + sinf(angle) * distance;

        int gridX = (int)floor(rayX);
        int gridY = (int)floor(rayY);

        if (field[gridY][gridX] == '@') {
            return distance; // Hit a wall or out of bounds
        }

        distance += stepSize;
        //DrawLine(playerX * 10, playerY * 10, rayX * 10, rayY * 10, RED); // Draw the ray for visualization
    }

    return -1.0f; // No wall hit within the maximum distance
}

    
// }

void castWalls(PlayerData p) {
    float fov = PI / 3.0f; // 60 degrees field of view
    int numRays = GetScreenWidth(); // one ray per screen column
    float startAngle = p.directionOfView - fov / 2;
    float angleStep = fov / (float)numRays;

    for (int x = 0; x < numRays; x++) {
        float angle = startAngle + x * angleStep;
        float distance = castRay(angle, p.positionOfPlayerX, p.positionOfPlayerY);

        if (distance < 0) continue; // if nothing hit — skip


        float correctedDistance = distance * cos(angle - player.directionOfView); // Correct the distance to avoid fish-eye effect

        int h = GetScreenHeight();
        int wallHeight = (int)(h / (correctedDistance + 0.001f)); // so we don't divide by 0
        int wallTop = (h / 2) - (wallHeight / 2);
        int wallBottom = wallTop + wallHeight;

        // color based on distance
        float maxDist = 15.0f; // max distance at which the color will be the lightest
        float intensityFloat = correctedDistance / maxDist; // from 0.0 to 1.0
        if (intensityFloat > 1.0f) intensityFloat = 1.0f; // limit the maximum

        unsigned char intensity = (unsigned char)((intensityFloat * 255) + 70);
         Color color = {intensity, intensity, intensity, 255};
        // draw the wall slice
        DrawLine(x, wallTop, x, wallBottom, color);
    }

  
}

void castFloar(PlayerData p) {
    // draw the floor
    for (int x = 0; x < GetScreenWidth(); x++) {
        float angle = p.directionOfView - (PI / 6) + ((float)x / GetScreenWidth()) * (PI / 3);
        float dist = castRay(angle, p.positionOfPlayerX, p.positionOfPlayerY);

        if (dist < 0) continue; // if nothing hit — skip

        int h = GetScreenHeight();
        int floorHeight = (int)(h / (dist + 0.001f)); // so we don't divide by 0
        int floorTop = (h / 2) + (floorHeight / 2);
        int floorBottom = h;

        // Color color = GRAY;
        // if (dist <= 2.0f) color = BLACK;
        // else if (dist <= 4.0f) color = DARKGRAY;
        // else if (dist <= 8.0f) color = GRAY;
        // else color = LIGHTGRAY;

        float maxDist = 10.0f; // max distance at which the color will be the lightest
        float intensityFloat = dist / maxDist; // from 0.0 to 1.0
        if (intensityFloat > 1.0f) intensityFloat = 1.0f; // limit the maximum

        unsigned char intensity = (unsigned char)(intensityFloat * 255);

        Color color = {intensity, intensity, intensity, 255};
        DrawLine(x, floorTop, x, floorBottom, color);
    }
}

void castRoof(PlayerData p) {
     for (int x = 0; x < GetScreenWidth(); x++) {
        float angle = p.directionOfView - (PI / 6) + ((float)x / GetScreenWidth()) * (PI / 3);
        float dist = castRay(angle, p.positionOfPlayerX, p.positionOfPlayerY);

        // if (dist < 0) continue; // if nothing hit — skip

        int h = GetScreenHeight();
        int floorHeight = (int)(h / (dist + 0.001f)); // so we don't divide by 0
        int floorTop = -h;
        int floorBottom = (h / 2) + (floorHeight / 2);

        Color color = {185, 230, 254 ,255};;
        // if (dist <= 2.0f) color = {93, 185, 254, 255};
        // else if (dist <= 4.0f) color = {133, 199, 253, 255};
        // else if (dist <= 8.0f) color = {185, 230, 254 ,255};
        // else color = {228, 254, 254, 255}; 

        DrawLine(x, floorTop, x, floorBottom, color);
    }
}