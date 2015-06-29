//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle Dimensions
#define PWIDTH 75
#define PHEIGHT 15
#define PyLoc HEIGHT*.8
#define PxLoc WIDTH/2 - PWIDTH/2

// Setting minimum ball speed to prevent zero horizontal velocity 
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN_SPEED 1
#define MIN(a, b) ((a) > (b) ? (b) : (a))


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial ball velocity
    double Xvelocity = drand48() + 1;
    double Yvelocity = 2.0;
    
    //int currLife = LIVES;
    //int lastLife = LIVES;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor only horizontally
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, PyLoc);
             }
         }
        
        
        // BALL CONTROL
        // move circle along x-axis
        move(ball, Xvelocity, Yvelocity);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            Xvelocity *= -1;
            //printf("%f\n",Xvelocity);
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            Xvelocity *= -1;
            //printf("%f\n",Xvelocity);
        }
        
        // bounce off top of window
        else if (getY(ball) <= 0)
        {
            Yvelocity *= -1;
        }
        
        
        // bounce off bottom of window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            
            lives -- ;
            
            float direct = drand48();
            
            // variability in direction of ball
            if (direct <= .5)
            {    
                Xvelocity = drand48() - 1;
                Yvelocity = 2.0;
            }
            else
            {
                Xvelocity = drand48() + .5;
                Yvelocity = 2.0;
            }
            
            waitForClick();
            
            setLocation(ball,WIDTH/2,HEIGHT/2);
            
            
        }
        

        // linger before moving again
        pause(10);

        GObject object = detectCollision(window, ball);
        
        // Paddle physics
        if (object != NULL)
        {
            if (object == paddle)
            {
                 if (getY(ball) + getHeight(ball) == getY(paddle))
                    {
                    // left side of paddle and ball coming from left to right
                    if (getX(ball) >= getX(paddle) && getX(ball) < getX(paddle) + (PWIDTH/2) && Xvelocity > 0)
                    {
                        Yvelocity *= -1;
                        Xvelocity = MAX(Xvelocity * .5, MIN_SPEED);
                        //printf("left side going right %f, paddle: %f , ball %f, vel %f\n",drand48(), getX(paddle), getX(ball), Xvelocity);
                    }
                    
                    // left side of paddle and ball coming from right to left
                    else if (getX(ball) >= getX(paddle) && getX(ball) < getX(paddle) + (PWIDTH/2) && Xvelocity < 0)
                    {
                        Yvelocity *= -1;
                        Xvelocity = MIN(Xvelocity * 1.5, MIN_SPEED);
                        //printf("right side going left %f, paddle: %f , ball %f, vel %f\n",drand48(), getX(paddle), getX(ball), Xvelocity);
                    }
                    
                    // right side of paddle and ball coming from left to right
                    else if (getX(ball) >= getX(paddle) + (PWIDTH/2) && getX(ball) < getX(paddle) + (PWIDTH) && Xvelocity > 0)
                    {
                        Yvelocity *= -1;
                        Xvelocity = MAX(Xvelocity * 1.5, MIN_SPEED);
                        //printf("right side: left to right %f, paddle: %f , ball %f, vel %f\n",drand48(), getX(paddle), getX(ball), Xvelocity);
                    }
                    
                    // right side of paddle and ball coming from right to left
                    else if (getX(ball) >= getX(paddle) + (PWIDTH/2) && getX(ball) < getX(paddle) + (PWIDTH) && Xvelocity < 0)
                    {
                        Yvelocity *= -1;
                        Xvelocity = MIN(Xvelocity * .5, MIN_SPEED);
                        //printf("right side: right to left %f, paddle: %f , ball %f, vel %f\n",drand48(), getX(paddle), getX(ball), Xvelocity);   
                    }
                }
                
                
            }
            
            
            
            // remove red bricks
            else if (strcmp(getType(object), "GRect") == 0 && getY(ball) < 450)
            {
                
                Yvelocity *= -1;
                removeGWindow(window,object);
                
                updateScoreboard(window,label, ++points);
                
                --bricks;
                
            }
         
        
        }
    
   }
    
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
    
    
}




/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{

int brickx = 1, bricky = 50;
int brickw = 37, brickh = 10; 

    // start atop the top left and work to bottom right
    for (int r  = 1; r <= ROWS; r ++)
    {
        for (int c = 1; c <= COLS; c ++)
        {
            GRect brick = newGRect(brickx, bricky, brickw, brickh);
            setFilled(brick,true);
            setColor(brick,"RED");
            add(window, brick);
            
            //increment x-coor
            brickx += 40;
        }
        
        //reset brickx
        brickx = 1;
        
        //increment y-coor
        bricky += 21;
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    
    GOval circle = newGOval(WIDTH/2, HEIGHT/2 , 10, 10);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    
    
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(PxLoc, PyLoc, PWIDTH, PHEIGHT);
    setFilled(paddle,true);
    setColor(paddle,"BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */

 
 
GLabel initScoreboard(GWindow window)
{
    // TODO
    char* score = "0";
    
    GLabel scoreBrd = newGLabel(score);
    setFont(scoreBrd, "SansSerif-18");
    add(window, scoreBrd);
    return scoreBrd;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
