# wlan_logger

A mitm sysmodule to log all arguments and objects going through `wlan:lcl`.

These mitm logging modules might get merged into one module at some point, but for now I'll leave them separate.

## References

- [WLAN swipcgen_server_modern.info](https://yls8.mtheall.com/ninupdates/sysupdatedl/autodl_sysupdates/2021-09-15_00-05-06-hac/0100000000000016/ALL/v872415452/swipcgen_server_modern.info)
- [WLAN services](https://switchbrew.org/wiki/WLAN_services)
- [MissionControl](https://github.com/ndeadly/MissionControl)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) (Stratosphère ams_mitm)

## Credits

Thank you to the ReSwitched Discord server for answering a lot of my questions and helping me understand IPC a bit better.

In particular I want to thank the following people:

- [@ndeadly](https://github.com/ndeadly) for guiding me through the process of getting this module to work and explaining a lot of mitm stuff.
- [@SciresM](https://github.com/SciresM) for helping with the countless issues I encounter and explaining everything I don't understand.
- [@misson20000](https://github.com/misson20000) for creating [twili](https://github.com/misson20000/twili) and [ilia](https://github.com/misson20000/ilia) which I used for debugging wlan.
- [@yellows8](https://github.com/yellows8) for creating the [Nintendo System Update reports](https://yls8.mtheall.com/) website, which I used a lot during reverse engineering and creating this sysmodule.
- [SwitchBrew](https://switchbrew.org/wiki/Main_Page) for documenting [WLAN services](https://switchbrew.org/wiki/WLAN_services) which gave me an inital understanding of the services hosted by the wlan sysmodule.


You might also want to take a look at [ldn_logger](https://github.com/TSRBerry/ldn_logger) which was the first mitm logging module I created.
