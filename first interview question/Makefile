all: addLinksHere.txt getLinks.py readEmails.py 
	python enti.py	
	python getLinks.py
	sort links.txt>links~.txt
	uniq links~.txt>links.txt
	python readEmails.py
	cat israel-emails.txt >> emails.txt
	sort emails.txt>emails~.txt
	uniq emails~.txt>emails.txt
	rm *~.txt

	
