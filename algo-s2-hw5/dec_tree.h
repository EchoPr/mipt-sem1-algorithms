#ifndef DEC_TREE_H
#define DEC_TREE_H

#include <functional>
#include <queue>
#include <stdexcept>

#define NODEPAIR std::pair<node*, node*>

class dec_tree
{
    struct node
    {
        int factor;
        unsigned int priority;
        node* left;
        node* right;
    };

public:
    unsigned size() {
        return _size;
    }

    node* operator[](unsigned index) {
        if (index >= _size)
            throw std::runtime_error("Index out of range!");

        NODEPAIR splited = split(m_root, index);
        node* res = splited.first;
        
        m_root = merge(splited.first, splited.second);
        return res;
    }

    void insert(node* other, unsigned index) {
        if (index >= _size)
            throw std::runtime_error("Index out of range!");

        NODEPAIR splited = split(m_root, index);
        m_root = merge(merge(splited.first, other), splited.second);
    }

    void remove(unsigned index) {
        if (index >= _size)
            throw std::runtime_error("Index out of range!");

        NODEPAIR splited = split(m_root, index);
        NODEPAIR children = split(splited.first, index);
        node* tmp = children.first->left;
        children.first = nullptr;

        m_root = merge(merge(tmp, children.second), splited.second);
    }


private:
    NODEPAIR split(node* n, int k)
    {
        if (n == nullptr)
            return { nullptr, nullptr };
        
        int left = n->left->factor;
        if (left >= k) {
            NODEPAIR res = split(n->left, k);

            n->left = res.second;
            n->factor = 1 + n->left->factor + n->right->factor;

            return { res.first, n };
        }
    }

    node* merge(node* t0, node* t1)
    {
        if (t0 == nullptr)
            return t1;
        if (t1 == nullptr)
            return t0;
        if (t0->priority > t1->priority)
        {
            t0->right = merge(t0->right, t1);
            return t0;
        }
        t1->left = merge(t0, t1->left);
        return t1;
    }


    node* m_root = nullptr;
    unsigned _size = 0;
};

#endif // DEC_TREE_H
