/*
    librouteros-api - Connect to RouterOS devices using official API protocol
    Copyright (C) 2012, Håkon Nessjøen <haakon.nessjoen@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

struct ros_result {
	int words;
	char **word;
	char done;
	char re;
	char trap;
	char fatal;
};

struct ros_connection {
	enum {
		ROS_SIMPLE,
		ROS_EVENT
	} type;
	int socket;
	unsigned char *buffer;
	struct ros_result *event_result;
	int expected_length;
	int length;
};

/*FIXME*/
struct ros_result *ros_send_command_event(struct ros_connection *conn, char *command, ...);
void ros_set_type(struct ros_connection *conn, int type);

void runloop_once(struct ros_connection *conn, void (*callback)(struct ros_result *result));
struct ros_connection *ros_connect(char *address, int port);
int ros_disconnect(struct ros_connection *conn);
struct ros_result *ros_send_command(struct ros_connection *conn, char *command, ...);
struct ros_result *ros_read_packet(struct ros_connection *conn);
void ros_free_result(struct ros_result *result);
char *ros_get(struct ros_result *result, char *key);
int ros_login(struct ros_connection *conn, char *username, char *password);
char *ros_get_tag(struct ros_result *result);

#define ROS_PORT 8728
