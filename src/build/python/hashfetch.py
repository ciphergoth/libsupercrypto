import os.path
import tempfile
import shutil
import hashlib
import urllib2


def copy_and_hash(h, fsrc, fdst, length=16*1024):
    """copy data from file-like object fsrc to file-like object fdst,
       updating hash as we go along"""
    while 1:
        buf = fsrc.read(length)
        if not buf:
            break
        h.update(buf)
        fdst.write(buf)

def fetch_and_hash(url, hexdigest, target):
    print "Fetching:", url
    tempdir = tempfile.mkdtemp()
    try:
        name = os.path.basename(target)
        fetch = os.path.join(tempdir, name)
        uf = urllib2.urlopen(url)
        try:
            with open(fetch, "w") as t:
                h = hashlib.sha256()
                copy_and_hash(h, uf, t)
                if h.hexdigest() != hexdigest:
                    print "Expected:", hexdigest
                    print "Got:", h.hexdigest()
                    raise Exception("Digest mismatch")
        finally:
            uf.close() # Doesn't bloody support "with"!
        os.rename(fetch, target)
    finally:
        shutil.rmtree(tempdir)


