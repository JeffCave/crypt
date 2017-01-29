wget http://www.textfiles.com/etext/FICTION/quixote

./enigma.exe /k jeff.key
./enigma.exe /s jeff.set
./enigma.exe /e jeff.key jeff.set quixote quixote.crypt
./enigma.exe /d jeff.key jeff.set quixote.crypt quixote.decrypt
