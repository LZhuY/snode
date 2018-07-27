LIBS = -L/usr/local/lib  -levent -lzmq -lpthread  -ldl
LINC = -I/usr/local/include

OBJS = ../src/base/TcpServer.cpp ../src/base/Channel.cpp ../src/base/EpollLooper.cpp ../src/base/EventLoop.cpp ../src/base/EventLoopPool.cpp ../src/base/Buff.h \
../src/base/App.h ../src/base/Uncopy.h ../src/base/ZmqNode.cpp Hall.cpp
TARGET = Hall

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LIBS) $(LINC)  "-std=c++0x"