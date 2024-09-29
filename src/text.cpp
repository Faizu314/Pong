#include "text.hpp"

namespace Assets {
    static std::unordered_map<int, TTF_Font*> _fonts;

    TTF_Font* GetFontAsset(int assetId) {
        std::string assetPath = GetAssetPath(assetId);

        if (_fonts.find(assetId) == _fonts.end())
            _fonts.insert(std::make_pair(assetId, TTF_OpenFont(assetPath.c_str(), Scene::FONT_SIZE)));

        return _fonts[assetId];
    }
}

namespace Game {

    typedef struct {
        uint8_t x;
        uint8_t y;
    } Vector2Int;

    static Vector2Int _characterSize;
    static Vector2Int _bitmapSize;
    static std::unordered_map<int, int> _unicodes;

    void InitDynamicTextBitmap() {
        tinyxml2::XMLDocument doc;

        std::string fontMetaPath = GetAssetPath(Assets::FONT_META);

        if (doc.LoadFile(fontMetaPath.c_str()) != tinyxml2::XML_SUCCESS) {
            printf("Failed to load XML file: %s", fontMetaPath.c_str());
            return;
        }

        // Extract CharacterSize
        tinyxml2::XMLElement* charSizeElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterSize");
        if (charSizeElement) {
            charSizeElement->QueryUnsignedAttribute("width", reinterpret_cast<unsigned int*>(&_characterSize.x));
            charSizeElement->QueryUnsignedAttribute("height", reinterpret_cast<unsigned int*>(&_characterSize.y));
        }

        // Extract SpriteSheet size
        tinyxml2::XMLElement* spriteSheetElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("SpriteSheetSize");
        if (spriteSheetElement) {
            spriteSheetElement->QueryUnsignedAttribute("sizeX", reinterpret_cast<unsigned int*>(&_bitmapSize.x));
            spriteSheetElement->QueryUnsignedAttribute("sizeY", reinterpret_cast<unsigned int*>(&_bitmapSize.y));
        }

        uint32_t index = 0;

        // Extract Characters
        tinyxml2::XMLElement* characterArray = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterArray");
        if (characterArray) {
            for (tinyxml2::XMLElement* characterElement = characterArray->FirstChildElement("Character"); characterElement != nullptr; characterElement = characterElement->NextSiblingElement("Character")) {
                int unicode;
                characterElement->QueryIntAttribute("unicode", &unicode);
                _unicodes[unicode] = index++;
            }
        }
    }

    void InitDynamicText(DynamicText& textObj, SDL_Texture* fontImage) {
        memset(&textObj, 0, sizeof(textObj));
        textObj.Texture = fontImage;
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

        if (textObj.CharCount != length) {
            delete textObj.Selection;
            textObj.Selection = new SDL_Rect[length];
            textObj.CharCount = length;
        }

        for (int i = 0; i < length; i++) {
            int index = _unicodes[formattedText[i]];
            int indexX = index % _bitmapSize.x;
            int indexY = index / _bitmapSize.x;

            textObj.Selection[i].x = indexX * _characterSize.x;
            textObj.Selection[i].y = indexY * _characterSize.y;
            textObj.Selection[i].w = _characterSize.x;
            textObj.Selection[i].h = _characterSize.y;
        }

        delete[] formattedText;
    }
}