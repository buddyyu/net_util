#ifndef __NET_PROTOCOL_H__
#define __NET_PROTOCOL_H__

//������Ϣȷ����Ϣ�Ľ��ա�ת������
typedef struct protocol {
	uint8_t 				_verion;			//����Э��汾
	uint32_t 				_code;				//Э������
	uint16_t 				_head_size;			//�����Զ�������Э��ͷ����
	uint32_t 				_body_size;			//������Ĵ�С
}protocol_t;

int package_protocol(protocol_t* protocol, uint8_t* data, uint32_t* size);
int unpackage_protocol(uint8_t* data, uint32_t size, protocol_t* protocol);

#endif