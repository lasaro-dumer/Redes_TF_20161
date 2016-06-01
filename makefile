binaries=bin/simulador
default: mkbin
	g++ -std=c++0x src/*.cpp -o bin/simulador
mkbin:
	mkdir -p bin
clean:
	rm -f $(binaries) src/*.gch
