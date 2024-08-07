#include "menu.h"


int mainMenu(Dict*& data)
{
	sf::RenderWindow windowMain(sf::VideoMode(1000, 700), "Dictionary App", sf::Style::Default);

	windowMain.setFramerateLimit(12);

	sf::Font font;
	if (!font.loadFromFile("Roboto-Regular.ttf")) {
		std::cerr << "Error loading font\n";
		return -1;
	}
	////////////////////////////////////////////////////// initialize
	sf::Color backGroundColor = sf::Color(113, 149, 182);

	spriteButton favoriteButton(windowMain);    favoriteButton.setPosition({ 154, 275 });
	favoriteButton.loadTextures("src/UI/sprite/Star 2.png", "src/UI/sprite/star1.png", "src/UI/sprite/Star 3.png");
	spriteButton changeModeButton(windowMain);    changeModeButton.setPosition({ 786,280 });
	changeModeButton.loadTextures("src/UI/sprite/changeMode1.png", "src/UI/sprite/changeMode2.png", "src/UI/sprite/changeMode2.png");
	spriteButton datasetButton(windowMain);    datasetButton.setPosition({ 6,1 });
	datasetButton.loadTextures("src/UI/sprite/Buttondata.png", "src/UI/sprite/Buttondata2.png", "src/UI/sprite/Buttondata2.png");
	spriteButton addWordButton(windowMain);    addWordButton.setPosition({ 6,142 });
	addWordButton.loadTextures("src/UI/sprite/Buttonadd_normal.png", "src/UI/sprite/Buttonadd_pressed.png", "src/UI/sprite/Buttonadd_pressed.png");
	spriteButton historyButton(windowMain);     historyButton.setPosition({ 6,95 });
	historyButton.loadTextures("src/UI/sprite/Buttonhistory_normal.png", "src/UI/sprite/Buttonhistory_pressed.png", "src/UI/sprite/Buttonhistory_pressed.png");
	spriteButton showFavoriteButton(windowMain);  showFavoriteButton.setPosition({ 6,48 });
	showFavoriteButton.loadTextures("src/UI/sprite/ButtonFavor_normal.png", "src/UI/sprite/ButtonFavor_pressed.png", "src/UI/sprite/ButtonFavor_pressed.png");
	spriteButton deleteButton(windowMain); deleteButton.setPosition({ 168,557 });
	deleteButton.loadTextures("src/UI/sprite/Buttondelete_normal.png", "src/UI/sprite/Buttondelete_pressed.png", "src/UI/sprite/Buttondelete_pressed.png");
	spriteButton editButton(windowMain); editButton.setPosition({ 168,608 });
	editButton.loadTextures("src/UI/sprite/ButtonEdit_normal.png", "src/UI/sprite/ButtonEdit_pressed.png", "src/UI/sprite/ButtonEdit_pressed.png");
	spriteButton nextButton(windowMain); nextButton.setPosition({ 786,603 });
	nextButton.loadTextures("src/UI/sprite/ButtonNext_normal.png", "src/UI/sprite/ButtonNext_status.png", "src/UI/sprite/ButtonNext_pressed.png");
	spriteButton randomButton(windowMain); randomButton.setPosition({ 710,279 });
	randomButton.loadTextures("src/UI/sprite/Rand_normal.png", "src/UI/sprite/Rand_pressed.png", "src/UI/sprite/Rand_pressed.png");

	sf::RectangleShape titleBox;
	titleBox.setFillColor(sf::Color(32, 201, 170));
	titleBox.setPosition({ 240,100 });
	titleBox.setSize({ 520,100 });

	sf::Text TitleTex;
	TitleTex.setFont(font); TitleTex.setCharacterSize(48); TitleTex.setFillColor(sf::Color::Black);
	TitleTex.setPosition(280.0f, 110.0f);

	TextBox searchBox({ 520, 50 }, { 240, 280 }, font);
	TextBox definitionBox({ 520,280 }, { 240,380 }, font);

	DropdownMenu dropdown({ 300, 50 }, { 270, 327 }, font, "Main Button");
	suggestDropdown(dropdown);

	int k = 0;
	std::string defString;
	bool startSearch = false;
	bool defSearchMode = false;
	Word* resultWord = nullptr;
	std::vector<Word*> result;

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
			if (event.key.code == sf::Keyboard::Enter) //search when enter
				startSearch = true;
			searchBox.updateTextBox(event);
		}
		windowMain.clear(backGroundColor);
		/////////////////////////////////////////////////////////////////
		if (startSearch)
		{
			result.clear();
			if (defSearchMode)
				result = data->searchWithDefinition(searchBox.inputString);
			else if (!defSearchMode)
				result = data->searchByKey(searchBox.inputString);
			dropdown.buttons.clear();
			for (int i = 0; (i < result.size() && i < 6); i++)
				dropdown.addButton(result[i]->data);
			dropdown.isOpen = true;
			startSearch = false;
		}

		int i = dropdown.handleEvent(event, mousePos);
		if (i >= 0 && result[i])
		{
			k = 0;
			resultWord = result[i];
			if (resultWord)
			{
				searchBox.inputString = resultWord->data;
				defString = resultWord->defs[k]->data;
			}
		}


		if (defSearchMode)
			TitleTex.setString("Search By Definition");
		else
			TitleTex.setString("Search By Key");

		if (changeModeButton.update(relMousePos))
			defSearchMode = !defSearchMode;
		if (datasetButton.update(relMousePos))
			datasetMenu(data, font);
		favoriteButton.update(relMousePos);

		if (addWordButton.update(relMousePos))
			addWordMenu(data, font);

		showFavoriteButton.update(relMousePos);

		historyButton.update(relMousePos);

		if (deleteButton.update(relMousePos) && resultWord)
			data->deleteWord(resultWord);

		if (editButton.update(relMousePos) && resultWord)
			defEditMenu(resultWord->defs[k], data, font);

		if (randomButton.update(relMousePos))
		{
			Definition* randomDef = data->getRandomWord();
			resultWord = randomDef->word;
			defString = randomDef->data;
			searchBox.inputString = resultWord->data;
		}

		searchBox.updateTextBox();
		if (nextButton.update(relMousePos) && resultWord)
		{
			k++; if (k >= resultWord->defs.size()) k = 0;
			defString = resultWord->defs[k]->data;
		}
		defBoxUpdate(definitionBox, defString, font);

		//////////////////////////////////////////////////////////
		changeModeButton.draw();
		datasetButton.draw();
		favoriteButton.draw();

		windowMain.draw(titleBox);
		windowMain.draw(TitleTex);
		searchBox.drawTextBox(windowMain);
		definitionBox.drawTextBox(windowMain);
		dropdown.draw(windowMain);
		addWordButton.draw();
		showFavoriteButton.draw();
		historyButton.draw();
		deleteButton.draw();
		editButton.draw();
		nextButton.draw();
		randomButton.draw();
		////////////////////////////////////////////////////////////

		windowMain.display();
	}
	return 0;
}

int bugNet()
{
	try {
		sf::RenderWindow window(sf::VideoMode(1000, 700), "Dictionary App", sf::Style::Default);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.display();
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


