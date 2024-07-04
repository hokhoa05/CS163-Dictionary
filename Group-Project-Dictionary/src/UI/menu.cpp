#include "menu.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font)
{
    // Set up the rectangle shape (background)
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(defaultColor);
    buttonShape.setOutlineColor(sf::Color(70, 70, 70));
    buttonShape.setOutlineThickness(2);

    // Set up the text
    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    // Center the text
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::update(const sf::Vector2i& mousePos)
{
    if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonShape.setFillColor(clickColor);
            return true;
        }
        else {
            buttonShape.setFillColor(hoverColor);
        }
    }
    else {
        buttonShape.setFillColor(defaultColor);
    }
    return false;
}

TextBox::TextBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font)
{
    // Set up the rectangle shape (background)
    textBoxShape.setSize(size);
    textBoxShape.setPosition(position);
    textBoxShape.setFillColor(sf::Color::White);
    textBoxShape.setOutlineColor(sf::Color::Black);
    textBoxShape.setOutlineThickness(1);

    // Set up the text
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 5, position.y + 5); // Small padding
}

void TextBox::drawTextBox(sf::RenderWindow& window) const
{
    window.draw(textBoxShape);
    window.draw(text);
    if (focused) {
        sf::RectangleShape cursor(sf::Vector2f(2, text.getCharacterSize()));
        cursor.setFillColor(sf::Color::Black); 
        cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 5, text.getPosition().y); 
        window.draw(cursor); 
    }
}
bool TextBox::updateTextBox(sf::Event event) {
    if (focused && event.type == sf::Event::TextEntered) 
    {
        if (event.text.unicode == 8) // Handle backspace
        { 
            if (!inputString.empty()) {
                inputString.pop_back();
            }
        }
        else if (inputString.length() >= 22)
        {
            return false;
        }
        else if (event.text.unicode < 128) // Handle ASCII characters
        { 
            inputString += static_cast<char>(event.text.unicode);
        }
        text.setString(inputString);
        return true;
    }
    return false;
    
}
void TextBox::handleMouseClick(const sf::Vector2i& mousePos) { 
    if (textBoxShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) { 
        focused = true; 
    }
    else {
        focused = false; 
    }
}

void DropdownMenu::addButton(const std::string& buttonText)
{
    sf::Vector2f buttonPosition = position + sf::Vector2f(0, buttons.size() * buttonSize.y);
    buttons.emplace_back(buttonSize, buttonPosition, buttonText, font);
}
void DropdownMenu::draw(sf::RenderWindow& window) const
{
    if (isOpen) {
        for (const auto& button : buttons) {
            button.draw(window);
        }
    }
}

int DropdownMenu::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mainButton.buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) 
        {
            isOpen = !isOpen;
            return 1;
        }
    }

    if (isOpen) {
        for (int i = 0;i<buttons.size();i++) 
        {
            if (buttons[i].update(mousePos))
            {
                isOpen = false;
                return i+1;
            }
        }
    }
    return 0;
}

void spriteButton::draw()
{
    if (isClicked) {
        window.draw(clickedSprite);
    }
    else {
        window.draw(defaultSprite);
    }
}

bool spriteButton::update(sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = defaultSprite.getGlobalBounds();

    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isClicked = true;
            return true;
        }
    }

    isClicked = false;
    return false;
}

void spriteButton::setPosition(const sf::Vector2f& position)
{
    defaultSprite.setPosition(position.x, position.y);
    clickedSprite.setPosition(position.x, position.y);
}



void update2(int& cooldown, sf::CircleShape& shape, sf::RenderWindow& window)
{
    if (cooldown < 8)
        cooldown++;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown >= 8)
    {
        shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        cooldown = 0;
    }
}


void openSubWin()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Sub-Window", sf::Style::Default);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.display();
    }
}

void suggest(DropdownMenu& dropdown)
{
    dropdown.addButton("Word 1");
    dropdown.addButton("Word 2");
    dropdown.addButton("Word 3");
    dropdown.addButton("Word 4");
    dropdown.addButton("Word 5");
}

int mainMenu()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "App1", sf::Style::Default);

    window.setFramerateLimit(10);

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
    ////////////////////////////////////////////////////// initialize


    sf::Texture defaultTexture;
    sf::Texture clickedTexture;
    defaultTexture.loadFromFile("src/UI/star3.png");
    //defaultTexture.setScale(sf::Vector2f(0.5f, 0.5f));
    clickedTexture.loadFromFile("src/UI/star4.png");

    spriteButton favoriteButton(window, defaultTexture, clickedTexture);
    favoriteButton.setPosition({ 100, 250 });


    Button button({ 100, 40 }, { 0, 0 }, "file", font);

    TextBox textBox({ 420, 50 }, { 200, 275 }, font);

    DropdownMenu dropdown({ 300, 50 }, { 270, 327 }, font, "Main Button");
    suggest(dropdown);

    bool keyWasPressed = false;

    /////////////////////////////////////////////////// main loop

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f relMousePos = static_cast<sf::Vector2f>(mousePos);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) 
                textBox.handleMouseClick(mousePos);
            if (textBox.updateTextBox(event) && textBox.inputString.length() >= 4)
                keyWasPressed = true;
        }
        window.clear(sf::Color::White);

    ///////////////////////////////////////////////////////////////// update
        if (keyWasPressed)
        {
            dropdown.isOpen = true;
            keyWasPressed = false;
        }       

        int i = dropdown.handleEvent(event, mousePos);
        if (i)
            std::cout << i;
        if (button.update(mousePos))
            openSubWin();
        favoriteButton.update(mousePos);
    /////////////////////////////////////////////////////////// draw

        favoriteButton.draw();
        button.draw(window);
        textBox.drawTextBox(window);
        dropdown.draw(window); 

     //////////////////////////////////////////////////////////// display

        window.display();
    }
    return 0;
}


