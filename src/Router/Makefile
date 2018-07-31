LIBS = -L/usr/local/lib  -lzookeeper_mt -levent  -lpthread  -ldl
LINC = -I/usr/local/include -I/usr/local/include/zookeeper

OBJS = ../base/TcpServer.cpp ../base/Channel.cpp ../base/EpollLooper.cpp ../base/EventLoop.cpp ../base/EventLoopPool.cpp ../base/Buff.h \
../base/Uncopy.h ../base/ZmqNode.cpp ../base/Conf.h Router.cpp ../base/App.h 
TARGET = Router

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LIBS) $(LINC)  "-std=c++0x" # 