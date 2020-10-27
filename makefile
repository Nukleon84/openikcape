module:
	g++ -g -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes` bindings/openikcape.cpp openikcape/*.cpp openikcape/*/*.cpp -o bin/openikcape`python3-config --extension-suffix` -I ./openikcape -I ./lib
	cp data/prop.dat bin/prop.dat
clean:
	rm -r bin
	mkdir bin
app:
	streamlit run examples/python/bsv.py
exe:
	g++ -std=c++17 -g -o ./bin/ikcflash -I ./openikcape -I ./lib ./openikcape/*.cpp ./openikcape/*/*.cpp   ./examples/cpp/ikcflash.cpp
	cp data/prop.dat bin/prop.dat
venv: 
	python3 -m venv venv
	/venv/bin/activate.bat
	pip3 install -r requirements.txt