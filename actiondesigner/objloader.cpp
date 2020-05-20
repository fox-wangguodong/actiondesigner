#include "objloader.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

#include <GL/glu.h> //若要使用gluPerspective函数则需引入该头文件

#include <QDebug>

ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}


bool ObjLoader::parseFloat(vertex *vt, const char *str)
{
    const char *current = str;
    const char *next = str;
    double temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = strtod(current, (char **)&next);
        if (current == next){
            return false;
        }
        else{
            current = next;
        }
    }
    vt->x = temp[0];
    vt->y = temp[1];
    vt->z = temp[2];
    return true;
}

bool ObjLoader::parseInt(face *f, const char *str)
{
    const char *current = str;
    const char *next = str;
    int temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = (int)strtod(current, (char **)&next);
        if (current == next){
            return false;
        }else{
            while (*next != 0x20){
                next++;
            }
            current = next;
        }
    }
    f->x = temp[0];
    f->y = temp[1];
    f->z = temp[2];
    return true;
}

bool ObjLoader::parse(const char *path)
{
    char str[1024] = {'\0'};
    int num=0;


    FILE *stream = fopen(path, "r");
    if(stream == NULL){
        qDebug()<<"文件打开失败";
        return false;
    }

    char ch = fgetc(stream);
    str[num]=ch;
    num++;
    while(ch!=EOF)
    {
        ch=fgetc(stream);
        if((ch == '\r' || ch == '\n') && num != 0)
        {
            switch (str[0])
            {
            case 'v':
            case 'V':
                vertex temp;
                switch (str[1])
                {
                case 'n':
                    break;
                case 't':
                    break;
                default:
                    if (parseFloat(&temp, &str[1])){
                        vertexs_v.push_back(temp);
                    }
                    break;
                }
                memset(str, 0, 1024);
                break;
            case 'f':
            case 'F':
                face ftemp;
                if (parseInt(&ftemp, &str[1])){
                    faces.push_back(ftemp);
                }
                memset(str, 0, 1024);
                break;
            }
            num = 0;
            for (int nn = 0; nn <= 1023; nn++){
                str[nn] = '\0';
            }
        }
        if( ch != '\r' && ch != '\n' ) {
            str[num]=ch;
            num++;
        }
    }
    fclose(stream);
    return true;
}

void ObjLoader::draw()
{
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < faces.size(); i++)
    {
        vertex v1 = vertexs_v[faces[i].x - 1];
        vertex v2 = vertexs_v[faces[i].y - 1];
        vertex v3 = vertexs_v[faces[i].z - 1];

        vertex normal;

        m3dFindNormal(&normal, &v1, &v2, &v3);
        glNormal3f(normal.x, normal.y, normal.z);

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}

void ObjLoader::m3dFindNormal(vertex *normal, const vertex *v1, const vertex *v2, const vertex *v3)
{
    float a[3], b[3];
    /*计算向量v1--->v2*/
    a[0] = v2->x - v1->x;
    a[1] = v2->y - v1->y;
    a[2] = v2->z - v1->z;
    /*计算向量v1--->v3*/
    b[0] = v3->x - v1->x;
    b[1] = v3->y - v1->y;
    b[2] = v3->z - v1->z;

    /*	计算法向量
    |  i    j   k   |
    | a0 a1 a2 | = (a1 * b2 - a2 *b1)i + (a2 * b0 - a0 * b2)j +(a0 * b1 - a1 * b0)k
    | b0 b1 b2 |
    */
    normal->x = a[1] * b[2] - a[2] * b[1];
    normal->y = a[2] * b[0] - a[0] * b[2];
    normal->z = a[0] * b[1] - a[1] * b[0];
}
