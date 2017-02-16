# Easy: https://medium.com/@dawran6/twitter-scraper-tutorial-with-python-requests-beautifulsoup-and-selenium-part-1-8e76d62ffd68#.qp1b0vd1r
# Medium and hard: https://medium.com/@dawran6/twitter-scraper-tutorial-with-python-requests-beautifulsoup-and-selenium-part-2-b38d849b07fe#.931wvlp95

import requests
from bs4 import BeautifulSoup

url = u'https://twitter.com/'
# user = u'realDonaldTrump'
user = u'jzrowdy'

r = requests.get(url+user)
soup = BeautifulSoup(r.text, 'html.parser')

tweets = [p.text for p in soup.findAll('p', class_='tweet-text')]

print(tweets)

# <div class="js-tweet-text-container">
#  <p class="TweetTextSize TweetTextSize--26px js-tweet-text tweet-text" lang="en" data-aria-label-part="0">Information is being illegally given to the failing <a href="/nytimes" class="twitter-atreply pretty-link js-nav" dir="ltr" data-mentioned-user-id="807095" ><s>@</s><b>nytimes</b></a> &amp; <a href="/washingtonpost" class="twitter-atreply pretty-link js-nav" dir="ltr" data-mentioned-user-id="2467791" ><s>@</s><b>washingtonpost</b></a> by the intelligence community (NSA and FBI?).Just like Russia</p>
# </div>
