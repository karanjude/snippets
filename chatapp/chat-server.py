import os, logging
import tornado. httpserver
import tornado. ioloop
import tornado. web
import uuid
import simplejson as json
from tornado. options import define, options

# Define options that can be changed as we run this via the command line
define("port", default=8888, help="Run server on a specific port", type=int)

# a convenience function to quickly build a notification object
def notification(_type, _data):
    return {' type': _type, 'data': _data}

# Declare the chat class. We'll fill it out later
class Chat(object):
    pass
# The Basic handler class
class BaseHandler(tornado.web.RequestHandler):
    @property
    def chat(self):
        return self.application.chat

# handle the main html request
class MainHandler(BaseHandler):
    def get(self):
        self. render("templates/chat-main.html")

# Extend tornado's web.Application module
class Application(tornado.web.Application):
    def __init__(self):
        # setup the URL handlers
        handlers = [
            (r"/", MainHandler),
            (r"/login/?", LoginHandler),
            (r"/updates/?", UpdateHandler),
            (r"/send/?", SendHandler),
            (r"/typing/?", TypingHandler),
            ]

        # setup the static path
        path = os.path.join(os.path.dirname(__file__), "static")
        settings = dict(static_path=path)
        tornado. web.Application.__init__(self, handlers, **settings)

        # Load the chat class
        self. chat = Chat()

# actually start up the server

class LoginHandler(BaseHandler):
    def post(self):
        # generate a unique ID for each user
        user_id = str(uuid.uuid4()) 

        # get the user_name submitted from the form
        user_name = self.get_argument('username')
        
        # Add this user to the chat class
        self. chat.add_user(user_id, user_name)
        
        # We' re done, notify the client.
        self. finish(dict(user_id=user_id, user_name=user_name, users=self.chat.users))

class Chat(object):
    listeners = []  # connected clients waiting for a callback
    users = [ ]      # the list of currently logged in users

    def add_listener(self, callback, user_id=None):
        data = {}
        data[ ' user_id'] = user_id
        data[ ' callback'] = callback
        self. listeners.append(data)

    def add_user(self, user_id, user_name):
        # assemble the user data into an object
        user_data = dict(user_id=user_id, user_name=user_name)
        # store the user data in the users list
        self. users.append(user_data)

        # let the other users know about this new user
        note = notification('login', user_data)
        self. send_notification(note)

    def send_notification(self, message, user_id=None):
        # create a copy of the listeners list and clear the original
        tmp_listeners = self.listeners
        self. listeners = []

        # loop through the list of listeners
        for data in tmp_listeners:
            # if we're not sending it to all users, 
            if user_id != None: 
                # and we're not sending it to this user
                if user_id != data['user_id']:
                    # keep listening, but don't send any messages
                    self.listeners.append(data)
            continue
            # run the callback function
            callback = data['callback']
            try:
                callback(message)
            except:
                logging.error("Error in listeners callback", exc_info=True)


class UpdateHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        user_id = self.get_argument('user_id')
        # add a listener, specifying the handle_updates callback
        self.chat.add_listener(self.async_callback(self.handle_updates),
                               user_id=user_id)

    # when we get a callback, send it to the client
    def handle_updates(self, update): 
        if not self.request.connection.stream.closed():
            self.finish(update)


class SendHandler(BaseHandler):
    def post(self):
        # who is the message to and from?
        to_user_id = self.get_argument('to_user_id')
        from_user_id = self.get_argument('from_user_id')
        # setup the message object that is sent to the user
        data = dict(from_user_id=from_user_id, 
                    to_user_id=to_user_id, 
                    text=self.get_argument('text'))
        # build and send the notification
        msg = notification('message', data)
        self.chat.send_notification(msg, user_id=to_user_id)
        # send a response to the user sending the message
        msg[ ' type'] = 'sent'
        self.finish(msg)

class TypingHandler(BaseHandler):
    def post(self):
        # Who is typing to who?
        to_user_id = self.get_argument('to_user_id')
        from_user_id = self.get_argument('from_user_id')
        # build and send the notification
        data = dict(from_user_id=from_user_id, to_user_id=to_user_id)
        msg = notification('typing', data)
        self. chat.send_notification(msg, user_id=to_user_id)
        # respond to the sending user
        msg[ ' type'] = 'recv'
        self. finish(msg)


if __name__ == "__main__":
    http_server = tornado.httpserver.HTTPServer(Application())
    tornado. options.parse_command_line()
    http_server. listen(options.port)
    tornado. ioloop.IOLoop.instance().start()

