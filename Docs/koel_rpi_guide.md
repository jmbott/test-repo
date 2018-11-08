Koel

http://stackoverflow.com/questions/31230133/how-to-make-a-raspberry-pi-2-laravel-5-1-server

$ sudo apt-get update
$ sudo apt-get upgrade

Install php7

Check what the most recent version is, on http://php.net/downloads.php

Download the source code

$ wget http://php.net/distributions/php-7.0.9.tar.gz

Extract the tarball
$ tar xvf php-7.0.9.tar.gz

Remove compressed version
$ rm php-7.0.9.tar.gz

Cd into the created directory
$ cd php-7.0.9

install dependencies

$ sudo apt-get install libkrb5-dev libc-client2007e libc-client2007e-dev libcurl4-openssl-dev libbz2-dev libjpeg-dev libmcrypt-dev libxslt1-dev libxslt1.1 libpq-dev build-essential git make

Configure:

```
./configure \
--prefix=/opt/php-7.0.9                      \
--with-config-file-path=/opt/php-7.0.9/etc   \
--with-zlib-dir                              \
--with-freetype-dir                          \
--enable-mbstring                            \
--with-libxml-dir=/usr                       \
--enable-soap                                \
--enable-calendar                            \
--with-curl                                  \
--with-mcrypt                                \
--with-zlib                                  \
--with-gd                                    \
--disable-rpath                              \
--enable-inline-optimization                 \
--with-bz2                                   \
--with-zlib                                  \
--enable-sockets                             \
--enable-sysvsem                             \
--enable-sysvshm                             \
--enable-pcntl                               \
--enable-mbregex                             \
--enable-exif                                \
--enable-bcmath                              \
--with-mhash                                 \
--enable-zip                                 \
--with-pcre-regex                            \
--with-pdo-mysql                             \
--with-mysqli                                \
--with-mysql-sock=/var/run/mysqld/mysqld.sock \
--with-jpeg-dir=/usr                         \
--with-png-dir=/usr                          \
--enable-gd-native-ttf                       \
--with-openssl                               \
--with-fpm-user=www-data                     \
--with-fpm-group=www-data                    \
--with-libdir=/usr/lib/arm-linux-gnueabihf          \
--enable-ftp                                 \
--with-imap                                  \
--with-imap-ssl                              \
--with-kerberos                              \
--with-gettext                               \
--with-xmlrpc                                \
--with-xsl                                   \
--enable-opcache                             \
--enable-fpm

```

Error #1

configure: error: Cannot find imap library (libc-client.a). Please check your c-client installation.
Solution: create a symbolic link and re-run the configure script.

$ sudo mkdir /usr/c-client/
$ sudo ln -s /usr/lib/libc-client.a /usr/c-client/

Possible Error,

Error #2

error: Kerberos libraries not found.

Check the path given to --with-kerberos (if no path is given, searches in /usr/kerberos, /usr/local and /usr )
Solution: create a symbolic link and re-run the configure script.

$ sudo mkdir /usr/kerberos

