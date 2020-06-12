#install 
#sudo apt install libglib2.0-dev

gdbus-codegen --generate-c-code=Hello  --c-namespace hello --interface-prefix com.yft.hello. hello.xml
$CC `pkg-config --cflags gtk+-3.0` -o server server.c Hello.c `pkg-config --libs gtk+-3.0`
$CC `pkg-config --cflags gtk+-3.0` -o client client.c Hello.c `pkg-config --libs gtk+-3.0`  

