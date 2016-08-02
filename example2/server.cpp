#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef G_OS_UNIX
//#include <gio/gunixfdlist.h>
/* For STDOUT_FILENO */
#include <unistd.h>
#endif

static GDBusNodeInfo *introspection_data = NULL;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
	"<node>"
	"<interface name='org.myapp.JelariInterface'>"
	"<method name='HelloWorld'>"
	"<arg type='s' name='greeting' direction='in'/>" 
        "<arg type='s' name='response' direction='out'/>"
        "</method>"
        "</interface>" 
         "</node>";

static void
handle_method_call (GDBusConnection * connection,
	const gchar * sender, const gchar * object_path, const gchar * interface_name, const gchar * method_name, GVariant * parameters, GDBusMethodInvocation * invocation, gpointer user_data)
{
	printf ("Inside Handle Method Call \n");

	if (g_strcmp0 (method_name, "HelloWorld") == 0)
	{
		const gchar *greeting;

		gchar *response;
		g_variant_get (parameters, "(&s)", &greeting);
		response = g_strdup_printf ("You typed '%s', !!! ", greeting);

		g_dbus_method_invocation_return_value (invocation, g_variant_new ("(s)", response));
		printf ("Sending %s  -> to the client ", response);

	}
}

static const GDBusInterfaceVTable interface_vtable = {
	handle_method_call,
	NULL,
	NULL
};

static void on_bus_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
	printf ("\n Inside on_bus_acquired \n");

	guint registration_id;

	registration_id = g_dbus_connection_register_object (connection, "/org/myapp/JelariObject", introspection_data->interfaces[0], &interface_vtable, NULL,	/* user_data */
		NULL,					/* user_data_free_func */
		NULL);					/* GError** */
	g_assert (registration_id > 0);

}

static void on_name_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
}

static void on_name_lost (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
	exit (1);
}

int main (int argc, char **argv)
{
	guint owner_id;
	GMainLoop *loop;
	g_type_init ();
	introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, NULL);
	g_assert (introspection_data != NULL);

	owner_id = g_bus_own_name(G_BUS_TYPE_SESSION, "org.myapp.JelariServer", G_BUS_NAME_OWNER_FLAGS_NONE, on_bus_acquired, on_name_acquired, on_name_lost, NULL, NULL);

	printf ("\n Owner id is %d ", owner_id);
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	g_bus_unown_name(owner_id);

	g_dbus_node_info_unref(introspection_data);

}
