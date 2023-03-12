/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */













































#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<iostream>
#include<vector>


using namespace std;
void init(){
     glClearColor(1,1,1,0);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-320,320,-320,320);


}

class Point{

public :

    int x,y;
    Point(int x,int y){

    this->x = x;
    this->y = y;
    }

};

class Window{

    int x1,x2,y1,y2;
    public:

    void create(int x1,int y1,int x2, int y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;

    }

    void plot(){

        glColor3d(0,0,0);

        int x3,y3,x4,y4;

        x3 = this->x2;
        y3 = this->y1;

        x4 = this->x1;
        y4 = this->y2;


    glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x3,y3);
        glVertex2f(x2,y2);
        glVertex2f(x4,y4);
    glEnd();
    glFlush();


    }

    vector<Point> windowPoints(){

        int x3,y3,x4,y4;

        x3 = this->x2;
        y3 = this->y1;

        x4 = this->x1;
        y4 = this->y2;
        vector<Point> Points;
        Points.push_back(Point(this->x1,this->y1));

        Points.push_back(Point(x3,y3));

        Points.push_back(Point(this->x2,this->y2));



        Points.push_back(Point(x4,y4));


        return Points;




    }
};
Window w;


vector <Point> polygon;

void drawPolygon(vector<Point> polygon)
{


    glColor3d(1,1,0);
    glBegin(GL_POLYGON);
        for(int i = 0 ;i < polygon.size() ; i++)
            glVertex2f(polygon[i].x,polygon[i].y);
    glEnd();


    glFlush();
    return;
}
static void display(void)
{
     glClear(GL_COLOR_BUFFER_BIT);

}

