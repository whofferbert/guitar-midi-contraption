#!/usr/bin/env python3
# by William Hofferbert

class midiThing(object):
    def __init__(self, channel, ccNum, startingVal):
        self.channel = channel
        self.ccNum = ccNum
        self.current = startingVal
        self.last = startingVal

    def update(self, value):
        self.last = self.current
        self.current = value

    def has_changed(self):
        # maybe this should be better...

        # testing comparing these as ints...
        if (int(float(self.last)) != int(float(self.current))):
             return 1
        else:
             return 0

