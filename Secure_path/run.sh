[run]
echo $PATH
sudo visudo
# This is preferred for security and reliability.
sudo /usr/sbin/service ssh restart
# Sudo searches secure_path for 'service'
sudo service ssh restart
