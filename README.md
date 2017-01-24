# com-gfx

Windows 64-bit
--------------
~~~
g++ -c -o "build/%1.o" "src/%1.cpp" -I"include" -std=c++14
g++ -o %1.exe %1.o -L"lib\x64" -lfreeglut -lopengl32 -lglu32 -std=c++14
~~~

Windows 32-bit
--------------
~~~
g++ -c -o "build/%1.o" "src/%1.cpp" -I"include" -std=c++14
g++ -o %1.exe %1.o -L"lib" -lfreeglut -lopengl32 -lglu32 -std=c++14
~~~

Linux
-----
~~~
g++ $1.cpp -o $1 -lGL -lGLU -lglut -std=c++14
~~~
