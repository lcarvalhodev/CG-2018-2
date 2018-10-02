SnowMan: Sphere.h Sphere.cpp main.cpp Vector3.h Vector3.cpp 
	g++ -o SnowMan main.cpp Sphere.cpp Vector3.cpp -lglut -lGLU -lGL

clean:
	rm SnowMan