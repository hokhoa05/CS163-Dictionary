#pragma once
#include<string>
const std::string PRINTABLE = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!”#$%&'()*+, -./:;?@[\\]^_`{|}~";
const int SEARCH_LIMIT = 10;
// 0 - Data, 1 - Favorite, 2 - Backup (For reset), 3 - History
const std::string ENG_ENG_FILE[4] = {
	"./data/eng-eng/Data.txt",
	"./data/eng-eng/Favorite.txt",
	"./data/eng-eng/Backup.txt",
	"./data/eng-eng/History.txt"
};
const std::string ENG_VIE_FILE[4] = {
	"./data/eng-vie/Data.txt",
	"./data/eng-vie/Favorite.txt",
	"./data/eng-vie/Backup.txt",
	"./data/eng-vie/History.txt"
};
const std::string VIE_ENG_FILE[4] = {
	"./data/vie-eng/Data.txt",
	"./data/vie-eng/Favorite.txt",
	"./data/vie-eng/Backup.txt",
	"./data/vie-eng/History.txt"
};
const std::string EMOJI_FILE[4] = {
	"./data/emojis/Data.txt",
	"./data/emojis/Favorite.txt",
	"./data/emojis/Backup.txt",
	"./data/emojis/History.txt"
};
const std::string SLANG_FILE[4] = {
	"./data/slang/Data.txt",
	"./data/slang/Favorite.txt",
	"./data/slang/Backup.txt",
	"./data/slang/History.txt"
};