#include "../baseBlock.cpp"

class DirtBlockType : public BaseBlockType
{
public:
    virtual KeyColorPairMap getTextureTemplateKeys()
    {
        KeyColorPairMap keyColorMap = KeyColorPairMap(2);
        keyColorMap.add(KeyColorPair('A', color(37, 21, 4)));
        keyColorMap.add(KeyColorPair('B', color(54, 31, 6)));

        return keyColorMap;
    }
};

class DirtBlock : public BaseBlock
{
public:
    DirtBlock() : BaseBlock(new DirtBlockType()) {}
};