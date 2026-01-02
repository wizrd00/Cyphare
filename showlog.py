#!/usr/bin/python3
import sys, os
import struct

LOGSIZE = 602
i = 1

def main() :
	global i
	if (len(sys.argv) != 2) :
		raise Exception("invalid arguments!")
	if (not os.path.exists(sys.argv[1])) :
		raise Exception(f"{sys.argv[1]} doesn't exists")
	with open(sys.argv[1], "rb") as logfile :
		while (True) :
			log = logfile.read(LOGSIZE)
			if not log :
				break
			level = log[:6].rstrip(b"\x00").decode()
			if not level :
				break
			date = log[6:17].rstrip(b"\x00").decode()
			clock = log[17:26].rstrip(b"\x00").decode()
			mod = log[26:58].rstrip(b"\x00").decode()
			pos = log[58:90].rstrip(b"\x00").decode()
			msg = log[90:602].rstrip(b"\x00").decode()
			print("[%d][%s][%s][%s][MOD:%s][POS:%s][MSG:%s]" % (i, level, date, clock, mod, pos, msg))
			i += 1
			logfile.seek(LOGSIZE, 1)
	return
main()
