/*
网络协议相关定义
*/
//用户接口定义


enum MsgType
{
	REQ_RSP			= 1,  //请求响应消息
	REQ_COMMIT		= 2,  //提交式请求
	REQ_PIPE		= 3,  //pipeline请求
	REQ_LIST		= 4,  //批量-分个返回请求
	REQ_INCR		= 5,  //增量请求
};

enum SerializeType
{
	JSON			= 1,
	XML				= 2,
	PB				= 3,
	THRIFT			= 4,
}

struct CAFMessage
{
	uint8 _msg_type;					//请求类型
	
};

struct CAFRequest 
{
	unsigned _serialize_type:4;			//序列化类型
	unsigned _req_id;					//请求标记ID
	unsigned _req_seq;					//请求序号
	Data*	_req_data;					//
};
typedef CAFRequest Request;

struct CAFResponse
{
	unsigned:4 	_rsp_status;			//响应状态
	unsigned _serialize_type:4;			//序列化类型
	unsigned _req_id;					//请求标记ID
	unsigned _req_seq;					//请求序号
	Data* _rsp_data;					//
}

int SendPBRequest(Service* srv, unsigned req_id, const google::message* req, Response* rsp)
{
	Request* req = make_request();
	req->_serialize_type = SerializeType::PB;
	req->_req_id = req_id;
	req->_req_seq = GeneratorSEQ();
	req->_req_data = req->SerializeString();
	
	return SendRequest(rep, rsp);
}

int SendRequest(Service* srv, const Request* req, Response* rsp)
{
	
	//iovec[0].data = req->head_data();
	//iovec[1].data = req->_req_data;
	//sendv(srv->NetManager::Instance()::getfd(), iovec, 2);
}

//业务管理模块
int HandleRequest(const Request* req, Response* rsp)
{
	int nret_code = 0;
	Data rsp_data = make_data();
	REQ_HANDLER req_handle = BusinessManager::Instance().findReqHandle(req->_req_id);
	switch (req->_serialize_type) {
		case JSON: {
			nret_code = req_handle(req->_req_id, REQ2JSON(req), &rsp_data);
			break;
		}
		case XML: {
			nret_code = req_handle(req->_req_id, REQ2XML(req), &rsp_data);
			break;
		}
		case PB: {
			nret_code = req_handle(req->_req_id, REQ2PB(req), &rsp_data);
			break;
		}
		case THRIFT: {
			break;
		}
		default: {
			
		}
	}//switch
	rsp->set_status(nret_code);
	rsp->set_data(rsp_data);
	
	return 0;
}







typedef struct {
	
}Buffer, *BufferPtr;

//创建并初始化tcp连接
typedef int (*CLIENT_INIT)();
typedef int (*CLIENT_RECV)();
typedef int (*CLIENT_SEND)();
typedef struct {
	int _fd;
	Buffer _recv_buffer;
	Buffer _send_buffer;
	CLIENT_INIT _init;
	CLIENT_SEND _send;
	CLIENT_RECV _recv;
}TcpSocket, *TcpSocketPtr;
/*
TcpSocket sock;
sock._init(&sock);
sock._send(&sock);
*/

typedef struct {
	uint32 _msg_uuid;
	uint32 _srv_uuid;
	void* _data;
}ReqMessage;

typedef struct {
	uint32 _msg_uuid;
	uint32 _srv_uuid;
	uint32 _rsp_to_uuid;
	void* _data;
}RspMessage;

typedef struct {
	uint16 _data_size;
	void* _data;
}Message, *MessagePtr;

typedef Message ReqMessage;
typedef Message RsqMessage;
typedef int (*MSG_CALLBACK) (RsqMessage *msg_data);
RsqMessage SendMsg(TcpSocket *tcp_scok, ReqMessage *msg_data);
int SendMsg(TcpSocket *tcp_scok, ReqMessage *msg_data, MSG_CALLBACK rsp_call);

//建议一个NetRobot
typedef struct {
	
}NetRobot, *NetRobotPtr;

static AddSock(NetRobot* net_robot, TcpSocket *tcp_scok);

NetRobot* CreateNetRobot();

static void NetworkUpdate(NetRobot* net_robot);

struct NetEngine;
typedef int (*ENGINE_INIT)(NetEngine* engine);
typedef void (*ENGINE_DESTROY)(NetEngine* engine);
typedef void (*ENGINE_WORK)(NetEngine* engine);
typedef struct {
	ENGINE_INIT _init;
	ENGINE_DESTROY _destroy;
	ENGINE_WORK _work_loop;
	pthread_t _pid;
	void* _data;
}NetEngine, *NetEnginePtr;



//---------------------------------
typedef struct {
	uint32 _magic;			//包头标记
	uint8 _verion;			//传输协议版本
	uint16 _head_size;		
	uint16 _code;			//传输服务类型
	uint32 _session_id;
	uint32 _channal_id;
	uint32 _msg_id;			//先放这里吧
	uint32 _pack_size;
}Head, *HeadPtr;
head_t
typedef struct {
	int _fd;
	uint32 _external_session_id;
	uint32 _internal_session_id;
	Buffer _recv_buf;
	Buffer _send_buf;	
}Session, *SessionPtr;

typedef struct {
	Session* _own;
	uint32 _start_time;
	uint32 _send_size;
	uint32 _recv_size;
	//uint8 _bad_pack_size;
}ControlSession, *ControlSessionPtr;

int onAccpet(int fd) 
{
	//先move未验证列表
	not_valider_list<int>.push_back(make_pair(fd, now_time));
	//--接收时处理：等待请求头
	Session* client_ss = MadeSession(fd);
	hash_map[fd] = client_ss;
}

int onRecv(Session* client_ss, char[] data, size_t data_size)
{
	if (0 == client_ss->_external_session_id) {
		if (data_size < sizeof(Head)) {
			client_ss->_recv_buf.append(data, data_size);
		}else {
			client_ss->_recv_buf.append(data, data_size);
			Head pack_head;
			uint32 mv_size = client_ss->_recv_buf.move(&pack_head, sizeof(pack_head));
			if (mv_size < 0) {
				
			}
			if (0 != pack_head._session_id) {
				Session* old_session = session_hash_map[pack_head._session_id];
				if (old_session) {
					old_session->append()
				}
			}
		}
	}else {
		client_ss->_recv_buf.append(data, data_size);
	}
}

int onSend(Session* client_ss, char[] data, size_t data_size) 
{
}

typedef WORK_PROC(Session* session, void* data);

Register(msg_id, WORK_PROC process)