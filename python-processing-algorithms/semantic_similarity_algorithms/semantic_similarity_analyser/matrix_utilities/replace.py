for x in range(0,255):
	f1 = open(str(x)+'.txt.tmp','r')
	f2 = open(str(x)+'.txt','w')
	for line in f1:
		f2.write(line.replace(']',''))
	f1.close()
	f2.close()
