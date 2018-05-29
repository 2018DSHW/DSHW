#ifndef RTREE_H
#define RTREE_H
#include <QVector>
#include <QString>


typedef struct RTreeNode
{
    int ID;//从零开始
    int rectID;
    QVector<int> feature;

}RTreeNode;

typedef struct Rect
{
    Rect* parent;
    int ID;
    bool type;//0表示叶子节点，1表示非叶子节点
    QVector<int> min;
    QVector<int> max;
    QVector<Rect*> rect;//指向Rect的指针
    QVector<RTreeNode*> node;


}Rect;

class RTree
{
public:
    RTree();

    bool SetFeatureNum(int);//设置维数，默认值为2，返回0false表示失败
    bool SetSplitNum(int);//设置分裂数，返回false表示失败
    int Insert(const int ID,QVector<int> feature);
    Rect* Search();
    Rect* ChooseLeaf(QVector<int> feature);
    bool Contain(Rect* out,QVector<int> feature);
    bool CompSqre(Rect* out1,Rect* out2);//返回值：S out1 < S out 2 ?

    long long int ExtendAera(Rect* rect,QVector<int>);//计算扩展量，扩展体积比原体积
    void Clear();
    void DeleteNode(Rect *rect);
    void update(Rect* rect);//更新最小值和最大值
    long long int Sqr(Rect* rect);//计算面积
    long long int Sqr(Rect* rect,Rect* add);//计算加入后的面积
    long long int Sqr(Rect* rect,RTreeNode* add);//计算加入后的面积
    long long int Sqr(Rect* rect,QVector<int> add);//计算加入后的面积
    long long int Sqr(QVector<int>,QVector<int>);

    QVector<int> find(QVector<int> input);//返回ID的vector
    QVector<int> find(QVector<int> input,int dep);//增加查询深度,0表示最相关，数字越大越不相关，返回空vector意为dep过大，超过根节点了或者小于0

    void AddNode(QVector<int>&input,Rect* root);
    int access_time;
private:
    Rect* root;
    QVector<Rect*> all_rect;
    void AdjustTree(Rect* now);
    int root_cur_id;
    int FEATURE_NUM;
    int MAX_SPLIT_NUM;
};

#endif // RTREE_H
