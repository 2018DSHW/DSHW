#include "rtree.h"

RTree::RTree()
{
    root = NULL;
    root_cur_id = 0;
}

int RTree::Insert(const int ID,QVector<int> feature)
{
    if (feature.size() != FEATURE_NUM)
        return 0;

    RTreeNode *temp = new RTreeNode;
    temp->ID = ID;
    temp->feature = feature;

    //如果空树
    if (root == NULL)
    {
        root = new Rect;
        root->parent = NULL;
        root->type = false;
        root->ID = root_cur_id;
        temp->rectID = root_cur_id;
        root_cur_id++;
        for (int i = 0;i < FEATURE_NUM;i++)
        {
            root->min[i] = root->max[i] = feature[i];
        }
        root->node.push_back(temp);


        all_rect.push_back(root);
    }
    else
    {
        Rect* aera = ChooseLeaf(feature);

        aera->node.push_back(temp);

        temp->rectID = aera->ID;
        update(aera);
        AdjustTree(aera);
        //split
    }
}


void RTree::AdjustTree(Rect *now)
{
    if (now->type == false)
    {
        if (now->node.size() < MAX_SPLIT_NUM)
        {
            return ;
        }

        int min_rank,max_rank;
        for (int i = 0;i < now->node.size();i++)
        {
            if (now->node[i]->feature == now->min)
            {
                min_rank = i;
            }
            if (now->node[i]->feature == now->max)
            {
                max_rank = i;
            }
        }//find seeds

        Rect    *rect1 = new Rect,*rect2 = new Rect;

        rect1->type = rect2->type = false;
        rect1->min  = now->node[min_rank]->feature;
        rect1->max = now->node[min_rank]->feature;
        rect2->min  = now->node[max_rank]->feature;
        rect2->max = now->node[max_rank]->feature;
        rect1->ID = now->ID;
        rect2->ID = root_cur_id;
        root_cur_id++;

        //init

        rect1->node.push_back(now->node[min_rank]);
        rect2->node.push_back(now->node[max_rank]);

        bool stat[MAX_SPLIT_NUM]={false};
        stat[min_rank] = stat[max_rank] = true;
        for (int i = 0;i < now->node.size() - 2;i++)
        {
            int choose,max = -1;
            for (int j = 0;j < now->node.size();j++)
            {
                if (stat[j] == true)
                {
                    continue;
                }

                int a = abs(Sqr(rect1,now->node[j]) - Sqr(rect2,now->node[j]));
                if (max < a)
                {
                    max = a;
                    choose = j;
                }
            }
            stat[choose] = true;
            if (Sqr(rect1) < Sqr(rect2))
            {
                rect1->node.push_back(now->node[choose]);
                now->node[choose]->rectID = rect1->ID;
            }
            else
            {
                rect2->node.push_back(now->node[choose]);
                now->node[choose]->rectID = rect2->ID;
            }
        }
        //add each

        rect1->parent = rect2->parent = NULL;

        update(rect1);
        update(rect2);
        //更新最大值最小值

        rect1->parent = rect2->parent = now->parent;

        all_rect[now->ID] = rect1;
        all_rect.push_back(rect2);
        //把now地位置存rect1，末尾加上rect2；
        if (root == now)
        {
            root = new Rect;
            root->rect.push_back(rect1);
            root->rect.push_back(rect2);
            root->max = rect1->max;
            root->min = rect1->min;
            rect1->parent = rect2->parent = root;
            root->ID = root_cur_id;
            root_cur_id ++;
            root->parent = NULL;
            root->type = true;
            update(root);
            all_rect.push_back(root);
        }
        else
        {
            Rect *te = rect1->parent;
            int to_delete;
            for (int i = 0;i < te->rect.size();i++)
            {
                if (te->rect[i] == now)
                {
                    to_delete = i;
                    break;
                }
            }
            QVector<Rect*>::iterator itr = te->rect.begin();
            for (int i = 0; i < to_delete;i++)
            {
                itr++;
            }
            te->rect.erase(itr);

            te->rect.push_back(rect1);
            te->rect.push_back(rect2);
            for (int i = 0;i < rect2->node.size();i++)
            {
                rect2->node[i]->rectID = rect2->ID;
            }

            AdjustTree(now->parent);
        }
        delete(now);

    }
    else
    {
        if (now->rect.size() < MAX_SPLIT_NUM)
        {
            return ;
        }
        int min_rank,max_rank;
        for (int i = 0;i < now->rect.size();i++)
        {
            if (now->rect[i]->min == now->min)
            {
                min_rank = i;
            }
            if (now->rect[i]->max == now->max)
            {
                max_rank = i;
            }
        }//find seeds


        Rect    *rect1 = new Rect,*rect2 = new Rect;

        rect1->type = rect2->type = true;
        rect1->min  = now->rect[min_rank]->min;
        rect1->max = now->rect[min_rank]->max;
        rect2->min  = now->rect[max_rank]->min;
        rect2->max = now->rect[max_rank]->max;


        //init

        rect1->rect.push_back(now->rect[min_rank]);
        now->rect[min_rank]->parent = rect1;
        rect2->rect.push_back(now->rect[max_rank]);
        now->rect[max_rank]->parent =rect2;
        bool stat[MAX_SPLIT_NUM]={false};
        stat[min_rank] = stat[max_rank] = true;
        for (int i = 0;i < now->rect.size() - 2;i++)
        {
            int choose,max = -1;
            for (int j = 0;j < now->rect.size();j++)
            {
                if (stat[j] == true)
                {
                    continue;
                }
                int a = abs(Sqr(rect1,now->rect[j]) - Sqr(rect2,now->rect[j]));
                if (max < a)
                {
                    max = a;
                    choose = j;
                }

            }
            stat[choose] = true;
            if (Sqr(rect1) < Sqr(rect2))
            {
                rect1->rect.push_back(now->rect[choose]);
                now->rect[choose]->parent = rect1;
            }
            else
            {
                rect2->rect.push_back(now->rect[choose]);
                now->rect[choose]->parent = rect2;
            }
        }
        //add each

        rect1->parent = rect2->parent = NULL;
        update(rect1);
        update(rect2);
        //更新最大值最小值

        rect1->parent = rect2->parent = now->parent;

        rect1->ID = now->ID;
        rect2->ID = root_cur_id;
        root_cur_id++;
        all_rect[now->ID] = rect1;
        all_rect.push_back(rect2);
        //把now地位置存rect1，末尾加上rect2；

        if (root == now)
        {
            root = new Rect;
            root->type = true;
            root->parent = NULL;
            root->rect.push_back(rect1);
            root->rect.push_back(rect2);
            rect1->parent = rect2->parent = root;
            root->ID = root_cur_id;
            root_cur_id ++;

            for (int i = 0;i < FEATURE_NUM;i++)
            {
                root->min[i] = rect1->min[i] < rect2->min[i] ?rect1->min[i] : rect2->min[i];
                root->max[i] = rect1->max[i] > rect2->max[i] ?rect1->max[i] : rect2->max[i];
            }
            all_rect.push_back(root);
        }
        else
        {
            Rect *te = rect1->parent;
            int to_delete;
            for (int i = 0;i < te->rect.size();i++)
            {
                if (te->rect[i] == now)
                {
                    to_delete = i;
                    break;
                }
            }
            QVector<Rect*>::iterator itr = te->rect.begin();
            for (int i = 0; i < to_delete;i++)
            {
                itr++;
            }
            te->rect.erase(itr);

            te->rect.push_back(rect1);
            te->rect.push_back(rect2);
            for (int i = 0;i < rect1->rect.size();i++)
            {
                rect1->rect[i]->parent = rect1;
            }
            for (int i = 0;i < rect2->rect.size();i++)
            {
                rect2->rect[i]->parent = rect2;
            }
            AdjustTree(now->parent);
        }
        delete(now);
    }
}

