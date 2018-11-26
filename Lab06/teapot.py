from math import *

# OpenGL imports for python
try:
    from OpenGL.GL import *
    from OpenGL.GLU import *
    from OpenGL.GLUT import *
except:
    print ("OpenGL wrapper for python not found")

# Last time when sphere was re-displayed
last_time = 0


def load():
    vertices =[]
    faces = []
    with open("teapot.obj") as f:
        for line in f.readlines():
            x = list(map(lambda x:x.strip(), line.strip().split()))
            if len(x)<2:
                continue
            if x[0]=="v":
                vertices.append(tuple(map(float,x[1:])))
            else:
                faces.append(tuple(map(int,x[1:])))
    return vertices,faces
    


class Teapot:

    # Constructor for the sphere class
    def __init__(self, radius,vertices,faces):

        # Radius of sphere
        self.radius = radius

        # Number of latitudes in sphere
        self.lats = 100

        # Number of longitudes in sphere
        self.longs = 100
        self.rotate = 0
        self.user_theta = 90
        self.user_height = -10

        # Direction of light
        self.direction = [0.0, 2.0, -1.0, 1.0]

        # Intensity of light
        self.intensity = [0.7, 0.7, 0.7, 1.0]

        # Intensity of ambient light
        self.ambient_intensity = [0.3, 0.3, 0.3, 1.0]

        # The surface type(Flat or Smooth)
        self.surface = GL_SMOOTH
        self.vertices = vertices
        self.faces = faces

    # Initialize
    def init(self):

        # Set background color to black
        glClearColor(0.0, 0.0, 0.0, 0.0)

        self.compute_location()

        # Set OpenGL parameters
        glEnable(GL_DEPTH_TEST)

        # Enable lighting
        glEnable(GL_LIGHTING)

        # Set light model
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, self.ambient_intensity)

        # Enable light number 0
        glEnable(GL_LIGHT0)

        # Set position and intensity of light
        glLightfv(GL_LIGHT0, GL_POSITION, self.direction)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, self.intensity)

        # Setup the material
        glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE)

    # Compute location
    def compute_location(self):
        x = 2 * cos(self.user_theta)
        y = 2 * sin(self.user_theta)
        z = self.user_height
        d = sqrt(x * x + y * y + z * z)
        
        # Set matrix mode
        glMatrixMode(GL_PROJECTION)

        # Reset matrix
        glLoadIdentity()
        glFrustum(-d * 0.5, d * 0.5, -d * 0.5, d * 0.5, d - 4.0, d + 4.0)

        # Set camera
        gluLookAt(x, y, z, 0, 0, 0, 0, 0, 1)

    # Display the sphere
    def display(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        # Set color to white
        glColor3f(1.0, 1.0, 1.0)

        # Set shade model
        glShadeModel(self.surface)
        self.draw()
        glutSwapBuffers()

    # Draw the sphere
    def draw(self):
        self.rotate+=2.0
        glPushMatrix()
        glRotatef(self.rotate,1,1,1)
        for f in self.faces:
            glBegin(GL_POLYGON)
            for v in f:
                glVertex3f(*self.vertices[v-1])
            glEnd()
        glPopMatrix()

    # Keyboard controller for sphere
    def special(self, key, x, y):

        # Scale the sphere up or down
        if key == GLUT_KEY_UP:
            self.user_height += 0.2
        if key == GLUT_KEY_DOWN:
            self.user_height -= 0.2
        # Rotate the cube
        if key == GLUT_KEY_LEFT:
            self.user_theta += 0.1
        if key == GLUT_KEY_RIGHT:
            self.user_theta -= 0.1

        # Toggle the surface
        if key == GLUT_KEY_F1:
            if self.surface == GL_FLAT:
                self.surface = GL_SMOOTH
            else:
                self.surface = GL_FLAT

        self.compute_location()
        glutPostRedisplay()
    #mouse callback
    def mouse(self,button,state,x,y):
        #print(button,state,x,y)
        if button==4:
            self.user_height += 0.2
        elif button==3:
            self.user_height -= 0.2
        elif button==0:
            if state==0:
                self.user_theta += 0.05
        self.compute_location()
        glutPostRedisplay()
        
    # The idle callback
    def idle(self):
        global last_time
        time = glutGet(GLUT_ELAPSED_TIME)

        if last_time == 0 or time >= last_time + 40:
            last_time = time
            glutPostRedisplay()

    # The visibility callback
    def visible(self, vis):
        if vis == GLUT_VISIBLE:
            glutIdleFunc(self.idle)
        else:
            glutIdleFunc(None)


# The main function
def main():

    # Initialize the OpenGL pipeline
    glutInit(sys.argv)

    # Set OpenGL display mode
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)

    # Set the Window size and position
    glutInitWindowSize(640, 480)
    glutInitWindowPosition(50, 100)

    # Create the window with given title
    glutCreateWindow('Teapot')

    # Instantiate the sphere object
    vertices,faces = load()
    s = Teapot(5.0,vertices,faces)

    s.init()

    # Set the callback function for display
    glutDisplayFunc(s.display)
    glutMouseFunc(s.mouse)  
    # Set the callback function for the visibility
    glutVisibilityFunc(s.visible)

    # Set the callback for special function
    glutSpecialFunc(s.special)
    
    # Run the OpenGL main loop
    glutMainLoop()


# Call the main function
if __name__ == '__main__':
    main()