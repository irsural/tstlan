set progname=tstlan4

rar a -rr -r -ep1 -ap%progname% -x*.obj -x*.tds -x*.~* -x*.il? -x*.bak -x*.*~ -x*.dcu -x~W*.tmp -x~$*.* -x*.map -x*.pch -x*.#?? "-ag yyyymmdd hhmmss" "..\old\%progname%.rar" .
pause