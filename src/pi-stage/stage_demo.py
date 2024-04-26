from pipython.pidevice.interfaces.piserial import PISerial
from pi_stage import Stage

import time

with PISerial(port="/dev/ttyUSB0", baudrate=115200) as X_gateway:  # open X axis
    with PISerial(port="/dev/ttyUSB1", baudrate=115200) as Y_gateway:  # open Y axis

        stage = Stage(X_gateway, Y_gateway)

        # let's make some moves
        stage.move(5,0)

        stage.move(5,5)

        stage.move(0,5)

        stage.move(0,0)

