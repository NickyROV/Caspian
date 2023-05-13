# Caspian
Caspian stems from England, but means “from Qazvin, Iran.” It’s the name of the salty sea located between Asia and Europe. The Caspian Sea is the world's largest Inland body of water, often described as the largest lake or a full-fledged sea.

Caspian is 4-DOF ROV with 2-3 claw, 6 Channel RC1 to control ROV ans 6 Channel RC2 as robotic arm control.

Top-side and on-board control hardware : Arduino MEGA

Status indicator : RC to top side control and top side to underwater data package delivery

RC to top-side MEGA Digital input, status check with LED as indicator. 

UART Serial Data package format <CH1><CH2><CH3><CH4><CH5><CH6><CH7><CH8><CH9><CH10><CH11><CH12>, on-board MEGA unpack the package and acknowledge once data intact. Status check with LED as indicator

# Data package protocol
Top-side control pack 12 channel data with delimiter "<" and ">", terminate with carriage return and line feed. Underwater un-pack by removing "<" and ">", acknowledge when Serial.Read = line feed. 
  
# Data Verification Protocol
RC Verification Indicator - When data communication checked between RC (2 units) and top side electronic control (MEGA). Methodology - Check corresponding Digital-Signal-IN for RC1Channel1 and RC2 Channel are greater than 0, or it can also be done by checking within PWM range (1000<=signal<=2000).
  
Tether Communication Acknowledge - Underwater electronic control (MEGA) send Acknowledge signal when received data package Checked. Methodology - Top-side MEGA pack data in <DATA><DATA>...<DATA> format and terminated with line feed character -> Underwater MEGA un-pack, check and once reach lind feed, Acknowledge "A" will be sent to top-side -> Top-side MEGA pick up "A" as confirmation of transmision.

Media - UART
