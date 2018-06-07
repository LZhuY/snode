LIBS = -L/usr/local/lib  -levent -lpthread  -ldl
LINC = -I/usr/local/include 

OBJS = echo.cpp ../src/tcpserver.cpp ../src/base/channel.cpp ../src/base/epolllooper.cpp ../src/base/eventloop.cpp 
TARGET = echo

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LINC) $(LIBS)  "-std=c++0x"