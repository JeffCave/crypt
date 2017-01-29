rm -rf ./bin
mkdir bin 2> /dev/null
g++ -funsigned-char -fpermissive src/*.h src/*.cpp -o ./bin/enigma.exe -lncurses
