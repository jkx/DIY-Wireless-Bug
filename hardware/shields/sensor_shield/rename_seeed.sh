#!/bin/sh

mv sensor_shield.group1.gbr sensor_shield.GBL
mv sensor_shield.bottomsilk.gbr sensor_shield.GBO
mv sensor_shield.bottommask.gbr sensor_shield.GBS
mv sensor_shield.outline.gbr sensor_shield.GML
mv sensor_shield.top.gbr sensor_shield.GTL
mv sensor_shield.topsilk.gbr sensor_shield.GTO
mv sensor_shield.topmask.gbr sensor_shield.GTS
mv sensor_shield.plated-drill.cnc sensor_shield.TXT

rm sensor_shield.*.gbr
zip sensor_shield.zip -xi sensor_shield.G* sensor_shield.TXT 

