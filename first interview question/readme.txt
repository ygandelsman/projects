first interview question - find 1000 emails of English teachers
===============================================================

the code that finds 1000 emails of English teachers divided between
"readEmails.py", "getLinks.py" and "enti.py"

the final answer is in "emails.txt"

to run and get the result (it can take 2 or 3 hours...), use the "makefile" on linux os. 


answer process
--------------

First I tried to understand how to crawl, scrape and parse http files.
I used Scrapy tool, but then I decided to work with simple string 
parsing that provided by Python. I read in stackoverflow that it is 
much simplier, so I started to read a little bit how to program in Python 
and how to parse string with this language.

I found a site that contains a lot of English teachers emails (the site of the 
English teachers association in Israel). I learned how to scrape and crawl in it
and how to parse strings in it.
The program "enti.py" is the final results if those attempts and it creates a file
with 52 emails - "israel-emails.txt".

I added this file to the answer too, because I wanted to show what I managed to 
do and learn through this mini-project. 


In my second attempt, I tried to use google API for scraping and google libraries
xgoogle and pygoogle to crawl and get thousands of url's that return from the google
search of "English teacher". 
This attempt failed because google gives only 100 queries per day, and I needed much more.
Also, I wanted to be sure that the sites that google returns are really connected to 
the subject and that the emails in those sites are real emails of english teachers.

After this attempt I decided to find on my own a small amount of site's 
urls that really connected to the subject and work with them (this is the 
"addLinksHere.txt" file). I searched for sites of English teachers job searches, 
English teachers networks, English teachers blogs and English teachers Associations to get 
better results.

Then, I wrote a simple scraper ("getLinks.py") that gets all the url links from every site 
that appears in "addLinksHere.txt". The scraper writes the new urls 
to "links.txt" (this file contains thousands of url's). 
It uses "Beautiful Soap" scraping tool.

I also wrote another scraper/crawler ("readEmails.py") that reads the http file of every url 
in "links.txt". 
If "readEmails.py" finds "interseting" words (like "English" and "teaching")
it searches for email's and writes them to the final file - "emails.txt".

I used linux functions to delete duplicates in files and append files.
  