bool RTree::Contain(Rect *out, QVector<int> feature)
{
    for (int i = 0;i < FEATURE_NUM;i++)
    {
        if (feature[i] >= out->min[i] && feature[i] <= out->max[i])
        {
            continue;
        }
        return false;
    }
    return true;
}

long long int RTree::ExtendAera(Rect *rect, QVector<int> add)
{
    return Sqr(rect,add) - Sqr(rect);
}

bool RTree::CompSqre(Rect *out1, Rect *out2)
{
    return Sqr(out1) < Sqr(out2);
}//

Rect* RTree::ChooseLeaf(QVector<int> feature)
{
    Rect* result;
    result = root;
    while(true)
    {
        if (result->type == false)
            return result;
        Rect* temp = NULL;
        long long int min_extend = LONG_LONG_MAX;
        for (int i= 0;i < result->rect.size();i++)
        {
            long long int a = ExtendAera(result->rect[i],feature);
            if (a < min_extend)
            {
                temp = result->rect[i];
                min_extend = a;
            }
            if (a == min_extend)
            {
                if (!CompSqre(temp,result->rect[i]))
                {
                    temp = result->rect[i];
                }
            }
        }
        result = temp;
    }
}

void RTree::update(Rect *rect)
{
    int min,max;
    bool change = false;
    if (rect->type == true)
    {
        for (int i = 0;i < FEATURE_NUM;i++)
        {
            min = rect->min[i];
            max = rect->max[i];
            for(int j = 0;j < rect->rect.size();j++)
            {

                if (rect->rect[j]->min[i] < min)
                {
                    min = rect->rect[j]->min[i];
                    change = true;
                }
                if (rect->rect[j]->max[i] > max)
                {
                    max = rect->rect[j]->max[i];
                    change = true;
                }
            }
            rect->min[i] = min;
            rect->max[i] = max;
        }
    }
    else
    {
        for (int i = 0;i < FEATURE_NUM;i++)
        {
            min = rect->min[i];
            max = rect->max[i];
            for(int j = 0;j < rect->node.size();j++)
            {
                if (rect->node[j]->feature[i] < min)
                {
                    min = rect->node[j]->feature[i];
                    change = true;
                }
                if (rect->node[j]->feature[i] > max)
                {
                    max = rect->node[j]->feature[i];
                    change = true;
                }
            }
            rect->min[i] = min;
            rect->max[i] = max;
        }
    }
    if (change == true && rect->parent != NULL)
    {
        update(rect->parent);
    }
}

