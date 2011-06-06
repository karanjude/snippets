import config
import os
from BeautifulSoup import BeautifulSoup, SoupStrainer
import urllib
from subprocess import *
import sys

process_queue = []

def process_item(item):
    html = urllib.urlopen(config.baseurl % (item[1]))
    html = html.read()
    hrefs = [tag["href"] for tag in BeautifulSoup(html, parseOnlyThese=SoupStrainer('a')) if str(tag).find("Download") > 0]
    os.chdir(item[0])
    for href in hrefs:
        if os.path.exists(os.path.join(os.getcwd(),href.split("/")[-1])):
            print "the video %s has already been downloaded" % (href.split("/")[-1])
            continue
        try:
            p = Popen("wget " + href, shell=True)
            retcode = os.waitpid(p.pid, 0)[1]
            if retcode < 0:
                print >>sys.stderr, "Child was terminated by signal", -retcode
            else:
                print >>sys.stderr, "Child returned", retcode
        except OSError, e:
            print >>sys.stderr, "Execution failed:", e


def process():
    for item in process_queue:
        process_item(item)

def create_subject_dirs_and_create_if_necessary():
    for k,v in config.subjects.iteritems():
        print "checking..", k
        create_dir_if_not_exists(os.path.join(config.basedir,k))
        process_queue.append((os.path.join(config.basedir,k),v))

def create_dir_if_not_exists(dirname):
    if os.path.exists(dirname) == False:
        print "creating ", dirname
        os.mkdir(dirname)
    else:
        print dirname , "exists"

if __name__ == "__main__":
    create_dir_if_not_exists(config.basedir)
    create_subject_dirs_and_create_if_necessary()
    process()
