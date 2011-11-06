LINE=$(head -n 1 eeprom.dmp)

NODEADDR=${LINE:9:2}
AESKEY=${LINE:12:16}

echo "Node address: $NODEADDR"
echo "AES128 key  : $AESKEY"

echo "Press return to write to bugone"
read

avrdude -c usbasp -p m168 -U eeprom:w:eeprom.dmp
