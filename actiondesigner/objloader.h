#ifndef IMPORTOBJ_H
#define IMPORTOBJ_H

#include <vector>

class ObjLoader
{
private:
    /*存放顶点坐标*/
    struct vertex
    {
        float x;
        float y;
        float z;
    };
    /*存放顶点坐标索引*/
    struct face
    {
        unsigned int x;
        unsigned int y;
        unsigned int z;
    };
    std::vector<vertex> vertexs_v; // 顶点
    std::vector<vertex> vertexs_vn; // 顶点法线
    std::vector<vertex> vertexs_vt; // 纹理坐标
    std::vector<face> faces; ////面集合


    bool parseFloat(vertex *vt, const char *str);//将字符串解析为float类型
    bool parseInt(face *f, const char *str);//将字符串解析为int类型
    void m3dFindNormal(vertex *normal, const vertex *v1, const vertex *v2, const vertex *v3);//给出三个点，求出其法线向量
public:
        ObjLoader();
        ~ObjLoader();
        bool parse(const char *path);//解析OBJ文件内容，参数为要解析的文件路径
        void draw();
};

#endif // IMPORTOBJ_H
