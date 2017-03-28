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
	uint32_t 					_magic;						//标记 
	uint32_t 					_server_id;					//目标服务ID
	uint32_t 					_msg_id;						//请求标记ID(moudle_id(16)+sub_msgid(16))
	uint32_t 					_msg_unique;					//同一消息多次重试发送，该字段不变
	uint32_t 					_msg_seq;					//请求消息序号
	uint32_t 					_msg_len;					//消息体长度
	uint8_t  					_msg_serialize;				//消息序列化类型
}message_head_t;

typedef struct message {
	message_head_t 		 		_head;						//
	queue_t(buffer) 			_data;						//数据缓存
	uint32 						_data_size;					//有效大小
	buffer_t* 					_buffer;					//当前操作buffer
	
}message_t;

#endif