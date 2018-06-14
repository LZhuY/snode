LIBS = -L/usr/local/lib  -levent -lpthread  -ldl
LINC = -I/usr/local/include 

OBJS = main.cpp echo.cpp ../src/base/TcpServer.cpp ../src/base/Channel.cpp ../src/base/EpollLooper.cpp ../src/base/EventLoop.cpp ../src/base/EventLoopPool.cpp
TARGET = echo

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LIBS) $(LINC)  "-std=c++0x"