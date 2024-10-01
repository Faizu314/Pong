#include "text.hpp"

namespace Assets {

    static std::unordered_map<int, DynamicFontAsset*> _dynamicFonts;
    static std::unordered_map<int, TTF_Font*> _sdlFonts;

    DynamicFontAsset* CreateDynamicFontAsset(SDL_Texture* bitmap, int fontMetaDataId) {
        DynamicFontAsset* font = new DynamicFontAsset();
        tinyxml2::XMLDocument doc;

        std::string fontMetaPath = GetAssetPath(fontMetaDataId);

        if (doc.LoadFile(fontMetaPath.c_str()) != tinyxml2::XML_SUCCESS) {
            printf("Failed to load XML file: %s", fontMetaPath.c_str());
            return nullptr;
        }

        // Extract CharacterSize
        tinyxml2::XMLElement* charSizeElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterSize");
        if (charSizeElement) {
            charSizeElement->QueryUnsignedAttribute("width", reinterpret_cast<unsigned int*>(&font->CharacterSize.x));
            charSizeElement->QueryUnsignedAttribute("height", reinterpret_cast<unsigned int*>(&font->CharacterSize.y));
        }

        // Extract SpriteSheet size
        tinyxml2::XMLElement* spriteSheetElement = doc.FirstChildElement("BitmapFont")->FirstChildElement("SpriteSheetSize");
        if (spriteSheetElement) {
            spriteSheetElement->QueryUnsignedAttribute("sizeX", reinterpret_cast<unsigned int*>(&font->BitmapSize.x));
            spriteSheetElement->QueryUnsignedAttribute("sizeY", reinterpret_cast<unsigned int*>(&font->BitmapSize.y));
        }

        uint32_t index = 0;

        // Extract Characters
        tinyxml2::XMLElement* characterArray = doc.FirstChildElement("BitmapFont")->FirstChildElement("CharacterArray");
        if (characterArray) {
            for (tinyxml2::XMLElement* characterElement = characterArray->FirstChildElement("Character"); characterElement != nullptr; characterElement = characterElement->NextSiblingElement("Character")) {
                int unicode;
                characterElement->QueryIntAttribute("unicode", &unicode);
                font->IndexToUnicode[unicode] = index++;
            }
        }

        font->Bitmap = bitmap;
        int fontId = (int)_dynamicFonts.size();
        
        _dynamicFonts.insert(std::make_pair(fontId, font));

        return font;
    }

    TTF_Font* GetFontAsset(int assetId) {
        std::string assetPath = GetAssetPath(assetId);

        if (_sdlFonts.find(assetId) == _sdlFonts.end())
            _sdlFonts.insert(std::make_pair(assetId, TTF_OpenFont(assetPath.c_str(), Scene::FONT_SIZE)));

        return _sdlFonts[assetId];
    }

    void DestroyDynamicFonts() {
        for (const auto& pair : _dynamicFonts) {
            delete pair.second;
        }
    }
}

namespace Game {

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
            int index = textObj.DynamicFont->IndexToUnicode[formattedText[i]];
            int indexX = index % textObj.DynamicFont->BitmapSize.x;
            int indexY = index / textObj.DynamicFont->BitmapSize.x;

            textObj.Selection[i].x = indexX * textObj.DynamicFont->CharacterSize.x;
            textObj.Selection[i].y = indexY * textObj.DynamicFont->CharacterSize.y;
            textObj.Selection[i].w = textObj.DynamicFont->CharacterSize.x;
            textObj.Selection[i].h = textObj.DynamicFont->CharacterSize.y;
        }

        delete[] formattedText;
    }
}
