New-Item -ItemType Directory -Path ./bin -Force
cls
gcc -g -Wall -Wpedantic .\main.c -o bin/main && .\bin\main.exe
