v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 46600 48500 1 0 0 MCP1640-1.sym
{
T 48895 50600 5 10 0 1 0 0 1
device=MCP1640
T 48895 50600 5 10 1 1 0 0 1
refdes=U1
T 46600 48500 5 10 0 0 0 0 1
footprint=SOT23-6
}
N 46600 49500 44700 49500 4
N 44700 49500 44700 49200 4
N 50100 50000 50700 50000 4
N 50100 49500 51500 49500 4
N 51500 49500 51500 50000 4
C 44600 48900 1 0 0 gnd-1.sym
C 51300 50000 1 0 0 vcc-1.sym
C 45300 49900 1 0 0 inductor-1.sym
{
T 45500 50400 5 10 0 0 0 0 1
device=INDUCTOR
T 45500 50200 5 10 1 1 0 0 1
refdes=L1
T 45500 50600 5 10 0 0 0 0 1
symversion=0.1
T 45300 49900 5 10 0 0 0 0 1
footprint=B82462G4472M
}
C 51700 48200 1 180 0 resistor-1.sym
{
T 51400 47800 5 10 0 0 180 0 1
device=RESISTOR
T 51500 47900 5 10 1 1 180 0 1
refdes=R1
T 51700 48200 5 10 0 0 0 0 1
footprint=0805
}
C 50300 48200 1 180 0 resistor-1.sym
{
T 50000 47800 5 10 0 0 180 0 1
device=RESISTOR
T 50100 47900 5 10 1 1 180 0 1
refdes=R2
T 50300 48200 5 10 0 0 0 0 1
footprint=0805
}
N 50300 48100 50800 48100 4
N 50100 49000 50600 49000 4
N 50600 49000 50600 48100 4
N 49400 48100 49200 48100 4
N 49200 48100 49200 47600 4
N 51700 48100 52600 48100 4
N 52600 48100 52600 48700 4
C 49100 47300 1 0 0 gnd-1.sym
C 52400 48700 1 0 0 vcc-1.sym
N 43700 50500 43700 50000 4
N 43700 50000 45300 50000 4
N 46200 50000 46600 50000 4
C 43500 50500 1 0 0 vss-1.sym
C 51500 49300 1 0 0 capacitor-1.sym
{
T 51700 50000 5 10 0 0 0 0 1
device=CAPACITOR
T 51700 49800 5 10 1 1 0 0 1
refdes=C2
T 51700 50200 5 10 0 0 0 0 1
symversion=0.1
T 51500 49300 5 10 0 0 0 0 1
footprint=1206
}
N 52400 49500 54300 49500 4
N 54300 49500 54300 49000 4
C 54200 48700 1 0 0 gnd-1.sym
N 45300 49000 46600 49000 4
C 43900 49100 1 90 0 capacitor-1.sym
{
T 43200 49300 5 10 0 0 90 0 1
device=CAPACITOR
T 43400 49300 5 10 1 1 90 0 1
refdes=C1
T 43000 49300 5 10 0 0 90 0 1
symversion=0.1
T 43900 49100 5 10 0 0 0 0 1
footprint=1206
}
C 43600 48700 1 0 0 gnd-1.sym
N 43700 49000 43700 49100 4
C 41300 47500 1 0 0 connector2-1.sym
{
T 41500 48500 5 10 0 0 0 0 1
device=CONNECTOR_2
T 41300 48300 5 10 1 1 0 0 1
refdes=BAT1
T 41300 47500 5 10 0 0 0 0 1
footprint=JUMPER2
}
C 43200 48300 1 0 0 vss-1.sym
N 43000 48000 43400 48000 4
N 43400 48000 43400 48300 4
C 43300 47000 1 0 0 gnd-1.sym
N 43000 47700 43400 47700 4
N 43400 47700 43400 47300 4
C 46400 45200 1 0 0 gnd-1.sym
C 45500 46600 1 0 0 vcc-1.sym
N 45700 45900 45700 46600 4
N 45300 49000 45300 48200 4
N 45300 48200 44200 48200 4
N 44200 48200 44200 50000 4
N 50400 50000 50400 51300 4
N 50400 51300 44500 51300 4
N 44500 51300 44500 50000 4
N 45700 45900 45400 45900 4
N 45400 45600 46500 45600 4
N 46500 45600 46500 45500 4
N 45000 44000 46700 44000 4
N 46700 44000 46700 44500 4
C 46500 44500 1 0 0 vss-1.sym
C 43700 45400 1 0 0 connector2-1.sym
{
T 43900 46400 5 10 0 0 0 0 1
device=CONNECTOR_2
T 43700 46200 5 10 1 1 0 0 1
refdes=VOUT
T 43700 45400 5 10 0 0 0 0 1
footprint=JUMPER2
}
C 45000 44400 1 180 0 connector1-2.sym
{
T 44300 43500 5 10 1 1 180 6 1
refdes=VREF
T 44700 43550 5 10 0 0 180 0 1
device=CONNECTOR_1
T 44700 43350 5 10 0 0 180 0 1
footprint=JUMPER1
}
