# LWHS Adaptive Game Controller

Coded with PlatformIO, designed for an Amazon Arduino ProMicro knockoff. Attach stereo plugs with one lead on a pin, the other connected to ground. Can solder directly to board or use perf board for a joint ground. Pins 2, 3, 4, 5 correspond to ports 1, 2, 3, 4 respectively (as labeled on the case).

Currently, a switch connected to port 1 will type "1," switch 2, "2," etc. This can be reprogrammed quite easily. Programmed with the "KnockoffProMicro" environment in PlatformIO.

# To-Do

- [X] Fix the bricked when starting up (until programming w/ website) issue
- [ ] Incorporate saving into EEPROM
-     [ ] Set default state at start when having empty eeprom
<!-- [ ] Where is the phantom left shift coming from? -->
[X] fix left shift—that capital characters are different unicode characters and have different keycodes, as well as left shift translating into an S, as well as cmd key not working
-     [ ] do more exhuastive testing
- [ ] add reset button functionality
- [ ] Add icon, public page
- [ ] Add error logging