

LIBS_FILE = -lpthread

CC=g++
CFLAGS=-g -O0 -DMACOS
OBJS= main.o JSThread.o JSEpoller.o JSTcpServer.o JSTcpClientManager.o JSTcpClientSession.o JSNetPkgHandleBase.o JSNetPkgHandleP2P.o


BIN= ipncServer
all: $(BIN)
ipncServer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS_FILE) -o $@
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(OBJS) $(BIN) *.core

