#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

const int width = 80;   // console width
const int height = 40;  // console height
const float cubeSize = 20;
const float camDist = 60;  // renamed from 'distance'

struct Vec3 {
    float x, y, z;
};

// 8 cube vertices
Vec3 cubeVertices[8] = {
    {-1, -1, -1},
    { 1, -1, -1},
    { 1,  1, -1},
    {-1,  1, -1},
    {-1, -1,  1},
    { 1, -1,  1},
    { 1,  1,  1},
    {-1,  1,  1}
};

// edges between vertices
int cubeEdges[12][2] = {
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
};

// rotate point
Vec3 rotate(Vec3 v, float angleX, float angleY, float angleZ) {
    // Rotate around X
    float cosX = cos(angleX), sinX = sin(angleX);
    float y = v.y * cosX - v.z * sinX;
    float z = v.y * sinX + v.z * cosX;
    v.y = y; v.z = z;

    // Rotate around Y
    float cosY = cos(angleY), sinY = sin(angleY);
    float x = v.x * cosY + v.z * sinY;
    z = -v.x * sinY + v.z * cosY;
    v.x = x; v.z = z;

    // Rotate around Z
    float cosZ = cos(angleZ), sinZ = sin(angleZ);
    x = v.x * cosZ - v.y * sinZ;
    y = v.x * sinZ + v.y * cosZ;
    v.x = x; v.y = y;

    return v;
}

// project 3D -> 2D
pair<int,int> project(Vec3 v) {
    float factor = cubeSize * camDist / (v.z + camDist);
    int x = (int)(width/2 + v.x * factor);
    int y = (int)(height/2 - v.y * factor);
    return {x, y};
}

int main() {
    float angle = 0.0f;

    while (true) {
        // Clear screen
        cout << "\x1b[2J\x1b[H"; 

        // buffer
        char screen[height][width];
        for (int i=0;i<height;i++)
            for (int j=0;j<width;j++)
                screen[i][j] = ' ';

        // draw cube edges
        for (int e=0;e<12;e++) {
            Vec3 v1 = rotate(cubeVertices[cubeEdges[e][0]], angle, angle, angle);
            Vec3 v2 = rotate(cubeVertices[cubeEdges[e][1]], angle, angle, angle);

            auto [x1,y1] = project(v1);
            auto [x2,y2] = project(v2);

            // simple Bresenham line
            int dx = abs(x2 - x1), dy = abs(y2 - y1);
            int sx = x1 < x2 ? 1 : -1;
            int sy = y1 < y2 ? 1 : -1;
            int err = dx - dy;

            while (true) {
                if (x1>=0 && x1<width && y1>=0 && y1<height)
                    screen[y1][x1] = '#';
                if (x1 == x2 && y1 == y2) break;
                int e2 = 2*err;
                if (e2 > -dy) { err -= dy; x1 += sx; }
                if (e2 < dx) { err += dx; y1 += sy; }
            }
        }

        // print frame
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++)
                cout << screen[i][j];
            cout << "\n";
        }

        angle += 0.05f;
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    return 0;
}
