#include "../baseBlock.cpp"

class LeaveBlockType : public BaseBlockType
{
public:
    virtual KeyColorPairMap getTextureTemplateKeys()
    {
        KeyColorPairMap keyColorMap = KeyColorPairMap(2);
        keyColorMap.add(KeyColorPair('A', color(22, 80, 1)));
        keyColorMap.add(KeyColorPair('B', color(25, 91, 1)));

        return keyColorMap;
    }
};

class LeaveBlock : public BaseBlock
{
public:
    LeaveBlock() : BaseBlock(new LeaveBlockType()) {}
};