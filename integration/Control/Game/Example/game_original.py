import math

# Import our own constants:
from globals import FOODMAX, STEPMAX, WIDTH, HEIGHT, X_MAX, Y_MAX, MS_TO_QUIT

import turtle


class thing:
    """ Root class.

        Attributes:
          ttl (turtle.Turtle): turtle object
          phase (int): phase used to flip appearance of animated screen objects
    """

    def __init__(self, x=0, y=0):
        """Special method to initialize a 'thing' object in memory.
           The 'self' parameter refers to the object.
           The 'x' and 'y' parameters define the screen position (x, y).
           NOTE: in the __init__() methods of the child-classes we also
                 call this method to set up the screen coordinates. (The child
                 inherits these data attributes from the parent, so we use the
                 parent's __init__() method for initialization.
        """
        self.ttl = turtle.Turtle()  # create a new Python turtle object
        self.ttl.penup()
        self.ttl.speed('fastest')
        self.ttl.goto(x, y)
        self.phase = 0

    def getPosition(self):
        """Method to return the screen position of a 'thing' object.
           The return-value is a tuple (x, y).
        """
        return (self.ttl.xcor(), self.ttl.ycor())  # retrieve coordinates from
        # turtle ttl and return tuple


class dobbogi(thing):
    """ Doboggi class for representing food in the game.

        The doboggi class is a sub-class of the 'thing' class. Therefore, it
        inherits all data attributes and methods from the 'thing' class.
    """

    def __init__(self, x=0, y=0):
        """Special method to initialize a 'doboggi' object in memory."""
        thing.__init__(self, x, y)  # Call __init__() of the superclass
        self.ttl.shape('dobbogi_2_small.gif')  # Set image of the object's turtle

    def setIsEaten(self):
        """Stop displaying this doboggi object in the game."""
        self.ttl.hideturtle()

    def __str__(self):
        """Special method for displaying a doboggi object.
           Python calls this method whenever it wants to show an object.
           For example, if d is a doboggi object, print(d) will make a call
           to __str__(). The string returned by __str__ will be printed."""
        # Note: we create the getPosition() method which the ghost class inherits
        # from the thing class to retrieve the position of the ghost.
        return 'Doboggi' + str(self.getPosition())


class ghost(thing):
    """ Class to represent ghost objects in the game.

        The ghost class is a sub-class of the 'thing' class. Therefore, it
        inherits all data attributes and methods from the 'thing' class.
    """

    def __init__(self, name, x=0, y=0):
        """Special method to initialize a ghost object."""
        thing.__init__(self, x, y)  # Call __init__ of the superclass
        self.name = name  # Initialize the name data attribute

    def updateShape(self):
        """This method switches the ghost object's turtle between two different
           images to give the impression of the ghost moving its legs. You can
           view the two gif images in any image viewer, for example the open-
           source gimp image editor.
        """
        if self.phase == 0:
            self.ttl.shape('ghost_red_1_small.gif')
            self.phase = 1
        else:
            self.ttl.shape('ghost_red_2_small.gif')
            self.phase = 0

    def move(self, pm):
        """Move a ghost to chase pacman. If the ghost left the screen
           at the right border, it is placed to the left of the left border to
           re-enter the game.
        """

        ### YOUR CODE HERE ###

        pmPos = pm.getPosition()
        ghPos = self.getPosition()
        degree = 0
        self.ttl.setheading(degree)

        ######

        if self.ttl.xcor() > X_MAX + 25:
            self.ttl.setx(-X_MAX - 25)
        elif self.ttl.xcor() > Y_MAX + 25:
            self.ttl.sety(-Y_max - 25)
        elif self.ttl.xcor() < -X_MAX - 25:
            self.ttl.setx(X_MAX + 25)
        elif self.ttl.xcor() < -Y_MAX - 25:
            self.ttl.setx(-Y_MAX - 25)
        else:
            self.ttl.forward(6)

    def __str__(self):
        """Special method for displaying a ghost object.
           Python calls this method whenever it wants to show an object.
           For example, if g is a ghost object, print(g) will make a call
           to __str__(). The string returned by __str__ will be printed."""
        # Note: we create the getPosition() method which the ghost class inherits
        # from the thing class to retrieve the position of the ghost.
        return 'Ghost ' + self.name + str(self.getPosition())


