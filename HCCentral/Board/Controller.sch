EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:74xgxx
LIBS:ac-dc
LIBS:dc-dc
LIBS:diode
LIBS:ftdi
LIBS:logo
LIBS:maxim
LIBS:Oscillators
LIBS:Power_Management
LIBS:powerint
LIBS:references
LIBS:sensors
LIBS:ESP8266
LIBS:mysensors_network
LIBS:mysensors_radios
LIBS:rj45-trj0011banl
LIBS:HCCentral-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA1284P-A IC2
U 1 1 56380186
P 4400 3350
F 0 "IC2" H 3550 5230 40  0000 L BNN
F 1 "ATMEGA1284P-A" H 4800 1400 40  0000 L BNN
F 2 "Housings_QFP:TQFP-44_10x10mm_Pitch0.8mm" H 4400 3350 30  0000 C CIN
F 3 "" H 4400 3350 60  0000 C CNN
	1    4400 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 56427B40
P 4250 5450
F 0 "#PWR035" H 4250 5200 50  0001 C CNN
F 1 "GND" H 4250 5300 50  0000 C CNN
F 2 "" H 4250 5450 60  0000 C CNN
F 3 "" H 4250 5450 60  0000 C CNN
	1    4250 5450
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR036
U 1 1 56427BA4
P 4200 1150
F 0 "#PWR036" H 4200 1000 50  0001 C CNN
F 1 "+3V3" H 4200 1290 50  0000 C CNN
F 2 "" H 4200 1150 60  0000 C CNN
F 3 "" H 4200 1150 60  0000 C CNN
	1    4200 1150
	1    0    0    -1  
$EndComp
Text HLabel 10100 3050 2    60   Output ~ 0
MOSI_LAN
Text HLabel 10100 3150 2    60   Input ~ 0
MISO_LAN
Text HLabel 10100 3250 2    60   Output ~ 0
SCK_LAN
Text HLabel 10100 2950 2    60   Output ~ 0
CS_LAN
$Comp
L Crystal_Small Y2
U 1 1 56440F28
P 3100 2250
F 0 "Y2" H 3100 2350 50  0000 C CNN
F 1 "16MHz" H 3100 2150 50  0000 C CNN
F 2 "w_crystal:hc-49_smd" H 3100 2250 60  0001 C CNN
F 3 "" H 3100 2250 60  0000 C CNN
	1    3100 2250
	0    -1   -1   0   
$EndComp
Text HLabel 5650 4650 2    60   Output ~ 0
MOSI_RF
Text HLabel 5650 4550 2    60   Input ~ 0
MISO_RF
Text HLabel 5650 4750 2    60   Output ~ 0
SCK_RF
Text HLabel 5650 3450 2    60   Input ~ 0
DIO0_433
Text HLabel 5650 4950 2    60   Input ~ 0
DIO1_433
Text HLabel 5650 5050 2    60   Input ~ 0
DIO2_433
Text HLabel 5650 4850 2    60   Input ~ 0
DIO5_433
Text HLabel 5650 3950 2    60   Input ~ 0
DIO0_866
Text HLabel 5650 3750 2    60   Input ~ 0
DIO1_866
Text HLabel 5650 3850 2    60   Input ~ 0
DIO2_866
Text HLabel 5650 3650 2    60   Input ~ 0
DIO5_866
$Comp
L LED D2
U 1 1 5644153C
P 9200 5750
F 0 "D2" H 9200 5850 50  0000 C CNN
F 1 "LED" H 9200 5650 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 9200 5750 60  0001 C CNN
F 3 "" H 9200 5750 60  0000 C CNN
	1    9200 5750
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 564415C7
P 8950 5750
F 0 "D1" H 8950 5850 50  0000 C CNN
F 1 "LED" H 8950 5650 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 8950 5750 60  0001 C CNN
F 3 "" H 8950 5750 60  0000 C CNN
	1    8950 5750
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X06 P4
U 1 1 56441790
P 10250 2350
F 0 "P4" H 10250 2700 50  0000 C CNN
F 1 "ISP" V 10350 2350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 10250 2350 60  0001 C CNN
F 3 "" H 10250 2350 60  0000 C CNN
	1    10250 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 56441A7A
