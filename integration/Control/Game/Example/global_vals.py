#
# This module contains global constants that are used throughout the game.
#

# Nr of dishes to eat

STEPMAX = 300
# Maximum number of steps until the game terminates. 

SCALE = 1
WIDTH, HEIGHT = 800, 500  # 실제로는 8000*5000
# Screen resolution

X_MAX = (WIDTH * SCALE  // 2) - (47 // 2)
Y_MAX = (HEIGHT * SCALE // 2) - (47 // 2)
# Max coordinate values for pacman to prevent it from leaving the screen.

MS_TO_QUIT = 2000
# Milli-seconds from termination to removal of window.
# We give the user some time to read the "Game Over..." message.



