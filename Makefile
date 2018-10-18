all: lab

lab: main.o Application.o shader.o Table.o Mesh.o Object.o texture.o Program.o Computer.o Sphere.o
	g++ -o lab main.o Application.o shader.o Table.o Mesh.o Object.o texture.o Program.o Computer.o Sphere.o -lglfw3 -lglew32 -lopengl32 -lpng

main.o: main.cpp
	g++ -o main.o -c main.cpp

Application.o: Application.cpp Application.h
	g++ -o Application.o -c Application.cpp

shader.o: shader.cpp shader.h
	g++ -o shader.o -c shader.cpp

Table.o: Table.cpp Table.h
	g++ -o Table.o -c Table.cpp

Mesh.o: Mesh.cpp Mesh.h
	g++ -o Mesh.o -c Mesh.cpp

Object.o: Object.cpp Object.h
	g++ -o Object.o -c Object.cpp

Program.o: Program.cpp Program.h
	g++ -o Program.o -c Program.cpp

Computer.o: Computer.cpp Computer.h
	g++ -o Computer.o -c Computer.cpp

Sphere.o: Sphere.cpp Sphere.h
	g++ -o Sphere.o -c Sphere.cpp

texture.o: texture.cpp texture.h
	g++ -o texture.o -c texture.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf lab