P 9900 4600
F 0 "#PWR037" H 9900 4350 50  0001 C CNN
F 1 "GND" H 9900 4450 50  0000 C CNN
F 2 "" H 9900 4600 60  0000 C CNN
F 3 "" H 9900 4600 60  0000 C CNN
	1    9900 4600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P7
U 1 1 56441B52
P 10150 4450
F 0 "P7" H 10150 4650 50  0000 C CNN
F 1 "UART" V 10250 4450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 10150 4450 60  0001 C CNN
F 3 "" H 10150 4450 60  0000 C CNN
	1    10150 4450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P6
U 1 1 56441EF8
P 2700 5450
F 0 "P6" H 2700 5800 50  0000 C CNN
F 1 "SPI" V 2800 5450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 2700 5450 60  0001 C CNN
F 3 "" H 2700 5450 60  0000 C CNN
	1    2700 5450
	1    0    0    -1  
$EndComp
Text HLabel 5600 2150 2    60   Input ~ 0
IRQ_LAN
$Comp
L C C22
U 1 1 56442881
P 2800 2450
F 0 "C22" H 2825 2550 50  0000 L CNN
F 1 "32pF" H 2825 2350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2838 2300 30  0001 C CNN
F 3 "" H 2800 2450 60  0000 C CNN
	1    2800 2450
	0    1    1    0   
$EndComp
$Comp
L C C21
U 1 1 56442906
P 2800 2050
F 0 "C21" H 2825 2150 50  0000 L CNN
F 1 "32pF" H 2825 1950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2838 1900 30  0001 C CNN
F 3 "" H 2800 2050 60  0000 C CNN
	1    2800 2050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR038
U 1 1 56442B0F
P 2550 2500
F 0 "#PWR038" H 2550 2250 50  0001 C CNN
F 1 "GND" H 2550 2350 50  0000 C CNN
F 2 "" H 2550 2500 60  0000 C CNN
F 3 "" H 2550 2500 60  0000 C CNN
	1    2550 2500
	1    0    0    -1  
$EndComp
$Comp
L C C23
U 1 1 56442D8A
P 3100 3000
F 0 "C23" H 3125 3100 50  0000 L CNN
F 1 "100nF" H 3125 2900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3138 2850 30  0001 C CNN
F 3 "" H 3100 3000 60  0000 C CNN
	1    3100 3000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR039
U 1 1 56442DFC
P 3100 3200
F 0 "#PWR039" H 3100 2950 50  0001 C CNN
F 1 "GND" H 3100 3050 50  0000 C CNN
F 2 "" H 3100 3200 60  0000 C CNN
F 3 "" H 3100 3200 60  0000 C CNN
	1    3100 3200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR040
U 1 1 5644337E
P 9950 1800
F 0 "#PWR040" H 9950 1650 50  0001 C CNN
F 1 "+3V3" H 9950 1940 50  0000 C CNN
F 2 "" H 9950 1800 60  0000 C CNN
F 3 "" H 9950 1800 60  0000 C CNN
	1    9950 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 5644351F
P 9950 2700
F 0 "#PWR041" H 9950 2450 50  0001 C CNN
F 1 "GND" H 9950 2550 50  0000 C CNN
F 2 "" H 9950 2700 60  0000 C CNN
F 3 "" H 9950 2700 60  0000 C CNN
	1    9950 2700
	1    0    0    -1  
$EndComp
Text HLabel 5650 3550 2    60   Output ~ 0
CS_RF433
Text HLabel 5650 4050 2    60   Output ~ 0
CS_RF866
$Comp
L SW_PUSH SW2
U 1 1 56473C6F
P 8600 5700
F 0 "SW2" H 8750 5810 50  0000 C CNN
F 1 "SW_PUSH" H 8600 5620 50  0000 C CNN
F 2 "SW0773:SW_0773" H 8600 5700 60  0001 C CNN
F 3 "" H 8600 5700 60  0000 C CNN
	1    8600 5700
	0    -1   -1   0   
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 56473DD6
P 2200 1950
F 0 "SW1" H 2350 2060 50  0000 C CNN
F 1 "Reset" H 2200 1870 50  0000 C CNN
F 2 "SW0773:SW_0773" H 2200 1950 60  0001 C CNN
F 3 "" H 2200 1950 60  0000 C CNN
	1    2200 1950
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 56473F24
P 8950 5250
F 0 "R12" V 9030 5250 50  0000 C CNN
F 1 "180R" V 8950 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8880 5250 30  0001 C CNN
F 3 "" H 8950 5250 30  0000 C CNN
	1    8950 5250
	-1   0    0    1   
