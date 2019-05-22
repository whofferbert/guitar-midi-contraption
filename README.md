# guitar-midi-contraption
The funnest contraption. Not limited to guitars!

Parts + Teensy LC + ESP8266 + Raspberry Pi 3B+ = wireless midi!

This project is a collection of scripts for various pieces of hardware, which allow for wireless midi signalling with analog electronics

Things like IPs and ports are coded in the files you would expect them to be. There are not many files (just a lot of moving parts)

---

# Background

It should be easy enough for anyone to tweak the code as need be, to suit their own needs.

This software, as is, currently operates attached to an electric guitar, which in turn is connected to a raspberry pi running MODEP, from BlokasLabs:\
MODEP: https://github.com/BlokasLabs/modep

The Teensy LC and the ESP8266 reside in the guitar, monitoring some potentiometers and switches, then sending that data to the Raspberry Pi wirelessly.

The Raspberry Pi runs an additional server (tcp-data-to-midi_server), which translates the analog values gotten by ResponsiveAnalogRead and Bounce2 into the midi-compatible 0-127 range:
ResponsiveAnalogRead: https://github.com/dxinteractive/ResponsiveAnalogRead\
Bounce2: https://github.com/thomasfredericks/Bounce2

That midi information is pushed out of the server via an amidithru (BlokasLabs again) device, which the MODEP software can connect to/use in various ways.

---

# RPI

rpi/tcp-data-to-midi_server\
rpi/midiThing.py

The script and class file for getting things running on the Raspberry Pi (Pi 3 B+ used in this case, with MODEP).

TCP server + midi data transmission to whatever it gets connected to.

PROBLEMS:

Relies on os.system and some linux commands.\
Not a real terrible problem I think, because: Raspberry Pi.

---

# Teensy LC

teensyLC/teensy_lc_to_esp.ino

The script that does the work of monitoring analog inputs and passing the data via serial to ESP8266

PROBLEMS:

Does an okay job, but no sanity checking that the ESP got the right data.

---

# ESP8266

esp8266/esp8266_serial_to_wifi_server.ino

The script to read serial data from the Teensy LC and push it via WiFi to the rpi.

PROBLEMS:

No sanity checking that it got the right data from the Teensy.

Also (worse probably) no sanity checking that the Pi got the right data.

Still works!

---

# More Problems

Probably the rpi script needs work and could be more pythonic.

Probably the rest of it needs more polishing.

If the rpi server stops for some reason, the esp8266 will not reconnect until a power off/on (or reset)

sometimes with power on, it seems to not initially update the midi state (IE midi switch is off, but software has state on, switch needs to be turned on and then off to put the software into an off state.)


