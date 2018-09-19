#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 mt(rd());

struct node
{
    int value, sz, prior;
    node *l, *r;

    node() {value = 0; sz = 0; prior = 0; l = nullptr; r = nullptr;}
    node(int val) {value = val; prior = mt(); sz = 1; l = nullptr; r = nullptr;}
};
typedef node* pnode;

int size(pnode v)
{
    return v ? v->sz : 0;
}

void pull(pnode &v)
{
    if (!v)
        return;
    v->sz = size(v->l) + size(v->r) + 1;
}

void merge(pnode &t, pnode l, pnode r)
{
    if (!l)
    {
        t = r;
        return;
    }
    if (!r)
    {
        t = l;
        return;
    }
    if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;

    pull(t);
}

void split(pnode t, pnode &l, pnode &r, int k)
{
    if (!t)
    {
        l = nullptr;
        r = nullptr;
        return;
    }
    if (t->value <= k)
        split(t->r, t->r, r, k), l = t;
    else
        split(t->l, l, t->l, k), r = t;

    pull(t);
}

void insert(pnode &t, pnode it)
{
    if (!t)
    {
        t = it;
        return;
    }

    if (it->prior > t->prior)
        split(t, it->l, it->r, it->value), t = it;
    else
        insert(it->value < t->value ? t->l : t->r, it);

    pull(t);
}

void erase(pnode &t, int k)
{
    if (!t)
        return;
    if (t->value == k)
        merge(t, t->l, t->r);
    else
        erase(k < t->value ? t->l : t->r, k);

    pull(t);
}

int index(pnode &t, int k, int add = 0)
{
    if (!t)
        return add;
    if (t->value == k)
        return add + size(t->l);
    if (t->value < k)
        return index(t->r, k, add + size(t->l) + 1);
    else
        return index(t->l, k, add);
}

int main()
{
    pnode treap = nullptr;

    for (int i = 0; i < 100; ++i)
    {
        insert(treap, new node(i));
    }

    for (int i = 0; i < 100; ++i)
    {
        std::cout << index(treap, i) << "\n";
    }

    for (int i = 0; i < 100; ++i)
    {
        erase(treap, i);
    }
}
