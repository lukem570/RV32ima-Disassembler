build-test:
	g++ src/main.cpp -o main
	./main -o output -f txt -i test/fibSeq.bin
build:
	g++ src/main.cpp -o main