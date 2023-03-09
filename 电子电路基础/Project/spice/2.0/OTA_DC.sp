.title OTA_DC

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

x1 Ibias gnd vcmfb vdd vin vip voutn voutp OTA
Iibias vdd ibias 100u
vvcmfb vcmfb gnd 0.9
vvdd vdd 0 1.8
vgnd gnd 0 0
vvin vin 0 0.9 ac 1 0
vvip vip 0 0.9 ac 1 180

.tf v(voutn) vvin
.noise v(voutp) vvip 10
.temp 27
.lib 'E:\EE\project\spice\2.0\ms018.lib' tt
.op
.ac dec 10 10 10g
.option post accurate probe
.probe noise inoise onoise
.probe vdb(voutn) vp(voutn)
.end
