# Caspian
Caspian stems from England, but means “from Qazvin, Iran.” It’s the name of the salty sea located between Asia and Europe.

Caspian is 4-DOF ROV with 2-3 claw, 6 Channel RC1 to control ROV ans 6 Channel RC2 as robotic arm control.

Top-side and on-board control hardware : Arduino MEGA

Status indicator : RC to top side control and top side to underwater data package delivery

RC to top-side MEGA Digital input, status check with LED as indicator. 

UART Serial Data package format <CH1><CH2><CH3><CH4><CH5><CH6><CH7><CH8><CH9><CH10><CH11><CH12>, on-board MEGA unpack the package and acknowledge once data intact. Status check with LED as indicator
