#!/bin/sh

cat << '_EOF_' > /etc/ppp/ip-up
#!/bin/sh

/sbin/route add -net 192.168.10.1/24 -iface "${1}"
/sbin/route add -net 192.168.22.1/24 -iface "${1}"
_EOF_
chown root: /etc/ppp/ip-up
chmod 755 /etc/ppp/ip-up

