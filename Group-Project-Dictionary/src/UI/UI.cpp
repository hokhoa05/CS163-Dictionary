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
		//else if (inputString.length() >= 22)
		//{
		//    return false;
		//}
		else if (event.text.unicode <= 126 && event.text.unicode >= 32) // printable ascii
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

bool spriteButton::loadTextures(std::string defaultPath, const std::string clickedPath, const std::string hoverPath) {
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
	defBox.inputString = newDef;
	return true;
}
bool buttonTextWrap(Button& button, std::string text, sf::Font& font)
{
	text = wrapText(text, font, button.buttonText.getCharacterSize(), button.buttonShape.getSize().x);
	button.buttonText.setString(text);
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
bool getNewQuestion(Dict*& data, int mode, std::string& question, std::string& answer, std::vector<std::string>& wrong)
{
	if (mode == 1)// def guess word
	{
		std::vector<std::string> ret = data->defGuessWord();
		question = ret[0];
		answer = ret[1];
		wrong.push_back(ret[2]);
		wrong.push_back(ret[3]);
		wrong.push_back(ret[4]);
		return true;
	}
	else if (mode == 2)
	{
		std::vector<std::string> ret = data->wordGuessDef();
		question = ret[0];
		answer = ret[1];
		wrong.push_back(ret[2]);
		wrong.push_back(ret[3]);
		wrong.push_back(ret[4]);
		return true;
	}
	else return false;

}

void putChoise(std::vector<Button>& choises, std::string& answer, std::vector<std::string>& wrong, int rng,sf::Font font)
{
	choises[rng].buttonText.setString(answer);
	buttonTextWrap(choises[rng], choises[rng].buttonText.getString(), font);
	for (int i = 0; i < 4; i++)
	{
		if (i == rng)
			continue;
		choises[i].buttonText.setString(wrong[i]);
		buttonTextWrap(choises[i], choises[i].buttonText.getString(), font);
	}
}
void miniGame(Dict*& data, sf::Font& font,int mode)
{
	sf::RenderWindow window(sf::VideoMode(650, 450), "Mini Game", sf::Style::Default);
	window.setFramerateLimit(12);

	std::string question, answer;
	std::vector<std::string> wrong;

	getNewQuestion(data, mode, question, answer, wrong);

	spriteButton replay(window); replay.setPosition({ 555,94 });
	replay.loadTextures("src/UI/sprite/ButtonRetry.png", "src/UI/sprite/ButtonRetry.png", "src/UI/sprite/ButtonRetry.png");

	TextBox questBox({ 480,120 }, { 35,30 }, font);
	questBox.inputString = question;
	defBoxUpdate(questBox, question, font);

	std::vector<Button> choises;
	for (int i = 0; i < 4; i++)
	{
		choises.push_back(Button({ 280,100 }, { 0,0 }, "", font));
		choises[i].defaultColor = sf::Color::White;
		choises[i].hoverColor = sf::Color(218, 218, 218);
		choises[i].clickColor = sf::Color(155, 155, 155);
	}
	int rng = rand() % 4;
	choises[0].buttonShape.setPosition({ 35,180 });
	choises[1].buttonShape.setPosition({ 335,180 });
	choises[2].buttonShape.setPosition({ 35,350 });
	choises[3].buttonShape.setPosition({ 335,350 });

	putChoise(choises, answer, wrong, rng, font);

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f relMousePos = static_cast<sf::Vector2f>(mousePos); 

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(113, 149, 182));
		int clicked = -1;

		if(choises[0].update(mousePos))
			clicked = 0;
		else if (choises[1].update(mousePos))
			clicked = 1;
		else if (choises[2].update(mousePos))
			clicked = 2;
		else if (choises[3].update(mousePos))
			clicked = 3;

		if (clicked == rng)
			choises[clicked].defaultColor = sf::Color(32, 201, 170);		
		else if (clicked != -1)
			choises[clicked].defaultColor = sf::Color(238, 50, 69);

		if (replay.update(relMousePos))
		{
			for (int i = 0; i < 4; i++)
				choises[i].defaultColor = sf::Color::White;
			rng = rand() % 4;
			getNewQuestion(data, mode, question, answer, wrong);
			questBox.inputString = question;
			defBoxUpdate(questBox, question, font);
			putChoise(choises, answer, wrong, rng, font);
		}

		replay.draw();
		questBox.drawTextBox(window);
		choises[0].draw(window);
		choises[1].draw(window);
		choises[2].draw(window);
		choises[3].draw(window);

		window.display();
	}
}

