#!/bin/sh

mv bugOne_mini.group1.gbr bugOne_mini.GBL
mv bugOne_mini.bottomsilk.gbr bugOne_mini.GBO
mv bugOne_mini.bottommask.gbr bugOne_mini.GBS
mv bugOne_mini.outline.gbr bugOne_mini.GML
mv bugOne_mini.top.gbr bugOne_mini.GTL
mv bugOne_mini.topsilk.gbr bugOne_mini.GTO
mv bugOne_mini.topmask.gbr bugOne_mini.GTS
mv bugOne_mini.plated-drill.cnc bugOne_mini.TXT

rm bugOne_mini.*.gbr 
zip bugOne_mini.zip -xi bugOne_mini.G* bugOne_mini.TXT 
