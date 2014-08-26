# About

The datastore on the plug computer is an embedded database: 

Berkeley DB (BDB), version 5.3.28 (which is the last open license before Oracle switched to AGPL3 starting with BDB version 6.x).

# Installation

* Download <tt>Berkeley DB 5.3.28.tar.gz</tt> from the [list of prior releases](http://www.oracle.com/technetwork/database/database-technologies/berkeleydb/downloads/index-082944.html)

* Unpack the file and change to the <tt>build_unix </tt> directory:
   ```
tar xvf db-5.3.28.tar.gz
cd db-5.3.28/build_unix
```

* Build and install ([full instructions here](http://docs.oracle.com/cd/E17076_04/html/installation/build_unix.html)):
   ```
../dist/configure
make
sudo make install
```

  Here's what a successful installation looks like:
   ```
Installing DB include files: /usr/local/BerkeleyDB.5.3/include ...
Installing DB library: /usr/local/BerkeleyDB.5.3/lib ...
libtool: install: cp -p .libs/libdb-5.3.so /usr/local/BerkeleyDB.5.3/lib/libdb-5.3.so
libtool: install: cp -p .libs/libdb-5.3.lai /usr/local/BerkeleyDB.5.3/lib/libdb-5.3.la
libtool: install: cp -p .libs/libdb-5.3.a /usr/local/BerkeleyDB.5.3/lib/libdb-5.3.a
libtool: install: chmod 644 /usr/local/BerkeleyDB.5.3/lib/libdb-5.3.a
libtool: install: ranlib /usr/local/BerkeleyDB.5.3/lib/libdb-5.3.a
libtool: install: cp -p libdb.a /usr/local/BerkeleyDB.5.3/lib/libdb.a
libtool: install: chmod 644 /usr/local/BerkeleyDB.5.3/lib/libdb.a
libtool: install: ranlib /usr/local/BerkeleyDB.5.3/lib/libdb.a
libtool: finish: PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/sbin" ldconfig -n /usr/local/BerkeleyDB.5.3/lib
----------------------------------------------------------------------
Libraries have been installed in:
   /usr/local/BerkeleyDB.5.3/lib
```
   ```
If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the `-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the `LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the `LD_RUN_PATH' environment variable
     during linking
   - use the `-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to `/etc/ld.so.conf'
```
   ```
See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
```

* Install pip (if not already installed)

  Check to see if it is already there:
   ```
which pip
```

  If there's no reponse from that command, install it like this:
   ```
sudo apt-get install python-setuptools
sudo easy_install pip
```

* Install the [bsddb3](https://pypi.python.org/pypi/bsddb3) python library
   ```
sudo pip install bsddb3
```

   It should detect the right version in <tt>/usr/local/BerkeleyDB.5.3/</tt> and build against it:
   ```
Downloading/unpacking bsddb3
  Downloading bsddb3-6.1.0.tar.gz (340Kb): 340Kb downloaded
  Running setup.py egg_info for package bsddb3
    Found Berkeley DB 5.3 installation.
      include files in /usr/local/BerkeleyDB.5.3/include
      library files in /usr/local/BerkeleyDB.5.3/lib
      library name is libdb-5.3
    Detected Berkeley DB version 5.3 from db.h  
    warning: no files found matching 'updatedb.bat'
    warning: no files found matching '*.py' under directory 'bsddb3'
    warning: no files found matching '*.jpg' under directory 'docs'
    warning: no files found matching '*.json' under directory 'docs'
    warning: no files found matching '*.txt' under directory 'patches'
    warning: no files found matching '*.patch' under directory 'patches'
    warning: no files found matching '*.py' under directory 'test'
    no previously-included directories found matching 'docs/build'
    no previously-included directories found matching 'docs/tools/docutils'
    no previously-included directories found matching 'docs/tools/sphinx'
    no previously-included directories found matching 'docs/tools/pygments'
    no previously-included directories found matching 'old'
    no previously-included directories found matching 'test/db_home'
    no previously-included directories found matching 'test/bsddb3'
Installing collected packages: bsddb3
  Running setup.py install for bsddb3
    Found Berkeley DB 5.3 installation.
      include files in /usr/local/BerkeleyDB.5.3/include
      library files in /usr/local/BerkeleyDB.5.3/lib
      library name is libdb-5.3
    Detected Berkeley DB version 5.3 from db.h
    building 'bsddb3._pybsddb' extension
    gcc -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC -I/usr/local/BerkeleyDB.5.3/include -I/usr/include/python2.7 -c Modules/_bsddb.c -o build/temp.linux-x86_64-2.7/Modules/_bsddb.o
    gcc -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-z,relro build/temp.linux-x86_64-2.7/Modules/_bsddb.o -L/usr/local/BerkeleyDB.5.3/lib -Wl,-R/usr/local/BerkeleyDB.5.3/lib -ldb-5.3 -o build/lib.linux-x86_64-2.7/bsddb3/_pybsddb.so
```

* Test and confirm

  Open a python shell and import the bsddb3 library:
   ```python
>>> import bsddb3 as db
```

  It should return a new prompt, without any exception or <tt>ImportError</tt>.
