#include "menu.h"

int mainMenu(Dict* &data) 
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
    favoriteButton.defaultSprite.setScale({ 0.5f, 0.5f });

    sf::Text TitleTex;
    TitleTex.setFont(font); TitleTex.setCharacterSize(48); TitleTex.setFillColor(sf::Color::Black);
    TitleTex.setPosition(100.0f, 100.0f);

    Button button({ 100, 40 }, { 0, 0 }, "file", font);
    Button defSearchButton({ 100, 50 }, { 630, 275 }, "DefSearch", font);
    TextBox searchBox({ 420, 50 }, { 200, 275 }, font);
    TextBox definitionBox({ 420,330 }, { 200,350 }, font);

    std :: string test = "This is a definition of the a word. It can be fitted in the definition box. it will automaticaly enter.";
    defBoxUpdate(definitionBox, test, font);

    DropdownMenu dropdown({ 300, 50 }, { 270, 327 }, font, "Main Button");
    suggestDropdown(dropdown);

    bool startSearch = false;
    bool defSearchMode = false;

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
            if (event.type == sf::Event::MouseButtonPressed) //focus on search box
                searchBox.handleMouseClick(mousePos);          
            if(event.key.code == sf::Keyboard::Enter) //search when enter
                startSearch = true;
            searchBox.updateTextBox(event);
        }
        window.clear(sf::Color::White);
    /////////////////////////////////////////////////////////////////
        if (startSearch&&defSearchMode) 
        {
            std::vector<Word*> result;
            result = data->searchWithDefinition(searchBox.inputString);
            dropdown.buttons.clear(); 
            for (int i = 0; (i < result.size() && i < 6); i++)
                dropdown.addButton(result[i]->data); 
            dropdown.isOpen = true;
            startSearch = false;
        }       
        int i = dropdown.handleEvent(event, mousePos);
        if (i >= 0 && defSearchMode)
                defBoxUpdate(definitionBox, dropdown.buttons[i].buttonText.getString(), font);
        if (defSearchMode)
            TitleTex.setString("Search By Definition");
        else
            TitleTex.setString("Search By Key");

        if (defSearchButton.update(mousePos))
            defSearchMode = !defSearchMode;
        if (button.update(mousePos))
            openSubWin();
        favoriteButton.update(mousePos);
    //////////////////////////////////////////////////////////

        //favoriteButton.draw();
        window.draw(TitleTex); 
        button.draw(window); 
        defSearchButton.draw(window);
        searchBox.drawTextBox(window);
        definitionBox.drawTextBox(window);
        dropdown.draw(window); 

     ////////////////////////////////////////////////////////////

        window.display();
    }
    return 0;
}


