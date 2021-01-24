EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Kiwi Easy Board"
Date "2020-12-19"
Rev "0.1"
Comp "Frank van Dam"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	9550 5350 10100 5350
Text Label 10100 5350 2    50   ~ 0
+5V
Wire Wire Line
	9550 5250 10100 5250
Text Label 10100 5250 2    50   ~ 0
GND
Text Label 10100 5150 2    50   ~ 0
LED-DIN
Text Label 10100 4950 2    50   ~ 0
I2C-SDA
Text Label 10100 4850 2    50   ~ 0
I2C-SCL
Text Label 3700 1650 0    50   ~ 0
D1mini-UART-Rx
Text Label 3700 1750 0    50   ~ 0
D1mini-UART-Tx
Text Label 5750 2200 0    50   ~ 0
GND
$Comp
L power:+3.3V #PWR0101
U 1 1 5FD459BB
P 1700 1750
F 0 "#PWR0101" H 1700 1600 50  0001 C CNN
F 1 "+3.3V" H 1715 1923 50  0000 C CNN
F 2 "" H 1700 1750 50  0001 C CNN
F 3 "" H 1700 1750 50  0001 C CNN
	1    1700 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 1750 1700 2100
Wire Wire Line
	1700 2100 2200 2100
Wire Wire Line
	1700 2800 2200 2800
$Comp
L power:GND #PWR0103
U 1 1 5FD47C54
P 1700 3300
F 0 "#PWR0103" H 1700 3050 50  0001 C CNN
F 1 "GND" H 1705 3127 50  0000 C CNN
F 2 "" H 1700 3300 50  0001 C CNN
F 3 "" H 1700 3300 50  0001 C CNN
	1    1700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3300 1700 3150
Wire Wire Line
	1700 3150 2200 3150
Wire Wire Line
	9450 1400 8850 1400
Text Label 8850 1400 0    50   ~ 0
LED-DIN
Text Label 4000 3400 0    50   ~ 0
GND
Text Label 4000 3300 0    50   ~ 0
+3.3V
Text Label 4000 3200 0    50   ~ 0
I2C-SCL
Text Label 4000 3100 0    50   ~ 0
I2C-SDA
Text Label 8100 2950 0    50   ~ 0
GND
Text Label 8100 3050 0    50   ~ 0
RCWL-OUT
Text Label 8100 3150 0    50   ~ 0
+5V
Text Notes 7350 2400 0    50   ~ 0
MH-Z19B
Text Notes 9350 6200 0    50   ~ 0
ESP8266-12F D1Mini
Wire Notes Line
	1050 1050 1050 3800
Wire Notes Line
	1050 3800 2950 3800
Wire Notes Line
	2950 3800 2950 1050
Wire Notes Line
	2950 1050 1050 1050
Text Notes 2300 3700 0    50   ~ 0
Power/Ground
Text Notes 6600 3700 0    50   ~ 0
SSD1306 128x32 OLED display
Text Notes 10400 3700 0    50   ~ 0
RCWL0516 Radar
Wire Notes Line
	8100 950  10400 950 
$Comp
L Connector:Conn_01x03_Female J8
U 1 1 5FD9167B
P 9650 1400
F 0 "J8" H 9500 1750 50  0000 L CNN
F 1 "LED connector" H 9500 1650 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 9650 1400 50  0001 C CNN
F 3 "~" H 9650 1400 50  0001 C CNN
	1    9650 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1300 8850 1300
Text Label 8850 1300 0    50   ~ 0
GND
Wire Notes Line
	8100 2100 10400 2100
Text Notes 9300 2050 0    50   ~ 0
LED connector WS2812B
Wire Wire Line
	7900 5950 7900 6150
Text Label 7350 6150 0    50   ~ 0
GND
Wire Wire Line
	8000 4350 8000 4050
Text Label 7800 4150 0    50   ~ 0
+5V
Text Label 8000 4050 0    50   ~ 0
+3.3V
Wire Wire Line
	7900 6150 7350 6150
Wire Wire Line
	8300 5550 8600 5550
Text Label 8800 5650 0    50   ~ 0
D1mini-UART-Rx
Text Label 8800 5750 0    50   ~ 0
D1mini-UART-Tx
$Comp
L power:GND #PWR01
U 1 1 5FD9B75A
P 850 6650
F 0 "#PWR01" H 850 6400 50  0001 C CNN
F 1 "GND" H 855 6477 50  0000 C CNN
F 2 "" H 850 6650 50  0001 C CNN
F 3 "" H 850 6650 50  0001 C CNN
	1    850  6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5FD9B31B
