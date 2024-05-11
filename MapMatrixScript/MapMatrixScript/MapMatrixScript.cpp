#include <iostream>
#include "raylib.h"
#include <sstream>
#include <fstream>

//bool exists(Image& img, Image* arr, unsigned size)
//{
//    for (int i = 0; i < size; i++)
//    {
//        if (img == arr[i])
//        {
//
//        }
//    }
//}

int main()
{
    InitWindow(800, 450, "test");
    SetTargetFPS(60);

    /*Image array[78];
    Image map = LoadImage("Solids/map.png");

    for (int i = 1; i < 79; i++)
    {
        std::stringstream ss("Solids/picture (");
        ss << i << ").png";

        array[i - 1] = LoadImage(ss.str().c_str());
    }*/

    int8_t matrix[128][128] = { 0 };

    for (int i = 0; i < 128; i++)
    {
        std::cout << std::endl;
        for (int j = 0; j < 128; j++)
        {
            if (i < 3 || i>124 || j < 1 || j>126)
                matrix[i][j] = 1;

            std::cout << (int)matrix[i][j];
        }
    }

    std::ofstream ofs("MapMatrix.dat", std::ios::binary | std::ios::out);

    ofs.write((const char*)matrix, 128 * 128 * sizeof(int8_t));

    while (!WindowShouldClose())
    {

    }
}

