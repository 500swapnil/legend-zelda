#include "ball.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Ball::Ball(float x, float y,float z,color_t color,float width, float height, float depth) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->xspeed = 0;
    this->yspeed = 0;
    this->zspeed = 0;
    this->height = height;
    this->width = width;
    this->depth = depth;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -this->height/2,-this->depth/2,-this->width/2, // triangle 1 : begin
                -this->height/2,-this->depth/2,this->width/2,
                -this->height/2,this->depth/2,this->width/2, // triangle 1 : end
                this->height/2,this->depth/2,-this->width/2, // triangle 2 : begin
                -this->height/2,-this->depth/2,-this->width/2,
                -this->height/2,this->depth/2,-this->width/2, // triangle 2 : end
                this->height/2,-this->depth/2,this->width/2,
                -this->height/2,-this->depth/2,-this->width/2,
                this->height/2,-this->depth/2,-this->width/2,
                this->height/2,this->depth/2,-this->width/2,
                this->height/2,-this->depth/2,-this->width/2,
                -this->height/2,-this->depth/2,-this->width/2,
                -this->height/2,-this->depth/2,-this->width/2,
                -this->height/2,this->depth/2,this->width/2,
                -this->height/2,this->depth/2,-this->width/2,
                this->height/2,-this->depth/2,this->width/2,
                -this->height/2,-this->depth/2,this->width/2,
                -this->height/2,-this->depth/2,-this->width/2,
                -this->height/2,this->depth/2,this->width/2,
                -this->height/2,-this->depth/2,this->width/2,
                this->height/2,-this->depth/2,this->width/2,
                this->height/2,this->depth/2,this->width/2,
                this->height/2,-this->depth/2,-this->width/2,
                this->height/2,this->depth/2,-this->width/2,
                this->height/2,-this->depth/2,-this->width/2,
                this->height/2,this->depth/2,this->width/2,
                this->height/2,-this->depth/2,this->width/2,
                this->height/2,this->depth/2,this->width/2,
                this->height/2,this->depth/2,-this->width/2,
                -this->height/2,this->depth/2,-this->width/2,
                this->height/2,this->depth/2,this->width/2,
                -this->height/2,this->depth/2,-this->width/2,
                -this->height/2,this->depth/2,this->width/2,
                this->height/2,this->depth/2,this->width/2,
                -this->height/2,this->depth/2,this->width/2,
                this->height/2,-this->depth/2,this->width/2,
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