$EndComp
$Comp
L R R11
U 1 1 56473FB5
P 9200 5250
F 0 "R11" V 9280 5250 50  0000 C CNN
F 1 "180R" V 9200 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9130 5250 30  0001 C CNN
F 3 "" H 9200 5250 30  0000 C CNN
	1    9200 5250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR042
U 1 1 56474329
P 8600 6050
F 0 "#PWR042" H 8600 5800 50  0001 C CNN
F 1 "GND" H 8600 5900 50  0000 C CNN
F 2 "" H 8600 6050 60  0000 C CNN
F 3 "" H 8600 6050 60  0000 C CNN
	1    8600 6050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR043
U 1 1 5647452B
P 8950 6050
F 0 "#PWR043" H 8950 5800 50  0001 C CNN
F 1 "GND" H 8950 5900 50  0000 C CNN
F 2 "" H 8950 6050 60  0000 C CNN
F 3 "" H 8950 6050 60  0000 C CNN
	1    8950 6050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR044
U 1 1 56474563
P 9200 6050
F 0 "#PWR044" H 9200 5800 50  0001 C CNN
F 1 "GND" H 9200 5900 50  0000 C CNN
F 2 "" H 9200 6050 60  0000 C CNN
F 3 "" H 9200 6050 60  0000 C CNN
	1    9200 6050
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 56475270
P 8300 2550
F 0 "R10" V 8380 2550 50  0000 C CNN
F 1 "15k" V 8300 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8230 2550 30  0001 C CNN
F 3 "" H 8300 2550 30  0000 C CNN
	1    8300 2550
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 56475323
P 8300 2100
F 0 "R8" V 8380 2100 50  0000 C CNN
F 1 "R" V 8300 2100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8230 2100 30  0001 C CNN
F 3 "" H 8300 2100 30  0000 C CNN
	1    8300 2100
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 5647546D
P 7950 2550
F 0 "C20" H 7975 2650 50  0000 L CNN
F 1 "100nF" H 7975 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7988 2400 30  0001 C CNN
F 3 "" H 7950 2550 60  0000 C CNN
	1    7950 2550
	-1   0    0    1   
$EndComp
$Comp
L +3V3 #PWR045
U 1 1 56475923
P 8300 1850
F 0 "#PWR045" H 8300 1700 50  0001 C CNN
F 1 "+3V3" H 8300 1990 50  0000 C CNN
F 2 "" H 8300 1850 60  0000 C CNN
F 3 "" H 8300 1850 60  0000 C CNN
	1    8300 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR046
U 1 1 564759AC
P 8300 2750
F 0 "#PWR046" H 8300 2500 50  0001 C CNN
F 1 "GND" H 8300 2600 50  0000 C CNN
F 2 "" H 8300 2750 60  0000 C CNN
F 3 "" H 8300 2750 60  0000 C CNN
	1    8300 2750
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 56476785
P 1750 1800
F 0 "C19" H 1775 1900 50  0000 L CNN
F 1 "100nF" H 1775 1700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1788 1650 30  0001 C CNN
F 3 "" H 1750 1800 60  0000 C CNN
	1    1750 1800
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 56476907
P 1200 1650
F 0 "R9" V 1280 1650 50  0000 C CNN
F 1 "10k" V 1200 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1130 1650 30  0001 C CNN
F 3 "" H 1200 1650 30  0000 C CNN
	1    1200 1650
	0    1    1    0   
$EndComp
$Comp
L +3V3 #PWR047
U 1 1 56476C07
P 1000 1550
F 0 "#PWR047" H 1000 1400 50  0001 C CNN
F 1 "+3V3" H 1000 1690 50  0000 C CNN
F 2 "" H 1000 1550 60  0000 C CNN
F 3 "" H 1000 1550 60  0000 C CNN
	1    1000 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 564770B2
