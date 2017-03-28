#ifndef __NET_BUFFER_H__
#define __NET_BUFFER_H__

typedef struct buffer {
	uint8* 				_buf;
	uint8* 				_capacity;
	uint8* 				_data;			//数据存放位置
}buffer_t;

//
uint32 buffer_capacity(buffer_t* buf);
uint32 buffer_size(buffer_t* buf);
uint32 buffer_put(buffer_t* buf, const uint8* data, uint32 size);
buffer_t* buffer_get(buffer_t* buf, uint32* inout_size);
buffer_t* buffer_split(buffer_t* buf, uint32* inout_size);
buffer_t* buffer_expand(buffer_t* buf, uint32 shink_size);
buffer_t* buffer_shrink(buffer_t* buf, uint32 shink_size);

#endif