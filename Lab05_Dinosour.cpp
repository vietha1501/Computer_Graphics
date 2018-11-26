
/* -- INCLUDE CPP ----------------------------------------------------------*/
#include <iostream>
#include <fstream>

/* -- INCLUDE FILES ------------------------------------------------------ */
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

using namespace std;

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLintPoint  {

      
      
};

typedef struct Piece {
    GLint numOfPoint;
    GLdouble* _x;
    GLdouble* _y;
} Piece;

/* -- GLOBAL VARIABLES --------------------------------------------------- */
int numOfSector;
Piece *pieces;  

/* -- LOCAL VARIABLES ---------------------------------------------------- */

//thuvh load file
void loadFile (string name);
     


/* ----------------------------------------------------------------------- */
/* Function    : void drawDot( GLint x, GLint y )
 *
 * Description : Draw a point at location (x, y) in the window.
 *
 * Parameters  : GLint x : X coordinate of point to draw.
 *               GLint y : X coordinate of point to draw.
 *
 * Returns     : void
 */

void drawDot( GLint x, GLint y )  {

}

/* ----------------------------------------------------------------------- */
/* Function    : void myInit( void )
 *
 * Description : Initialize OpenGL and the window where things will be
 *               drawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myInit( void )  {
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 1.0, 0.0, 0.0 );
  glPointSize( 1.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 700.0, 0.0, 600.0 );

}


/* ----------------------------------------------------------------------- */
/* Function    : void myDisplay( void )
 *
 * Description : This function gets called everytime the window needs to
 *               be redrawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void thuvh_display2 ( void ){
     glClear (GL_COLOR_BUFFER_BIT );

     
     for (int i = 0; i < numOfSector; i++){
              glBegin (GL_LINE_STRIP);
         int n = pieces[i].numOfPoint;
         for (int j = 0; j < n; j++){
             glVertex2f (pieces[i]._x[j], pieces[i]._y[j]);
         }
              glEnd ();
     }

     glFlush ();
}

void thuvh_display ( Piece p ){

  glBegin (GL_LINE_STRIP);
  int n = p.numOfPoint;
  
  for (int i = 0; i < n; i++){
      glVertex2f (p._x[i], p._y[i]);
  }
  
//  glVertex2f (p._x[0], p._y[0]);
  
  glEnd();

}



void myDisplay( void )  {
     // comment for viewport
//  glClear( GL_COLOR_BUFFER_BIT );
//  glBegin (GL_LINE_STRIP);
//  glVertex2i (100, 50);
//  glVertex2i (100, 130);
//  glVertex2i (150, 130);
//  glVertex2i (100, 50);
  for (int i = 0; i < numOfSector; i++){
      thuvh_display (pieces[i]);
  }    
//  glEnd();
// comment for viewport
//  glFlush(); 
}

void tillThuvh ( void ){
     glClear ( GL_COLOR_BUFFER_BIT );
     for (int i = 0; i < 5; i++){
         for (int j = 0; j < 5; j++){
             glViewport (i * 70, j * 60, 70, 60);
             
             myDisplay ();
         }
     }
     
     glFlush ();    
}

/* ----------------------------------------------------------------------- */
/* Function    : int main( int argc, char** argv )
 *
 * Description : This is the main function. It sets up the rendering
 *               context, and then reacts to user events.
 *
 * Parameters  : int argc     : Number of command-line arguments.
 *               char *argv[] : Array of command-line arguments.
 *
 * Returns     : int : Return code to pass to the shell.
 */

int main( int argc, char *argv[] )  {
  
  //load data
  loadFile("dinosaur.dat");
  // Initialize GLUT.
  glutInit( &argc, argv );
  // Set the mode to draw in.
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  // Set the window size in screen pixels.
  glutInitWindowSize( 720, 480 );
  // Set the window position in screen pixels.
  glutInitWindowPosition( 100, 150 );
  // Create the window.
  glutCreateWindow( "Lab" );
  // Set the callback funcion to call when we need to draw something.
 // glutDisplayFunc( myDisplay );
  //glutDisplayFunc( tillThuvh );
  glutDisplayFunc (thuvh_display2);
  // Initialize some things.
  myInit( );
  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );


}

/* ----------------------------------------------------------------------- */


void loadFile (string name){
     ifstream fi (name.c_str ());
     
     fi >> numOfSector;
     pieces = new Piece [numOfSector];
     
     for (int i = 0; i < numOfSector; i++){
         int tmp = 0;
         fi >> tmp;
         pieces[i].numOfPoint = (GLint)tmp;
         pieces[i]._x = new GLdouble[tmp];
         pieces[i]._y = new GLdouble[tmp];
         
         for (int j = 0; j < tmp; j++){
             double a = 0.0;
             double b = 0.0;
             
             fi >> a;
             fi >> b;
             
             pieces[i]._x[j] = a;
             pieces[i]._y[j] = b;   
         }
     }
          
     fi.close ();
}     