long long int RTree::Sqr(Rect *rect)
{
    return Sqr(rect->max,rect->min);
}

long long int RTree::Sqr(Rect *rect,RTreeNode* add)
{
    long long int output =1;
    for (int i = 0;i < FEATURE_NUM;i++)
    {
        int min = rect->min[i] < add->feature[i] ? rect->min[i] : add->feature[i];
        int max = rect->max[i] > add->feature[i] ? rect->max[i] : add->feature[i];
        if (min == max)
        {
            continue;
        }
        output *= (max - min);
    }
    return output;
}

long long int RTree::Sqr(Rect *rect,QVector<int> add)
{
    long long int output =1;
    for (int i = 0;i < FEATURE_NUM;i++)
    {
        int min = rect->min[i] < add[i] ? rect->min[i] : add[i];
        int max = rect->max[i] > add[i] ? rect->max[i] : add[i];
        if (min == max)
        {
            continue;
        }
        output *= (max - min);
    }
    return output;
}


long long int RTree::Sqr(Rect *rect,Rect* add)
{
    long long int output =1;
    for (int i = 0;i < FEATURE_NUM;i++)
    {
        int min = rect->min[i] < add->min[i] ? rect->min[i] : add->min[i];
        int max = rect->max[i] > add->max[i] ? rect->max[i] : add->max[i];
        if (min == max)
        {
            continue;
        }
        output *= (max - min);
    }
    return output;
}

long long int RTree::Sqr(QVector<int> mi,QVector<int> ma)
{
    long long int output =1;
    for (int i = 0;i < FEATURE_NUM;i++)
    {
        int min = mi[i] < ma[i] ? mi[i] : ma[i];
        int max = ma[i] < mi[i] ? mi[i] : ma[i];
        if (min == max)
        {
            continue;
        }
        output *= (max - min);
    }
    return output;
}

