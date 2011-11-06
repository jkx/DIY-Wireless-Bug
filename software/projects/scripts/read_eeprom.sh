avrdude -c usbasp -p m168 -U eeprom:r:eeprom.dmp:i

LINE=$(head -n 1 eeprom.dmp)

NODEADDR=${LINE:9:2}
AESKEY=${LINE:12:16}

echo "Node address: $NODEADDR"
echo "AES128 key  : $AESKEY"
