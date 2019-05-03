# guitar-midi-contraption
A collection of scripts for various pieces of hardware, which allow for wireless midi signalling with analog electronics

Most things like IPs and ports are coded in multiple files, without a central config or build script.

---

# RPI

The script and class file for getting things running on the raspberry pi.

TCP server + midi data transmission.

Relies on os.system and some linux commands.
Not a terrible problem I think, because: Raspberry Pi.

---

# Teensy LC

The script that does the work of monitoring analog inputs and passing the data via serial to ESP8266

Does an okay job, bot no sanity checking that the ESP got the right data.

---

# ESP8266

The script to read serial data from the Teensy LC and push it via WiFi to the rpi.

No sanity checking that it got the right data from the Teensy.

Also (worse) no sanity checking that the Pi got the right data.

Still works

---

# Problems

Pi script still is not configured to send midi data to the amidithru object, but that will be simple to implement.

No sanity checking or SYN/ACK style reliability (aside from what the ESP does by default because of TCP)

probably the rpi script needs work and could be more pythonic.

probably the rest of it needs more polishing.
