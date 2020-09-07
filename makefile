module:
	g++ -g -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` spike/openikcape.cpp src/*.cpp -o bin/openikcape`python3-config --extension-suffix` -I ./
	cp data/prop.dat bin/prop.dat
clean:
	rm -r bin
	mkdir bin