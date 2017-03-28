#ifndef __NET_MESSAGE_H__
#define __NET_MESSAGE_H__

#include "buffer.h"
#include "queue.h"

enum msg_serialize_t {
	SERIALIZE_BINARY			= 0,
	SERIALIZE_JSON				= 1,
	SERIALIZE_XML				= 2,
	SERIALIZE_PROTOBUFFER		= 3,
	TSERIALIZE_HRIFT			= 4,
};

typedef struct message_head {
	uint32_t 					_magic;						//��� 
	uint32_t 					_server_id;					//Ŀ�����ID
	uint32_t 					_msg_id;						//������ID(moudle_id(16)+sub_msgid(16))
	uint32_t 					_msg_unique;					//ͬһ��Ϣ������Է��ͣ����ֶβ���
	uint32_t 					_msg_seq;					//������Ϣ���
	uint32_t 					_msg_len;					//��Ϣ�峤��
	uint8_t  					_msg_serialize;				//��Ϣ���л�����
}message_head_t;

typedef struct message {
	message_head_t 		 		_head;						//
	queue_t(buffer) 			_data;						//���ݻ���
	uint32 						_data_size;					//��Ч��С
	buffer_t* 					_buffer;					//��ǰ����buffer
	
}message_t;

#endif