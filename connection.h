#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

typedef struct connection
{
	struct connection* 		_next;
	int 					_sock;
	unsigned 				_events;				//
	//
	queue_t(buffer) 		_read_data;				//���ݻ���
	uint32 					_read_size;				//��Ч��С
	buffer_t* 				_read_buffer;			//��ǰ����buffer
	//
	queue_t(buffer) 		_write_data;			//���ݻ���
	uint32 					_write_size;			//��Ч��С
	buffer_t* 				_write_buffer;			//��ǰ����buffer
	//
	uint32 					_timeout;				//����ʱ��
	uint32 					_control_end_time;		//������������
	uint32 					_control_read_size;		//���ڷ��ʹ�С
	uint32 					_control_write_size;	//���ڽ��մ�С
	
}connection_t;

//conn_open
connection* made_conn();
int conn_open(connection* conn);
int conn_close(connection* conn);
int conn_send(connection* conn, uint8* data, uint32 size);
int conn_recv(connection* conn, uint8* data, uint32 size);

#endif