.title OPA_CMRR

.include 'OPA.cdl'

x1 1 2 3 4 5 OPAMP
* 1 vip
* 2 vin
* 3 vout
* 4 VDD
* 5 VSS
VDD 4 0 DC  2.5 
VSS 0 5 DC  2.5
CL 3 0 10P
.PARAM VCM=1
VCM1 1 0 DC 0 AC VCM
VCM2 2 3 DC 0 AC VCM 

.ac dec 10 1 1g
.print ac vdb(3) vp(3)
* Vout / Vcm = 1 / CMRR		Allen eq. 6.6-3, fig. 6.6-7
* cmrr_db = - (vdb(3))   	即，仅正负号区别
* cmrr_phase = - (vp(3))  即，仅正负号区别
* use expression builder to display cmrr information

.temp 27								* 仿真温度27度
.option post accurate probe

.end