$ sudo ln -s /usr/lib/arm-linux-gnueabihf/mit-krb5/* /usr/kerberos


Make with quad core RPi,

$ make -j4

If this fails just try $ make

This could take a while

Test it out,

$ make test

Install PHP 7

$ sudo make install

Rename configuration files

sudo mv /opt/php-7.0.9/etc/php-fpm.conf.default /opt/php-7.0.9/etc/php-fpm.conf
sudo mv /opt/php-7.0.9/etc/php-fpm.d/www.conf.default

Copy the php.ini-production file to the php-fpm config folder

sudo cp /home/pi/php-7.0.9/php.ini-production /opt/php-7.0.9/etc/

Make sure php is correctly installed

/opt/php-7.0.9/bin/php -v

Temporarily add to path

export PATH=$PATH:/opt/php-7.0.9/bin
export PATH=$PATH:/opt/php-7.0.9/sbin

And test,

php -v

More permanently,

Check the Path,

$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/php-7.0.9/sbin

Create a backup

sudo cp /etc/profile /etc/profile-bak

Add `:/opt/php-7.0.9/bin:/opt/php-7.0.9/sbin` to the end of the PATH in line 7

$ diff /etc/profile /etc/profile-bak
7c7
<   PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games:/opt/php-7.0.9/bin:/opt/php-7.0.9/sbin"
---
>   PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/local/games:/usr/games"

Reboot,

sudo reboot

Test php,

$ php -v
PHP 7.0.9 (cli) (built: Aug  2 2016 15:31:23) ( NTS )
Copyright (c) 1997-2016 The PHP Group
Zend Engine v3.0.0, Copyright (c) 1998-2016 Zend Technologies

Install other packages (If not already)

sudo apt-get install -y apache2 mysql-server g++ git curl

Install composer

$ sudo su
# curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/bin --filename=composer
# exit

Test,

composer -v

Install Node

$ sudo su
# curl -sL https://deb.nodesource.com/setup_6.x | bash -
# apt-get install nodejs
# exit

Test,

nodejs -v

Setup Database,

mysql -u root -p

Enter Password

Create user:

CREATE USER 'koel'@'localhost' IDENTIFIED BY '****';
GRANT ALL PRIVILEGES ON koel.* TO 'koel'@'localhost' WITH GRANT OPTION;
exit;

Get the koel repo

git clone https://github.com/phanan/koel.git

cd koel
npm install
composer install

Edit .env file with `sed`

$ sed -i 's/ADMIN_EMAIL=/ADMIN_EMAIL=millerbott@gmail.com/g' .env
$ sed -i 's/ADMIN_NAME=/ADMIN_NAME=admin/g' .env
$ sed -i 's/ADMIN_PASSWORD=/ADMIN_PASSWORD=numlock/g' .env
$ sed -i 's/DB_CONNECTION=/DB_CONNECTION=mysql/g' .env
$ sed -i 's/DB_HOST=/DB_HOST=127.0.0.1/g' .env
$ sed -i 's/DB_DATABASE=homestead/DB_DATABASE=koel/g' .env
$ sed -i 's/DB_USERNAME=homestead/DB_USERNAME=koel/g' .env
$ sed -i 's/DB_PASSWORD=secret/DB_PASSWORD=****/g' .env

sudo nano .env

add database name, username, password. Above didn't work correctly.

php artisan koel:init

/home/pi/koel/artisan serve --host 0.0.0.0 --port 8888

mount usb or hard drive then add it as the media path

[REF](http://www.raspberrypi-spy.co.uk/2014/05/how-to-mount-a-usb-flash-disk-on-the-raspberry-pi/)

lsusb
ls -l /dev/disk/by-uuid/
sudo mkdir /media/usb
sudo chown -R pi:pi /media/usb
sudo cp /etc/fstab /etc/fstab.bak
ls /etc/fstab*
sudo nano /etc/fstab

Add `UUID=2ecc3831-ee9e-4336-9d41-c6cfab8a8af7 /media/usb ext4 rw,exec,auto,users 0 1`
Save and exit

$ sudo diff /etc/fstab /etc/fstab.bak
6,7d5
<
< UUID=2ecc3831-ee9e-4336-9d41-c6cfab8a8af7 /media/usb ext4 rw,exec,auto,users 0 1

sudo mount -a

sudo reboot

Find file types,

find . -type f | perl -ne 'print $1 if m/\.([^.\/]+)$/' | sort -u
[REF](http://stackoverflow.com/questions/1842254/how-can-i-find-all-of-the-distinct-file-extensions-in-a-folder-hierarchy)

php artisan -v koel:sync

Completed! 5045 new or updated song(s), 4568 unchanged song(s), and 649 invalid file(s).


crontab -e

@reboot php /home/pi/koel/artisan serve --host 0.0.0.0 --port 8888

or for php-7, 

@reboot /opt/php-7.0.9/bin/php /home/pi/koel/artisan serve --host 0.0.0.0 --port 8888

duckdns setup