P 2200 2350
F 0 "#PWR048" H 2200 2100 50  0001 C CNN
F 1 "GND" H 2200 2200 50  0000 C CNN
F 2 "" H 2200 2350 60  0000 C CNN
F 3 "" H 2200 2350 60  0000 C CNN
	1    2200 2350
	1    0    0    -1  
$EndComp
Text HLabel 5650 4150 2    60   Output ~ 0
Reset_RF
$Comp
L SD_Card CON2
U 1 1 56491680
P 5350 6850
F 0 "CON2" H 4700 7400 50  0000 C CNN
F 1 "SD_Card" H 5950 6300 50  0000 C CNN
F 2 "Connect:SD_Card_Receptacle" H 5550 7200 50  0000 C CNN
F 3 "" H 5350 6850 60  0000 C CNN
	1    5350 6850
	1    0    0    -1  
$EndComp
$Comp
L C C24
U 1 1 564A85C7
P 2650 6900
F 0 "C24" H 2675 7000 50  0000 L CNN
F 1 "100nF" H 2675 6800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2688 6750 30  0001 C CNN
F 3 "" H 2650 6900 60  0000 C CNN
	1    2650 6900
	-1   0    0    1   
$EndComp
$Comp
L +3V3 #PWR049
U 1 1 564A896D
P 3800 6300
F 0 "#PWR049" H 3800 6150 50  0001 C CNN
F 1 "+3V3" H 3800 6440 50  0000 C CNN
F 2 "" H 3800 6300 60  0000 C CNN
F 3 "" H 3800 6300 60  0000 C CNN
	1    3800 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR050
U 1 1 564A89BA
P 4300 7350
F 0 "#PWR050" H 4300 7100 50  0001 C CNN
F 1 "GND" H 4300 7200 50  0000 C CNN
F 2 "" H 4300 7350 60  0000 C CNN
F 3 "" H 4300 7350 60  0000 C CNN
	1    4300 7350
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 564A9419
P 3950 6450
F 0 "R13" V 4030 6450 50  0000 C CNN
F 1 "1kR" V 3950 6450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3880 6450 30  0001 C CNN
F 3 "" H 3950 6450 30  0000 C CNN
	1    3950 6450
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 564A95A6
P 3950 7250
F 0 "R14" V 4030 7250 50  0000 C CNN
F 1 "1kR" V 3950 7250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3880 7250 30  0001 C CNN
F 3 "" H 3950 7250 30  0000 C CNN
	1    3950 7250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR051
U 1 1 564AA291
P 6300 7350
F 0 "#PWR051" H 6300 7100 50  0001 C CNN
F 1 "GND" H 6300 7200 50  0000 C CNN
F 2 "" H 6300 7350 60  0000 C CNN
F 3 "" H 6300 7350 60  0000 C CNN
	1    6300 7350
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR052
U 1 1 564AB59F
P 2650 6700
F 0 "#PWR052" H 2650 6550 50  0001 C CNN
F 1 "+3V3" H 2650 6840 50  0000 C CNN
F 2 "" H 2650 6700 60  0000 C CNN
F 3 "" H 2650 6700 60  0000 C CNN
	1    2650 6700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR053
U 1 1 564AB78A
P 2650 7100
F 0 "#PWR053" H 2650 6850 50  0001 C CNN
F 1 "GND" H 2650 6950 50  0000 C CNN
F 2 "" H 2650 7100 60  0000 C CNN
F 3 "" H 2650 7100 60  0000 C CNN
	1    2650 7100
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 564AC27E
P 1800 1050
F 0 "C15" H 1825 1150 50  0000 L CNN
F 1 "100nF" H 1825 950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1838 900 30  0001 C CNN
F 3 "" H 1800 1050 60  0000 C CNN
	1    1800 1050
	-1   0    0    1   
$EndComp
$Comp
L C C16
U 1 1 564AC6A2
P 2100 1050
F 0 "C16" H 2125 1150 50  0000 L CNN
F 1 "100nF" H 2125 950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2138 900 30  0001 C CNN
F 3 "" H 2100 1050 60  0000 C CNN
	1    2100 1050
	-1   0    0    1   
