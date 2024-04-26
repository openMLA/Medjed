from pipython.pidevice.gcscommands import GCSCommands
from pipython.pidevice.gcsmessages import GCSMessages
from pipython import pitools

import time

class Stage:
    '''
    Minimal stage object for two PI C-663.11 axes
    
    The stages are assumed to be connected separately (e.g. on two different USB-to-RS232 adapters),
    rather than connected in series through the RS232 daisy chaining functionality. Consult the 
    documentation for pipython and the MS163E Software Manual on GCS Commands. The latter can
    be used to send a greater set of commands, through the more manual axis.send({cmd_string})
    and axis.read({cmd_string}) approach.
    '''
    def __init__(self, x_gateway, y_gateway):
        self.Xaxis = GCSCommands(GCSMessages(x_gateway))
        self.Yaxis = GCSCommands(GCSMessages(y_gateway))

        # for axis 1 (only 1 axis connected per controller) disable joystick
        # this particular controller was used with controller and I think maybe there
        # is some startup macro setting it to joystick mode. Anyway, lets turn it off upon
        # initialisation.
        self.Xaxis.send("JON 1 0")  
        self.Yaxis.send("JON 1 0")  

        print(f"Axis velocity: X={self.Xaxis.read('VEL?')}, Y={self.Yaxis.read('VEL?')}")
        print(f"Max velocity: X={self.Xaxis.read('SPA? 1 10')}, Y={self.Yaxis.read('SPA? 1 10')}")

    def move(self, x_target, y_target, wait=True):
        self.Xaxis.MOV(1, x_target) 
        self.Yaxis.MOV(1, y_target)

        if wait:  # wait for stages to reach target (blocking)
            pitools.waitontarget(self.Xaxis, 1)
            pitools.waitontarget(self.Yaxis, 1)

            print(f"Stage move complete. Stage is at {self.Xaxis.qPOS()['1']},{self.Yaxis.qPOS()['1']}")

    def get_position(self):
        posX = self.Xaxis.qPOS()['1']
        posY = self.Yaxis.qPOS()['1']
        return (posX, posY) 
