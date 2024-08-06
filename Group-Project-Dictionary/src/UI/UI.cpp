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
        else if (event.text.unicode <= 126 && event.text.unicode >= 32 ) // printable ascii
        {
            inputString += static_cast<char>(event.text.unicode);
        }
        text.setString(inputString);
        return true;
    }
    return false;
}
bool TextBox::updateTextBox()
{
    text.setString(inputString);
    return true;
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
    if (isOpen && buttons.size() != 0)
    {
        for (const auto& button : buttons)
            button.draw(window);
    }
}

int DropdownMenu::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos) {
    // If the dropdown is open, check the buttons inside it
    if (isOpen) {
        for (int i = 0; i < buttons.size(); ++i) {
            if (event.type == sf::Event::MouseButtonPressed && buttons[i].buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isOpen = false;
                    return i;              
            }
            else if (buttons[i].buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                buttons[i].buttonShape.setFillColor(buttons[i].hoverColor);
            }
            else
                buttons[i].buttonShape.setFillColor(buttons[i].defaultColor);
        }
    }
    if (event.type == sf::Event::MouseButtonPressed && mainButton.buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))   
    {
            isOpen = !isOpen;
            return -2;
    }
    return -1;
}

bool spriteButton::loadTextures( std::string defaultPath, const std::string clickedPath, const std::string hoverPath) {
    if (!defaultTexture.loadFromFile(defaultPath)) {
        return false;
    }
    if (!clickedTexture.loadFromFile(clickedPath)) {
        return false;
    }
    if (!hoverTexture.loadFromFile(hoverPath)) {
        return false;
    }
    defaultSprite.setTexture(defaultTexture);
    clickedSprite.setTexture(clickedTexture);
    hoverSprite.setTexture(hoverTexture);
    return true;
}

void spriteButton::draw() {
    if (isClicked) {
        window.draw(clickedSprite);
    }
    else if (defaultSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
        window.draw(hoverSprite);
    }
    else {
        window.draw(defaultSprite);
    }
}

bool spriteButton::update(const sf::Vector2f& mousePos) {
    if (defaultSprite.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isClicked = true;
        }
        else {
            if (isClicked) {
                isClicked = false;
                return true; // Button was clicked and released
            }
        }
    }
    return false; // No click event
}

void spriteButton::setPosition(const sf::Vector2f& position) {
    defaultSprite.setPosition(position);
    clickedSprite.setPosition(position);
    hoverSprite.setPosition(position);
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

void suggestDropdown(DropdownMenu& dropdown)
{
    dropdown.addButton("Word 1");
    dropdown.addButton("Word 2");
    dropdown.addButton("Word 3");
    dropdown.addButton("Word 4");
    dropdown.addButton("Word 5");
}

std::string wrapText(std::string& text, sf::Font& font, unsigned int characterSize, float maxWidth)
{
    std::string wrappedText;
    std::string word;
    float lineWidth = 0; // current line width
    float spaceWidth = font.getGlyph(' ', characterSize, false).advance;

    for (char character : text)
    {
        if (character == ' ')     // || c == '\n') 
        {
            float wordWidth = spaceWidth;
            for (char i : word) {
                wordWidth += font.getGlyph(i, characterSize, false).advance;
            }

            if (lineWidth + wordWidth > maxWidth) // need enter
            {
                wrappedText += '\n';
                lineWidth = 0;
            }
            wrappedText += word + character;
            lineWidth += wordWidth;
            word.clear();
        }
        else {
            word += character;
        }
    }

    if (!word.empty()) // check the last word // for cases of double space...
    {
        float wordWidth = spaceWidth;
        for (char i : word)
        {
            wordWidth += font.getGlyph(i, characterSize, false).advance;
        }

        if (lineWidth + wordWidth > maxWidth)
        {
            wrappedText += '\n';
        }
        wrappedText += word;
    }

    return wrappedText;
}
bool defBoxUpdate(TextBox& defBox, std::string newDef, sf::Font& font)
{
    newDef = wrapText(newDef, font, defBox.text.getCharacterSize(), defBox.textBoxShape.getSize().x);
    defBox.text.setString(newDef);
    return true;
}
void updateTitle(sf::Text& Title, int& Mode)
{
    switch (Mode)
    {
    case(1):
        Title.setString("Search By Key");
        Title.setPosition(100.0f, 100.0f);
        break;
    default:
        break;
    }
}
/*std::string defSearchwindow(Dict * &data, sf::Font & font)
{
    sf::RenderWindow window(sf::VideoMode(300, 570), "Definition Search", sf::Style::Default);
    window.setFramerateLimit(60);

    TextBox searchBox({ 300, 50 }, { 0, 0 }, font);
    searchBox.focused = true;
    std::vector<Word*> result;
    DropdownMenu choises({ 300, 50 }, { 0, 50 }, font, "Main Button");
    choises.isOpen = true;
    bool newResult = false;
    int k = -1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    result.clear();
                    result = data->searchWithDefinition(searchBox.inputString);
                    newResult = true;
                }
            }
            searchBox.updateTextBox(event);
        }
        window.clear(sf::Color::Blue);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (newResult)
        {
            choises.buttons.clear();
            for (int i = 0; (i < 10 && i < result.size()); i++)
            {
                choises.addButton(result[i]->data);
            }
            newResult = false;
        }
        k = choises.handleEvent(event,mousePos);
        if (k >= 0)
            return choises.buttons[k].buttonText.getString();

        searchBox.drawTextBox(window);
        choises.draw(window);
        window.display();
    }
}*/