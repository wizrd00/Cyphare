import sys
sys.path.append("./include")
sys.path.append("./source")
from rufshare_types import *
from cyphare import *

run = PushFile("./LICENSE", "LICENSE", "TestMan", ("0.0.0.0", 1337), ("127.0.0.1", 13370), 32, 3)
print(run.push())
