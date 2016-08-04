$CC server.cpp  $(pkg-config --cflags --libs dbus-1) -o server
$CC client.cpp  $(pkg-config --cflags --libs dbus-1) -o client
