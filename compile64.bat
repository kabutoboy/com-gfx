g++ -std=c++14 -c -o %1.o %1.cpp -I"C:\Program Files\Common Files\MinGW\freeglut\include"
g++ -std=c++14 -o %1.exe %1.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib\x64" -lfreeglut -lopengl32 -lglu32
%1.exe
