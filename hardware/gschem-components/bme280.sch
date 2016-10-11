v 20130925 2
B 500 0 2500 2500 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
{
T 500 5000 5 10 0 1 0 0 1
footprint=DFN8
T 500 5000 5 10 0 1 0 0 1
numslots=1
}
P 0 2000 500 2000 1 0 0
{
T -500 2000 5 10 0 0 0 0 1
pintype=pwr
T 555 1995 5 10 1 1 0 0 1
pinlabel=GND
T 405 2045 5 10 1 1 0 6 1
pinnumber=1
T -500 2000 5 10 0 0 0 0 1
pinseq=1
}
P 0 1500 500 1500 1 0 0
{
T -500 1500 5 10 0 0 0 0 1
pintype=in
T 555 1495 5 10 1 1 0 0 1
pinlabel=CSB
T 405 1545 5 10 1 1 0 6 1
pinnumber=2
T -500 1500 5 10 0 0 0 0 1
pinseq=2
}
P 0 1000 500 1000 1 0 0
{
T -500 1000 5 10 0 0 0 0 1
pintype=io
T 555 995 5 10 1 1 0 0 1
pinlabel=SDI
T 405 1045 5 10 1 1 0 6 1
pinnumber=3
T -500 1000 5 10 0 0 0 0 1
pinseq=3
}
P 0 500 500 500 1 0 0
{
T -500 500 5 10 0 0 0 0 1
pintype=in
T 555 495 5 10 1 1 0 0 1
pinlabel=SCK
T 405 545 5 10 1 1 0 6 1
pinnumber=4
T -500 500 5 10 0 0 0 0 1
pinseq=4
}
P 3500 2000 3000 2000 1 0 0
{
T 4000 2000 5 10 0 0 0 0 1
pintype=pwr
T 2945 1995 5 10 1 1 0 6 1
pinlabel=VDD
T 3095 2045 5 10 1 1 0 0 1
pinnumber=8
T 4000 2000 5 10 0 0 0 0 1
pinseq=8
}
P 3500 1500 3000 1500 1 0 0
{
T 4000 1500 5 10 0 0 0 0 1
pintype=pwr
T 2945 1495 5 10 1 1 0 6 1
pinlabel=GND
T 3095 1545 5 10 1 1 0 0 1
pinnumber=7
T 4000 1500 5 10 0 0 0 0 1
pinseq=7
}
P 3500 1000 3000 1000 1 0 0
{
T 4000 1000 5 10 0 0 0 0 1
pintype=pwr
T 2945 995 5 10 1 1 0 6 1
pinlabel=VDDIO
T 3095 1045 5 10 1 1 0 0 1
pinnumber=6
T 4000 1000 5 10 0 0 0 0 1
pinseq=6
}
P 3500 500 3000 500 1 0 0
{
T 4000 500 5 10 0 0 0 0 1
pintype=io
T 2945 495 5 10 1 1 0 6 1
pinlabel=SDO
T 3095 545 5 10 1 1 0 0 1
pinnumber=5
T 4000 500 5 10 0 0 0 0 1
pinseq=5
}
T 500 2300 8 10 0 1 0 0 1
device=BME280
T 1500 100 8 10 1 1 0 0 1
refdes=U?
T 3100 200 8 10 0 1 0 0 1
numslots=1
T 600 2600 9 10 1 0 0 0 1
BME280 Hum/Temp/Pressure
