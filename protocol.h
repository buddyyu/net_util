#ifndef __NET_PROTOCOL_H__
#define __NET_PROTOCOL_H__

//根据消息确定消息的接收、转发策略
typedef struct protocol {
	uint8_t 				_verion;			//传输协议版本
	uint32_t 				_code;				//协议类型
	uint16_t 				_head_size;			//包括自定义区的协议头长度
	uint32_t 				_body_size;			//数据体的大小
}protocol_t;

int package_protocol(protocol_t* protocol, uint8_t* data, uint32_t* size);
int unpackage_protocol(uint8_t* data, uint32_t size, protocol_t* protocol);

#endif