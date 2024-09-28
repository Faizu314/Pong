#include "text.hpp"

typedef struct {
    uint8_t x;
    uint8_t y;
} Vector2Int;

static Vector2Int characterSize;
static Vector2Int bitmapSize;
static std::unordered_map<int, int> unicodes;
static std::unordered_map<int, TTF_Font*> fonts;

void InitDynamicTextBitmap() {
    tinyxml2::XMLDocument doc;
    
    std::string fontMetaPath = GetAssetPath(FONT_META);

    if (doc.LoadFile(fontMetaPath.c_str()) != tinyxml2::XML_SUCCESS) {
        printf("Failed to load XML file: %s", fontMetaPath);
        return;
    }

    // Extract CharacterSize
    tinyxml2::XMLElement* charSizeElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterSize");
    if (charSizeElement) {
        charSizeElement->QueryUnsignedAttribute("width", reinterpret_cast<unsigned int*>(&characterSize.x));
        charSizeElement->QueryUnsignedAttribute("height", reinterpret_cast<unsigned int*>(&characterSize.y));
    }

    // Extract SpriteSheet size
    tinyxml2::XMLElement* spriteSheetElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("SpriteSheetSize");
    if (spriteSheetElement) {
        spriteSheetElement->QueryUnsignedAttribute("sizeX", reinterpret_cast<unsigned int*>(&bitmapSize.x));
        spriteSheetElement->QueryUnsignedAttribute("sizeY", reinterpret_cast<unsigned int*>(&bitmapSize.y));
    }

    uint32_t index = 0;
    
    // Extract Characters
    tinyxml2::XMLElement* characterArray = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterArray");
    if (characterArray) {
        for (tinyxml2::XMLElement* characterElement = characterArray->FirstChildElement("Character"); characterElement != nullptr; characterElement = characterElement->NextSiblingElement("Character")) {
            int unicode;
            characterElement->QueryIntAttribute("unicode", &unicode);
            unicodes[unicode] = index++;
        }
    }
}

TTF_Font* GetFontAsset(int assetId) {
    std::string assetPath = GetAssetPath(assetId);

    if (fonts.find(assetId) == fonts.end())
        fonts.insert(std::make_pair(assetId, TTF_OpenFont(assetPath.c_str(), FONT_SIZE)));

    return fonts[assetId];
}

void InitDynamicText(DynamicText& textObj, SDL_Texture* fontImage) {
    memset(&textObj, 0, sizeof(textObj));
    textObj.texture = fontImage;
}

void SetDynamicText(DynamicText& textObj, const char* text, ...) {
    va_list args;

    va_start(args, text);

    va_list args_copy;
    va_copy(args_copy, args);
    int length = vsnprintf(nullptr, 0, text, args_copy);
    va_end(args_copy);

    char* formattedText = new char[length + 1];

    vsnprintf(formattedText, length + 1, text, args);

    va_end(args);
    
    if (textObj.charCount != length) {
        delete textObj.selection;
        textObj.selection = new SDL_Rect[length];
        textObj.charCount = length;
    }
    
    for (int i = 0; i < length; i++) {
        int index = unicodes[formattedText[i]];
        int indexX = index % bitmapSize.x;
        int indexY = index / bitmapSize.x;
        
        textObj.selection[i].x = indexX * characterSize.x;
        textObj.selection[i].y = indexY * characterSize.y;
        textObj.selection[i].w = characterSize.x;
        textObj.selection[i].h = characterSize.y;
    }
    
    delete[] formattedText;
}
