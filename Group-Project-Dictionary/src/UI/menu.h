#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "../../src/Data-Structures/Structures.h"
//#include<cstdlib>
class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font);
    //~Button();
    void draw(sf::RenderWindow& window) const;

    bool update(const sf::Vector2i& mousePos);

    sf::RectangleShape buttonShape;
    sf::Text buttonText;

    sf::Color defaultColor = sf::Color(100, 100, 100); // Default color
    sf::Color hoverColor = sf::Color(70, 70, 70);      // Hover color
    sf::Color clickColor = sf::Color(50, 50, 50);      // Click color
};

class TextBox {
public:
    TextBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font);

    void drawTextBox(sf::RenderWindow& window) const;

    bool updateTextBox(sf::Event event);
    bool updateTextBox();

    void handleMouseClick(const sf::Vector2i& mousePos);
    bool isFocused() const { return focused; }

    bool focused = false;
    sf::RectangleShape textBoxShape;
    sf::Text text;
    std::string inputString;
};

class DropdownMenu {
public:

    sf::Vector2f buttonSize;
    sf::Vector2f position;
    sf::Font font;
    Button mainButton;
    std::vector<Button> buttons;
    bool isOpen;

     DropdownMenu(const sf::Vector2f& buttonSize, const sf::Vector2f& position, const sf::Font& font, const std::string& mainButtonText)
     : buttonSize(buttonSize), position(position), font(font), isOpen(false), mainButton(buttonSize, position, mainButtonText, font) {}
     
     void addButton(const std::string& buttonText);

     void draw(sf::RenderWindow& window) const;

     int handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);
};

class spriteButton {
public:
    sf::Sprite defaultSprite;
    sf::Sprite clickedSprite;
    sf::Sprite hoverSprite;
    sf::RenderWindow& window;
    bool isClicked;

    spriteButton(sf::RenderWindow& win)
        : window(win), isClicked(false) {}

    void draw();
    bool update(const sf::Vector2f& mousePos);
    void setPosition(const sf::Vector2f& position);
    bool loadTextures(std::string defaultPath, const std::string clickedPath, const std::string hoverPath);

    sf::Texture defaultTexture;
    sf::Texture clickedTexture;
    sf::Texture hoverTexture;
};

//void typingBoxUpdate(sf::Event& event, sf::Text& text, std::string& input);
void openSubWin();
//void update2(int& cooldown, sf::CircleShape& shape, sf::RenderWindow& window);
void suggestDropdown(DropdownMenu& dropdown);
std::string wrapText(std::string& text,sf::Font& font, unsigned int characterSize, float maxWidth);

bool defBoxUpdate(TextBox& defBox, std::string newDef, sf::Font& font);
void updateTitle(sf::Text& Title, int& Mode);
//std::string defSearchwindow(Dict*& data, sf::Font& font);
bool datasetMenu(Dict*& data, sf::Font& font);
int mainMenu(Dict*& data);


