#!/bin/sh

mv batch1.group1.gbr batch1.GBL
mv batch1.bottomsilk.gbr batch1.GBO
mv batch1.bottommask.gbr batch1.GBS
mv batch1.outline.gbr batch1.GML
mv batch1.top.gbr batch1.GTL
mv batch1.topsilk.gbr batch1.GTO
mv batch1.topmask.gbr batch1.GTS
mv batch1.plated-drill.cnc batch1.TXT

rm batch1.*.gbr
zip batch1.zip -xi batch1.G* batch1.TXT 
rm batch1.G* batch1.TXT

mv batch2.group1.gbr batch2.GBL
mv batch2.bottomsilk.gbr batch2.GBO
mv batch2.bottommask.gbr batch2.GBS
mv batch2.outline.gbr batch2.GML
mv batch2.top.gbr batch2.GTL
mv batch2.topsilk.gbr batch2.GTO
mv batch2.topmask.gbr batch2.GTS
mv batch2.plated-drill.cnc batch2.TXT

rm batch2.*.gbr
zip batch2.zip -xi batch2.G* batch2.TXT 
rm batch2.G* batch2.TXT

mv batch3.group1.gbr batch3.GBL
mv batch3.bottomsilk.gbr batch3.GBO
mv batch3.bottommask.gbr batch3.GBS
mv batch3.outline.gbr batch3.GML
mv batch3.top.gbr batch3.GTL
mv batch3.topsilk.gbr batch3.GTO
mv batch3.topmask.gbr batch3.GTS
mv batch3.plated-drill.cnc batch3.TXT

rm batch3.*.gbr
zip batch3.zip -xi batch3.G* batch3.TXT 
rm batch3.G* batch3.TXT
