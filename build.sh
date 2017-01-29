rm -rf ./bin
mkdir bin 2> /dev/null
g++ -std=gnu++11 -funsigned-char -fpermissive src/*.h src/*.cpp -o ./bin/enigma.exe -lncurses
