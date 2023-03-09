.title OPA_unity_gain

.include 'OPA.cdl'

x1 1 3 3 4 5 OPAMP
* 1 vip
* 2 vin
* 3 vout
* 4 VDD
* 5 VSS
VDD 4 0 DC  2.5 
VSS 0 5 DC  2.5
vvip 1 0 PWL(0 -2 10N -2 20N 2 2U 2 2.01U -2 4U -2 4.01U
+ -0.1 6U -0.1 6.01U 0.1 8U 0.1 8.01U -0.1 10U -0.1)
CL 3 0 10P

.tf v(3) vvip		    		* 计算小信号传输函数
.dc vvip -2.5 2.5 0.1		* 直流仿真，设置扫描变量，
.print dc v(3)	id(x1.m5)											
.tran 0.05U 10U 0 10n
.print tran v(3) v(1)

.temp 27								* 仿真温度27度
.option post accurate probe

.end