# ldn_logger

A mitm sysmodule to log all arguments and objects going through LDN.

Forked from [ldn_mitm](https://github.com/spacemeowx2/ldn_mitm).

## Progress

- [x] Implement all IUserLocalCommunicationService shims
- [x] Don't crash the console immediately
- [ ] Fix broken functions
- [ ] Log everything in a nice format

## References

- [LDN swipcgen_server_modern.info](https://yls8.mtheall.com/ninupdates/sysupdatedl/autodl_sysupdates/2022-03-22_00-05-06-hac/0100000000000018/ALL/v939525336/swipcgen_server_modern.info)
- [LDN services](https://switchbrew.org/wiki/LDN_services)
- [MissionControl](https://github.com/ndeadly/MissionControl)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) (Stratosphère mitm sysmodules)
- [Libnx](https://switchbrew.github.io/libnx/ldn_8h.html)

## Credits

Thank you to the ReSwitched Discord server for answering a lot of my questions and helping me understand IPC a bit better.

In particular I want to thank the following people:

- [@ndeadly](https://github.com/ndeadly) for helping me figure out how to write a mitm sysmodule and answering my questions.
- [@SciresM](https://github.com/SciresM) for helping with the countless issues I encounter and explaining everything I don't understand.
- [@misson20000](https://github.com/misson20000) for creating [twili](https://github.com/misson20000/twili) and [ilia](https://github.com/misson20000/ilia) which I used as a starting point for debugging LDN.
- [@Narr the Reg](https://github.com/german77) for reverse engineering LDN and helping me understand the structure of IPC command functions better.
- [@yellows8](https://github.com/yellows8) for creating the [Nintendo System Update reports](https://yls8.mtheall.com/) website, which I used a lot during reverse engineering and creating this sysmodule.
- [@spacemeowx2](https://github.com/spacemeowx2/) for creating [ldn_mitm](https://github.com/spacemeowx2/ldn_mitm), the basis of this sysmodule.
- [SwitchBrew](https://switchbrew.org/wiki/Main_Page) for documenting [LDN services](https://switchbrew.org/wiki/LDN_services) which helped a lot for understanding LDN in general.
