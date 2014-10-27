#!/bin/sh

mv pilot_wire_shield.group1.gbr pilot_wire_shield.GBL
mv pilot_wire_shield.bottomsilk.gbr pilot_wire_shield.GBO
mv pilot_wire_shield.bottommask.gbr pilot_wire_shield.GBS
mv pilot_wire_shield.outline.gbr pilot_wire_shield.GML
mv pilot_wire_shield.top.gbr pilot_wire_shield.GTL
mv pilot_wire_shield.topsilk.gbr pilot_wire_shield.GTO
mv pilot_wire_shield.topmask.gbr pilot_wire_shield.GTS
mv pilot_wire_shield.plated-drill.cnc pilot_wire_shield.TXT

rm pilot_wire_shield.*.gbr
zip pilot_wire_shield.zip -xi pilot_wire_shield.G* pilot_wire_shield.TXT 

