#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

typedef struct connection
{
	struct connection* 		_next;
	int 					_sock;
	unsigned 				_events;				//
	//
	queue_t(buffer) 		_read_data;				//数据缓存
	uint32 					_read_size;				//有效大小
	buffer_t* 				_read_buffer;			//当前操作buffer
	//
	queue_t(buffer) 		_write_data;			//数据缓存
	uint32 					_write_size;			//有效大小
	buffer_t* 				_write_buffer;			//当前操作buffer
	//
	uint32 					_timeout;				//过期时间
	uint32 					_control_end_time;		//流量控制周期
	uint32 					_control_read_size;		//周期发送大小
	uint32 					_control_write_size;	//周期接收大小
	
}connection_t;

//conn_open
connection* made_conn();
int conn_open(connection* conn);
int conn_close(connection* conn);
int conn_send(connection* conn, uint8* data, uint32 size);
int conn_recv(connection* conn, uint8* data, uint32 size);

#endif