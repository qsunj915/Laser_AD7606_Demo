### README

***

*file name: Laser_AD7606_Demo* 

*update time: 2021/7/16*



该模块的量程为0-10V，不可更改（理论上可更改）

## Tips

* 接线：

  | AD7606                    | MCU            |
  | ------------------------- | -------------- |
  | D0-D6,D8-D15              | GND/浮空       |
  | D7(MISO)                  | A6             |
  | FD&BUSY                   | 浮空           |
  | GND                       | GND            |
  | 5V                        | **电源管理5V** |
  | CS (NSS)                  | A4             |
  | RD (SCK)                  | A5             |
  | CB-CA (默认短接) (CONVST) | **A1**         |
  | RANGE                     | 3V3(推荐)/C8   |
  | OS1                       | GND(推荐)/E3   |
  | OS2                       | GND(推荐)/E4   |
  | OS0                       | GND(推荐)/E2   |

* 使用说明：

  * 采样数据由TIM3中断得到,200Hz
  * 可通过 *Get_AD7606_voltdata* 得到所需通道的电压值

* 提供的参考资料中的程序有问题，自行取舍

