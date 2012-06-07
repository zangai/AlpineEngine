INCLUDES = -I./src -I./src/shared -I/usr/include/soci -I/usr/include/mysql \
           -I/usr/local/lib/boost/include -L/usr/local/lib/boost/lib \
           -I/usr/include/cryptopp

OUTDIR = bin
INTDIR = obj
OPTIONS = -ggdb -g3 -Wall -O0

alpine-server : Shared.a AsyncServerSocket.obj PlayerHandler.obj PacketHandler.obj Session.obj Server.obj User.obj Database.obj init
	g++ $(INCLUDES) $(OPTIONS) \
	    -pthread \
            -o $(OUTDIR)/alpine-server src/server/main.cpp \
	    $(INTDIR)/AsyncServerSocket.obj \
	    $(INTDIR)/PacketHandler.obj \
	    $(INTDIR)/Database.obj \
	    $(INTDIR)/PlayerHandler.obj \
	    $(INTDIR)/Session.obj \
	    $(INTDIR)/User.obj \
	    $(INTDIR)/Server.obj \
	    $(INTDIR)/Shared.a \
            -Wl,-Bstatic -lcryptopp \
	    -Wl,-Bdynamic \
	    -lboost_system \
	    -lsoci_mysql-gcc-3_0 \
	    -lsoci_core-gcc-3_0 \
	    -ldl

Server.obj : src/server/Server.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Server.obj src/server/Server.cpp

AsyncServerSocket.obj : src/server/AsyncServerSocket.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/AsyncServerSocket.obj src/server/AsyncServerSocket.cpp

PlayerHandler.obj : src/server/PlayerHandler.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/PlayerHandler.obj src/server/PlayerHandler.cpp

PacketHandler.obj : src/server/PacketHandler.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/PacketHandler.obj src/server/PacketHandler.cpp

Session.obj : src/server/Session.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Session.obj src/server/Session.cpp

User.obj : src/server/User.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/User.obj src/server/User.cpp

Database.obj : src/server/Database.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Database.obj src/server/Database.cpp \

# Shared.a
Shared.a : Packet.obj Flags.obj AsyncSocket.obj Log.obj init
	ar -cvq $(INTDIR)/Shared.a \
	    $(INTDIR)/Packet.obj \
	    $(INTDIR)/Flags.obj \
	    $(INTDIR)/AsyncSocket.obj \
	    $(INTDIR)/Log.obj
	ranlib $(INTDIR)/Shared.a

Packet.obj : src/shared/packet.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Packet.obj src/shared/packet.cpp

Flags.obj : src/shared/Flags.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Flags.obj src/shared/Flags.cpp

AsyncSocket.obj : src/shared/AsyncSocket.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/AsyncSocket.obj src/shared/AsyncSocket.cpp

Log.obj : src/shared/Log.cpp init
	g++ -c $(INCLUDES) $(OPTIONS) -o $(INTDIR)/Log.obj src/shared/Log.cpp

init:
	mkdir -p bin obj

clean:
	rm -f $(INTDIR)/*.obj $(INTDIR)/*.a
