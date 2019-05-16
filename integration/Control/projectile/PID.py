from __future__ import print_function, absolute_import, division
import time
import sys

class PID:

    def __init__(self, dt=0.05, Kp=0, Ki=0, Kd=0):

        self.dt = dt
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.reset()

    def feedback(self, err):

        if type(self.err_p) == type(None):
            self.err_p = err
        self.errsum += err*self.dt
        d_err = (err-self.err_p)/self.dt
        self.err_p = err

        return self.Kp*err+self.Ki*self.errsum+self.Kd*d_err

    def reset(self):
        self.err_p = None
        self.errsum = 0.0