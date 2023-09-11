#pragma once

struct Coordinate2D
{
    int xVal;
    int yVal;

    Coordinate2D(int x, int y) : xVal(x), yVal(y) {}
};

struct KeyColorPair
{
    char keyVal;
    uint16_t colorVal;

    KeyColorPair() : keyVal(0), colorVal(0) {}  // Default constructor
    KeyColorPair(char k, uint16_t c) : keyVal(k), colorVal(c) {}
};

struct KeyColorPairMap
{
public:
    int size;
    int currentSize = 0;
    KeyColorPair* data;  // Use a pointer for dynamic allocation

    KeyColorPairMap(int conSize)
    {
        size = conSize;
        data = new KeyColorPair[conSize];  // Allocate memory for 'data' based on 'conSize'
    }

    ~KeyColorPairMap()
    {
        delete[] data;
    }

    void add(KeyColorPair addData)
    {
        if (currentSize < size)
        {
            data[currentSize] = addData;
            currentSize++;
        }
    }

    uint16_t get(char key)
    {
        for (int i = 0; i < currentSize; i++)  // Loop through 'currentSize' elements, not 'size'
        {
            if (data[i].keyVal == key)
            {
                return data[i].colorVal;
            }
        }

        return 0xF0F;
    }
};

struct TemplatePatternMap
{
    char textureTemplatePattern[17][16];

    // Constructor that accepts a dynamically-sized 2D array
    TemplatePatternMap(char c[][16])
    {
        for (int i = 0; i < 17; ++i)
        {
            for (int j = 0; j < 16; ++j)
            {
                textureTemplatePattern[i][j] = c[i][j];
            }
        }
    }
};
