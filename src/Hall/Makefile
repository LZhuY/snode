LIBS = -L/usr/local/lib  -levent -lzmq -lpthread  -ldl
LINC = -I/usr/local/include

OBJS = ../base/TcpServer.cpp ../base/Channel.cpp ../base/EpollLooper.cpp ../base/EventLoop.cpp ../base/EventLoopPool.cpp ../base/Buff.h \
../base/App.h ../base/Uncopy.h ../base/ZmqNode.cpp ../base/Conf.h Hall.cpp
TARGET = Hall

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LIBS) $(LINC)  "-std=c++0x"