build-test:
	g++ src/main.cpp -o main
	./main -o output -f txt -i test/vmlinux.bin -l
build-test-csv:
	g++ src/main.cpp -o main
	./main -o output -f csv -i test/fibSeq.bin -b -l
build:
	g++ src/main.cpp -o main