#!/bin/bash
BTMAC="24:0A:C4:9A:E8:EA"
DB=iot
DBPWD="3fedfwre@KD&"
# READ="$(gatttool -b $BTMAC --char-read --handle=0x002a 2>&1)"
# if [[ $READ =~ "refused" ]]; then
#      logger –t $0 "DEV $BTMAC nao encontrado."
# else
#     ANSW="$(echo $READ | cut -d : -f2| xxd -r -p)"
#     # echo ANSW= $ANSW
#     TEMP=$(echo $ANSW|cut -d "," -f1)
#     HUMD=$(echo $ANSW|cut -d "," -f2)
#     # echo TEMP= $TEMP
#     # echo HUMD= $HUMD
#     mysql $DB -u $DB -p$DBPWD -e "insert into tempLog values (now()- INTERVAL 3 HOUR,$TEMP,$HUMD)" 2>&1 | logger -t $0
# 
# fi
hexchars="0123456789ABCDEF"
uid=$( for i in {1..6} ; do echo -n ${hexchars:$(( $RANDOM % 16 )):1} ; done | sed -e "s/\(..\)/:\1/g" )
mysql -s -u $DB -p$DBPWD -e "insert into $DB.presenca (timestamp,uid) values (now() - INTERVAL 3 HOUR,\"00$uid\")" 