bool addWordMenu(Dict*& data, sf::Font& font)
{
	sf::RenderWindow window(sf::VideoMode(400, 500), "New Word", sf::Style::Default);
	window.setFramerateLimit(12);

	spriteButton applyButton(window); applyButton.setPosition({ 200,420 });
	applyButton.loadTextures("src/UI/sprite/Buttonapply.png", "src/UI/sprite/Buttonapply.png", "src/UI/sprite/Buttonapply.png");

	spriteButton cancelButton(window); cancelButton.setPosition({ 100,420 });
	cancelButton.loadTextures("src/UI/sprite/Buttoncancel.png", "src/UI/sprite/Buttoncancel.png", "src/UI/sprite/Buttoncancel.png");

	TextBox keyBox({ 280,80 }, { 10, 10 }, font);

	TextBox definitionBox({ 280,300 }, { 10,10 }, font);
	std::string newDef;

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f relMousePos = static_cast<sf::Vector2f>(mousePos);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) //focus def box
				definitionBox.handleMouseClick(mousePos);
			if (definitionBox.updateTextBox(event))
				newDef = definitionBox.inputString;

			if (event.type == sf::Event::MouseButtonPressed) //focus key box 
				keyBox.handleMouseClick(mousePos);
			keyBox.updateTextBox(event);

		}

		defBoxUpdate(definitionBox, newDef, font);

		if (applyButton.update(relMousePos))
		{
			data->addWordAndDef(keyBox.inputString, definitionBox.inputString);
			window.close();
		}
		if (cancelButton.update(relMousePos))
			window.close();
		applyButton.draw();
		cancelButton.draw();
		keyBox.drawTextBox(window);
		definitionBox.drawTextBox(window);
		window.display();
	}
	return true;
}
bool defEditMenu(Definition*& def, Dict*& data, sf::Font& font)
{

	sf::RenderWindow window(sf::VideoMode(300, 500), "Edit Definition", sf::Style::Default);
	window.setFramerateLimit(12);

	spriteButton deleteDef(window); deleteDef.setPosition({ 10,420 });
	deleteDef.loadTextures("src/UI/sprite/Buttondelete_pressed.png", "src/UI/sprite/Buttondelete_pressed.png", "src/UI/sprite/Buttondelete_pressed.png");

	spriteButton applyButton(window); applyButton.setPosition({ 200,420 });
	applyButton.loadTextures("src/UI/sprite/Buttonapply.png", "src/UI/sprite/Buttonapply.png", "src/UI/sprite/Buttonapply.png");

	spriteButton cancelButton(window); cancelButton.setPosition({ 100,420 });
	cancelButton.loadTextures("src/UI/sprite/Buttoncancel.png", "src/UI/sprite/Buttoncancel.png", "src/UI/sprite/Buttoncancel.png");

	TextBox keyBox({ 280,80 }, { 10, 10 }, font);
	keyBox.inputString = def->word->data;

	TextBox definitionBox({ 280,300 }, { 10,10 }, font);
	

	std::string newDef =  def->data; 
	definitionBox.inputString = newDef;

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f relMousePos = static_cast<sf::Vector2f>(mousePos);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) //focus def box
				definitionBox.handleMouseClick(mousePos);
			if (definitionBox.updateTextBox(event))
				newDef = definitionBox.inputString;

			//if (event.type == sf::Event::MouseButtonPressed) //focus key box 
			//	keyBox.handleMouseClick(mousePos);
			//keyBox.updateTextBox(event);

		}
		window.clear(sf::Color::White);
		defBoxUpdate(definitionBox, newDef, font);

		if (applyButton.update(relMousePos))
		{
			def->data = newDef;
			window.close();
		}
		if (deleteDef.update(relMousePos))
		{
			data->deleteDefinition(def);
			window.close();
		}
		if (cancelButton.update(relMousePos))
			window.close();
		applyButton.draw();
		deleteDef.draw();
		cancelButton.draw();
		keyBox.drawTextBox(window);
		definitionBox.drawTextBox(window);
		window.display();
	}
	return true;
}
bool datasetMenu(Dict*& data, sf::Font& font)
{
	sf::RenderWindow window(sf::VideoMode(300, 500), "Dataset", sf::Style::Default);
	window.setFramerateLimit(12);
	DropdownMenu Datasets({ 300, 100 }, { 0, 0 }, font, "mainButton");
	Datasets.addButton("ENG-ENG");
	Datasets.addButton("ENG-VIET");
	Datasets.addButton("VIET-ENG");
	Datasets.addButton("EMOJI");
	Datasets.addButton("SLANG");
	Datasets.isOpen = true;
	delete data;
	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		int i = Datasets.handleEvent(event, mousePos);
		switch (i)
		{
		case 0:
			data = new Dict(ENG_ENG_FILE);
			return true;
		case 1:
			data = new Dict(ENG_VIE_FILE);
			return true;
		case 2:
			data = new Dict(VIE_ENG_FILE);
			return true;
		case 3:
			data = new Dict(EMOJI_FILE);
			return true;
		case 4:
			data = new Dict(SLANG_FILE);
			return true;
		default:
			break;
		}

		Datasets.draw(window);
		window.display();
	};
	return false;
}