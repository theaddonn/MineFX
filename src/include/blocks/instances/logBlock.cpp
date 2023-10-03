#include "../baseBlock.cpp"

class LogBlockType : public BaseBlockType
{
public:
    virtual uint8_t id(){ return 0x05; }

    virtual TemplatePatternMap getTextureTemplatePattern()
    { 
        static char textureTemplatePattern[17][16] = {
            {'#', '#', '#', '#', '#', '#', '#', 'A', 'A', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '#', '#', '#', '#', 'A', 'A', 'B', 'B', 'A', 'A', '#', '#', '#', '#', '#'},
            {'#', '#', '#', 'A', 'A', 'B', 'B', 'C', 'C', 'B', 'B', 'A', 'A', '#', '#', '#'},
            {'#', 'A', 'A', 'B', 'B', 'C', 'C', 'B', 'B', 'C', 'C', 'B', 'B', 'A', 'A', '#'},
            {'A', 'B', 'B', 'C', 'C', 'B', 'B', 'C', 'C', 'B', 'B', 'C', 'C', 'B', 'B', 'A'},
            {'A', 'A', 'A', 'B', 'B', 'C', 'C', 'B', 'B', 'C', 'C', 'B', 'B', 'A', 'A', 'A'},
            {'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'B', 'B', 'A', 'A', 'A', 'A', 'A'},
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
        KeyColorPairMap keyColorMap = KeyColorPairMap(4);
        keyColorMap.add(KeyColorPair('A', color(41, 24, 7)));
        keyColorMap.add(KeyColorPair('B', color(50, 30, 10)));
        keyColorMap.add(KeyColorPair('C', color(62, 37, 13)));

        return keyColorMap;
    }
};

class LogBlock : public BaseBlock
{
public:
    LogBlock() : BaseBlock(new LogBlockType()) {}
};