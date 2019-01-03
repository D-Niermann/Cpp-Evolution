#compile but does not build the exe
g++ -c main.cpp;
g++ ./main.cpp -o MainApp -lsfml-graphics -lsfml-window -lsfml-system;
./MainApp;