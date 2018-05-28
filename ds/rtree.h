#ifndef RTREE_H
#define RTREE_H
#include <QVector>
#include <QString>

#define FEATURE_NUM 2
#define MAX_SPLIT_NUM 3


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
    QVector<int> min = QVector<int>(FEATURE_NUM);
    QVector<int> max = QVector<int>(FEATURE_NUM);

    QVector<Rect*> rect;//指向Rect的指针
    QVector<RTreeNode*> node;


}Rect;

class RTree
{
public:
    RTree();

    int Insert(const int ID,QVector<int> feature);
    Rect* Search();
    Rect* ChooseLeaf(QVector<int> feature);
    bool Contain(Rect* out,QVector<int> feature);
    bool CompSqre(Rect* out1,Rect* out2);//返回值：S out1 < S out 2 ?

    long long int ExtendAera(Rect* rect,QVector<int>);//计算扩展量，扩展体积比原体积
    void Clear();
    void update(Rect* rect);//更新最小值和最大值
    long long int Sqr(Rect* rect);//计算面积
    long long int Sqr(Rect* rect,Rect* add);//计算加入后的面积
    long long int Sqr(Rect* rect,RTreeNode* add);//计算加入后的面积
    long long int Sqr(Rect* rect,QVector<int> add);//计算加入后的面积
    long long int Sqr(QVector<int>,QVector<int>);
private:
    Rect* root;
    QVector<Rect*> all_rect;
    void AdjustTree(Rect* now);
    int root_cur_id;


};

#endif // RTREE_H
