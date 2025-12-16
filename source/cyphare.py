import sys, os
import ipaddress
from ctypes import *
from include import rufshare_types
from include import rufshare_func

class PushFile :
	def __init__(self,
		path : str,
		filename : str,
		name : str,
		local_addr : tuple[str, int],
		remote_addr : tuple[str, int],
		chunk_size : int,
		trycount : int
	) -> None :
		self._path = self.path = path
		self._filename = self.filename = filename
		self._name = self.name = name
		self._local = self.local = local_addr
		self._remote = self.remote = remote_addr
		self._chsize = self.chsize = chunk_size
		self._trycount = self.trycount = trycount
		self.config = rufshare_types.InitConfig()
		return

	@property
	def path(self) -> str :
		return self._path
	
	@path.setter
	def path(self, value : str) -> None :
		if (os.path.exists(value)) :
			self._path = value
		else :
			raise Exception(f"invalid path '{value}'")
		return
	
	@property
	def filename(self) -> str :
		return self._filename

	@filename.setter
	def filename(self, value : str) -> None :
		if (value) :
			self._filename = value
		else :
			raise Exception("empty filename")
		return
	
	@property
	def name(self) -> str :
		return self._name

	@name.setter
	def name(self, value : str) -> None :
		if (value and value.isascii()) :
			self._name = value
		else :
			raise Exception(f"invalid name '{value}'")
		return
	
	@property
	def local(self) -> tuple[str, int] :
		return self._local
	
	@local.setter
	def local(self, value : tuple[str, int]) -> None :
		try :
			ip = ipaddress.ip_address(value[0])
			if (ip.version == 4 and value[1] > 0 and value[1] <= 65535) :
				self._local = value
			else :
				raise Exception(f"invalid local address '{value[0]}:{value[1]}'")
		except :
			raise Exception(f"invalid local address '{value[0]}:{value[1]}'")
		return
	
	@property
	def remote(self) -> tuple[str, int] :
		return self._remote
	
	@remote.setter
	def remote(self, value : tuple[str, int]) -> None :
		try :
			ip = ipaddress.ip_address(value[0])
			if (ip.version == 4 and value[1] > 0 and value[1] <= 65535) :
				self._remote = value
			else :
				raise Exception(f"invalid remote address '{value[0]}:{value[1]}'")
		except :
			raise Exception(f"invalid remote address '{value[0]}:{value[1]}'")
		return

	@property
	def chsize(self) -> int :
		return self._chsize
	
	@chsize.setter
	def chsize(self, value : int) -> None :
		if (value > 0 and value <= 65535) :
			self._chsize = value
		else :
			raise Exception(f"invalid chunk size '{value}'")
		return
	
	@property
	def trycount(self) -> int :
		return self._trycount

	@trycount.setter
	def trycount(self, value : int) -> None :
		if (value > 0) :
			self._trycount = value
		else :
			raise Exception(f"invalid trycount '{value}'")
		if (value > 8) :
			print(f"[\x1b[31mWARNNING\x1b[0m] : trycount value should be in range 1 to 8 which {value} is not")
		return

	def initconfig(self) -> None :
		self.config.chsize = self.chsize
		self.config.pchsize = 0
		self.config.chcount = 0
		self.config.seq = 0
		self.config.addrs.filename = self.filename
		self.config.addrs.name = self.name
		self.config.addrs.local_ip = self.local[0]
		self.config.addrs.remote_ip = self.remote[0]
		self.config.addrs.local_port = self.local[1]
		self.config.addrs.remote_port = self.remote[1]
		self.config.tf_trycount = self.trycount
		return
	
	def push(self) -> bool :
		path = create_string_buffer(bytes(self.path.encode()))
		result = rufshare_func.push_file(POINTER(self.config), path)
		#TODO
		return True if (result == 0) else False