class pacman(thing):
    """ Class to represent the pacman object in the game.

        Attributes:
          dir (string): direction pacman is facing ('east', 'west', 'south', or
                        'north').
          steps (integer): number of remaining steps until the game ends.
          isYum (Boolean): controls the "Yum" cartoon bubble.
          isYumOff(Boolean): another control variable for the "Yum" cartoon bubble.
    """

    def __init__(self, x=0, y=0):
        """Special method to initialize a pacman object"""
        thing.__init__(self, x, y)  # call __init__() of the superclass
        self.dir = 'east'  # set initial direction
        self.steps = STEPMAX  # remaining steps
        self.isYum = False  # no
        self.isYumOff = False  # bubble

    def updateShape(self):
        """Method to control the appearance of pacman.

           The appearance can be either the "Yum" bubble or the pacman image
           (open or closed) facing any of the four directions.

           The open versus closed pacman image is controlled by the 'phase'
           data attribute (inherited from the 'thing' class).
        """
        if self.isYumOff:
            self.isYumOff = False
            self.isYum = False
        if self.isYum:
            self.isYumOff = True
            self.ttl.shape('yum.gif')
            turtle.update()
            return
        if self.phase == 0:
            if self.dir == 'east':
                self.ttl.shape('pac_open_small_east.gif')
            elif self.dir == 'west':
                self.ttl.shape('pac_open_small_west.gif')
            elif self.dir == 'north':
                self.ttl.shape('pac_open_small_north.gif')
            else:
                self.ttl.shape('pac_open_small_south.gif')
            self.phase = 1
        else:
            if self.dir == 'east':
                self.ttl.shape('pac_wopen_small_east.gif')
            elif self.dir == 'west':
                self.ttl.shape('pac_wopen_small_west.gif')
            elif self.dir == 'north':
                self.ttl.shape('pac_wopen_small_north.gif')
            else:
                self.ttl.shape('pac_wopen_small_south.gif')
            self.phase = 0

    def move(self):
        """Method to move pacman across the screen."""
        # Don't move beyond screen border:
        if self.dir == 'east' and self.ttl.xcor() > X_MAX:
            return
        if self.dir == 'west' and self.ttl.xcor() < -X_MAX:
            return
        if self.dir == 'north' and self.ttl.ycor() > Y_MAX:
            return
        if self.dir == 'south' and self.ttl.ycor() < -Y_MAX:
            return

        # Move forward:
        self.ttl.forward(10)

    def getRemainingSteps(self):
        """Return the steps left until the game terminates"""
        return self.steps

    def decrementSteps(self):
        """Decrement remaining steps by 1"""
        self.steps -= 1

    def turnEast(self):
        """Turn pacman's direction to the east."""
        if self.dir == 'east':  # do nothing if already facing east
            return
        self.ttl.setheading(0)  # change pacman turtle's direction to east
        self.dir = 'east'  # remember our new direction
        self.updateShape()  # call to switch image according our new direction

    def turnSouth(self):
        """Ditto for south"""
        if self.dir == 'south':
            return
        self.ttl.setheading(270)
        self.dir = 'south'
        self.updateShape()

    def turnWest(self):
        """Ditto for west"""
        if self.dir == 'west':
            return
        self.ttl.setheading(180)
        self.dir = 'west'
        self.updateShape()

    def turnNorth(self):
        """Ditto for north"""
        if self.dir == 'north':
            return
        self.ttl.setheading(90)
        self.dir = 'north'
        self.updateShape()

    def setIsYum(self):
        """Remember to display the "Yum" bubble and call
           updateShape() to switch pacman's appearance.
        """
        self.isYum = True
        self.updateShape()