$EndComp
$Comp
L C C17
U 1 1 564AC70C
P 2400 1050
F 0 "C17" H 2425 1150 50  0000 L CNN
F 1 "100nF" H 2425 950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2438 900 30  0001 C CNN
F 3 "" H 2400 1050 60  0000 C CNN
	1    2400 1050
	-1   0    0    1   
$EndComp
$Comp
L C C18
U 1 1 564AC779
P 2750 1050
F 0 "C18" H 2775 1150 50  0000 L CNN
F 1 "100nF" H 2775 950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2788 900 30  0001 C CNN
F 3 "" H 2750 1050 60  0000 C CNN
	1    2750 1050
	-1   0    0    1   
$EndComp
$Comp
L +3V3 #PWR054
U 1 1 564AC833
P 2250 800
F 0 "#PWR054" H 2250 650 50  0001 C CNN
F 1 "+3V3" H 2250 940 50  0000 C CNN
F 2 "" H 2250 800 60  0000 C CNN
F 3 "" H 2250 800 60  0000 C CNN
	1    2250 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR055
U 1 1 564AC902
P 2250 1300
F 0 "#PWR055" H 2250 1050 50  0001 C CNN
F 1 "GND" H 2250 1150 50  0000 C CNN
F 2 "" H 2250 1300 60  0000 C CNN
F 3 "" H 2250 1300 60  0000 C CNN
	1    2250 1300
	1    0    0    -1  
$EndComp
Text HLabel 3550 6650 0    60   Output ~ 0
MOSI_LAN
Text HLabel 3550 7150 0    60   Input ~ 0
MISO_LAN
Text HLabel 3550 6950 0    60   Output ~ 0
SCK_LAN
Wire Wire Line
	4100 5450 4400 5450
Wire Wire Line
	4100 5450 4100 5350
Wire Wire Line
	4400 5450 4400 5350
Connection ~ 4250 5450
Wire Wire Line
	4200 5350 4200 5450
Connection ~ 4200 5450
Wire Wire Line
	4300 5350 4300 5450
Connection ~ 4300 5450
Wire Wire Line
	4100 1150 4500 1150
Wire Wire Line
	4100 1150 4100 1350
Wire Wire Line
	4500 1150 4500 1350
Connection ~ 4200 1150
Wire Wire Line
	4200 1150 4200 1350
Wire Wire Line
	4300 1350 4300 1150
Connection ~ 4300 1150
Wire Wire Line
	5400 3250 10100 3250
Wire Wire Line
	5400 3150 10100 3150
Wire Wire Line
	5400 3050 10100 3050
Wire Wire Line
	5400 4550 5650 4550
Wire Wire Line
	5650 4650 5400 4650
Wire Wire Line
	5400 4750 5650 4750
Wire Wire Line
	2950 2050 3400 2050
Wire Wire Line
	2950 2450 3400 2450
Wire Wire Line
	3100 2350 3100 2450
Connection ~ 3100 2450
Wire Wire Line
	3100 2150 3100 2050
Connection ~ 3100 2050
Wire Wire Line
	2650 2050 2550 2050
Wire Wire Line
	2550 2050 2550 2500
Wire Wire Line
	2650 2450 2550 2450
Connection ~ 2550 2450
Wire Wire Line
	3400 2850 3100 2850
Wire Wire Line
	3100 3200 3100 3150
Wire Wire Line
	10050 2100 9850 2100
Wire Wire Line
	10050 2300 9750 2300
Wire Wire Line
	10050 2400 9650 2400
Wire Wire Line
	10050 2600 9950 2600
Wire Wire Line
	9950 2600 9950 2700
Wire Wire Line
	9950 1800 9950 2200
Wire Wire Line
	9950 2200 10050 2200
Wire Wire Line
	8300 2250 8300 2400
Connection ~ 8300 2350
Connection ~ 7950 2350
Wire Wire Line
	8300 2750 7950 2750
Wire Wire Line
	7950 2750 7950 2700
Wire Wire Line
	8300 2750 8300 2700
