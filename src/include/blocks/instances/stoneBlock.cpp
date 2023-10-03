#include "../baseBlock.cpp"

class StoneBlockType : public BaseBlockType
{
public:
    virtual uint8_t id(){ return 0x07; }

    virtual KeyColorPairMap getTextureTemplateKeys()
    {
        KeyColorPairMap keyColorMap = KeyColorPairMap(2);
        keyColorMap.add(KeyColorPair('A', color(49, 49, 49)));
        keyColorMap.add(KeyColorPair('B', color(56, 57, 56)));

        return keyColorMap;
    }
};

class StoneBlock : public BaseBlock
{
public:
    StoneBlock() : BaseBlock(new StoneBlockType()) {}
};