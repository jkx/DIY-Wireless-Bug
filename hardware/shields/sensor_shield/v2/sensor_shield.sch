v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 43000 47400 1 0 0 connector10-1.sym
{
T 44900 50400 5 10 0 0 0 0 1
device=CONNECTOR_10
T 43100 50600 5 10 1 1 0 0 1
refdes=CONN1
T 42900 47400 5 10 1 1 0 0 1
footprint=JUMPER10
}
C 40500 47400 1 0 0 connector10-1.sym
{
T 42400 50400 5 10 0 0 0 0 1
device=CONNECTOR_10
T 40600 50600 5 10 1 1 0 0 1
refdes=CONN2
T 40500 47400 5 10 1 1 0 0 1
footprint=JUMPER10
}
C 44800 50600 1 0 0 vcc-1.sym
N 44700 50300 45000 50300 4
N 45000 50300 45000 50600 4
C 44800 47100 1 0 0 gnd-1.sym
C 42300 47100 1 0 0 gnd-1.sym
N 44700 47600 44900 47600 4
N 44900 47600 44900 47400 4
N 42200 47600 42400 47600 4
N 42400 47600 42400 47400 4
C 42300 50500 1 0 0 vee-1.sym
N 42200 50300 42500 50300 4
N 42500 50300 42500 50500 4
N 42200 50000 42500 50000 4
{
T 41600 50000 5 10 1 1 0 0 1
netname=CONN2_2
}
N 42200 49700 42500 49700 4
{
T 41600 49700 5 10 1 1 0 0 1
netname=DATA1
}
N 42200 49400 42500 49400 4
{
T 42100 49400 5 10 1 1 0 0 1
netname=SCL
}
N 42200 49100 42500 49100 4
{
T 42100 49100 5 10 1 1 0 0 1
netname=SDA
}
N 42200 48800 42500 48800 4
{
T 41600 48800 5 10 1 1 0 0 1
netname=BATSENSE
}
N 42200 48500 42500 48500 4
{
T 41600 48500 5 10 1 1 0 0 1
netname=CONN2_7
}
N 42200 48200 42500 48200 4
{
T 41600 48200 5 10 1 1 0 0 1
netname=CONN2_8
}
N 42200 47900 42500 47900 4
{
T 41600 47900 5 10 1 1 0 0 1
netname=CONN2_9
}
N 44700 50000 45000 50000 4
{
T 44100 50000 5 10 1 1 0 0 1
netname=FOUT
}
N 44700 49700 45000 49700 4
{
T 44100 49700 5 10 1 1 0 0 1
netname=CONN1_3
}
N 44700 49400 45000 49400 4
{
T 44100 49400 5 10 1 1 0 0 1
netname=CONN1_4
}
N 44700 48500 45000 48500 4
{
T 44100 48500 5 10 1 1 0 0 1
netname=CONN1_7
}
N 44700 48200 45000 48200 4
{
T 44100 48200 5 10 1 1 0 0 1
netname=CONN1_8
}
N 44700 47900 45000 47900 4
{
T 44100 47900 5 10 1 1 0 0 1
netname=CONN1_9
}
N 44700 48800 45300 48800 4
{
T 44100 48800 5 10 1 1 0 0 1
netname=CONN1_6
}
N 44700 49100 45500 49100 4
{
T 44100 49100 5 10 1 1 0 0 1
netname=OWBUS
}
C 40500 44700 1 0 0 connector4-1.sym
{
T 42300 45600 5 10 0 0 0 0 1
device=CONNECTOR_4
T 40500 46100 5 10 1 1 0 0 1
refdes=ALIM1
T 40500 44700 5 10 1 1 0 0 1
footprint=JUMPER4
}
C 43000 44700 1 0 0 connector4-1.sym
{
T 44800 45600 5 10 0 0 0 0 1
device=CONNECTOR_4
T 40500 44400 5 10 1 1 0 0 1
refdes=ALIM2
T 43000 44700 5 10 1 1 0 0 1
footprint=JUMPER4
}
N 42200 45800 42600 45800 4
N 42200 45500 42600 45500 4
N 42200 45200 42600 45200 4
N 42200 44900 42600 44900 4
N 44700 45800 45100 45800 4
N 44700 45500 45100 45500 4
N 44700 45200 45100 45200 4
N 44700 44900 45100 44900 4
C 44800 44400 1 0 0 gnd-1.sym
C 42300 44400 1 0 0 gnd-1.sym
N 42400 44900 42400 44700 4
N 44900 44700 44900 44900 4
N 44900 45800 44900 46300 4
N 44900 45500 44900 45600 4
N 44900 45600 45300 45600 4
N 45300 45600 45300 46300 4
C 45100 46300 1 0 0 vcc-1.sym
C 44700 46300 1 0 0 vss-1.sym
N 42400 45800 42400 46300 4
C 42200 46300 1 0 0 vcc-1.sym
N 56200 48600 56500 48600 4
C 56800 49800 1 0 0 gnd-1.sym
N 56200 50100 56900 50100 4
N 52700 50100 52100 50100 4
{
T 52100 50100 5 10 1 1 0 0 1
netname=SDA
}
N 52100 48600 52700 48600 4
{
T 52100 48700 5 10 1 1 0 0 1
netname=SCL
}
C 54100 48000 1 270 0 ds18b20.sym
{
T 55395 49300 5 10 0 1 270 0 1
device=DS18B20
T 55695 47100 5 10 1 1 270 0 1
refdes=U4
T 54095 50385 5 10 0 1 270 0 1
footprint=TO92
}
C 53400 47600 1 270 0 gnd-1.sym
N 53700 47500 54100 47500 4
N 54100 47000 52900 47000 4
{
T 52900 47100 5 10 1 1 0 0 1
netname=OWBUS
}
C 53000 45900 1 0 0 resistor-1.sym
{
T 53300 46300 5 10 0 0 0 0 1
device=RESISTOR
T 53200 46200 5 10 1 1 0 0 1
refdes=R1
T 53100 45700 5 10 1 1 0 0 1
footprint=1206
}
N 53000 47000 53000 46000 4
N 53900 46000 53900 46500 4
C 54000 45600 1 0 0 gnd-1.sym
N 54100 46500 54100 45900 4
C 47200 40800 1 0 0 resistor-1.sym
{
T 47500 41200 5 10 0 0 0 0 1
device=RESISTOR
T 47400 41100 5 10 1 1 0 0 1
refdes=R2
T 47200 40800 5 10 0 0 0 0 1
footprint=1206
T 47900 40700 5 10 1 1 0 0 1
value=4.7k
}
C 47200 40200 1 0 0 resistor-1.sym
{
T 47500 40600 5 10 0 0 0 0 1
device=RESISTOR
T 47400 40500 5 10 1 1 0 0 1
refdes=R3
T 47200 40200 5 10 0 0 0 0 1
footprint=1206
T 47900 40100 5 10 1 1 0 0 1
value=4.7k
}
N 46300 40900 47200 40900 4
{
T 46300 40900 5 10 1 1 0 0 1
netname=SDA
}
N 46300 40300 47200 40300 4
{
T 46300 40300 5 10 1 1 0 0 1
netname=SCL
}
N 48800 40900 48100 40900 4
N 48800 40300 48100 40300 4
C 42100 43000 1 90 0 resistor-1.sym
{
T 41700 43300 5 10 0 0 90 0 1
device=RESISTOR
T 41800 43200 5 10 1 1 90 0 1
refdes=R4
T 42100 43000 5 10 0 2 0 0 1
footprint=1206
T 42300 43000 5 10 1 1 90 0 1
value=200k
}
C 42100 41900 1 90 0 resistor-1.sym
{
T 41700 42200 5 10 0 0 90 0 1
device=RESISTOR
T 41800 42100 5 10 1 1 90 0 1
refdes=R5
T 42100 41900 5 10 0 0 0 0 1
footprint=1206
T 42300 42100 5 10 1 1 90 0 1
value=200k
}
N 42000 43000 42000 42800 4
N 42000 41600 42000 41900 4
C 41900 41300 1 0 0 gnd-1.sym
N 42000 42900 40500 42900 4
{
T 40200 43000 5 10 1 1 0 0 1
netname=BATSENSE
}
C 42900 44100 1 0 0 vss-1.sym
C 56500 48800 1 270 0 vee-1.sym
C 48600 41300 1 0 0 vee-1.sym
C 53900 46300 1 90 0 vee-1.sym
C 45200 43000 1 0 1 connector3-1.sym
{
T 43400 43900 5 10 0 0 0 6 1
device=CONNECTOR_3
T 45200 44100 5 10 1 1 0 6 1
refdes=JMP1
T 45200 43000 5 10 1 1 0 0 1
footprint=JUMPER3
}
N 48800 41300 48800 40300 4
N 43100 44100 43100 43800 4
N 43100 43800 43500 43800 4
N 43500 43500 42400 43500 4
N 42400 43500 42400 43900 4
N 42400 43900 42000 43900 4
C 43100 43000 1 90 0 vcc-1.sym
N 43100 43200 43500 43200 4
C 52700 48100 1 0 0 sht31d.sym
{
T 53200 50400 5 10 1 1 0 0 1
device=SHT31D
T 54200 48200 5 10 1 1 0 0 1
refdes=U1
T 52700 48100 5 10 0 0 0 0 1
footprint=DFN8
}
N 56200 50100 56200 49600 4
N 52700 49600 51600 49600 4
N 51600 49600 51600 49400 4
C 51500 49100 1 0 0 gnd-1.sym
N 56200 48600 56200 49100 4
N 51000 48600 50600 48600 4
N 51000 47800 51000 49600 4
C 50900 47500 1 0 0 gnd-1.sym
N 51000 49600 50600 49600 4
N 47100 50100 46400 50100 4
N 46400 50100 46400 48000 4
C 46300 47700 1 0 0 gnd-1.sym
N 47100 49100 46600 49100 4
{
T 46600 49200 5 10 1 1 0 0 1
netname=SDA
}
N 47100 48600 46600 48600 4
{
T 46600 48700 5 10 1 1 0 0 1
netname=SCL
}
N 50600 50100 51000 50100 4
N 51000 50100 51000 50700 4
C 50800 50700 1 0 0 vee-1.sym
C 47100 49400 1 90 0 vee-1.sym
C 44400 41600 1 270 0 capacitor-1.sym
{
T 45100 41400 5 10 0 0 270 0 1
device=CAPACITOR
T 44900 41400 5 10 1 1 270 0 1
refdes=C1
T 45300 41400 5 10 0 0 270 0 1
symversion=0.1
T 44700 40800 5 10 1 1 0 0 1
footprint=1206
T 44000 40900 5 10 1 1 0 0 1
value=100nF
}
C 44500 40200 1 0 0 gnd-1.sym
C 44400 42000 1 0 0 vee-1.sym
N 44600 42000 44600 41600 4
N 44600 40500 44600 40700 4
C 54300 41800 1 0 0 connector10-1.sym
{
T 56200 44800 5 10 0 0 0 0 1
device=CONNECTOR_10
T 54400 45000 5 10 1 1 0 0 1
refdes=CONN1B
T 54200 41800 5 10 1 1 0 0 1
footprint=JUMPER10
}
C 51800 41800 1 0 0 connector10-1.sym
{
T 53700 44800 5 10 0 0 0 0 1
device=CONNECTOR_10
T 51900 45000 5 10 1 1 0 0 1
refdes=CONN2B
T 51800 41800 5 10 1 1 0 0 1
footprint=JUMPER10
}
C 56100 45000 1 0 0 vcc-1.sym
N 56000 44700 56300 44700 4
N 56300 44700 56300 45000 4
C 56100 41500 1 0 0 gnd-1.sym
C 53600 41500 1 0 0 gnd-1.sym
N 56000 42000 56200 42000 4
N 56200 42000 56200 41800 4
N 53500 42000 53700 42000 4
N 53700 42000 53700 41800 4
C 53600 44900 1 0 0 vee-1.sym
N 53500 44700 53800 44700 4
N 53800 44700 53800 44900 4
N 53500 44400 53800 44400 4
{
T 52900 44400 5 10 1 1 0 0 1
netname=CONN2_2
}
N 53500 44100 53800 44100 4
{
T 52900 44100 5 10 1 1 0 0 1
netname=DATA1
}
N 53500 43800 53800 43800 4
{
T 53400 43800 5 10 1 1 0 0 1
netname=SCL
}
N 53500 43500 53800 43500 4
{
T 53400 43500 5 10 1 1 0 0 1
netname=SDA
}
N 53500 43200 53800 43200 4
{
T 52900 43200 5 10 1 1 0 0 1
netname=BATSENSE
}
N 53500 42900 53800 42900 4
{
T 52900 42900 5 10 1 1 0 0 1
netname=CONN2_7
}
N 53500 42600 53800 42600 4
{
T 52900 42600 5 10 1 1 0 0 1
netname=CONN2_8
}
N 53500 42300 53800 42300 4
{
T 52900 42300 5 10 1 1 0 0 1
netname=CONN2_9
}
N 56000 44400 56300 44400 4
{
T 55400 44400 5 10 1 1 0 0 1
netname=FOUT
}
N 56000 44100 56300 44100 4
{
T 55400 44100 5 10 1 1 0 0 1
netname=CONN1_3
}
N 56000 43800 56300 43800 4
{
T 55400 43800 5 10 1 1 0 0 1
netname=CONN1_4
}
N 56000 42900 56300 42900 4
{
T 55400 42900 5 10 1 1 0 0 1
netname=CONN1_7
}
N 56000 42600 56300 42600 4
{
T 55400 42600 5 10 1 1 0 0 1
netname=CONN1_8
}
N 56000 42300 56300 42300 4
{
T 55400 42300 5 10 1 1 0 0 1
netname=CONN1_9
}
N 56000 43200 56600 43200 4
{
T 55400 43200 5 10 1 1 0 0 1
netname=CONN1_6
}
N 56000 43500 56800 43500 4
{
T 55400 43500 5 10 1 1 0 0 1
netname=OWBUS
}
C 46900 45000 1 0 0 BH1750.sym
{
T 48000 46800 5 10 1 1 0 0 1
device=BH1750
T 51600 47200 5 10 0 1 0 0 1
footprint=WSOF6I
T 49100 45100 5 10 1 1 0 0 1
refdes=U3
}
N 51400 46500 52500 46500 4
{
T 52100 46600 5 10 1 1 0 0 1
netname=SCL
}
N 51400 45500 52500 45500 4
{
T 52100 45600 5 10 1 1 0 0 1
netname=SDA
}
N 46900 46500 46500 46500 4
N 46500 46500 46500 47100 4
C 46300 47100 1 0 0 vee-1.sym
N 46900 45500 46500 45500 4
C 45900 44200 1 0 0 gnd-1.sym
N 46000 46000 46900 46000 4
N 51400 46000 52500 46000 4
{
T 52100 46100 5 10 1 1 0 0 1
netname=DVI
}
N 48000 43500 49000 43500 4
{
T 48000 43600 5 10 1 1 0 0 1
netname=DVI
}
C 48800 43500 1 270 0 capacitor-1.sym
{
T 49500 43300 5 10 0 0 270 0 1
device=CAPACITOR
T 49700 43300 5 10 0 0 270 0 1
symversion=0.1
T 49300 43300 5 10 1 1 270 0 1
refdes=C1
T 49100 42700 5 10 1 1 0 0 1
footprint=1206
T 48400 42800 5 10 1 1 0 0 1
value=100nF
}
C 48900 42100 1 0 0 gnd-1.sym
N 49000 42400 49000 42600 4
C 49100 43500 1 90 0 resistor-1.sym
{
T 48700 43800 5 10 0 0 90 0 1
device=RESISTOR
T 49100 43500 5 10 0 2 0 0 1
footprint=1206
T 48800 43700 5 10 1 1 90 0 1
refdes=R6
T 49300 43700 5 10 1 1 90 0 1
value=1k
}
C 48800 44400 1 0 0 vee-1.sym
N 46500 45500 46500 44700 4
N 46500 44700 46000 44700 4
N 46000 44500 46000 44800 4
C 46100 44800 1 90 0 resistor-1.sym
{
T 45700 45100 5 10 0 0 90 0 1
device=RESISTOR
T 46100 44800 5 10 0 2 0 0 1
footprint=1206
T 45800 45000 5 10 1 1 90 0 1
refdes=R6
T 46300 45000 5 10 1 1 90 0 1
value=100k
}
N 46000 46000 46000 45700 4
C 47100 48100 1 0 0 bme280.sym
{
T 47600 50400 5 10 0 1 0 0 1
device=BME280
T 48600 48200 5 10 1 1 0 0 1
refdes=U2
T 47100 48100 5 10 0 0 0 0 1
footprint=LGA8
}
C 50600 49200 1 0 0 vee-1.sym
N 50600 49100 50800 49100 4
N 50800 49100 50800 49200 4
