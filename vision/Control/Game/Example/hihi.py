
import global_vals
# Import our own constants
from game import Tank, tanktop, Bullet, Wall
# Import our game character classes
import numpy as np

import turtle
import random

def shutDownHander():
  """Outputs score and terminates the program"""
  global score
  print('Your score:', score)
  window.bye()

def get_intersect(a1, a2, b1, b2):
    """
    Returns the point of intersection of the lines passing through a2,a1 and b2,b1.
    a1: [x, y] a point on the first line
    a2: [x, y] another point on the first line
    b1: [x, y] a point on the second line
    b2: [x, y] another point on the second line
    """
    s = np.vstack([a1,a2,b1,b2])        # s for stacked
    h = np.hstack((s, np.ones((4, 1)))) # h for homogeneous
    l1 = np.cross(h[0], h[1])           # get first line
    l2 = np.cross(h[2], h[3])           # get second line
    x, y, z = np.cross(l1, l2)          # point of intersection
    if z == 0:                          # lines are parallel
        return (float('inf'), float('inf'))
    return (x/z, y/z)

# if __name__ == "__main__":
#     print(get_intersect((0, 1), (0, 2), (1, 10), (1, 9)) ) # parallel  lines
#     print(get_intersect((0, 1), (0, 2), (1, 10), (2, 10))) # vertical and horizontal lines
#     print(get_intersect((0, 1), (1, 2), (0, 10), (1, 9)))  # another line for fun


def hitWall(bullet, wall):
    global isQuit
    # left_low, right_low, left_high, right_high
    prev_bullet_position = bullet.prevPosition
    curr_bullet_position = bullet.getPosition()

    # left, right, high, low
    sides = wall.sides()
    #
    for side in sides:

        inter = get_intersect(side[0], side[1], prev_bullet_position, curr_bullet_position)
        # print(prev_bullet_position, curr_bullet_position)
        if ( min(prev_bullet_position[0], curr_bullet_position[0]) < inter[0] < max(prev_bullet_position[0], curr_bullet_position[0]) )\
                and ( min(side[0][0], side[1][0]) < inter[0] < max(side[0][0], side[1][0]) ):
            print(side[0], side[1], inter)

            return True

        if ( min(prev_bullet_position[1], curr_bullet_position[1]) < inter[1] < max(prev_bullet_position[1], curr_bullet_position[1]) )\
                and ( min(side[0][1], side[1][1]) < inter[1] < max(side[0][1], side[1][1]) ):
            print(side[0], side[1], inter)

            return True

    return False


def hitTank(bullet, tank):
    pass

def periodicTimer():

  global phase
  global isQuit
  global food
  global score
  turtle.tracer(0, 0) # disable screen updates

  for bullet in Bullet.all:
    bullet.fly()

    for wall in Wall.all:
        if hitWall(bullet, wall):
            bullet.ttl.hideturtle()
            Bullet.all.remove(bullet)
            break



  turtle.tracer(1, 10) # re-enable periodic screen updates
  tank_pos = tank.getPosition()



  if isQuit:
    # Game will terminate, put the "Game Over" image:
    game_over.setposition(0, -global_vals.HEIGHT//2 + 22)
    game_over.shape('game_over.gif')
    game_over.showturtle()
    # Trigger the shutdown handler function to be called in MS_TO_QUIT ms
    # from now:
    window.ontimer(shutDownHander, global_vals.MS_TO_QUIT)
  else:
    # Trigger the next firing of our timer function, in 90ms from now:
    window.ontimer(periodicTimer, 5)


def Foward():
    tank_pos = tank.getPosition()
    tank.goForward()

def Backward():
    tank_pos = tank.getPosition()
    tank.goBackward()



def TurnLeft():
    tank_pos = tank.getPosition()
    tank.turnCCW()


def TurnRight():
    tank_pos = tank.getPosition()
    tank.turnCW()


def GunLeft():
    tank.gun.rotateCCW()

def GunRight():
    tank.gun.rotateCW()


def quitKeyHandler():
  global isQuit
  isQuit = True


isQuit = False
score = 0
turtle.setup(global_vals.WIDTH, global_vals.HEIGHT)
window = turtle.Screen()
window.title('Robomaster')
window.bgcolor('white')

turtle.register_shape('game_over.gif')

def Fire():
    tank.gun.fire(tank.getPosition(), tank)



# Wall(x, y, width, height)
width = global_vals.WIDTH
height = global_vals.HEIGHT

Wall(0, height/2 + 5, width+20, 10)
Wall(0, -height/2 - 5, width+20, 10)  # top and bottom

Wall(width/2 + 5, 0, 10, height)
Wall(-width/2 - 5, 0, 10, height)  # sides

Wall(0, height/2-25, 100, 50)
Wall(0, -height/2+25, 100, 50)  # D

Wall(0, 0, 100, 25)  #center


Wall(width/2 - 140 - 12.5, 50, 25, 100)
Wall(-width/2 + 140 + 12.5, -50, 25, 100)


tank = Tank(100, 100)

# Prepare the "game over" turtle already:
game_over = turtle.Turtle()
game_over.hideturtle()
game_over.speed('fastest')
# Install the keyboard handlers:
window.onkey(TurnRight, 'd')
window.onkey(TurnLeft,  'a')
window.onkey(Foward,    'w')
window.onkey(Backward,  's')

window.onkey(GunLeft,  'Left')
window.onkey(GunRight,  'Right')

window.onkey(Fire,  'space')

window.onkey(quitKeyHandler,  'q')
periodicTimer()

window.listen()
window.mainloop()
