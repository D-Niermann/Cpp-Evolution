# compiles the project
g++ ./main.cpp -std=c++14 -O3 -o ./build/main -I "Dependencies/SFML-2.5.1/include" -lsfml-graphics -lsfml-window -lsfml-system;

cd ./build
./main;