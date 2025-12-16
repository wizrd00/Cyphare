from rufshare_types import *

rufshare = CDLL("./library/librufshare.so")

push_file = rufshare.push_file
push_file.argtypes = [POINTER(InitConfig), POINTER(c_char)]

# what my roommates wrote when I wasn't coding :) -> pull_file = rufshare.pull_file xnxx/ pornhub.com/ xvideos.com/ eporner.net/ nhentai.net/ literotica.com/ coomer.st/ xmegadrive.org/ onlyfans/ kemono.cr / simpcity.su / rule34.xxx /

pull_file = rufshare.pull_file
pull_file.argtypes = [POINTER(InitConfig), POINTER(c_char), POINTER(c_char)]

broadcast = rufshare.broadcast
broadcast.argtypes = [POINTER(InitConfig)]

scanpair = rufshare.scanpair
scanpair.argtypes = [POINTER(InitConfig), POINTER(PairInfo), POINTER(c_size_t)]