Connection ~ 8300 2750
Wire Wire Line
	8300 1950 8300 1850
Wire Wire Line
	1350 1650 3400 1650
Connection ~ 2200 1650
Connection ~ 1750 1650
Wire Wire Line
	1050 1650 1000 1650
Wire Wire Line
	1000 1650 1000 1550
Wire Wire Line
	2200 2350 1750 2350
Wire Wire Line
	1750 2350 1750 1950
Wire Wire Line
	2200 2250 2200 2350
Connection ~ 2200 2350
Wire Wire Line
	4450 6750 4300 6750
Wire Wire Line
	4300 6750 4300 7350
Wire Wire Line
	4450 7050 4300 7050
Connection ~ 4300 7050
Wire Wire Line
	3800 6850 4450 6850
Wire Wire Line
	3800 6300 3800 7250
Connection ~ 3800 6850
Wire Wire Line
	4100 6450 4450 6450
Wire Wire Line
	4100 7250 4450 7250
Wire Wire Line
	4450 6650 3550 6650
Wire Wire Line
	4450 6950 3550 6950
Wire Wire Line
	4450 7150 3550 7150
Connection ~ 3800 6450
Wire Wire Line
	6250 6950 6300 6950
Wire Wire Line
	6300 6950 6300 7350
Wire Wire Line
	6250 7050 6300 7050
Connection ~ 6300 7050
Wire Wire Line
	2650 6700 2650 6750
Wire Wire Line
	2650 7100 2650 7050
Wire Wire Line
	1800 1300 2750 1300
Wire Wire Line
	1800 1300 1800 1200
Wire Wire Line
	2750 1300 2750 1200
Connection ~ 2250 1300
Wire Wire Line
	2100 1200 2100 1300
Connection ~ 2100 1300
Wire Wire Line
	2400 1200 2400 1300
Connection ~ 2400 1300
Wire Wire Line
	1800 900  1800 800 
Wire Wire Line
	1800 800  2750 800 
Wire Wire Line
	2750 800  2750 900 
Connection ~ 2250 800 
Wire Wire Line
	2100 900  2100 800 
Connection ~ 2100 800 
Wire Wire Line
	2400 900  2400 800 
Connection ~ 2400 800 
Wire Wire Line
	3600 5900 6750 5900
Wire Wire Line
	3600 5900 3600 6550
Wire Wire Line
	3600 6550 4450 6550
Wire Wire Line
	6550 2850 6550 6750
Wire Wire Line
	6550 6750 6250 6750
Wire Wire Line
	6650 2750 6650 6650
Wire Wire Line
	6650 6650 6250 6650
Wire Wire Line
	9900 4600 9900 4550
Wire Wire Line
	9900 4550 9950 4550
Wire Wire Line
	5400 4450 9950 4450
Wire Wire Line
	5400 4350 9950 4350
Wire Wire Line
	8950 5400 8950 5550
Wire Wire Line
	9200 5400 9200 5550
Wire Wire Line
	8950 5950 8950 6050
Wire Wire Line
	9200 5950 9200 6050
Wire Wire Line
	5400 4850 5650 4850
Wire Wire Line
	5650 4950 5400 4950
Wire Wire Line
	5400 5050 5650 5050
Wire Wire Line
	5400 3450 5650 3450
Wire Wire Line
	5400 3550 5650 3550
Wire Wire Line
	5400 3650 5650 3650
Wire Wire Line
	5400 3750 5650 3750
Wire Wire Line
	5400 3850 5650 3850
Wire Wire Line
	5400 3950 5650 3950
Wire Wire Line
	5400 4050 5650 4050
Wire Wire Line
	5400 2350 8300 2350
Wire Wire Line
	6550 2850 5400 2850
Wire Wire Line
	5400 2750 6650 2750
Wire Wire Line
	6750 5900 6750 2650
Wire Wire Line
	6750 2650 5400 2650
Wire Wire Line
	5400 4150 5650 4150
Wire Wire Line
	7350 4850 9200 4850
Wire Wire Line
	9200 4850 9200 5100
Wire Wire Line
	7200 4950 8950 4950
Wire Wire Line
	8950 4950 8950 5100
Wire Wire Line
	8600 6050 8600 6000
