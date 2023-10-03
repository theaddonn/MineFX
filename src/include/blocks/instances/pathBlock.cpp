#include "../baseBlock.cpp"

class PathBlockType : public BaseBlockType
{
public:
    virtual uint8_t id(){ return 0x06; }

    virtual TemplatePatternMap getTextureTemplatePattern()
    { 
        static char textureTemplatePattern[17][16] = {
            {'#', '#', '#', '#', '#', '#', '#', 'A', 'A', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '#', '#', '#', '#', 'A', 'A', 'B', 'B', 'A', 'A', '#', '#', '#', '#', '#'},
            {'#', '#', '#', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', '#', '#', '#'},
            {'#', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', '#'},
            {'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A'},
            {'C', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'C'},
            {'C', 'C', 'C', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A', 'C', 'C', 'C'},
            {'C', 'D', 'D', 'C', 'C', 'A', 'A', 'B', 'B', 'A', 'A', 'C', 'C', 'D', 'D', 'C'},
            {'C', 'D', 'D', 'D', 'D', 'C', 'C', 'A', 'A', 'C', 'C', 'D', 'D', 'D', 'D', 'C'},
            {'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C', 'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C'},
            {'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C', 'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C'},
            {'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C', 'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C'},
            {'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C', 'C', 'D', 'D', 'D', 'D', 'D', 'D', 'C'},
            {'#', 'C', 'C', 'D', 'D', 'D', 'D', 'C', 'C', 'D', 'D', 'D', 'D', 'C', 'C', '#'},
            {'#', '#', '#', 'C', 'C', 'D', 'D', 'C', 'C', 'D', 'D', 'C', 'C', '#', '#', '#'},
            {'#', '#', '#', '#', '#', 'C', 'C', 'C', 'C', 'C', 'C', '#', '#', '#', '#', '#'},
            {'#', '#', '#', '#', '#', '#', '#', 'C', 'C', '#', '#', '#', '#', '#', '#', '#'},
        };

        TemplatePatternMap pattern = TemplatePatternMap(textureTemplatePattern);

        return pattern;
    }
    virtual KeyColorPairMap getTextureTemplateKeys()
    {
        KeyColorPairMap keyColorMap = KeyColorPairMap(4);
        keyColorMap.add(KeyColorPair('A', color(66, 55, 18)));
        keyColorMap.add(KeyColorPair('B', color(73, 61, 20)));
        keyColorMap.add(KeyColorPair('C', color(37, 21, 4)));
        keyColorMap.add(KeyColorPair('D', color(54, 31, 6)));

        return keyColorMap;
    }
};

class PathBlock : public BaseBlock
{
public:
    PathBlock() : BaseBlock(new PathBlockType()) {}
};