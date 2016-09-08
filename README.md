net_util：基于目前分布式框架（convenient and fast : CAF）,开发一套客户端易用的网络库。主要包含以下功能：
（1）一般的长连接服务，基于TCP实现；
（2）UDP的简单包装，支持重传、流量控制，不保证有序性；
（3）大数据量的传输服务，如文件，基于TCP+UDP,参考：RTP/RTCP
