#ifndef MHASH_H
#define MHASH_H

#include <queue>

#include "mvector.h"
#include "mlist.h"
#include "output.h"

class mhashtab
{
public:
    mhashtab() = default;

    void insert(unsigned long long k)//  h : 0 <= k < 2**64-1 -> 0 <= k1 < 256
    {
        reserve(m_size + 1);
        int index = h(k, m_p);// k % 256      0xFFFFFFFFFFFFFF00
        if (m_tab[index].find(k) == m_tab[index].end())
        {
            history.push(k);
            m_tab[index].push_front(k);
            ++m_size;
        }
    }

    void remove(unsigned long long k)
    {
        int index = h(k, m_p);// k % 256      0xFFFFFFFFFFFFFF00
        auto it = m_tab[index].find(k);
        if (it != m_tab[index].end())
        {
            update_history_on_remove(k);
            m_tab[index].remove(it);
            --m_size;
        }
    }

    bool contains(unsigned long long k)
    {
        int index = h(k, m_p);
        return m_tab[index].find(k) != m_tab[index].end();
    }

    void print()
    {
        std::cout << m_tab << std::endl;
    }

    void print_history() {
        int history_size = history.size();
        while (history_size--) {
            cout << history.front() << " ";
            history.pop();
        }
        cout << endl;
    }

    unsigned long long h(unsigned long long k)
    {
        return h(k, m_p);
    }

    void reserve(int new_cap)
    {
        if (new_cap > m_tab.size()) // m_tab.size() == old_cap
        {
            int p = m_p;
            while ((1 << p) < new_cap)
                ++p;
            mvector<mlist<unsigned long long>> tab(1 << p);
            for (auto& lst : m_tab)
                for (auto k : lst) {
                    int index = h(k, p);
                    if (tab[index].find(k) == tab[index].end())
                        tab[index].push_front(k);
                }
            m_tab = std::move(tab);
            m_p = p;
        }
    }
private:
    static unsigned long long h(unsigned long long k, int p)
    {
        auto x = k * 11400714819323199488ull;
        return x >> (64 - p);// m_tab.size() == 2**m_p
    }

    mvector<mlist<unsigned long long>> m_tab;
    queue<unsigned long long> history;
    int m_size = 0;
    int m_p = 2;

    void update_history_on_remove(unsigned long long k) {
        int history_size = history.size();
        while (history_size--) {
            if (history.front() != k)
                history.push(history.front());
            history.pop();
        }
    }
};


class mhashtabopenaddr
{
    enum cell_state {
        nil = 0,
        value,
        deleted
    };

public:
    mhashtabopenaddr() :m_tab(), m_state(), m_p(1) {}

    void insert(unsigned long long k)//  h : 0 <= k < 2**64-1 -> 0 <= k1 < 256
    {
        reserve(m_size + 1);
        int index0 = h(k, m_p);
        for (int i = 0; i < m_tab.size(); ++i)
        {
            int index = prob(index0, i, m_p);
            if (m_state[index] == nil || m_state[index] == deleted)
            {
                m_tab[index] = k;
                m_state[index] = value;
                ++m_size;
                return;
            }
            if (m_state[index] == value && m_tab[index] == k)
                return;
        }
        throw std::out_of_range("");
    }

    void remove(unsigned long long k)
    {
        int index0 = h(k, m_p);
        for (int i = 0; i < m_tab.size(); ++i)
        {
            int index = prob(index0, i, m_p);
            if (m_state[index] == nil)
                return;
            if (m_state[index] == value && m_tab[index] == k)
            {
                m_state[index] = deleted;
                m_tab[index] = 0;
                --m_size;
                return;
            }
        }
        throw std::out_of_range("");
    }


    bool contains(unsigned long long k)//  h : 0 <= k < 2**64-1 -> 0 <= k1 < 256
    {
        int index0 = h(k, m_p);
        for (int i = 0; i < m_tab.size(); ++i)
        {
            int index = prob(index0, i, m_p);
            if (m_state[index] == nil)
                return false;
            if (m_state[index] == value && m_tab[index] == k)
                return true;
        }
        throw std::out_of_range("");
    }


    void reserve(int new_cap)
    {
        if (new_cap > m_tab.size()) // m_tab.size() == old_cap
        {
            int p = m_p;
            while ((1 << p) < new_cap)
                ++p;
            mvector<unsigned long long> tab(1 << p);
            mvector<cell_state> state(1 << p);

            for (int j = 0; j < m_tab.size(); ++j)
            {
                if (m_state[j] == value)
                {
                    int index0 = h(m_tab[j], m_p);
                    for (int i = 0; i < tab.size(); ++i)
                    {
                        int index = prob(index0, i, p);
                        if (state[index] == nil)
                        {
                            tab[index] = m_tab[j];
                            state[index] = value;
                            break;
                        }
                    }
                }
            }
            m_tab = std::move(tab);
            m_state = std::move(state);
            m_p = p;
        }
    }

private:
    static unsigned long long h(unsigned long long k, int p)
    {
        auto x = k * 11400714819323199488ull;
        return x >> (64 - p);// m_tab.size() == 2**m_p
    }
    /*int prob(int index0,int i,int p)
    {
        return (index0 + i) % (1 << p);
    }*/
    static int prob(int index0, int i, int p)
    {
        return (index0 + (i + i * i) / 2) % (1 << p);
    }
    mvector<unsigned long long> m_tab;
    mvector<cell_state> m_state;
    int m_size = 0;
    int m_p = 2;
public:
    void print()
    {
        for (int i = 0; i < m_tab.size(); ++i)
        {
            switch (m_state[i])
            {
            case nil:
                std::cout << "nil    " << " " << m_tab[i] << std::endl;
                break;
            case value:
                std::cout << "value  " << " " << m_tab[i] << std::endl;
                break;
            case deleted:
                std::cout << "deleted" << " " << m_tab[i] << std::endl;
                break;
            }
        }
    }

};



#endif // MHASH_H