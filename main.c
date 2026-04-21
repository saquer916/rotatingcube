#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

float a, b, c;
float cubeWidth = 40;
#define width 80
#define height 44
float zbuf[width*height]; // z buffer for depth perception
char buf[width*height]; // buffer for chars, the width*height specifies a size of every single character on the screen
float x, y, z;
int k1 = 40;
int xp, yp;
float ooz;
int idx;
int distanceFromCam = 100; // distanceFromCam is the distance from the camera's field of view to the camera point.
char bgChar = ' ';



float changeX(int x, int y, int z) {
    return -(y*cos(b)*sin(c))+(z*sin(b))+(x*cos(b)*cos(c));
}

float changeY(int x, int y, int z) {
    return (y*cos(a)*cos(c))-(y*sin(a)*sin(b)*sin(c))-(z*sin(a)*cos(b))+(x*(cos(a)*sin(c)+sin(a)*sin(b)*cos(c)));
}

float changeZ(int x, int y, int z) {
    return (y*cos(a)*cos(b)*sin(c))+(y*sin(a)*cos(c))+(z*cos(a)*cos(b))+(x*(sin(a)*sin(c)-cos(a)*sin(b)*cos(c)));
}

void calculatePtPos(float i, float j, float k, char ch) {
    x = changeX(i, j, k);
    y = changeY(i, j, k);
    z = changeZ(i, j, k) + distanceFromCam;

    ooz = 1/z;
    xp = (int)(width/2 + k1 * x * ooz * 2); // width/2 is used to center it, otherwise the center of the image would not be in the center of the screen, the *2 is used as normally characters are twice as high then as wide.
    yp = (int)(height/2 + k1 * y * ooz);
    idx = xp + yp * width; // This formula is to translate the 2d point into the 1d array.
    if (idx >= 0 && idx < width*height) { // boundary check
        if (ooz > zbuf[idx]) {
            buf[idx] = ch;
            zbuf[idx] = ooz;
        }
    }


}


int main() {
    printf("\x1b[2J]");

    while (1) {
        memset(buf, bgChar, width*height);
        for (int i = 0; i < width*height; i++) zbuf[i] = 0;
        // memset(zbuf, 0, width*height);
        float halfWidth = cubeWidth / 2;

        for (float i = -halfWidth; i < halfWidth; i += 0.15) {
            for (float j = -halfWidth; j < halfWidth; j += 0.15) {
                calculatePtPos(i, j, -halfWidth, '=');
                calculatePtPos(i, j, halfWidth, '-');
                calculatePtPos(halfWidth, i, j, '$');
                calculatePtPos(-halfWidth, i, j, '&');
                calculatePtPos(i, -halfWidth, j, '.');
                calculatePtPos(i, halfWidth, j, '~');
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < width*height; k++) {
            putchar(k % width ? buf[k] : 10);
        }
        a += 0.05;
        b += 0.05;
        c += 0.01;
        usleep(8000 * 2);
    }

    return 0;

}

// /*
// Six sides of a cube:
// 1. "="
// 2. "-"
// 3. "$"
// 4. "&"
// 5. "."
// 6. "~"