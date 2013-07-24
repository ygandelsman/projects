# This was my first attempt to understand how to crawl and scrape http files.
# First I used 'Scrapy' tools and modules but then I decided to parse and read https with the given python libraries.
# I scrape here english teachers journal (the "about the writers of the current issue" section).
# you can see the issues of the journal in "http://www.etni.org.il/etnirag/issue*/writers.htm", where * can be any number from 1 to 9

import urllib
import re		

emails = open("israel-emails.txt","wb")
for i in range(1,9):
	f = urllib.urlopen("http://www.etni.org.il/etnirag/issue"+str(i)+"/writers.htm")
	match = re.findall(r'Email: .*\n',f.read())
	for m in match:
		if "(at)" in m:
			stri = m.split(' ')[1].split('\'')[0].replace("(at)", "@").replace("(dot)", ".").replace("</a>","")
			
		else:
			stri = m.split('<')[1].split('>')[1]
		emails.write(stri.replace("\n","").replace("\r",""))
		emails.write("\n")
