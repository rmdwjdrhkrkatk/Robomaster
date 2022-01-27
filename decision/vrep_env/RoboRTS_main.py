import numpy as np
from RoboRTS_env3 import RoboRTS
import os
from api import vrep

episodes = 1000
is_batch_norm = True

def main():
    env = RoboRTS()
    
    counter = 0
    step = 0

    for i in range(episodes):
        print ("==== Starting episode no:", i, "====","\n")
        observation = env.reset()
        while True:

            x = observation
            
            env.step()
            
        step += 1


if __name__ == '__main__':
    main()  

       