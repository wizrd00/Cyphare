from ctypes import *

FOREVER_TIMEOUT = -1
MAXFILENAMESIZE = 256
MAXNAMESIZE = 32
MAXIPV4SIZE = 16

SUCCESS = 0
FAILURE = 1
TIMEOUT = 2
LOWSIZE = 3
EXPTRY0 = 4
EXPTRY1 = 5
ZEROACK = 6
ZEROSEQ = 7
ZEROCHK = 9
FAILSET = 10
FAILCRC = 11
FAILLOG = 12
BADCONF = 13
BADFLOW = 14
BADARGS = 15
BADINET = 16
BADTYPE = 17
BADIPV4 = 18
BADPORT = 19
NOMFILE = 20
NOFSTAT = 21
NOAVAIL = 22
NOCREAT = 23
NOTRUNC = 24
NOCLOSE = 25
ERRBIND = 26
ERRCONN = 27
ERRRECV = 28
ERRSEND = 29
ERRLSTN = 30
ERRPOLL = 31
ERRTIME = 32
EMALLOC = 33
ETHREAD = 34
INVSOCK = 35
INVPATH = 36
TESTVAL = 37

class addr_pair(Structure) :
	_fields_ = [
		("ip", POINTER(c_char)),
		("port", c_ushort)
	]

class PairInfo(Structure) :
	_fields_ = [
		("name", c_char * MAXNAMESIZE),
		("addr", addr_pair)
	]

class CntlAddrs(Structure) :
	_fields_ = [
		("filename", c_char * MAXFILENAMESIZE),
		("name", c_char * MAXNAMESIZE),
		("local_ip", c_char * MAXIPV4SIZE),
		("remote_ip", c_char * MAXIPV4SIZE),
		("local_port", c_ushort),
		("remote_port", c_ushort)
	]

class MFILE(Structure) :
	_fields_ = [
		("file", c_void_p),
		("open", c_short),
		("size", c_size_t),
		("pos", c_size_t),
		("buf", c_void_p)
	]

class FileContext(Structure) :
	_fields_ = [
		("mfile", MFILE),
		("size", c_size_t),
		("name", c_char * MAXFILENAMESIZE)
	]

class InitConfig(Structure) :
	_fields_ = [
		("chsize", c_uint16),
		("pchsize", c_uint16),
		("chcount", c_uint32),
		("seq", c_uint32),
		("cntl_sock", c_int),
		("data_sock", c_int),
		("conn_sock", c_int),
		("cast_sock", c_int),
		("filec", FileContext),
		("addrs", CntlAddrs),
		("segsize", c_size_t),
		("hst_send", c_int),
		("hst_recv", c_int),
		("vft_send", c_int),
		("vft_recv", c_int),
		("tft_flow", c_int),
		("tft_recv", c_int),
		("tft_data", c_int),
		("bct_cast", c_int),
		("spt_cast", c_int),
		("bc_interval", c_short),
		("sp_interval", c_short),
		("tf_trycount", c_short),
		("bc_trycount", c_short),
		("sp_trycount", c_short)
	]
