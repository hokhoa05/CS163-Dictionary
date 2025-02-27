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
	spriteButton minigame1(windowMain); minigame1.setPosition({ 6,608 });
	minigame1.loadTextures("src/UI/sprite/ButtonMinigame1.png", "src/UI/sprite/ButtonMini1_clicked.png", "src/UI/sprite/ButtonMini1_clicked.png");
	spriteButton minigame2(windowMain); minigame2.setPosition({ 6,655 });
	minigame2.loadTextures("src/UI/sprite/ButtonMini2.png", "src/UI/sprite/ButtonMini2_clicked.png", "src/UI/sprite/ButtonMini2_clicked.png");
	spriteButton resetDatButton(windowMain); resetDatButton.setPosition({ 6,189 });
	resetDatButton.loadTextures("src/UI/sprite/ButtonresetDat.png", "src/UI/sprite/ButtonResetDat_C.png", "src/UI/sprite/ButtonResetDat_C.png");

	sf::RectangleShape titleBox;
	titleBox.setFillColor(sf::Color(59, 189, 166));
	titleBox.setPosition({ 240,100 });
	titleBox.setSize({ 520,122 });

	sf::Text TitleTex;
	TitleTex.setFont(font); TitleTex.setCharacterSize(40); TitleTex.setFillColor(sf::Color::White);
	TitleTex.setPosition(266.0f, 110.0f);

	sf::Text datasetText; datasetText.setCharacterSize(20); datasetText.setFillColor(sf::Color::Black);
	datasetText.setFont(font); datasetText.setPosition({ 266,176 });

	TextBox searchBox({ 520, 50 }, { 240, 280 }, font);
	TextBox definitionBox({ 520,280 }, { 240,380 }, font);

	DropdownMenu dropdown({ 410, 50 }, { 270, 327 }, font, "Main Button");



	sf::Sprite* starred = new sf::Sprite;
	*starred = favoriteButton.clickedSprite;
	sf::Sprite* hate = new sf::Sprite;
	*hate = favoriteButton.defaultSprite;
	int k = 0;
	std::string defString;
	datasetText.setString("Emoji");
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

		if (showFavoriteButton.update(relMousePos))
		{
			searchBox.inputString = buttonMenu(data, font, 1);
			//startSearch = true;
			result = data->searchByKey(searchBox.inputString);
			if (result[0]->data == searchBox.inputString)
			{
				resultWord = result[0];
				defString = resultWord->defs[0]->data;
				searchBox.inputString = resultWord->data;
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
				data->addHistory(resultWord);
			}
			else
				startSearch = true;
		}

		if (historyButton.update(relMousePos))
		{
			searchBox.inputString = buttonMenu(data, font, 2);
			result = data->searchByKey(searchBox.inputString);
			if (result[0]->data == searchBox.inputString)
			{
				resultWord = result[0];
				defString = resultWord->defs[0]->data;
				searchBox.inputString = resultWord->data;
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
				data->addHistory(resultWord);
			}
			else
				startSearch = true;
		}

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
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
				data->addHistory(resultWord);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isClickOutsideRectangle(mousePos, dropdown.getSize(), dropdown.position))
			dropdown.isOpen = false;
		if (favoriteButton.update(relMousePos) && resultWord)
		{
			if (resultWord->isFavorite)
			{
				data->deleteFavorite(resultWord);
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
			}
			else
			{
				data->addFavorite(resultWord);
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
			}
		}

		if (defSearchMode)
			TitleTex.setString("Search By Definition");
		else
			TitleTex.setString("Search By Key");

		if (changeModeButton.update(relMousePos))
			defSearchMode = !defSearchMode;
		if (datasetButton.update(relMousePos))
			datasetText.setString(datasetMenu(data, font, datasetText.getString()));

		if (resetDatButton.update(relMousePos))
			resetData(data);

		if (addWordButton.update(relMousePos))
			addWordMenu(data, font);
		if (deleteButton.update(relMousePos) && resultWord)
		{
			data->deleteWord(resultWord);
			resultWord = nullptr;
			defString = "";
			searchBox.inputString = "";
			updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
		}

		if (editButton.update(relMousePos) && resultWord)
		{
			int l = defEditMenu(resultWord->defs[k], data, font);
			if (l == 2)
			{
				resultWord = nullptr;
				defString = "";
				searchBox.inputString = "";
				updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
			}
			else if (l == 1)
			{
				k = 0;
				defString = resultWord->defs[k]->data;
			}
			else
				defString = resultWord->defs[k]->data;
		}

		if (randomButton.update(relMousePos))
		{
			Definition* randomDef = data->getRandomWord();
			resultWord = randomDef->word;
			defString = randomDef->data;
			searchBox.inputString = resultWord->data;
			updateFavoriteButton(favoriteButton, *starred, *hate, resultWord);
			data->addHistory(resultWord);
		}
		if (minigame1.update(relMousePos))
			miniGame(data, font, 1);
		if (minigame2.update(relMousePos))
			miniGame(data, font, 2);

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
		resetDatButton.draw();
		windowMain.draw(titleBox);
		windowMain.draw(datasetText);
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
		minigame1.draw();
		minigame2.draw();
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
// can there be duplicate in favorite?
//