Point intersection(Point A, Point B, Point C, Point D) {
   // Line AB represented as a1x + b1y = c1
   double a = B.y- A.y;
   double b = A.x - B.x;
   double c = a*(A.x) + b*(A.y);
   // Line CD represented as a2x + b2y = c2
   double a1 = D.y- C.y;
   double b1 = C.x - D.x;
   double c1 = a1*(C.x)+ b1*(C.y);

   double det = a*b1 - a1*b;

    double x = (b1*c - b*c1)/det;
    double y = (a*c1 - a1*c)/det;
    cout<<"\nintersected point :  x  - "<<x << " y - "<<y;

    glColor3d(1,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2d(x,y);
    glEnd();
    glFlush();
    return Point(x, y);

}

void sutherland_hodgman(vector<Point> polygon)
{
    vector<Point> windowpoints = w.windowPoints();

    for(int i = 0 ;i < windowpoints.size() ; i++){

        cout<<" x:  "<< windowpoints[i].x <<"   y : "<<windowpoints[i].y;
    }



    cout<<"\n inside sutherland\n";




    //left 0 and 3
    vector<Point> polygon1;
    for(int i = 0 ;i < polygon.size() ; i++)
    {
        int x1 = polygon[i].x;
        int y1 = polygon[i].y;

        int x2,y2;
        if(i == polygon.size() - 1)
        {   x2 = polygon[0].x;
            y2 = polygon[0].y;

        }
        else{

        x2 = polygon[i+1].x;
        y2 = polygon[i+1].y;

        }

        // in - in

        cout<<" \n iteration " << i <<"\n";
        cout<<"\n x1 :  "<<x1<< "  y1   "<<y1<<"  x2 "<<x2 << " y2  "<< y2 ;


        if(x1 > windowpoints[0].x && x2 > windowpoints[0].x)
        {

            cout<<"\n in in \n\n";
                polygon1.push_back(Point(x2,y2));
        }
        // in - out

        else if(x1 > windowpoints[0].x && x2 < windowpoints[0].x)
            {
                 // we need to find the intersection

                cout<<"\n in out\n\n ";

                Point p1 = intersection(windowpoints[0],windowpoints[3],Point(x1,y1),Point(x2,y2));
                polygon1.push_back(p1);


            }
        // out - in
        else if(x1 < windowpoints[0].x && x2 > windowpoints[0].x)
            {

                cout<<"\n out in \n\n";
                Point p1 = intersection(windowpoints[0],windowpoints[3],Point(x1,y1),Point(x2,y2));
                polygon1.push_back(p1);
                polygon1.push_back(Point(x2,y2));


            }

            else{
                cout<<" \nout out \n";
            }


        // out - out

    }

    cout<<"\n after left";


    for(int i = 0 ;i < polygon1.size() ; i++){

        cout<<" x:  "<< polygon1[i].x <<"   y : "<<polygon1[i].y;
    }


    //right 1 and 2


    vector<Point> polygon2;
    for(int i = 0 ;i < polygon1.size(); i++)
    {
        int x1 = polygon1[i].x;
        int y1 = polygon1[i].y;

        int x2,y2;
        if(i == polygon1.size() - 1)
        {    x2 = polygon1[0].x;
             y2 = polygon1[0].y;

        }
        else{

         x2 = polygon1[i+1].x;
         y2 = polygon1[i+1].y;

        }


        // in - in

        if(x1 < windowpoints[1].x && x2 < windowpoints[1].x)
            {
                cout<<"\n in in \n";
                polygon2.push_back(Point(x2,y2));
            }
        // in - out

            else if(x1 < windowpoints[1].y && x2 > windowpoints[1].x)
            {
                 // we need to find the intersection

                Point p1 = intersection(windowpoints[1],windowpoints[2],Point(x1,y1),Point(x2,y2));
                polygon2.push_back(p1);


            }
        // out - in
            else if(x1 > windowpoints[1].x && x2 < windowpoints[1].x)
            {
                Point p1 = intersection(windowpoints[1],windowpoints[2],Point(x1,y1),Point(x2,y2));
                polygon2.push_back(p1);
                polygon2.push_back(Point(x2,y2));


            }


        // out - out

        else{
            cout<<"\n out out";
        }

    }




    cout<<"\n after right\n";

    for(int i = 0 ;i < polygon2.size() ; i++){

        cout<<" x:  "<< polygon2[i].x <<"   y : "<<polygon2[i].y;
    }




    //bottom 3and 2


    vector<Point> polygon3;
    for(int i = 0 ;i < polygon2.size() ; i++)
    {
        int x1 = polygon2[i].x;
        int y1 = polygon2[i].y;

        int x2,y2;

        if(i == polygon2.size() - 1)
        {   x2 = polygon2[0].x;
            y2 = polygon2[0].y;

        }
        else{

         x2 = polygon2[i+1].x;
         y2 = polygon2[i+1].y;

        }

        // in - in

        if(y1 > windowpoints[3].y && y2 > windowpoints[3].y)
            {
                polygon3.push_back(Point(x2,y2));
            }
        // in - out

        else if(y1 > windowpoints[3].y && y2 < windowpoints[3].y)
            {
                 // we need to find the intersection

                Point p1 = intersection(windowpoints[3],windowpoints[2],Point(x1,y1),Point(x2,y2));
                polygon3.push_back(p1);


            }
        // out - in
        else if(y1 < windowpoints[3].y && y2 > windowpoints[3].y)
            {
                Point p1 = intersection(windowpoints[3],windowpoints[2],Point(x1,y1),Point(x2,y2));
                polygon3.push_back(p1);
                polygon3.push_back(Point(x2,y2));


            }

        else{
            cout<<"\n out out\n";
        }


        // out - out

    }


    cout<<"\n after bottom\n";

    for(int i = 0 ;i < polygon3.size() ; i++){

        cout<<" x:  "<< polygon3[i].x <<"   y : "<<polygon3[i].y;
    }





    //top 0 and 1



    vector<Point> polygon4;
    for(int i = 0 ;i < polygon3.size() ; i++)
    {
        int x1 = polygon3[i].x;
        int y1 = polygon3[i].y;

        int x2,y2;

        if(i == polygon3.size() - 1)
        {   x2 = polygon3[0].x;
            y2 = polygon3[0].y;

        }
        else{

        x2 = polygon3[i+1].x;
        y2 = polygon3[i+1].y;

        }
        // in - in

        if(y1 < windowpoints[0].y && y2 < windowpoints[0].y)
            {
                polygon4.push_back(Point(x2,y2));
            }
        // in - out

            else if(y1 < windowpoints[0].y && y2 > windowpoints[0].y)
            {
                 // we need to find the intersection

                Point p1 = intersection(windowpoints[0],windowpoints[1],Point(x1,y1),Point(x2,y2));
                polygon4.push_back(p1);


            }
        // out - in
            else if(y1 > windowpoints[0].y && y2 < windowpoints[0].y)
            {
                Point p1 = intersection(windowpoints[0],windowpoints[1],Point(x1,y1),Point(x2,y2));
                polygon4.push_back(p1);
                polygon4.push_back(Point(x2,y2));


            }


        // out - out

    }

    cout<<"\n after top";



    glColor3d(0,1,0);

    for(int i = 0 ;i < polygon4.size() ; i++){

        cout<<"\n x:  "<< polygon4[i].x <<"   y : "<<polygon4[i].y;
    }

    cout<<"hi  "<<polygon4.size();
  glBegin(GL_POLYGON);
    for(int i = 0;i< polygon4.size();i++)
        glVertex2f(polygon4[i].x,polygon4[i].y);
    glEnd();
    glFlush();


}

static void key(unsigned char key, int x, int y)
{

if(key == 's')
{
    w.plot();
    drawPolygon(polygon);
    sutherland_hodgman(polygon);


    cout<<"hi";
}
}

void mouseHandler(int button, int state, int mouse_x, int mouse_y)
{
    static int count = 0;
    static int x1,x2,y1,y2;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        int x = mouse_x - 320;
        int y = 640 - mouse_y - 320;

        if(count == 0)
        {

            x1 = x;
            y1 = y;
            count ++;


        }

        else if(count == 1)
        {
            x2 = x;
            y2 = y;
            count++;


            w.create(x1,y1,x2,y2);

            w.plot();
        }

        else{

            Point p(x,y);
            polygon.push_back(p);

            cout<<" \n polygon size "<< polygon.size();


        }


    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {


        w.plot();
        drawPolygon(polygon);
        glFlush();

    }


}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT polygon clipping");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouseHandler);

   // glClearColor(1,1,1,1);


    glutMainLoop();

    return EXIT_SUCCESS;
}
