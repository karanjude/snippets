import logging
import tornado. httpserver
import tornado. ioloop
import tornado. web
from tornado. options import define, options
import os
import uuid
import threading
import re
import simplejson as json
# Setup the queue
import Queue
import urllib2
import base64 

tweetQueue = Queue.Queue(0)

# Define options that can be changed as we run this via the command line
define("port", default=8888, help="Run server on a specific port", type=int)

class TweetFirehose(threading.Thread): 

    def run(self):
        status_sample_url = 'http://stream.twitter.com/1/statuses/sample.json'
        request = urllib2.Request(status_sample_url)
 
        # Be sure to use your own twitter login information
        auth_basic = base64.encodestring('karanjude:fuckme123')[:-1] 
        request. add_header('Authorization', 'Basic %s' % auth_basic)
 
        # open the connection
        firehose = urllib2.urlopen(request)
 
        for tweet in firehose:
            if len(tweet) > 2:
                tweetQueue.put(tweet)
        #    print tweet
        firehose.close()
        print "killing fire hose........"
        
class TweetProcessor(threading.Thread):


  def run(self):
        # pre-compile some regular expressions
        links = re.compile("(http\:\/\/[^\ ]+)")
        hashtag = re.compile("(\#[0-9a-zA-Z]+)")
        ats = re.compile("(\@[0-9a-zA-Z]+)")
        retweets = re.compile("RT|via\ ")
        while True:
            tweet = tweetQueue.get()
            if tweet:
                t = json.loads(tweet)
                try:
                    stats = {}
                    stats['hashtags'] = hashtag.findall(t['text'])
                    stats['ats'] = ats.findall(t['text'])
                    stats['links'] = links.findall(t['text'])
                    stats['retweets'] = retweets.findall(t['text'])
            # pack the message up
                    message = {
                        "id": str(uuid.uuid4()),
                        "stats": stats
                        }
                    message["html"] = "<div class=\"message\" id=\"m" + message["id"] + "\"><strong>" + t['user']['screen_name'] + ": </strong>" + t['text'] + "</div>"
                    #print "read tweeet ........."
                    #print message

                    Tweet().new_tweets([message])
                except Exception, e:
                    print "exception.........", e
                    # ignore any exceptions
                    pass


class MainHandler(tornado.web.RequestHandler):
    def get(self):
        logging. info("Request to MainHandler!")
        self.render("templates/main.html")
        #self.write("Great, now let's make this app speak in realtime.")

class Tweet(object):
    waiters = [ ]      # a list of clients waiting for updates
    cache = [ ]        # a list of recent tweets
    cache_size = 200  # the amount of recent tweets to store
    
    def wait_for_messages(self, callback, cursor=None):
        cls = Tweet
        if cursor:
            index = 0
            for i in xrange(len(cls.cache)): 
                index = len(cls.cache) - i - 1
                if cls.cache[index]["id"] == cursor: break 
            recent = cls.cache[index + 1:]
            if recent:
                callback(recent)
                return
        #print "call back added " , str(callback)
        cls.waiters.append(callback)

    def new_tweets(self, messages):
        cls = Tweet
        for callback in cls.waiters:
            try:
                print "about to call callback ......... "
                callback(messages)
            except:
                logging.error("Error in waiter callback", exc_info=True)
        cls. waiters = []
        cls. cache.extend(messages)
        if len(cls.cache) > self.cache_size:
            cls. cache = cls.cache[-self.cache_size:]

class UpdateHandler(tornado.web.RequestHandler, Tweet):
    @tornado.web.asynchronous
    def post(self):
        cursor = self.get_argument("cursor", None)
        self.wait_for_messages(self.async_callback(self.on_new_tweets),
                               cursor=cursor)

    def on_new_tweets(self, tweets): 
        if not self.request.connection.stream.closed():
            self.finish(dict(tweets=tweets))

local_static_path = os.path.join(os.path.dirname(__file__), "static")

application = tornado.web.Application([
    (r"/", MainHandler),
    (r"/updates", UpdateHandler),
] , static_path=local_static_path)

if __name__ == "__main__":
    http_server = tornado.httpserver.HTTPServer(application)
    tornado. options.parse_command_line()
    http_server. listen(options.port)
    TweetProcessor().start()
    TweetFirehose().start()
    tornado.ioloop.IOLoop.instance().start()

