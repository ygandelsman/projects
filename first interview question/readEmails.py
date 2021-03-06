# This code reads a file with url's, that generated by "getLinks.py".
# For any url, it checks if the http file contains contant that related to "english teachers".
# If the page is related, the program scrapes and writes to another file the email addresses in the page. 
# The execution of this code takes almost 2 hours...

import urllib
import re		
import socket

emails = open("emails.txt","wb")
links = open("links.txt")
emailNum = 0
errors = 0
socket.setdefaulttimeout(60)
lines = links.readlines()
linesNum = len(lines)
print "number of links:", linesNum

for url in range(1,linesNum):
	print "url number =", url	
	try:
		line = lines[url]
		f = urllib.urlopen(line)
		currentText = f.read()
		tolower = currentText.lower()
		if (("teaching" in tolower or "tutor" in tolower or "teacher" in tolower) and "english" in tolower): # search for two words - "teacher/teaching/tutor" and "english"
			match = re.findall(r'[a-zA-Z\.][0-9a-zA-Z\.]+@[0-9a-zA-Z\.]+\.[0-9a-zA-Z]+',currentText) # regular expression of email
			for m in match:							
				emails.write(m)
				emails.write("\n")
				emailNum += 1				
				print "emails:", emailNum			
	except IOError:
		errors += 1
		print "errors:", errors