P 1900 6650
F 0 "#PWR02" H 1900 6400 50  0001 C CNN
F 1 "GND" H 1905 6477 50  0000 C CNN
F 2 "" H 1900 6650 50  0001 C CNN
F 3 "" H 1900 6650 50  0001 C CNN
	1    1900 6650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5FD8C9B6
P 850 6550
F 0 "H1" H 950 6599 50  0000 L CNN
F 1 "MountingHole_Pad" H 950 6508 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_TopBottom" H 850 6550 50  0001 C CNN
F 3 "~" H 850 6550 50  0001 C CNN
	1    850  6550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5FD8AE1D
P 1900 6550
F 0 "H2" H 2000 6599 50  0000 L CNN
F 1 "MountingHole_Pad" H 2000 6508 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_TopBottom" H 1900 6550 50  0001 C CNN
F 3 "~" H 1900 6550 50  0001 C CNN
	1    1900 6550
	1    0    0    -1  
$EndComp
Text Notes 1650 5750 0    50   ~ 0
BME280 \nPressure/Temperature/Humidity
Wire Notes Line
	4700 4650 4700 5800
Wire Notes Line
	1400 5800 1400 4650
Text Label 1800 5350 0    50   ~ 0
I2C-SDA
Text Label 1800 5250 0    50   ~ 0
I2C-SCL
Text Label 1800 5150 0    50   ~ 0
GND
Text Label 1800 5050 0    50   ~ 0
+3.3V
Wire Wire Line
	5750 1950 5750 2200
Wire Wire Line
	4850 1400 5350 1400
Wire Wire Line
	5350 1500 5150 1500
Wire Wire Line
	5150 1500 5150 1750
Text Label 5750 1050 0    50   ~ 0
+5V
Wire Notes Line
	7900 750  3650 750 
Wire Notes Line
	7900 750  7900 2500
Wire Notes Line
	3650 2500 7900 2500
Wire Notes Line
	3650 750  3650 2500
$Comp
L KiwiAirMonitorModules:mh_z19b_MH-Z19B U2
U 1 1 5FD975FE
P 5750 1600
F 0 "U2" H 5950 2100 50  0000 C CNN
F 1 "MH-Z19B" H 6050 2000 50  0000 C CNN
F 2 "mh-z19:MH-Z19" H 5750 950 50  0001 C CNN
F 3 "https://www.winsen-sensor.com/d/files/MH-Z19B.pdf" H 5700 1350 50  0001 C CNN
	1    5750 1600
	1    0    0    -1  
$EndComp
$Comp
L KiwiAirMonitorModules:KiwiAirMonitorModules_BME280_Board U5
U 1 1 5FDD25C9
P 3350 5650
F 0 "U5" H 3700 6550 50  0000 L CNN
F 1 "BME280_Board" H 3450 6450 50  0000 L CNN
F 2 "KiwiAirMonitorModules:BME280_Board" H 3700 6350 50  0001 C CNN
F 3 "" H 3700 6350 50  0001 C CNN
	1    3350 5650
	1    0    0    -1  
$EndComp
Wire Notes Line
	1400 5800 4700 5800
Wire Notes Line
	1400 4650 4700 4650
Wire Wire Line
	8300 4750 8750 4750
Text Label 8750 4400 0    50   ~ 0
RCWL-OUT
$Comp
L KiwiAirMonitorModules:KiwiAirMonitorModules_SSD1306_OLED_0.91_128x32 U3
U 1 1 5FDAE526
P 6100 3500
F 0 "U3" H 6400 4150 50  0000 C CNN
F 1 "OLED_0.91_128x32" H 6450 4050 50  0000 C CNN
F 2 "KiwiAirMonitorModules:OLED_0.91_128x32" H 6100 3500 50  0001 C CNN
F 3 "" H 6100 3500 50  0001 C CNN
	1    6100 3500
	1    0    0    -1  
$EndComp
Wire Notes Line
	3650 2600 7900 2600
Wire Notes Line
	7900 2600 7900 3750
Wire Notes Line
	3650 2600 3650 3750
