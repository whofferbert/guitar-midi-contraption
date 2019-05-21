# guitar-midi-contraption
The funnest contraption. Not limited to guitars!

---

A collection of scripts for various pieces of hardware, which allow for wireless midi signalling with analog electronics

Most things like IPs and ports are coded in the files you would expect, without a central config or build script.

---

# RPI

rpi/tcp-data-to-midi_server
rpi/midiThing.py

The script and class file for getting things running on the raspberry pi.

TCP server + midi data transmission.

Relies on os.system and some linux commands.
Not a terrible problem I think, because: Raspberry Pi.

---

# Teensy LC

teensyLC/teensy_lc_to_esp.ino

The script that does the work of monitoring analog inputs and passing the data via serial to ESP8266

Does an okay job, but no sanity checking that the ESP got the right data.

---

# ESP8266

esp8266/esp8266_serial_to_wifi_server.ino

The script to read serial data from the Teensy LC and push it via WiFi to the rpi.

No sanity checking that it got the right data from the Teensy.

Also (worse probably) no sanity checking that the Pi got the right data.

Still works!

---

# Problems

Probably the rpi script needs work and could be more pythonic.

Probably the rest of it needs more polishing.

If the rpi server stops for some reason, the esp8266 will not reconnect until a power off/on (or reset)

sometimes with power on, it seems to not initially update the midi state (IE midi switch is off, but software has state on, switch needs to be turned on and then off to put the software into an off state.)
