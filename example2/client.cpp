#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef G_OS_UNIX
//#include <gio/gunixfdlist.h>
/* For STDOUT_FILENO */
#include <unistd.h>
#endif

GDBusProxy *bproxy;
GMainLoop * g_main_loop;

void mycallback (GObject * gobj, GAsyncResult * res, gpointer user_data)
{
	printf ("\n Inside mycallback\n ");

	GError *error;
	GVariant *result;
	gchar *str;

	error = NULL;
	result = g_dbus_proxy_call_finish (bproxy, res, &error);
	g_variant_get (result, "(s)", &str);
	printf ("String from Server is: %s \n", str);
	g_main_loop_quit(g_main_loop);
	exit(0);
}

int main (int argc, char **argv)
{
	GDBusConnection *bcon;
	GMainLoop *loop;

	g_type_init ();
	bcon = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL);
	bproxy = g_dbus_proxy_new_sync (bcon, G_DBUS_PROXY_FLAGS_NONE, NULL, "org.myapp.JelariServer", "/org/myapp/JelariObject", "org.myapp.JelariInterface", NULL, NULL);
	g_dbus_proxy_call (bproxy, "HelloWorld", g_variant_new ("(s)", "Wow"), G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) mycallback, NULL);

	g_main_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(g_main_loop);
	return 0;
}
