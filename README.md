By: Owen Rasor

The cross reference generator is a C++ program that uses regex to find words in a .txt file.
The regex accepts words that begin with a letter and can contain '-' or '\'' characters.
The words are used as the keys in the map. The maps values are a map with the line number in which the
word appears, with that value as the count of the amount of times the word appears in that line.
The map is sorted not by ascii, but by a case-insensitive alphabet. This required a custom operator
using _stricmp to sort the map's keys.

It is a demonstration of my knowledge of file reading, regex and the regex iterator, custom operators,
and maps.
