#!/bin/bash

### TO USE:
#### Open ftbrony on your test device
#### Change host/port combination
#### Run the script

HOST=192.168.xx.xx
PORT=5000

ftp -n ftp://$HOST:$PORT <<END_SCRIPT
cd /3ds
put citra-hwtests.3dsx
quit

END_SCRIPT
exit 0
