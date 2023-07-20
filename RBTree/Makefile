
#  make WordFrequency       makes WordFrequency Order
#  make Order               makes Order
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryTest under valgrind

WordFrequency : WordFrequency.o Dictionary.o
	g++ -std=c++17 -Wall -o WordFrequency WordFrequency.o Dictionary.o

WordFrequency.o : Dictionary.h WordFrequency.cpp
	g++ -std=c++17 -Wall -c WordFrequency.cpp

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o

Order.o : Dictionary.h Order.cpp
	g++ -std=c++17 -Wall -c Order.cpp

DictionaryTest : DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o 

DictionaryTest.o : Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -c DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp

clean :
	rm -f Order Order.o WordFrequency WordFrequency.o DictionaryTest DictionaryTest.o Dictionary.o

WordFrequencyCheck: WordFrequency
	valgrind --leak-check=full WordFrequency GutenBerg.txt

DictionaryCheck: DictionaryTest
	valgrind --leak-check=full DictionaryTest