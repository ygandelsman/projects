# This code uses "Beautiful Soup" to scrape given url's (from the file "addLinksHere.txt" that created and filled by the user).
# It finds all the url's in the current http file and print them to the file "links.txt"

from BeautifulSoup import BeautifulSoup
import urllib2
import socket
import re


socket.setdefaulttimeout(60)
tofile = open("links.txt", "wb")
fromfile = open("addLinksHere.txt")
links = fromfile.readlines()
linksNum = len(links)

print "number of links:", linksNum
for line in range(1,linksNum):
	try:
		print "link =", line
		nextLink = links[line]	
		tofile.write(nextLink)
		html_page = urllib2.urlopen(nextLink)
		soup = BeautifulSoup(html_page)
		for link in soup.findAll('a', attrs={'href': re.compile("^http://")}):
			tofile.write(link.get('href'))
			tofile.write("\n")

	except IOError:
		print "error"

