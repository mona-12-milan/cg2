










































#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <stdio.h>
#include <math.h>
#include<iostream>
#include<vector>

using namespace std;



class Point{
    public :
    int x, y;
};

struct Color {
    float r,g,b;
};
vector<Point> points;
void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0 , 640 , 0 , 480);
}


struct Color getPixelColor(int x, int y) {
    struct Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}


void setPixelColor(int x, int y,struct Color color) {

    glColor3f(color.r, color.g, color.b);

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

}


void flood(int x, int y,struct Color old_col,struct Color new_col)
{

      struct Color color;
      color = getPixelColor(x,y);
      printf("%f %f %f\n",color.r,color.g,color.b);

      //check current pixel is old_color or not
      if(color.r==new_col.r && color.g==new_col.g && color.b == new_col.b)
        return;
      if (color.r==old_col.r && color.g==old_col.g && color.b == old_col.b) {

              glColor3f(new_col.r,new_col.g,new_col.b);
              glBegin(GL_POINTS);

              glVertex2i(x,y);
              glEnd();
              glFlush();

              flood(x + 1, y,old_col,new_col);
              flood(x - 1, y,old_col,new_col);
              flood(x, y + 1,old_col,new_col);
              flood(x, y - 1,old_col,new_col);
              return;
        }

return;
}

bool isValid(struct Color c1,struct Color c2)
{

    printf(" c1 %f %f %f  c2 %f %f %f \n",c1.r,c1.g,c1.b,c2.r,c2.g,c2.b);
    if(c1.r != c2.r || c1.g!=c2.g || c1.b!=c2.b)
    {
        return true;
    }
    else{
       return false;
    }
}

void boundary_fill(int x,int y,struct Color fillColor,struct Color boundary_color)
{
      struct Color color;
      color = getPixelColor(x,y);
      printf("%f %f %f\n",color.r,color.g,color.b);
    if(isValid(color,fillColor)==true && isValid(color,boundary_color)==true)
    {
        cout<<"hi";
        glBegin(GL_POINTS);
        glColor3f(fillColor.r,fillColor.g,fillColor.b);
        glVertex2i(x,y);
        glEnd();
        glFlush();

        boundary_fill(x + 1, y,fillColor,boundary_color);
        boundary_fill(x - 1, y,fillColor,boundary_color);
        boundary_fill(x, y + 1,fillColor,boundary_color);
        boundary_fill(x, y - 1,fillColor,boundary_color);

        return;
    }
    return;
}

void drawPolygon()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<points.size();i++)
    {
        glVertex2f(points[i].x,points[i].y);
    }
    glEnd();
    glFlush();

}




void yx() {

        drawPolygon();

        for(int y = 0; y <= 480; y++) {      // For each scan line
            vector<int> intersections;
            int n = points.size();

            for(int i = 0, j = 1; i < n; i++, j = (++j) % n) {      // For each edge

                int y1 = points[i].y;
                int y2 = points[j].y;

                if(y1 < y2) {
                    if(y >= y1 && y < y2) {
                        int x = (y - y1) * (points[j].x - points[i].x) / (y2 - y1) + points[i].x;
                        intersections.push_back(x);
                    }
                } else {
                    if (y >= y2 && y < y1) {
                        int x = (y - y1) * (points[j].x - points[i].x) / (y2 - y1) + points[i].x;
                        intersections.push_back(x);
                    }
                }
            }

            sort(intersections.begin(), intersections.end());
            int m = intersections.size();

            glColor3f(0, 1, 0);
            for(int i = 0; i < m; i += 2) {
                int x1 = intersections[i];
                int x2 = intersections[i + 1];
                glBegin(GL_LINES);
                    glVertex2i(x1, 480 - y);
                    glVertex2i(x2, 480 - y);
                glEnd();


            }
        }

        cout<<"Finished filling!\n";

        glFlush();

    }



void y_x()
{

    drawPolygon();

    int numIntersections = 0;


            for(int y = 0; y <= 480; y++) {      // For each scan line
            vector<int> intersections;
            int n = points.size();

            for(int i = 0, j = 1; i < n; i++, j = (++j) % n) {      // For each edge
                int y1 = points[i].y;
                int y2 = points[j].y;

                if(y1 < y2) {
                    if(y >= y1 && y < y2) {
                        int x = (y - y1) * (points[j].x - points[i].x) / (y2 - y1) +points[i].x;
                        intersections.push_back(x);
                    }
                } else {
                    if (y >= y2 && y < y1) {
                        int x = (y - y1) * (points[j].x - points[i].x) / (y2 - y1) + points[i].x;
                        intersections.push_back(x);
                    }
                }
            }

            sort(intersections.begin(), intersections.end());
            int m = intersections.size();

            glColor3f(0, 1, 0);
            for(int i = 0; i < m; i += 2) {
                int x1 = intersections[i];
                int x2 = intersections[i + 1];
                glBegin(GL_LINES);
                    glVertex2i(x1, y);
                    glVertex2i(x2, y);
                glEnd();

                glFlush();
            }
        }

        cout<<"Finished filling!\n";

        glFlush();

    }




void createrectangle(void)
{
    //to clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);



}


void handleMouse(int button,int state , int x_loc,int y_loc)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int x = x_loc;
        int y = 480 - y_loc;
        points.push_back({x,y});
        glFlush();
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        int x = x_loc;
        int y = 480 - y_loc;
        drawPolygon();

        struct Color old_col={1.0,0.0,0.0};
        struct Color new_col={1.0,1.0,0.0};
        int x_start =0;
        int y_start =0;
        for(int i=0;i<points.size();i++)
        {
            x_start+=points[i].x;
            y_start+=points[i].y;
        }
        x_start= x_start/points.size();
        y_start = y_start/points.size();
        //flood(x_start,y_start,old_col,new_col);
        y_x();
        //boundary_fill(x_start,y_start,new_col,old_col);
    }
}


int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(640, 480);
glutInitWindowPosition(10, 10);
glutCreateWindow("Flood fill");
Init();
glutDisplayFunc(createrectangle);
glutMouseFunc(handleMouse);

glutMainLoop();
}

