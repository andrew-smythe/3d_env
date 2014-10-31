run: asn04
	./asn04
	
asn04: asn04.o Camera.o Terrain.o Animation.o Tree.o
	g++ -g -o asn04 asn04.o Camera.o Terrain.o Animation.o Tree.o -lGL -lGLU -lglut
	
asn04.o: asn04.cpp Camera.h
	g++ -c asn04.cpp -o asn04.o
	
Camera.o: Camera.cpp Camera.h
	g++ -c Camera.cpp -o Camera.o
	
Terrain.o: Terrain.cpp Terrain.h
	g++ -c Terrain.cpp -o Terrain.o
	
Animation.o: Animation.cpp Animation.h
	g++ -c Animation.cpp -o Animation.o
	
Tree.o: Tree.cpp Tree.h Animation.h
	g++ -c Tree.cpp -o Tree.o
	
clean:
	rm -f *.o *~ asn04
		
