## Board description

This shield is designed to provide different possibilities to create a sensor
shield, for relative humidity, temperature, pressure and lux. All choices do not need to be
soldered. 

## BOM 

The following components can be soldered on the board:
   - TAOS TSL2561 (U1)
   - TE HTU2XD(F) (U2)
   - Maxim DS18B20 (U3): popular 1-Wire temperature sensor Maxim. 
		http://datasheets.maximintegrated.com/en/ds/DS18B20

Other possibilites were:
	- Sensirion SHT31D : cheap (~5$ at Farnell) QFP sensor, using I2C for communication
	https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/Humidity_Sensors/Sensirion_Humidity_Sensors_SHT3x_Datasheet_digital.pdf
	- Bosch BME280 : temperature, humidity and pressure. The package seems more protected than the Sensirion (and we had troubles with the Sensirion which seems to age fast). 
	https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280_DS001-11.pdf
	- Rohm BH1750 : Light sensor (Luxmeter)
	http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1750fvi-e.pdf


C1 and C2 stabilizes the power line for their components. Expected value is 100nF. They need to be placed near their components
R1 and R2 are the pull-up resistors for I2C bus. Values can range from 1.8 to 10k. I prefer using 1.8k (strong pull-up), but the higher the resistance, the lower the current consumption. 
R3 is the pull-up for the interrupt line of the TSL2561. Value is 100k (datasheet)
R4 is the pull-up resistor for 1-Wire bus. Expected value is 4.7kOhm.
R5 and R6 are a voltage divider for battery sensing. It divides voltage by 2, allowing a battery up to 6.6V. 
R7 and R8 are only there to provide solder pads. Only one can be soldered at a time. They allow selection of the power line for which the voltage must be measured (Vss or Vcc)

U1, U2 and U3 uses I2C.

Shield pinout : 

CONN1_2 : FOUT, PD5
CONN1-5 : 1-Wire bus, PB1
CONN2_4 : SCL, PC5
CONN2_5 : SDA, PC4
CONN2_6 : battery sense, PC3
