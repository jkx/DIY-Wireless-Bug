v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 75800 45700 1 0 0 megaX8-tqfp32.sym
{
T 80300 52200 5 10 1 1 0 6 1
refdes=U1
T 76100 52500 5 10 0 0 0 0 1
device=ATMega48-TQFP32
T 76100 52700 5 10 0 0 0 0 1
footprint=TQFP32_7
}
C 68500 49400 1 0 0 avr-isp-6.sym
{
T 69900 58800 5 10 0 0 0 0 1
device=AVR ISP 6
T 69900 59000 5 10 0 0 0 0 1
footprint=HEADER6_2
T 70500 52000 5 10 1 1 0 0 1
refdes=ISP
T 69900 59400 5 10 0 0 0 0 1
symversion=1.0
}
C 67900 45300 1 0 0 rfm12S.sym
{
T 69300 54700 5 10 0 0 0 0 1
device=RFM12
T 69300 54900 5 10 0 0 0 0 1
footprint=rfm12b
T 70700 48800 5 10 1 1 0 0 1
refdes=U2
T 69300 55300 5 10 0 0 0 0 1
symversion=1.0
}
C 82600 43400 1 270 0 vcc-1.sym
C 81300 43100 1 0 0 resistor-1.sym
{
T 81600 43500 5 10 0 0 0 0 1
device=RESISTOR
T 81500 43400 5 10 1 1 0 0 1
refdes=R1
T 81300 43100 5 10 0 1 0 0 1
value=10k
T 81300 43100 5 10 0 0 0 0 1
footprint=0805
}
N 82200 43200 82600 43200 4
C 68600 50800 1 90 0 vcc-1.sym
N 67600 51300 69000 51300 4
N 68600 52300 73200 52300 4
N 73200 52300 73200 50400 4
N 73200 50400 75800 50400 4
C 77900 45200 1 0 0 gnd-1.sym
N 78000 45500 78000 45700 4
N 78000 45600 78400 45600 4
N 78400 45600 78400 45700 4
C 71800 51200 1 90 0 gnd-1.sym
N 71100 51300 71500 51300 4
N 71100 50700 75800 50700 4
N 68600 51300 68600 52300 4
N 69000 50700 68700 50700 4
N 68700 50700 68700 50100 4
N 68700 50100 75800 50100 4
N 71200 47300 72600 47300 4
N 72600 47300 72600 50700 4
N 71200 47600 72300 47600 4
N 72300 47600 72300 50100 4
N 68600 51000 69000 51000 4
N 67600 51300 67600 47900 4
N 67600 47900 68000 47900 4
N 71100 51000 72900 51000 4
N 72900 43200 72900 51000 4
N 80900 43200 80900 46500 4
C 67800 45700 1 0 0 gnd-1.sym
N 67900 46000 67900 46100 4
N 67900 46100 68000 46100 4
C 72500 46500 1 270 0 vcc-1.sym
C 71700 46600 1 90 0 gnd-1.sym
N 71200 46700 71400 46700 4
C 81200 50600 1 90 0 gnd-1.sym
N 80600 50700 80900 50700 4
C 77800 52600 1 0 0 vcc-1.sym
N 78000 52600 78000 52400 4
N 78000 52500 78400 52500 4
N 78400 52500 78400 52400 4
C 69300 43400 1 0 0 connector4-1.sym
{
T 71100 44300 5 10 0 0 0 0 1
device=CONNECTOR_4
T 69300 44800 5 10 1 1 0 0 1
refdes=ALIM1
T 69300 43400 5 10 1 1 0 0 1
footprint=JUMPER4
}
C 71400 44700 1 270 0 vcc-1.sym
N 71000 44500 71400 44500 4
C 71700 43500 1 90 0 gnd-1.sym
N 71000 43600 71400 43600 4
N 73200 43900 73200 48600 4
N 73200 48600 75800 48600 4
N 73500 44200 73500 48300 4
N 73500 48300 75800 48300 4
C 85200 50300 1 270 0 led-1.sym
{
T 85800 49500 5 10 0 0 270 0 1
device=LED
T 85100 49600 5 10 1 1 90 0 1
refdes=LED2
T 86000 49500 5 10 0 0 270 0 1
symversion=0.1
T 85200 50300 5 10 1 1 0 0 1
footprint=0805
}
C 83800 50500 1 0 0 resistor-1.sym
{
T 84100 50900 5 10 0 0 0 0 1
device=RESISTOR
T 84500 50300 5 10 1 1 0 0 1
refdes=R2
T 83800 50500 5 10 1 1 0 0 1
footprint=0805
T 83800 50500 5 10 0 0 0 0 1
value=1k
}
C 85800 49000 1 0 0 gnd-1.sym
N 80600 46500 80900 46500 4
N 75800 48000 73800 48000 4
N 73800 48000 73800 49000 4
N 73800 49000 67300 49000 4
N 67300 47600 67300 49000 4
N 67300 47600 68000 47600 4
N 71200 47900 72100 47900 4
N 80600 46800 81800 46800 4
C 80900 51200 1 270 0 vcc-1.sym
N 80600 51000 80900 51000 4
C 82400 51200 1 90 0 gnd-1.sym
C 81100 51100 1 0 0 capacitor-1.sym
{
T 81400 51600 5 10 1 1 0 0 1
refdes=C4
T 81100 51100 5 10 1 1 0 0 1
footprint=0805
}
N 80600 51300 81100 51300 4
N 82000 51300 82100 51300 4
C 83000 50200 1 0 0 resistor-1.sym
{
T 83300 50600 5 10 0 0 0 0 1
device=RESISTOR
T 83700 50400 5 10 1 1 0 0 1
refdes=R3
T 83000 50200 5 10 1 1 0 0 1
footprint=0805
T 83000 50200 5 10 0 0 0 0 1
value=1k
}
C 86100 50300 1 270 0 led-1.sym
{
T 86700 49500 5 10 0 0 270 0 1
device=LED
T 86000 49600 5 10 1 1 90 0 1
refdes=LED1
T 86900 49500 5 10 0 0 270 0 1
symversion=0.1
T 86100 50300 5 10 1 1 0 0 1
footprint=0805
}
N 86300 50600 86300 50300 4
N 85400 49400 85400 49300 4
N 85400 49300 86300 49300 4
N 86300 49300 86300 49400 4
N 74900 51600 75800 51600 4
N 74600 51300 75800 51300 4
N 74300 51000 75800 51000 4
C 76100 53000 1 0 0 vcc-1.sym
N 75800 53000 75800 52800 4
N 75800 52800 76300 52800 4
N 76300 52800 76300 53000 4
C 73000 52500 1 0 0 gnd-1.sym
N 73100 52800 73100 53000 4
N 80600 48300 80800 48300 4
N 80800 48300 80800 49400 4
N 80600 48000 81000 48000 4
N 80600 47700 81200 47700 4
N 81200 47700 81200 48800 4
N 81200 48800 83100 48800 4
C 82300 49800 1 270 0 gnd-1.sym
N 82600 49700 83100 49700 4
N 82000 54300 83200 54300 4
C 83700 55100 1 0 0 resistor-1.sym
{
T 84000 55500 5 10 0 0 0 0 1
device=RESISTOR
T 83900 55400 5 10 1 1 0 0 1
refdes=R0
T 84300 55400 5 10 1 1 0 0 1
footprint=0805
}
C 85900 53500 1 90 0 capacitor-1.sym
{
T 85600 53600 5 10 1 1 90 0 1
refdes=C1
T 85900 53500 5 10 1 1 0 0 1
footprint=1206
}
C 82500 53300 1 90 0 capacitor-1.sym
{
T 82200 53400 5 10 1 1 90 0 1
refdes=C2
T 82500 53300 5 10 1 1 0 0 1
footprint=1206
}
N 85700 53200 85700 53500 4
C 85600 52900 1 0 0 gnd-1.sym
C 82200 52900 1 0 0 gnd-1.sym
N 82300 54200 82300 54300 4
N 82300 53200 82300 53300 4
C 86800 45400 1 180 0 connector4-1.sym
{
T 85000 44500 5 10 0 0 180 0 1
device=CONNECTOR_4
T 86800 44000 5 10 1 1 180 0 1
refdes=ALIM2
T 86800 45400 5 10 1 1 0 0 1
footprint=JUMPER4
}
C 84500 45300 1 270 0 gnd-1.sym
C 84800 44100 1 90 0 vss-1.sym
N 84800 44300 85100 44300 4
N 84800 45200 85100 45200 4
C 85000 44400 1 90 0 vcc-1.sym
N 85000 44600 85100 44600 4
N 80900 43700 83800 43700 4
N 73200 43900 71000 43900 4
N 73500 44200 71000 44200 4
N 82000 49100 82000 50600 4
N 82200 49400 82200 50300 4
N 82000 50600 83800 50600 4
N 84700 50600 86300 50600 4
N 82200 50300 83000 50300 4
N 83900 50300 85400 50300 4
N 80800 49400 83100 49400 4
N 81000 48000 81000 49100 4
N 81000 49100 83100 49100 4
N 80600 47400 81400 47400 4
N 81400 47400 81400 48500 4
N 81400 48500 83100 48500 4
N 80600 47100 81600 47100 4
N 81600 47100 81600 48200 4
N 81600 48200 83100 48200 4
N 81800 46800 81800 47900 4
N 81800 47900 83100 47900 4
N 72100 47900 72100 46500 4
N 72100 46500 75800 46500 4
C 84800 49900 1 180 0 connector10-1.sym
{
T 82900 46900 5 10 0 0 180 0 1
device=CONNECTOR_10
T 84700 46700 5 10 1 1 180 0 1
refdes=CONN2
T 84800 49900 5 10 1 1 0 0 1
footprint=JUMPER10
}
C 72900 54700 1 270 0 connector10-1.sym
{
T 75900 52800 5 10 0 0 270 0 1
device=CONNECTOR_10
T 76100 54600 5 10 1 1 270 0 1
refdes=CONN1
T 72900 54700 5 10 1 1 0 0 1
footprint=JUMPER10
}
N 73400 50100 73400 53000 4
N 73700 53000 73700 50400 4
N 74000 53000 74000 50700 4
N 74300 51000 74300 53000 4
N 74600 51300 74600 53000 4
N 74900 51600 74900 53000 4
N 75800 46800 75200 46800 4
N 75200 46800 75200 53000 4
N 75800 47100 75500 47100 4
N 75500 47100 75500 53000 4
N 83800 43700 83800 44900 4
N 83800 44900 85100 44900 4
N 72900 43200 81300 43200 4
N 75800 47700 74500 47700 4
N 74500 47700 74500 45100 4
N 74500 45100 82000 45100 4
N 82000 45100 82000 47600 4
N 82000 47600 83100 47600 4
N 75800 47400 74800 47400 4
N 74800 47400 74800 44800 4
N 74800 44800 82200 44800 4
N 82200 44800 82200 47300 4
N 82200 47300 83100 47300 4
N 82000 54300 82000 54500 4
C 81800 54500 1 0 0 vcc-1.sym
C 85200 53700 1 0 1 MCP170xT-1.sym
{
T 83700 54750 5 10 1 1 0 6 1
refdes=U3
T 84900 54750 5 10 1 1 0 6 1
device=MCP170xT
T 84900 55000 5 10 0 0 0 6 1
footprint=SOT89
}
N 85200 54300 85500 54300 4
N 85500 54300 85500 54500 4
N 84200 53700 84200 53300 4
C 84100 53000 1 0 0 gnd-1.sym
C 88300 54500 1 0 0 vss-1.sym
C 72400 45800 1 90 0 mosfet-with-diode-1.sym
{
T 71900 46700 5 10 0 0 90 0 1
device=NPN_TRANSISTOR
T 71900 46700 5 10 1 1 90 0 1
refdes=Q1
T 72400 45800 5 10 1 1 0 0 1
footprint=SOT23_PMOS
}
N 72500 46400 72500 46300 4
N 71900 44600 71900 45800 4
N 71400 46400 71200 46400 4
{
T 71400 46400 5 10 1 1 0 0 1
netname=VRFM
}
N 72400 46400 72500 46400 4
C 71900 45300 1 0 0 diode-1.sym
{
T 72300 45900 5 10 0 0 0 0 1
device=DIODE
T 72200 45800 5 10 1 1 0 0 1
refdes=D1
T 71900 45300 5 10 0 0 0 0 1
footprint=SOD323
}
N 71900 45500 72000 45500 4
N 72800 45500 72900 45500 4
N 82300 54300 82300 55200 4
N 82300 55200 83700 55200 4
N 84600 55200 85700 55200 4
N 85500 54500 88500 54500 4
N 85700 55200 85700 54500 4
N 85700 54400 85700 54500 4
N 71900 44600 74100 44600 4
N 74100 44600 74100 49500 4
N 74100 49500 75800 49500 4
C 71500 45000 1 90 0 resistor-1.sym
{
T 71100 45300 5 10 0 0 90 0 1
device=RESISTOR
T 71200 45200 5 10 1 1 90 0 1
refdes=R4
T 71200 45600 5 10 1 1 90 0 1
footprint=0805
}
C 70800 44800 1 90 0 vcc-1.sym
N 70800 45000 71400 45000 4
N 71400 45900 71400 46400 4
C 82500 45500 1 0 0 connector3-1.sym
{
T 84300 46400 5 10 0 0 0 0 1
device=CONNECTOR_3
T 82500 46600 5 10 1 1 0 0 1
refdes=JMP1
T 82500 45500 5 10 1 1 0 0 1
footprint=JUMPER3
}
N 84200 46300 84800 46300 4
{
T 84200 46300 5 10 1 1 0 0 1
netname=VRFM
}
N 84200 46000 85000 46000 4
N 85000 46000 85000 46800 4
N 85000 46800 82700 46800 4
N 82700 46800 82700 47000 4
N 82700 47000 83100 47000 4
N 84200 45700 85500 45700 4
C 85300 45900 1 0 0 vcc-1.sym
N 85500 45700 85500 45900 4
