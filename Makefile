main.exe: temp/main.o graphlib.dll
	g++ temp/main.o -o main.exe -L. -L C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\bin -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lgraphlib 

temp/main.o: src/main.cpp include/*.hpp
	g++ -c src/main.cpp -o temp/main.o -fPIC -I ./include -I C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include

temp/grp0.o: src/graph/grp0.cpp include/GRAPH/Graphsheet.hpp
	g++ -c src/graph/grp0.cpp -o temp/grp0.o -fPIC -I ./include -I ./include/GRAPH -I C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include

temp/ut0.o: src/util/ut0.cpp include/GRAPH/Graphsheet.hpp
	g++ -c src/util/ut0.cpp -o temp/ut0.o -fPIC -I ./include -I ./include/GRAPH -I C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include

temp/gline0.o: src/graph/gline0.cpp include/GRAPH/GraphLine.hpp
	g++ -c src/graph/gline0.cpp -o temp/gline0.o -fPIC -I ./include -I ./include/GRAPH -I C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include

graphlib.dll: temp/grp0.o temp/gline0.o temp/ut0.o include/GraphLib.hpp
	g++ -shared temp/grp0.o temp/gline0.o temp/ut0.o -o graphlib.dll -L C:\Users\KingCollinsX\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\bin -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2