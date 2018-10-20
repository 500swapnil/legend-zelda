#include "main.h"
#include "timer.h"
#include "ball.h"
#include <string>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************`
* Customizable functions *
**************************/
Monster boss;
Boat boat1;
bool vc= true,fc=true;
int t = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
char view = 'f';
int n_rocks = 1000;
int health = 100,lives = 3,score =0;
int n_mons = 40;
int n_barrels = 200;
bool machineGun = false;
Rock rocks[10000];
vector <CannonBall> balls;
vector <Ball> gifts;
vector <Ball> barrels;
vector <Monster> monsters;
float heliX = 20, heliY = -5, heliZ= -5;
float boatspeed = 0.05;
Sail test;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    camera_rotation_angle = boat1.rotation;
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up (1, 0, 0);
    if(view == 'f')
    {
        // Eye - Location of camera. Don't change unless you are sure!!
        eye = glm::vec3( boat1.position.x + 5, boat1.position.y - 6*cos(camera_rotation_angle*M_PI/180.0f) ,boat1.position.z - 6*sin(camera_rotation_angle*M_PI/180.0f) );

        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        target = glm::vec3( boat1.position.x, boat1.position.y + 12*cos(camera_rotation_angle*M_PI/180.0f), boat1.position.z + 12*sin(camera_rotation_angle*M_PI/180.0f));

    }
    else if(view == 't')
    {
        eye = glm::vec3( boat1.position.x + 20, boat1.position.y - 5*cos(camera_rotation_angle*M_PI/180.0f) ,boat1.position.z - 5*sin(camera_rotation_angle*M_PI/180.0f) );
        target = glm::vec3( boat1.position.x, boat1.position.y, boat1.position.z);
    }
    else if(view == 'c')
    {
        eye = glm::vec3( 10,-20 ,-20 );
        target = glm::vec3( boat1.position.x, boat1.position.y, boat1.position.z);
    }
    else if(view == 'b')
    {
        eye = glm::vec3( boat1.position.x + 2, boat1.position.y  ,boat1.position.z  );

        // Target - Where is the camera looking at.  Don't change unless you are sure!!
        target = glm::vec3( boat1.position.x, boat1.position.y + 12*cos(camera_rotation_angle*M_PI/180.0f), boat1.position.z + 12*sin(camera_rotation_angle*M_PI/180.0f));
    }
    else
    {
        eye = glm::vec3(heliX, heliY,heliZ);
        target = glm::vec3(0 , heliY + 5*cos(camera_rotation_angle*M_PI/180.0f), heliZ + 5*sin(camera_rotation_angle*M_PI/180.0f));
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    boat1.drawOcean(VP);
    boat1.draw(VP);
    boss.draw(VP);
    if(balls.size()>0)
    {
        for(int i=0 ; i<balls.size() ; i++)
            balls[i].draw(VP);
    }
    for(int i=0 ; i<gifts.size() ; i++)
        gifts[i].draw(VP);
    for(int i=0 ; i<barrels.size() ; i++)
        barrels[i].draw(VP);
//    test.draw(VP);
    for(int i=0 ; i<monsters.size() ; i++)
        monsters[i].draw(VP);
    for(int i=0 ; i<n_rocks ; i++)
        rocks[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int cam = glfwGetKey(window, GLFW_KEY_C);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int d = glfwGetKey(window, GLFW_KEY_D);

    if (w) {
        heliY += 1;
    }
    if (s) {
        heliY -= 1;
    }
    if (a) {
        heliZ += 1;
    }
    if (d) {
        heliZ -= 1;
    }
    if (left) {
//        camera_rotation_angle += 1;
        boat1.rotation += 0.5;
        boat1.yspeed = boat1.yspeed*cos(boat1.rotation*3.14/180);
        boat1.zspeed = boat1.zspeed*sin(boat1.rotation*3.14/180);
    }
    if (right) {
//        camera_rotation_angle -= 1;
        boat1.rotation -= 0.5;
    }
    if(abs(boat1.yspeed)< boatspeed*6 && abs(boat1.zspeed)<boatspeed*6)
    {
        if (up) {
            boat1.yspeed += boatspeed*cos(boat1.rotation*3.14/180) ;
            boat1.zspeed += boatspeed*sin(boat1.rotation*3.14/180) ;
        }
        if (down) {
            boat1.yspeed -= boatspeed*cos(boat1.rotation*3.14/180);
            boat1.zspeed -= boatspeed*sin(boat1.rotation*3.14/180);
        }
    }
    boat1.yspeed += boat1.wind*cos(boat1.direction*3.14/180);
    boat1.zspeed +=  boat1.wind*sin(boat1.direction*3.14/180);
    if (fire && fc == true)
    {
        fc = false;
        CannonBall shot = CannonBall(boat1.position.x, boat1.position.y + 3.0*cos(boat1.rotation*3.14/180), boat1.position.z + 3.0*sin(boat1.rotation*3.14/180),COLOR_RED,2);
        shot.yspeed = 2.5*cos(boat1.rotation*3.14/180);
        shot.zspeed = 2.5*sin(boat1.rotation*3.14/180);
        shot.xspeed = 0.1;
        balls.push_back(shot);
    }
    if (cam && vc == true) {
        vc = false;
        if(view == 'f')
            view = 't';
        else if(view == 't')
            view = 'c';
        else if(view=='c')
            view = 'b';
        else if(view=='b')
            view = 'h';
        else
            view = 'f';
    }
    if (jump && boat1.position.x < 2)
    {
        boat1.xspeed += 0.07;
    }
    t++;
    if (t%4==0)
    {
        if(t%320==0)
        {
            boat1.wind = rand()%10/700.0;
            boat1.direction = rand()%360;
            machineGun = false;
        }
        if(t%1280==0 && monsters.size() < 40)
        {
            spawnMonster();
        }
        if(t%2400==0)
        {
            boss.position = glm::vec3(4, -1*(rand()%2 + 1)*rand()%100, -1*(rand()%2 + 1)*rand()%100);
            boss.ehealth = 10;
        }
        t%=2400;
        if(t%40==0)
            vc = true;
        if(t%40==0 || machineGun)
            fc = true;
    }
}

void spawnMonster(){
    int choose = rand()%100;
    int type = 1;
    if(choose < 15)
        type = 3;
    else if(choose < 50)
        type = 2;
    monsters.push_back(Monster(2, -1*(rand()%2 + 1)*rand()%100, -1*(rand()%2 + 1)*rand()%100,type));
}

void spawnBarrel(){
    int randomy = -1*(rand()%2 + 1)*rand()%1000, randomz = -1*(rand()%2 + 1)*rand()%1000;
    int choose = rand()%100;
    if(choose < 40)
    {
        gifts.push_back(Ball(3.3,randomy,randomz,COLOR_LGREEN,3,3,3));
        gifts.back().power = 'h';

    }
    else if(choose < 90)
    {
        gifts.push_back(Ball(3.3,randomy,randomz,COLOR_ORANGE,3,3,3));
        gifts.back().power = 'p';
    }
    else
    {
        gifts.push_back(Ball(3.3,randomy,randomz,COLOR_PINK,3,3,3));
        gifts.back().power = 'm';
    }
    barrels.push_back(Ball(-2,randomy,randomz,COLOR_LBROWN,3,3,3));
    barrels.back().height = 20;
}

void tick_elements() {
    boat1.tick();
    boss.tick(boat1.position.y,boat1.position.z);

    for(int i=0 ; i<monsters.size() ; i++)
    {
        monsters[i].tick(boat1.position.y,boat1.position.z);
        if(detect_collision(monsters[i].bounding_box(),boat1.bounding_box()))
        {
            boat1.yspeed = -1.3*boat1.yspeed;
            boat1.zspeed = -1.3*boat1.zspeed;
            health -= 20;
            if(monsters[i].type == 3)
                health -= 10;
            monsters.erase(monsters.begin() + i--);
        }

    }
    for(int i=0 ; i<n_barrels ; i++)
    {
        if(detect_collision(barrels[i].bounding_box(),boat1.bounding_box()))
            barrels.erase(barrels.begin() + i--);
    }
//    camera_rotation_angle += 1;
    for(int i=0 ; i<n_rocks ; i++)
    {
        if(detect_collision(rocks[i].bounding_box(),boat1.bounding_box()))
        {
            boat1.yspeed = -1.3*boat1.yspeed;
            boat1.zspeed = -1.3*boat1.zspeed;
            health -= 10;
        }
    }
    if(detect_collision(boss.bounding_box(),boat1.bounding_box()) || health <= 0)
    {
        lives -= 1;
        boat1.position = glm::vec3(1,rand()%100,rand()%100);
        health = 100;
    }
    for(int i=0 ; i<balls.size() ; i++)
    {

        balls[i].tick();
        if(balls[i].position.x < -3)
        {
            balls.erase(balls.begin() + i--);
            continue;
        }

        for(int j=0 ; j<n_rocks ; j++)
        {
            if(detect_collision(rocks[j].bounding_box(),balls[i].bounding_box()))
            {
                balls.erase(balls.begin() + i--);
                rocks[j].position.x = -100;

//               cout<<"Collision!"<<endl;
                break;
            }
        }
        if(detect_collision(boss.bounding_box(),balls[i].bounding_box()))
        {
            balls.erase(balls.begin() + i--);
//                    cout<<monsters[j].type<<endl;
            boss.ehealth -= 1;
            if(boss.ehealth == 0)
            {
                gifts.push_back(Ball(4,boss.position.y,boss.position.z,COLOR_RED,3,3,3));
                gifts.back().power = 'b';
                boss.position.x = 19999;
                score += 500;
             }
        }
            for(int j=0 ; j<monsters.size() ; j++)
            {
                if(detect_collision(monsters[j].bounding_box(),balls[i].bounding_box()))
                {
                    balls.erase(balls.begin() + i--);
//                    cout<<monsters[j].type<<endl;
                    monsters[j].ehealth -= 1;
                    if(monsters[j].ehealth == 0)
                    {
                        if(monsters[j].type == 1)
                        {   gifts.push_back(Ball(3.3,monsters[j].position.y,monsters[j].position.z,COLOR_LGREEN,3,3,3));
                            gifts.back().power = 'h';
                            score += 50;

                        }
                        else if(monsters[j].type == 2)
                        {
                            gifts.push_back(Ball(3.3,monsters[j].position.y,monsters[j].position.z,COLOR_ORANGE,3,3,3));
                            gifts.back().power = 'p';
                            score+=50;
                        }
                        else
                        {

                                gifts.push_back(Ball(3.3,monsters[j].position.y,monsters[j].position.z,COLOR_PINK,3,3,3));
                                gifts.back().power = 'm';
                                score +=100;

                        }
                        monsters.erase(monsters.begin() + j);
                }

//                    cout<<"Collision!"<<endl;
                    break;
                }
            }
    }
    for(int i=0 ; i<gifts.size() ; i++)
    {

            if(detect_collision(gifts[i].bounding_box(),boat1.bounding_box()))
            {
                if(gifts[i].power == 'h')
                    health += 40;
                else if(gifts[i].power == 'p')
                    score += 50;
                else if(gifts[i].power == 'm')
                {
                    machineGun = true;
                    t = 0;
                }
                else
                {
                    boatspeed *= 2;
                }
                gifts.erase(gifts.begin() + i--);
                continue;
            }

        gifts[i].rotation += 3;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat1       = Boat(-1, 0, 0);

//    test =Sail(4,5,1);
    for(int i=0 ; i<n_rocks ; i++)
    {
        rocks[i] = Rock(-2, -1*(rand()%2 + 1)*rand()%1000, -1*(rand()%2 + 1)*rand()%1000,COLOR_GREY,3,2);
    }
    for(int i=0 ; i<n_mons ; i++)
    {
        spawnMonster();
    }
    for(int i=0 ; i<n_barrels ; i++)
    {
        spawnBarrel();
    }
    boss = Monster(1000, -1*(rand()%2 + 1)*rand()%100, -1*(rand()%2 + 1)*rand()%100,4);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1366;
    int height = 768;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window) && lives>0) {
        // Process timers

        if (t60.processTick() ) {
            // 60 fps
            // OpenGL Draw commands
            string disp = "The Legend of Zelda | Score: "+to_string(score)+ " | Health: " + to_string(health) + " | Lives: "+to_string(lives);
            glfwSetWindowTitle(window,const_cast<char*>(disp.c_str()));
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.z - b.z) * 2 < (a.width + b.width)) &&
           (abs(a.x - b.x) * 2 < (a.height + b.height)) &&
           (abs(a.y - b.y) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
