invert: build build/ppm.o build/invert.o
	g++ build/ppm.o build/invert.o -o build/invert

build:
	mkdir -p build

build/ppm.o: modules/ppm.cppm | build
	g++ -std=c++23 -fmodules-ts -Wall -Wextra -c modules/ppm.cppm -o build/ppm.o

build/invert.o: invert.cpp | build
	g++ -std=c++23 -fmodules-ts -Wall -Wextra -c invert.cpp -o build/invert.o

clean:
	rm -rf build gcm.cache