Wire Wire Line
	7050 5050 8600 5050
Wire Wire Line
	8600 5050 8600 5400
NoConn ~ 5400 2250
Wire Wire Line
	9550 2500 10050 2500
Wire Wire Line
	9550 1300 9550 2500
Wire Wire Line
	9550 1300 3400 1300
Wire Wire Line
	3400 1300 3400 1650
Connection ~ 3400 1650
Connection ~ 9650 3050
Connection ~ 9850 3150
Connection ~ 9750 3250
$Comp
L +3V3 #PWR056
U 1 1 564438AB
P 1600 5600
F 0 "#PWR056" H 1600 5450 50  0001 C CNN
F 1 "+3V3" H 1600 5740 50  0000 C CNN
F 2 "" H 1600 5600 60  0000 C CNN
F 3 "" H 1600 5600 60  0000 C CNN
	1    1600 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 2100 9850 3150
Wire Wire Line
	9650 2400 9650 3050
Wire Wire Line
	9750 2300 9750 3250
$Comp
L GND #PWR057
U 1 1 5644381C
P 2450 5800
F 0 "#PWR057" H 2450 5550 50  0001 C CNN
F 1 "GND" H 2450 5650 50  0000 C CNN
F 2 "" H 2450 5800 60  0000 C CNN
F 3 "" H 2450 5800 60  0000 C CNN
	1    2450 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2950 10100 2950
Wire Wire Line
	2500 5700 2450 5700
Wire Wire Line
	2450 5700 2450 5800
Text HLabel 2150 5400 0    60   Input ~ 0
MISO_RF
Text HLabel 2150 5500 0    60   Output ~ 0
MOSI_RF
Text HLabel 2150 5300 0    60   Output ~ 0
SCK_RF
Wire Wire Line
	2150 5400 2500 5400
Wire Wire Line
	7650 2950 7650 2550
Wire Wire Line
	7650 2550 5400 2550
$Comp
L R R16
U 1 1 566309B4
P 9450 5250
F 0 "R16" V 9530 5250 50  0000 C CNN
F 1 "180R" V 9450 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9380 5250 30  0001 C CNN
F 3 "" H 9450 5250 30  0000 C CNN
	1    9450 5250
	-1   0    0    1   
$EndComp
$Comp
L LED D4
U 1 1 56630A1E
P 9450 5750
F 0 "D4" H 9450 5850 50  0000 C CNN
F 1 "LED" H 9450 5650 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 9450 5750 60  0001 C CNN
F 3 "" H 9450 5750 60  0000 C CNN
	1    9450 5750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR058
U 1 1 56630A8F
P 9450 6050
F 0 "#PWR058" H 9450 5800 50  0001 C CNN
F 1 "GND" H 9450 5900 50  0000 C CNN
F 2 "" H 9450 6050 60  0000 C CNN
F 3 "" H 9450 6050 60  0000 C CNN
	1    9450 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 5400 9450 5550
Wire Wire Line
	9450 5950 9450 6050
Wire Wire Line
	5400 1950 7050 1950
Wire Wire Line
	7050 1950 7050 5050
Wire Wire Line
	5400 1850 7200 1850
Wire Wire Line
	7200 1850 7200 4950
Wire Wire Line
	5400 1750 7350 1750
Wire Wire Line
	7350 1750 7350 4850
Wire Wire Line
	5400 1650 7500 1650
Wire Wire Line
	7500 1650 7500 4750
Wire Wire Line
	7500 4750 9450 4750
Wire Wire Line
	9450 4750 9450 5100
Wire Wire Line
	2150 5300 2500 5300
Wire Wire Line
	2500 5500 2150 5500
Text GLabel 5600 2050 2    60   Output ~ 0
CS_EXT
Text GLabel 2150 5200 0    60   Input ~ 0
CS_EXT
Wire Wire Line
	1600 5600 2500 5600
Wire Wire Line
	2150 5200 2500 5200
Wire Wire Line
	7950 2400 7950 2350
Wire Wire Line
	5400 2050 5600 2050
Wire Wire Line
	5400 2150 5600 2150
NoConn ~ 5400 2950
$EndSCHEMATC