#include <iostream>
#include <math.h>
#include <string.h> 
#include <unistd.h>

float A, B, C;

float cubeWidth = 10;
const int width = 160, height = 44;
float zBuffer[width * height];
char buffer[width * height];
int backgeoundASCIICode = ' ';
int distance = 60; 
float K1 = 40;

float incrementSpeed = 0.6; 

float x, y, z; 
float ooz; 
int xp, yp; 
int idx; 

float calculateX(int i, int j, int k)
{
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k)
{
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k)
{
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calcSurface(float cubeX, float cubeY, float cubeZ, int ch) { 
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distance;

    ooz = 1/z;

    xp = (int) (width/2 - 2 * cubeWidth + K1 * ooz * x * 2);
    yp = (int) (height/2 + K1 * ooz * y);

    idx = xp + yp * width;

    if(idx >= 0 && idx < width*height) {
        if(ooz > zBuffer[idx]) { 
            zBuffer[idx] = ooz; 
            buffer[idx] = ch; 
        }
    }
}

int main()
{
    std::cout << "\x1b[2J";

    while(1) { 
        memset(buffer, backgeoundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);

        for(float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) { 
            for(float cubeY = - cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed ) { 
                calcSurface(cubeX, cubeY, -cubeWidth, '.');
                calcSurface(cubeWidth, cubeY, cubeX, '$');
                calcSurface(-cubeWidth, cubeY, -cubeX, '~');
                calcSurface(-cubeX, cubeY, cubeWidth, '#');
                calcSurface(cubeX, -cubeWidth, -cubeY , ';'); 
                calcSurface(cubeX, cubeWidth, cubeY , '+'); 
            }
        }
        std::cout << "\x1b[H";

        for(int k = 0; k < width * height; k++) { 
            putchar(k % width ? buffer[k] : 10);
        }

        A+= 0.005; 
        B += 0.005; 
        usleep(1000);


    }


    return 0;
}