Wire Notes Line
	7900 3750 3650 3750
$Comp
L KiwiAirMonitorModules:KiwiAirMonitorModules_RCWL-0516-Board U4
U 1 1 5FDAB549
P 9500 3350
F 0 "U4" H 10050 4100 50  0000 L CNN
F 1 "RCWL-0516 Board" H 10000 4000 50  0000 L CNN
F 2 "KiwiAirMonitorModules:RCWL-0516" H 9550 4000 50  0001 C CNN
F 3 "" H 9550 4000 50  0001 C CNN
	1    9500 3350
	1    0    0    -1  
$EndComp
Wire Notes Line
	8000 3750 11100 3750
Wire Notes Line
	11100 3750 11100 2500
Wire Notes Line
	11100 2500 8000 2500
Wire Notes Line
	8000 2500 8000 3750
Wire Wire Line
	4850 1400 4850 1650
$Comp
L Connector:Conn_01x02_Female J10
U 1 1 5FE25583
P 9750 5750
F 0 "J10" H 9642 5425 50  0000 C CNN
F 1 "Conn_D1Mini_UART" H 9642 5516 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9750 5750 50  0001 C CNN
F 3 "~" H 9750 5750 50  0001 C CNN
	1    9750 5750
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J12
U 1 1 5FE3839F
P 10300 4950
F 0 "J12" H 10192 4625 50  0000 C CNN
F 1 "Conn_D1Mini_I2C" H 10192 4716 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10300 4950 50  0001 C CNN
F 3 "~" H 10300 4950 50  0001 C CNN
	1    10300 4950
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J13
U 1 1 5FE5136F
P 9400 4300
F 0 "J13" H 9300 4500 50  0000 C CNN
F 1 "Conn_RCWL_Out" H 9350 4400 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 9400 4300 50  0001 C CNN
F 3 "~" H 9400 4300 50  0001 C CNN
	1    9400 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J14
U 1 1 5FE59941
P 4650 6850
F 0 "J14" H 4542 6525 50  0000 C CNN
F 1 "Conn_Power" H 4542 6616 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4650 6850 50  0001 C CNN
F 3 "~" H 4650 6850 50  0001 C CNN
	1    4650 6850
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J15
U 1 1 5FE5AA57
P 4600 7400
F 0 "J15" H 4492 7175 50  0000 C CNN
F 1 "Conn_Ground" H 4492 7266 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4600 7400 50  0001 C CNN
F 3 "~" H 4600 7400 50  0001 C CNN
	1    4600 7400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 6750 5550 6750
Wire Wire Line
	4850 6850 5550 6850
Wire Wire Line
	4850 6950 5550 6950
Wire Wire Line
	4800 7400 5550 7400
Text Label 5550 6750 0    50   ~ 0
GND
Text Label 5550 6950 0    50   ~ 0
+5V
Text Label 5550 6850 0    50   ~ 0
+3.3V
Text Label 5550 7400 0    50   ~ 0
GND
Wire Notes Line
	10800 3950 10800 6350
NoConn ~ 6250 1400
NoConn ~ 6250 1500
NoConn ~ 6250 1650
NoConn ~ 6250 1750
NoConn ~ 9500 2850
NoConn ~ 9500 3250
NoConn ~ 7500 5150
NoConn ~ 7500 5050
NoConn ~ 7500 4750
NoConn ~ 8300 4650
NoConn ~ 8300 5050
NoConn ~ 8300 5350
NoConn ~ 8300 5450
NoConn ~ 3350 5450
NoConn ~ 3350 5550
Text Label 2200 2100 0    50   ~ 0
+3.3V
Text Label 2200 2800 0    50   ~ 0
+5V
Text Label 2200 3150 0    50   ~ 0
GND
NoConn ~ 5350 1750
Wire Wire Line
	7800 4350 7800 4150
$Comp
L MCU_Module:WeMos_D1_mini U1
U 1 1 5FD7E74C
P 7900 5150
F 0 "U1" H 8150 6050 50  0000 C CNN
F 1 "WeMos_D1_mini" H 8100 5950 50  0000 L CNN
F 2 "Module:WEMOS_D1_mini_light" H 7900 4000 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 6050 4000 50  0001 C CNN
	1    7900 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5FF23882
