New-Item -ItemType Directory -Path ./bin -Force
cls
gcc -I../../HashTable/c -g -Wall -Wpedantic .\main.c -o bin/main && .\bin\main.exe
