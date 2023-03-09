.title gm_ac

.SUBCKT OTA Ibias gnd vcmfb vdd vin vip voutn voutp
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

.SUBCKT gm_c_3th_lowpass Ibias gnd vcmfb vdd vin_I vin_IB vout_I vout_IB 
XI45 Ibias gnd vcmfb vdd net055 net056 net056 net055 / OTA
XI49 Ibias gnd vcmfb vdd vout_IB vout_I net84 net83 / OTA
XI46 Ibias gnd vcmfb vdd net056 net055 net84 net83 / OTA
XI47 Ibias gnd vcmfb vdd net84 net83 vout_I vout_IB / OTA
XI1  Ibias gnd vcmfb vdd vin_IB vin_I net056 net055 / OTA
XI44 Ibias gnd vcmfb vdd net83 net84 net056 net055 / OTA
XI48 Ibias gnd vcmfb vdd vout_IB vout_I vout_I vout_IB/ OTA
CC1 net056 gnd 8.815p
CC2 net055 gnd 8.815p
CC3 net84 gnd 4.331p
CC4 net83 gnd 4.331p
CC5 vout_I gnd 8.815p
CC6 vout_IB gnd 8.815p
.ENDS

x1 Ibias gnd vcmfb vdd vin_I vin_IB vout_I vout_IB gm_c_3th_lowpass
Iibias vdd ibias 700u
vvdd vdd 0 1.8
vgnd gnd 0 0
vvcmfb vcmfb 0 0.9
vvin_I vin_I 0 0.9 ac 1 0
vvin_IB vin_IB 0 0.9 ac 1 180

.tf v(vout_I) vvin_I
.temp 27
.lib 'E:\EE\project\spice\2.0\ms018.lib' tt
.op
.noise v(vout_I) vvin_I 10
.ac dec 10 10 10g
.option post accurate probe nomod captab
.probe noise inoise onoise
.probe vdb(vout_I) vp(vout_I)
.end