P 1700 2550
F 0 "#PWR0102" H 1700 2400 50  0001 C CNN
F 1 "+5V" H 1715 2723 50  0000 C CNN
F 2 "" H 1700 2550 50  0001 C CNN
F 3 "" H 1700 2550 50  0001 C CNN
	1    1700 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2550 1700 2800
$Comp
L power:GND #PWR0104
U 1 1 5FE37F7A
P 850 7400
F 0 "#PWR0104" H 850 7150 50  0001 C CNN
F 1 "GND" H 855 7227 50  0000 C CNN
F 2 "" H 850 7400 50  0001 C CNN
F 3 "" H 850 7400 50  0001 C CNN
	1    850  7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5FE37F80
P 850 7300
F 0 "H3" H 950 7349 50  0000 L CNN
F 1 "MountingHole_Pad" H 950 7258 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_TopBottom" H 850 7300 50  0001 C CNN
F 3 "~" H 850 7300 50  0001 C CNN
	1    850  7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4850 10100 4850
Wire Wire Line
	8300 4950 10100 4950
Wire Wire Line
	8300 5150 10100 5150
Wire Wire Line
	8750 4300 9200 4300
Wire Wire Line
	8750 4300 8750 4750
Wire Wire Line
	8600 5550 8600 5750
Wire Wire Line
	8600 5750 9550 5750
Wire Wire Line
	8750 5250 8750 5650
Wire Wire Line
	8750 5650 9550 5650
Wire Wire Line
	8300 5250 8750 5250
Wire Notes Line
	6850 3950 6850 6350
Wire Notes Line
	10800 3950 6850 3950
Wire Notes Line
	6850 6350 10800 6350
Wire Wire Line
	3700 1750 5150 1750
Wire Wire Line
	3700 1650 4850 1650
Wire Wire Line
	8100 2950 9500 2950
Wire Wire Line
	8100 3050 9500 3050
Wire Wire Line
	8100 3150 9500 3150
Wire Wire Line
	4000 3400 6000 3400
Wire Wire Line
	4000 3300 6000 3300
Wire Wire Line
	4000 3200 6000 3200
Wire Wire Line
	4000 3100 6000 3100
Wire Wire Line
	1800 5050 3350 5050
Wire Wire Line
	1800 5150 3350 5150
Wire Wire Line
	1800 5250 3350 5250
Wire Wire Line
	1800 5350 3350 5350
Wire Wire Line
	5750 1250 5750 1050
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5FE6907A
P 2050 7300
F 0 "H4" H 2150 7349 50  0000 L CNN
F 1 "MountingHole_Pad" H 2150 7258 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_TopBottom" H 2050 7300 50  0001 C CNN
F 3 "~" H 2050 7300 50  0001 C CNN
	1    2050 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FE6975F
P 2050 7400
F 0 "#PWR0105" H 2050 7150 50  0001 C CNN
F 1 "GND" H 2055 7227 50  0000 C CNN
F 2 "" H 2050 7400 50  0001 C CNN
F 3 "" H 2050 7400 50  0001 C CNN
	1    2050 7400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5FE6B372
P 8650 1750
F 0 "D1" H 8650 1533 50  0000 C CNN
F 1 "1N4007" H 8650 1624 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8650 1575 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8650 1750 50  0001 C CNN
	1    8650 1750
	-1   0    0    1   
$EndComp
Wire Notes Line
	8100 950  8100 2100
Wire Notes Line
	10400 950  10400 2100
Text Label 8200 1750 0    50   ~ 0
+5V
Wire Wire Line
	8800 1750 9100 1750
Wire Wire Line
	9100 1750 9100 1500
Wire Wire Line
	9100 1500 9450 1500
Text Label 8900 1750 0    50   ~ 0
VLED
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5FE7ACB3
P 8650 2000
F 0 "JP1" H 8650 2205 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 8650 2114 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_TrianglePad1.0x1.5mm" H 8650 2000 50  0001 C CNN
F 3 "~" H 8650 2000 50  0001 C CNN
	1    8650 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2000 9100 2000
Wire Wire Line
	9100 2000 9100 1750
Connection ~ 9100 1750
Wire Wire Line
	8500 2000 8350 2000
Wire Wire Line
	8350 2000 8350 1750
Wire Wire Line
	8200 1750 8350 1750
Connection ~ 8350 1750
Wire Wire Line
	8350 1750 8500 1750
$EndSCHEMATC
