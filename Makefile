all: lab

lab: main.o Application.o shader.o Triangle.o Mesh.o Object.o
	g++ -o lab main.o Application.o shader.o Triangle.o Mesh.o Object.o -lglfw3 -lglew32 -lopengl32 

main.o: main.cpp
	g++ -o main.o -c main.cpp

Application.o: Application.cpp
	g++ -o Application.o -c Application.cpp

shader.o: shader.cpp
	g++ -o shader.o -c shader.cpp

Triangle.o: Triangle.cpp
	g++ -o Triangle.o -c Triangle.cpp

Mesh.o: Mesh.cpp
	g++ -o Mesh.o -c Mesh.cpp

Object.o: Object.cpp
	g++ -o Object.o -c Object.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf lab