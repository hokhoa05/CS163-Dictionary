# Group Project Dictionary

This project is a dictionary application that supports eng-eng, eng-vie, vie-eng, slang and emoji definitions. It is built using C++ and SFML (Simple and Fast Multimedia Library) for graphical and audio functionalities.

## Prerequisites

- Visual Studio 2022 or later
- SFML library

## Building the Project

1. Open the solution file 

Group-Project-Dictionary.sln

 in Visual Studio.
2. Build the project using the desired configuration (Debug/Release and x64/Win32).

## Project Configuration

The project is configured to include SFML headers and libraries from the `aditional-include/SFML` directory. Ensure that the SFML library files are correctly placed in this directory.

## Running the Application

1. Build the project as described above.
2. Run the executable generated in the [`Debug`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary.sln%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A9%2C%22character%22%3A2%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition") or [`Release`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary.sln%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A11%2C%22character%22%3A2%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition") folder.

## Data Files

The application uses various data files for different dictionaries. These files are located in the [`data`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A17%2C%22character%22%3A1%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.h%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A177%2C%22character%22%3A22%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Faditional-include%2FSFML%2Finclude%2FSFML%2FGraphics%2FTransformable.hpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A316%2C%22character%22%3A14%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A423%2C%22character%22%3A16%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition") directory:

- [`data/emojis/Data.txt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A17%2C%22character%22%3A1%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.h%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A177%2C%22character%22%3A22%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition")
- [`data/eng-eng/Data.txt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A17%2C%22character%22%3A1%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.h%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A177%2C%22character%22%3A22%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition")
- [`data/eng-vie/Data.txt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A17%2C%22character%22%3A1%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.h%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A177%2C%22character%22%3A22%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition")
- [`data/slang/Data.txt`](command:_github.copilot.openSymbolFromReferences?%5B%22%22%2C%5B%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.cpp%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A17%2C%22character%22%3A1%7D%7D%2C%7B%22uri%22%3A%7B%22scheme%22%3A%22file%22%2C%22authority%22%3A%22%22%2C%22path%22%3A%22%2Fd%3A%2FHCMUS%2FYear%201%2FTerm%203%2FData%20Structures%2FLab%2FGroup08%2FGroup08%2FCS163-Dictionary%2FGroup-Project-Dictionary%2Fsrc%2FData-Structures%2FStructures.h%22%2C%22query%22%3A%22%22%2C%22fragment%22%3A%22%22%7D%2C%22pos%22%3A%7B%22line%22%3A177%2C%22character%22%3A22%7D%7D%5D%2C%22bda1c395-6bcf-4e59-bc42-bda177e90cb2%22%5D "Go to definition")

## Source Code

The main source code files are located in the `src` directory:

- src/main.cpp: Entry point of the application.
- src/Data-Structures/Static.h: Contains constants and file paths.
- src/Data-Structures/Structures.h: Header file for data structures.
- src/Data-Structures/Structures.cpp: Implementation of data structures.
- src/Data-Structures/Trie.h: Header file for Trie data structure.
- src/UI/menu.h: Header file for the menu UI.
- src/UI/menu.cpp: Implementation of the menu UI.
- src/UI/UI.cpp: Implementation of other UI components.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgements

- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library

## Contact

For any questions or issues, please contact the project maintainers.