all: clean parser

parser:
	g++ src/main.cpp src/Lexer.cpp src/Parser.cpp src/TreeNode.cpp src/Token.cpp -o parser -std=c++17


clean: 
	rm -rf parser *.o
