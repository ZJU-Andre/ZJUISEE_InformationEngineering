.title gm_complex

.SUBCKT OTA_gm Ibias gnd vcmfb vdd vin vip voutn voutp
R1 net39 net29 9000
Mbias Ibias Ibias gnd gnd n18 W=20u L=1u M=1
M1 voutn vip net39 gnd n18 W=75u L=2u M=1
M2 voutp vin net29 gnd n18 W=75u L=2u M=1
M3 net39 Ibias gnd gnd n18 W=20u L=1u M=1
M4 net29 Ibias gnd gnd n18 W=20u L=1u M=1
M5 voutp net0124 vdd vdd p18 W=158u L=2u M=1
M6 voutn net0124 vdd vdd p18 W=158u L=2u M=1
M7 net0124 net0124 vdd vdd p18 W=158u L=2u M=1
M8 vdd voutn net065 gnd n18 W=75u L=2u M=1
M9 net0124 vcmfb net065 gnd n18 W=75u L=2u M=1
M10 net0124 vcmfb net053 gnd n18 W=75u L=2u M=1
M11 vdd voutp net053 gnd n18 W=75u L=2u M=1
Mtail1 net065 Ibias gnd gnd n18 W=20u L=1u M=1
Mtail2 net053 Ibias gnd gnd n18 W=20u L=1u M=1
.ENDS

.SUBCKT ОTА_frequency_move_1 Ibias gnd vcmfb vdd vin vip voutn voutp
R1 net39 net29 2000
.ENDS

.SUBCKT OTА_frequency_move_2 Ibias gnd vcmfb vdd vin vip voutn voutp
R1 net39 net29 4000
.ENDS

.SUBCKT gyrator3 Ibias cap_connect_1 cap_connect_2 gnd vcmfb vdd vin vip voutn voutp
XI37 Ibias gnd vcmfb vdd vin vip cap_connect_1 cap_connect_2 OTA_gm
XI38 Ibias gnd vcmfb vdd cap_connect_2 cap_connect_1 vin vip OTA_gm
XI39 Ibias gnd vcmfb vdd voutp voutn cap_connect_1 cap_connect_2 ОTА_gm
XI40 Ibias gnd vcmfb vdd cap_connect_1 cap_connect_2 voutn voutp OTA_gm
.ENDS

.SUBCKT GM_c_3th_bandpass Ib1 Ib2 Ib3 Ib4 Ib5 Ib6 Ibias Ibias1 Ibias1_b Ibias_b gnd

XI78 Ib1 gnd vcmfb vdd net143 net144 net120 net119 OTA_frequency_move_1
XI79 Ib2 gnd vcmfb vdd net120 net119 net144 net143 OTA_frequency_move_1
XI80 Ib5 gnd vcmfb vdd net2 net1 net1b net2b / OTA_frequency_move_2
XI81 Ib6 gnd vcmfb vdd net1b net2b net1 net2 / OTA_frequency_move_2
XI82 Ib3 gnd vcmfb vdd vout_IB vout_I vout_Q vout_QB OTA_frequency_move_1
XI83 Ib4 gnd vcmfb vdd vout_Q vout_QB vout_I vout_IB OTA_frequency_move_1
XI72 Ibias1 net1 net2 gnd vcmfb vdd net144 net143 vout_IB vout_I / gyrator3
XI73 Ibias1_b net1b net2b gnd vcmfb vdd net120 net119 vout_QB vout_Q / gyrator3
XI76 Ibias_b gnd vcmfb vdd net119 net120 net120 net119 / OTA_gm
XI75 Ibias_b gnd vcmfb vdd vin_QB vin_Q net120 net119 / OTA_gm
XI74 Ibias_b gnd vcmfb vdd vout_QB vout_Q vout_Q vout_QB / OTA_gm
XI71 Ibias gnd vcmfb vdd vin_IB vin_I net144 net143 / OTA_gm
XI45 Ibias gnd vcmfb vdd net143 net144 net144 net143 / OTA_gm
XI48 Ibias gnd vcmfb vdd vout_IB vout_I vout_I vout_IB / OTA_gm
.ENDS


x1 Ib1 1b2 Ib3 Ib4 Ib5 Ib6 Ibias Ibias1 Ibias1_b Ibias_b gnd 
+vcmfb vdd vin_I vin_IB vin_Q vin_QB vout_I vout_IB vout_Q vout_QB GM_c_3th_bandpass 
Iibias vdd ibias 300u
Iibias1 vdd ibias1 400u
Iibias_b vdd ibias_b 300u
Iibias1_b vdd ibias1_b 400u
Ilb1 vdd ib1 100u
IIb2 vdd ib2 100u
IIb3 vdd ib3 100u
IIb4 vdd ib4 100u
ITb5 vdd ib5 100u
IIb6 vdd ib6 100u
vvcmfb vcmfb 0 0.9
vvdd vdd 0 1.8
vgnd gnd 0 0
vvin_I vin_I 0 sin(0.9 0.005 6meg 0 0 0)
vvin_IB vin_IB 0 sin(0.9 0.005 6meg 0 0 180)
vvin_Q vin_Q 0 sin(0.9 0.005 6meg 0 0 90)
vvin_QB vin_QB 0 sin(0.9 0.005 6meg 0 0 270)


.tf v(vout_I) vvin_I
.temp 27
.lib 'E:\EE\project\spice\2.0\ms018.lib' tt
.op
.noise v(vout_I) vvin_I 10
.ac dec 10 10 10g
.option post accurate probe nomod captab
.probe noise inoise onoise
.probe vdb(vout_I) vp(vout_I)
.tran 0.1n 150u
.option post accurate probe nomod captab 1
.probe v(vin_I) v(vout_I) v(vin_IB) v(vout_IB) 1
.fft v(vout_I) np=32768 start=1u stop=100u fmin=100 fmax=11meg
.end
