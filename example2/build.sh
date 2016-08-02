rm server
rm client 
$CC client.cpp  $(pkg-config --cflags gio-2.0 --libs gio-2.0) -o client
$CC server.cpp  $(pkg-config --cflags gio-2.0 --libs gio-2.0) -o server

#gcc client.cpp  $(pkg-config --cflags gio-2.0 --libs gio-2.0) -o client
#gcc server.cpp  $(pkg-config --cflags gio-2.0 --libs gio-2.0) -o server

