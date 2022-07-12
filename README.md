# LDN Debug Logger

A mitm sysmodule to log all IPC calls to `ldn:u` and `wlan:lcl`.

## References

### wlan:lcl

- [WLAN swipcgen_server_modern.info](https://yls8.mtheall.com/ninupdates/sysupdatedl/autodl_sysupdates/2021-09-15_00-05-06-hac/0100000000000016/ALL/v872415452/swipcgen_server_modern.info)
- [WLAN services](https://switchbrew.org/wiki/WLAN_services)
- [MissionControl](https://github.com/ndeadly/MissionControl)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) (Stratosphère ams_mitm)

### ldn:u

- [LDN swipcgen_server_modern.info](https://yls8.mtheall.com/ninupdates/sysupdatedl/autodl_sysupdates/2022-03-22_00-05-06-hac/0100000000000018/ALL/v939525336/swipcgen_server_modern.info)
- [LDN services](https://switchbrew.org/wiki/LDN_services)
- [MissionControl](https://github.com/ndeadly/MissionControl)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) (Stratosphère ams_mitm)
- [Libnx](https://switchbrew.github.io/libnx/ldn_8h.html)
- [ldn_mitm](https://github.com/spacemeowx2/ldn_mitm)

## Credits

Thank you to the ReSwitched Discord server for answering a lot of my questions and helping me understand IPC a bit better.

In particular I want to thank the following people:

- [@ndeadly](https://github.com/ndeadly) for guiding me through the process of getting this module to work, letting me use a lot of his [MissionControl](https://github.com/ndeadly/MissionControl) code and explaining a lot of mitm stuff.
- [@SciresM](https://github.com/SciresM) for helping with the countless issues I encounter and explaining everything I don't understand.
- [@misson20000](https://github.com/misson20000) for creating [twili](https://github.com/misson20000/twili) and [ilia](https://github.com/misson20000/ilia) which I used for debugging wlan.
- [@yellows8](https://github.com/yellows8) for creating the [Nintendo System Update reports](https://yls8.mtheall.com/) website, which I used a lot during reverse engineering and creating this sysmodule.
- [SwitchBrew](https://switchbrew.org/wiki/Main_Page) for documenting [LDN services](https://switchbrew.org/wiki/LDN_services) and [WLAN services](https://switchbrew.org/wiki/WLAN_services) which gave me an inital understanding of the services hosted by the sysmodules.
- [@spacemeowx2](https://github.com/spacemeowx2/) for creating [ldn_mitm](https://github.com/spacemeowx2/ldn_mitm), the basis of the first version of this module.
- [@Lenrow](https://github.com/Lenrow) for enduring me only talking about this topic for the last few days.