Rock::Rock(float x,float y, float z,color_t color,float height, float width){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->height = height;
    this->rotationz = 0;
    this->width = width;
    this->depth = width;
    GLfloat vertex_buffer_data[] = {
          height, 0.0f, 0.0f,
           0.0f,-width,width,
           0.0f,-width,-width,

           height,0.0f, 0.0f,
           0.0f,-width,width,
            0.0f,width,width,

            height,0.0f, 0.0f,
            0.0f,width,-width,
           0.0f,-width,-width,

          height, 0.0f, 0.0f,
           0.0f,width,-width,
           0.0f,width,width,
        };
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

Boat::Boat(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->direction = 0;
    this->wind = 0;
    this->width = 4;
    this->height = 2;
    this->depth = 4;
    GLfloat vertex_buffer_data[] = {

        -1.0f, 1.0f,-1.0f, // triangle 2 : begin
        1.0f,-2.0f,-2.0f,
        1.0f, 2.0f,-2.0f, // triangle 2 : end

        -1.0f,-1.0f, 1.0f,
        1.0f,-2.0f,-2.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-2.0f,-2.0f,


        -1.0f,-1.0f, 1.0f,
         1.0f,-2.0f,2.0f,
        1.0f,-2.0f,-2.0f,

        1.0f, 2.0f, 2.0f,
        1.0f,-2.0f,2.0f,
        -1.0f,-1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 2.0f,-2.0f,

        -1.0f, 1.0f, 1.0f,
        1.0f, 2.0f,-2.0f,
        1.0f, 2.0f, 2.0f,

        -1.0f, 1.0f, 1.0f,
        1.0f, 2.0f, 2.0f,
        -1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {


        0.3f, 0.7f, 0.2f,
        0.3f, 0.7f, 0.2f,
        0.3f, 0.7f, 0.2f,

        0.2f, 0.1f, 0.1f,
        0.2f, 0.1f, 0.1f,
        0.2f, 0.1f, 0.1f,


        0.3f, 0.7f, 0.2f,
        0.3f, 0.7f, 0.2f,
        0.3f, 0.7f, 0.2f,


        0.2f, 0.1f, 0.1f,
        0.2f, 0.1f, 0.1f,
        0.2f, 0.1f, 0.1f,

        0.2f, 0.7f, 0.8f,
        0.2f, 0.7f, 0.8f,
        0.2f, 0.7f, 0.8f,

        0.7f, 0.1f, 0.1f,
        0.7f, 0.1f, 0.1f,
        0.7f, 0.1f, 0.1f,

        0.7f, 0.1f, 0.1f,
        0.7f, 0.1f, 0.1f,
        0.7f, 0.1f, 0.1f,


        0.2f, 0.8f, 0.5f,
        0.2f, 0.8f, 0.5f,
        0.2f, 0.8f, 0.5f,

        0.2f, 0.8f, 0.5f,
        0.2f, 0.8f, 0.5f,
        0.2f, 0.8f, 0.5f,


        0.2f, 0.7f, 0.8f,
        0.2f, 0.7f, 0.8f,
        0.2f, 0.7f, 0.8f,

    };
    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    this->arrowBody = Ball(this->position.x,this->position.y,this->position.z,COLOR_RED,0.05,0.05,0.5);
    this->arrowHead = Rock(this->position.x,this->position.y,this->position.z,COLOR_RED,0.3,0.1);
    this->sail = Sail(this->position.x,this->position.y,this->position.z);
    this->guy = Monster(this->position.x,this->position.y,this->position.z,5);
    this->arrowHead.rotationz = 90;
}


Sail::Sail(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    GLfloat vertex_buffer_data[] = {
        -0.5f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
        1.5f, 0.0f, -1.5f,
    };
    GLfloat color_buffer_data[] = {
            1.0f,1.0f,1.0f,
            1.0f,1.0f,1.0f,
            1.0f,1.0f,1.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

Monster::Monster(float x,float y, float z,int type){
    this->position = glm::vec3(x, y, z);
    this->rotation = rand()%360;
    this->height = 6;
    this->width = 4;
    this->depth = 3;
    this->ehealth = 1;
    this->type = type;
    if(type == 3)
        this->ehealth = 2;
    if(type == 4)
        this->ehealth = 10;

    this->rotationz = 0;
    switch(type){
        case 1:this->body[0] = Ball(0,0,0,COLOR_GREEN,4,5,3);break;
        case 2:this->body[0] = Ball(0,0,0,COLOR_YELLOW,4,5,3);break;
        case 3:this->body[0] = Ball(0,0,0,COLOR_PURPLE,5,6,4);break;
    }
    if(type==4)
    {
        this->height = 10;
        this->width = 8;
        this->depth = 6;
        this->body[0] = Ball(0,0,0,COLOR_ORANGE,8,10,6);
        this->body[1] = Ball(0,0,6,COLOR_BLACK,4,2,2);
        this->body[2] = Ball(0,0,-6,COLOR_BLACK,4,2,2);
        this->body[3] = Ball(-8,0,-2.6,COLOR_BLACK,2,6,2);
        this->body[4] = Ball(-8,0,2.6,COLOR_BLACK,2,6,2);
        this->head = CannonBall(5,0,0,COLOR_BLACK,6);
    }
    else if(type == 5)
    {
        this->height = 3;
        this->width = 2;
        this->depth = 2;
        this->body[0] = Ball(0,-0.25,0,COLOR_ORANGE,0.75,1,0.5);
        this->body[1] = Ball(0,0,0.5,COLOR_BLACK,0.5,0.25,0.25);
        this->body[2] = Ball(0,0,-0.5,COLOR_BLACK,0.5,0.25,0.25);
        this->body[3] = Ball(-1,0,-0.3,COLOR_BLACK,0.25,0.5,0.25);
        this->body[4] = Ball(-1,0,0.3,COLOR_BLACK,0.25,0.5,0.25);
        this->head = CannonBall(0.6,0,0,COLOR_BLACK,0.5);
    }
    else
    {
    this->body[1] = Ball(0,0,3,COLOR_BLACK,2,1,1);
    this->body[2] = Ball(0,0,-3,COLOR_BLACK,2,1,1);
    this->body[3] = Ball(-4,0,-1.3,COLOR_BLACK,1,3,1);
    this->body[4] = Ball(-4,0,1.3,COLOR_BLACK,1,3,1);
    this->head = CannonBall(2.5,0,0,COLOR_BLACK,3);
    }

}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0 ; i<5 ; i++)
        this->body[i].draw(MVP);
    this->head.draw(MVP);
}

void Monster::tick(float usery, float userz) {
    float speed = 0.08;
    if(type == 4)
        speed = 0.27;
    if(usery > this->position.y)
    {
        this->yspeed = speed;
    }
    else
        this->yspeed = -speed;

    if(userz > this->position.z)
    {
        this->zspeed = speed;
    }
    else
        this->zspeed = -speed;
    this->rotation += (rand()%2+1)*-1*rand()%10/2.0;
    this->position.y += yspeed + rand()%10/100.0 - 0.05;
    this->position.z += zspeed + rand()%10/100.0 - 0.05;

}

CannonBall::CannonBall(float x, float y,float z,color_t color,float width) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->xspeed = 0.0;
    this->yspeed = 0.0;
    this->zspeed = 0.0;
    this->width = width;
    this->height = width;
    this->depth = width;
    int sides = 80;
    float r = width/2;
    float angle = 2*3.1415/sides;
    GLfloat vertex_buffer_data[100000];
    for(int i=0;i<sides;i++)
        for(int j=0;j<sides;j++)
        {

            vertex_buffer_data[9*(sides*j + i)] = 0.0f;

            vertex_buffer_data[9*(sides*j + i) + 1] = r*sin(i*angle);
            vertex_buffer_data[9*(sides*j + i) + 2] = r*sin(i*angle);
            vertex_buffer_data[9*(sides*j + i) + 3] = r*cos(j*angle)*cos(i*angle);
            vertex_buffer_data[9*(sides*j + i) + 4] = r*sin(j*angle)*cos(i*angle);

            vertex_buffer_data[9*(sides*j + i) + 5] = 0.0f;
            vertex_buffer_data[9*(sides*j + i) + 6] = r*cos((j+1)*angle)*cos(i*angle);
            vertex_buffer_data[9*(sides*j + i) + 7] = r*sin((j+1)*angle)*cos(i*angle);
            vertex_buffer_data[9*(sides*j + i) + 8] = r*sin(i*angle);


        }

    this->object = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->arrowBody.position = glm::vec3( this->position.x + 5.5, this->position.y - 5.0*cos(this->rotation*M_PI/180.0f) ,this->position.z - 5.0*sin(this->rotation*M_PI/180.0f) );
    this->arrowHead.position = glm::vec3( this->position.x + 5.5, this->position.y - 5.0*cos(this->rotation*M_PI/180.0f) ,this->position.z - 5.0*sin(this->rotation*M_PI/180.0f) );
    this->sail.position = glm::vec3( this->position.x , this->position.y ,this->position.z );
    this->guy.position = glm::vec3( this->position.x + 1, this->position.y  - 1.0*cos(this->rotation*M_PI/180.0f) ,this->position.z - 1*sin(this->rotation*M_PI/180.0f));
    this->arrowBody.rotation = this->direction;
    this->arrowHead.rotation = this->direction;
    this->sail.rotation = this->direction;
    this->guy.rotation = this->rotation;
    this->arrowBody.draw(VP);
    this->arrowHead.draw(VP);
    this->sail.draw(VP);
    this->guy.draw(VP);
}

void Ball::drawOcean(glm::mat4 VP) {
    float depth = -2, size = 1000;
    const GLfloat g_vertex_buffer_data[18] = {
         depth,size,-size,
          depth,size,size,
         depth,-size,size,

        depth,-size,-size,
         depth,size,-size,
        depth,-size,size,
    };
    color_t color = COLOR_BLUE;
    VAO *object;
    object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);


}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += xspeed;
    this->position.y += yspeed;
    this->position.z += zspeed;
    xspeed -= 0.03;
}

void Boat::tick() {
    if( this->position.x < -0.8)
        this->xspeed = 0.02;
    else if(this->position.x >= 0.2)
        this->xspeed += -0.02;
    this->position.x += xspeed;
    this->position.y += yspeed;
    this->position.z += zspeed;
    yspeed /= 1.05;
    zspeed /=1.05;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float width = this->width, height = this->height, depth = this->depth;
    bounding_box_t bbox = { x, y,z, width, height, depth };
    return bbox;
}
