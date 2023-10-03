#include <sdk/calc/calc.hpp>
#include "../utils.cpp"
#pragma once

class BaseBlockType
{
public:
    virtual uint8_t id(){ return 0x00; }

    virtual TemplatePatternMap getTextureTemplatePattern()
    { 
        static char textureTemplatePattern[17][16] = {
            {'#', '#', '#', '#', '#', '#', '#', 'A', 'A', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '#', '#', '#', '#', 'A', 'A', 'B', 'B', 'A', 'A', '#', '#', '#', '#', '#'},
            {'#', '#', '#', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', '#', '#', '#'},
            {'#', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', '#'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'A', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'A'},
            {'A', 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'A', 'A', 'A'},
            {'A', 'B', 'B', 'A', 'A', 'A', 'A', 'B', 'B', 'A', 'A', 'A', 'A', 'B', 'B', 'A'},
            {'A', 'B', 'B', 'B', 'B', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'A'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'#', 'A', 'A', 'B', 'B', 'B', 'B', 'A', 'A', 'B', 'B', 'B', 'B', 'A', 'A', '#'},
            {'#', '#', '#', 'A', 'A', 'B', 'B', 'A', 'A', 'B', 'B', 'A', 'A', '#', '#', '#'},
            {'#', '#', '#', '#', '#', 'A', 'A', 'A', 'A', 'A', 'A', '#', '#', '#', '#', '#'},
            {'#', '#', '#', '#', '#', '#', '#', 'A', 'A', '#', '#', '#', '#', '#', '#', '#'},
        };

        TemplatePatternMap pattern = TemplatePatternMap(textureTemplatePattern);

        return pattern;
    }

    virtual KeyColorPairMap getTextureTemplateKeys()
    {
        KeyColorPairMap keyColorMap = KeyColorPairMap(2);
        keyColorMap.add(KeyColorPair('A', color(0, 0, 0)));
        keyColorMap.add(KeyColorPair('B', color(127, 0, 127)));

        return keyColorMap;
    }

    virtual bool isVisable() { return true; }
    virtual bool isBreakable() { return true; }

    virtual void onPlace(){}
    virtual void onTryPlace(){}

    virtual void onDestroy(){}
    virtual void onTryDestroy(){}

    virtual void onPlayerStepOn(){}
    virtual void onPlayerStepOff(){}
    virtual void onPlayerFallOn(){}

    virtual void onEntityStepOn(){}
    virtual void onEntityStepOff(){}
    virtual void onEntityFallOn(){}

    virtual void onEveryTick(){}
    virtual void onBlockUpdate(){}

    virtual void onClick(){}

    ~BaseBlockType() {}
};

class BaseBlock
{
public:
    BaseBlockType* type;

    BaseBlock(BaseBlockType* blockType) : type(blockType) {}
    BaseBlock() : type(nullptr) {} // Initialize type to nullptr
    ~BaseBlock() {}
};
