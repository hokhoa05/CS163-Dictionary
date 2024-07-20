#include "menu.h"

int mainMenu(Dict* &data) 
{
    sf::RenderWindow windowMain(sf::VideoMode(1000, 700), "Dictionary App", sf::Style::Default); 

    windowMain.setFramerateLimit(8);

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
    ////////////////////////////////////////////////////// initialize
    sf::Color backGroundColor = sf::Color(113, 149, 182,100);

    spriteButton favoriteButton(windowMain);
    favoriteButton.loadTextures( "src/UI/sprite/Star 2.png","src/UI/sprite/star1.png", "src/UI/sprite/Star 3.png" );
    favoriteButton.setPosition({ 154, 275 });

    spriteButton changeModeButton(windowMain);
    changeModeButton.loadTextures("src/UI/sprite/changeMode1.png", "src/UI/sprite/changeMode2.png", "src/UI/sprite/changeMode2.png");
    changeModeButton.setPosition({ 786,280 });

    spriteButton datasetButton(windowMain);
    datasetButton.loadTextures("src/UI/sprite/Buttondata.png", "src/UI/sprite/Buttondata2.png", "src/UI/sprite/Buttondata2.png");
    datasetButton.setPosition({ 6,1 });



    sf::Text TitleTex;
    TitleTex.setFont(font); TitleTex.setCharacterSize(48); TitleTex.setFillColor(sf::Color::Black);
    TitleTex.setPosition(100.0f, 100.0f);


    TextBox searchBox({ 520, 50 }, { 240, 280 }, font);
    TextBox definitionBox({ 520,280 }, { 240,380 }, font);

    std :: string test = "This is a definition of the a word. It can be fitted in the definition box. it will automaticaly enter.";
    defBoxUpdate(definitionBox, test, font);

    DropdownMenu dropdown({ 300, 50 }, { 270, 327 }, font, "Main Button");
    suggestDropdown(dropdown);

    bool startSearch = false;
    bool defSearchMode = false;

    /////////////////////////////////////////////////// main loop

    while (windowMain.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(windowMain);
        sf::Vector2f relMousePos = static_cast<sf::Vector2f>(mousePos);

        while (windowMain.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                windowMain.close();
            if (event.type == sf::Event::MouseButtonPressed) //focus on search box
                searchBox.handleMouseClick(mousePos);          
            if(event.key.code == sf::Keyboard::Enter) //search when enter
                startSearch = true;
            searchBox.updateTextBox(event);
        }
        windowMain.clear(backGroundColor);
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

        if (changeModeButton.update(relMousePos))
            defSearchMode = !defSearchMode;
        if (datasetButton.update(relMousePos))
            openSubWin();
        favoriteButton.update(relMousePos);
        
    //////////////////////////////////////////////////////////
        changeModeButton.draw();
        datasetButton.draw();
        favoriteButton.draw();
        windowMain.draw(TitleTex); 
        searchBox.drawTextBox(windowMain);
        definitionBox.drawTextBox(windowMain);
        dropdown.draw(windowMain); 

     ////////////////////////////////////////////////////////////

        windowMain.display();
    }
    return 0;
}


