import math

# Import our own constants:
import global_vals

import turtle

class thing:
  def __init__(self, x = 0, y = 0):

    self.ttl = turtle.Turtle() # create a new Python turtle object
    self.ttl.hideturtle()
    self.ttl.penup()
    # self.ttl.pendown()
    self.ttl.speed('fastest')
    self.ttl.goto(x, y)
    self.ttl.showturtle()

  def getPosition(self):
    """Method to return the screen position of a 'thing' object.
       The return-value is a tuple (x, y).
    """
    return (self.ttl.xcor(), self.ttl.ycor()) # retrieve coordinates from
                                              # turtle ttl and return tuple


class Wall(thing):
    all = []

    def __init__(self, x, y, width, height):
        thing.__init__(self, x, y)
        self.ttl.shape('square')
        self.ttl.color('gray')
        self.ttl.shapesize(global_vals.SCALE * height/20, global_vals.SCALE * width/20)
        self.x = x
        self.y = y
        self.width = width
        self.height = height

        self.all.append(self)

    def range(self):
        left_low = (self.x - self.width/2, self.y - self.height/2)
        right_low = (self.x + self.width/2, self.y - self.height/2)

        left_high = (self.x - self.width/2, self.y + self.height/2)
        right_high = (self.x + self.width/2, self.y + self.height/2)

        return left_low, right_low, left_high, right_high

    def sides(self):
        left_low, right_low, left_high, right_high = self.range()

        left = (left_high, left_low)
        right = (right_high, right_low)
        high = (left_high, right_high)
        low = (left_low, right_low)

        return left, right, high, low





class Bullet(thing):
    all = []

    def __init__(self, tank, x=0, y=0, heading=0):
        thing.__init__(self, x, y) # Call __init__ of the superclass
        self.ttl.setheading(heading)
        self.prevPosition = (x, y)
        self.tank = tank
        tank.bullets.append(self)
        self.all.append(self)

    def fly(self):

        self.prevPosition = self.getPosition()
        self.ttl.forward(50)

class tanktop(thing):

    def __init__(self, x=0, y=0):
        thing.__init__(self, x, y)
        self.ttl.shape('arrow')
        self.ttl.color('green')
        self.ttl.shapesize(stretch_wid=0.5, stretch_len=2)
        self.rotateAngle = 10

    def setPosition(self, tankPosition):
        self.ttl.setposition(tankPosition[0], tankPosition[1])

    def rotateCW(self):
        self.ttl.right(self.rotateAngle)

    def rotateCCW(self):
        self.ttl.left(self.rotateAngle)

    def fire(self, position, tank):
        heading = self.ttl.heading()
        Bullet(tank, position[0], position[1], heading)





class Tank(thing):
  all = []
  stepFW = 3
  stepBW = 3

  def __init__(self, x = 0, y = 0):
    thing.__init__(self, x, y) # call __init__() of the superclass
    self.steps = global_vals.STEPMAX       # remaining steps

    self.turnAngle = 10
    self.isYum = False         # no
    self.isYumOff = False      # bubble

    self.hp = 3

    self.ttl.shape('square')
    self.ttl.shapesize(stretch_wid=1, stretch_len=2)
    self.gun = tanktop(x, y)
    self.bullets = []

    self.all.append(self)

  def otherTanks(self):
      copy = self.all[:]
      copy.remove(self)
      return copy

  def blocked(self):
    if self.ttl.xcor() > global_vals.X_MAX or self.ttl.xcor() < -global_vals.X_MAX or self.ttl.ycor() > global_vals.Y_MAX or self.ttl.ycor() < -global_vals.Y_MAX:
      return True
    else:
      return False


  def decreaseHP(self):
      self.hp -= 1

      if self.hp <= 0:
        self.all.remove(self)







  def getRemainingSteps(self):
    """Return the steps left until the game terminates"""
    return self.steps

  def decrementSteps(self):
    """Decrement remaining steps by 1"""
    self.steps -= 1

  def turnCCW(self):
    self.ttl.left(self.turnAngle)
    self.gun.ttl.left(self.turnAngle)


  def turnCW(self):
    self.ttl.right(self.turnAngle)
    self.gun.ttl.right(self.turnAngle)


  def goForward(self, step=stepFW):
    if self.blocked():
      self.ttl.back(5)
      return
    self.ttl.forward(step)
    self.gun.setPosition(self.getPosition())
    print(int(self.getPosition()[0]), int(self.getPosition()[1]))

  def goBackward(self, step=stepBW):
    if self.blocked():
      self.ttl.forward(5)
      return
    self.ttl.back(step)
    self.gun.setPosition(self.getPosition())
    print(int(self.getPosition()[0]), int(self.getPosition()[1]))


  def setIsYum(self):
    """Remember to display the "Yum" bubble and call 
    """
    self.isYum = True
