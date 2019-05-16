from globals import FOODMAX,  STEPMAX, WIDTH, HEIGHT, X_MAX, Y_MAX, MS_TO_QUIT
from globals import FOOD as food, GHOSTS as ghosts
# Import our own constants

from game import ghost, dobbogi, pacman, tanktop
# Import our game character classes

import turtle
import random

def shutDownHander():
  """Outputs score and terminates the program"""
  global score
  print('Your score:', score)
  window.bye()

def checkCollision(t1, t2):
  """Input: 2 coordinate tuples.
     Return: True if the coordinates are sufficiently close
             False otherwise
  """
  if (abs(t1[0] - t2[0]) < 25) and (abs(t1[1] - t2[1]) < 25):
    return True
  return False

def periodicTimer():
  """Timer function which is called periodically by Python.
     This function implements the game logic:
     - creating all objects
     - arranging objects on the screen
     - calling object's move() methods
     - checking for collisions
     - checking for invalid moves
     - detection program termination conditions (all food eaten, ...)
     - initiate termination
  """
  global phase
  global isQuit
  global food
  global score        # pacman's achieved score
  turtle.tracer(0, 0) # disable screen updates

  # for g in ghosts:
  #   g.updateShape()   # make ghost change its shape
  #   g.move(pm)          # move ghost

  # turtle.update()      # force turtle module's screen update
  turtle.tracer(1, 10) # re-enable periodic screen updates
  # pm.decrementSteps()  # pacman made one step, decrement counter

  # check collisions pm versus ghosts:
  pm_pos = pm.getPosition()
  for g in ghosts:
    if checkCollision(pm_pos, g.getPosition()):
      isQuit = True
      print('You bumped into a ghost!')
  # check collisions pm versus food:
  # eaten_dishes = []
  # for dish in food:
  #   if checkCollision(pm_pos, dish.getPosition()):
  #     pm.setIsYum()
  #     dish.setIsEaten()
  #     eaten_dishes.append(dish)
  #     score += 1

  if isQuit:
    # Game will terminate, put the "Game Over" image:
    game_over.setposition(0, -HEIGHT//2 + 22)
    game_over.shape('game_over.gif')
    game_over.showturtle()
    # Trigger the shutdown handler function to be called in MS_TO_QUIT ms
    # from now:
    window.ontimer(shutDownHander, MS_TO_QUIT)
  else:
    # Trigger the next firing of our timer function, in 90ms from now:
    window.ontimer(periodicTimer, 90)


def Foward():
    global food
    pm_pos = pm.getPosition()
    for dish in food:
        if checkCollision(pm_pos, dish.getPosition()):
            pm.goBackward()
            return
    pm.goForward()

def Backward():
    global food
    pm_pos = pm.getPosition()
    for dish in food:
        if checkCollision(pm_pos, dish.getPosition()):
            pm.goForward()
            return
    pm.goBackward()


def TurnLeft():
    global food
    pm_pos = pm.getPosition()
    for dish in food:
        if checkCollision(pm_pos, dish.getPosition()):
            return
    pm.turnCCW()


def TurnRight():
    global food
    pm_pos = pm.getPosition()
    for dish in food:
        if checkCollision(pm_pos, dish.getPosition()):
            return
    pm.turnCW()


def GunLeft():
    pm.gun.rotateCCW()

def GunRight():
    pm.gun.rotateCW()

def Fire():
    pm.gun.fire()


def quitKeyHandler():
  """Handler function for the 'q' key."""
  global isQuit
  isQuit = True

def placeFood():
  """Compute doboggi screen positions and instantiate doboggi objects.
     Returns: a list of doboggi objects.
  """
  food = []
  Upper = True
  for i in range(0, FOODMAX):
    ok = False
    while not ok: # loop until proper position was computed:
      r_x = random.randrange(-X_MAX + 20, X_MAX - 20)
      if Upper:
        # Position above the ghosts:
        r_y = random.randrange(160, Y_MAX)
      else:
        # Position below the ghosts:
        r_y = random.randrange(-Y_MAX, -40)
      new_pos = (r_x, r_y)
      HaveCollision = False
      for i in food:
        HaveCollision = HaveCollision or checkCollision(new_pos, i.getPosition())
      if not HaveCollision:
        food.append(dobbogi(r_x, r_y))
        ok = True
    Upper = not Upper # toggle between ``above'' and ``below" ghost's
                      # screen part.
  return food

#
# Main program
#
isQuit = False  # Set to true to initiate game termination.
score = 0
turtle.setup(WIDTH, HEIGHT)
window = turtle.Screen()
window.title('Dobbogi-Man')
window.bgcolor('white')

turtle.register_shape('ghost_red_1_small.gif')
turtle.register_shape('ghost_red_2_small.gif')
turtle.register_shape('pac_open_small_east.gif')
turtle.register_shape('pac_open_small_west.gif')
turtle.register_shape('pac_open_small_north.gif')
turtle.register_shape('pac_open_small_south.gif')
turtle.register_shape('pac_wopen_small_east.gif')
turtle.register_shape('pac_wopen_small_west.gif')
turtle.register_shape('pac_wopen_small_north.gif')
turtle.register_shape('pac_wopen_small_south.gif')
turtle.register_shape('dobbogi_2_small.gif')
turtle.register_shape('yum.gif')
turtle.register_shape('game_over.gif')
#
# Instantiate ghost objects:
#
# ghosts.append(ghost('inky'))
# ghosts.append(ghost('pinky', 120, 120))
#
# Comment-out the following line and uncomment the next line to
# use your auto-pacman:
#
pm = pacman(120, -40) # Instantiate pacman object

#
#
#
food += placeFood()
# Prepare the "game over" turtle already:
game_over = turtle.Turtle()
game_over.hideturtle()
game_over.speed('fastest')
phase = 0
# Install the keyboard handlers:
window.onkey(TurnRight, 'd')
window.onkey(TurnLeft,  'a')
window.onkey(Foward,    'w')
window.onkey(Backward,  's')

window.onkey(GunLeft,  'Left')
window.onkey(GunRight,  'Right')

window.onkey(Fire,  'space')

window.onkey(quitKeyHandler,  'q')
periodicTimer() # Call periodic timer function for the first time.
                # Subsequent calls will be triggered from inside
                # this function, by setting up a timer.

window.listen()
window.mainloop()
