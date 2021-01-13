main.out : HttpServer.o TCPServer.o main.o
	g++ -o main.out main.o TCPServer.o HttpServer.o -lpthread -std=c++14

TCPServer.o : TCPServer.cpp
	g++ -c -o TCPServer.o TCPServer.cpp

HttpServer.o : HttpServer.cpp
	g++ -c -o HttpServer.o HttpServer.cpp

HtmlRender.o : HtmlRender.cpp
	g++ -c -o HtmlRender.o HtmlRender.cpp

main.o :
	g++ -c -o main.o main.cpp

clean :
	rm *.o *.out
