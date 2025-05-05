#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

class Set
{
public:
    Set() : m_root(nullptr), m_size(0) {}

    Set(const Set& s) {
        m_root = s.m_root;
        m_size = s.m_size;
    }

    void load(const std::string &nome_arquivo)
    {
        std::ifstream arq(nome_arquivo);
        if (!arq)
        {
            std::cerr << "Erro ao abrir o arquivo para leitura.\n";
            return;
        }
        int valor;
        while (arq >> valor)
        {
            insert(valor);
        }
        arq.close();
    }

    void save(const std::string &nome_arquivo) const
    {
        std::ofstream arq(nome_arquivo);
        if (!arq)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita.\n";
            return;
        }
        _salvar(m_root, arq);
        arq.close();
    }

    void _salvar(Node *node, std::ofstream &arq) const
    {
        if (!node)
            return;
        _salvar(node->left, arq);
        arq << node->key << "\n";
        _salvar(node->right, arq);
    }

    static Set intersection(const Set &P, const Set &Q)
    {
        Set result;
        P._intersection(P.m_root, Q, result);
        return result;
    }

    static Set difference(const Set &P, const Set &Q)
    {
        Set result;
        P._difference(P.m_root, Q, result);
        return result;
    };

    static Set union_between(const Set &P, const Set &Q)
    {
        Set result;

        P._inorder_insert(P.m_root, result);
        Q._inorder_insert(Q.m_root, result);
        return result;
    }

    int maximum()
    {
        if (m_root == nullptr)
        {
            throw std::runtime_error("Set is empty!");
        }

        Node *aux = m_root;
        while (aux->right != nullptr)
        {
            aux = aux->right;
        }

        return aux->key;
    }

    int minimum()
    {
        if (m_root == nullptr)
        {
            throw std::runtime_error("Set is empty!");
        }

        Node *aux = m_root;
        while (aux->left != nullptr)
        {
            aux = aux->left;
        }

        return aux->key;
    }

    int succ(int x)
    {
        if (m_root == nullptr)
        {
            throw std::runtime_error("Nenhum elemento no Set");
        }

        Node *aux = m_root;
        Node *sucessor = nullptr;

        while (aux != nullptr)
        {
            if (x < aux->key)
            {
                sucessor = aux;
                aux = aux->left;
            }
            else
            {
                aux = aux->right;
            }
        }

        if (sucessor == nullptr)
        {
            throw std::runtime_error("Nao existe sucessor no set");
        }

        return sucessor->key;
    }

    int pred(int x)
    {
        if (m_root == nullptr)
        {
            throw std::runtime_error("Nenhum elemento no Set");
        }

        Node *aux = m_root;
        Node *pred = nullptr;

        while (aux != nullptr)
        {
            if (x > aux->key)
            {
                pred = aux;
                aux = aux->right;
            }
            else
            {
                aux = aux->left;
            }
        }

        if (pred == nullptr)
        {
            throw std::runtime_error("Nao existe predecessor no set");
        }

        return pred->key;
    }

    bool empty()
    {
        return !size();
    }

    int size()
    {
        return m_size;
    }

    void swap(Set &P)
    {
        std::swap(m_root, P.m_root);
        std::swap(m_size, P.m_size);
    }

    void insert(int v)
    {
        if (!contains_iterativo(v))
        {
            m_root = _insert(m_root, v);
            m_size++;
        }
    }

    void remove(int k)
    {
        if (contains_iterativo(k))
        {
            m_root = _remove(m_root, k);
            m_size--;
        }
    }

    bool contains(int k)
    {
        return _contains(m_root, k) != nullptr;
    }

    void set_show()
    {
        std::cout << "[";
        bool first = true;
        _inorder_print(m_root, first);
        std::cout << "]" << std::endl;
    }

    bool contains_iterativo(int k) const
    {
        Node *curr = m_root;
        while (curr != nullptr)
        {
            if (curr->key == k)
                return true;
            curr = (k < curr->key) ? curr->left : curr->right;
        }
        return false;
    }

    void show()
    {
        bshow(m_root, "");
    }

    void clear()
    {
        m_root = clear(m_root);
        m_size = 0;
    }

    ~Set()
    {
        clear();
    }

private:
    Node *m_root;
    int m_size;

    int height(Node *node)
    {
        return node ? node->height : 0;
    }

    int balance(Node *node)
    {
        return height(node->right) - height(node->left);
    }

    Node *update_height(Node *node)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
        return node;
    }

    Node *right_rotation(Node *p)
    {
        Node *u = p->left;
        p->left = u->right;
        u->right = p;
        update_height(p);
        update_height(u);
        return u;
    }

    Node *left_rotation(Node *p)
    {
        Node *u = p->right;
        p->right = u->left;
        u->left = p;
        update_height(p);
        update_height(u);
        return u;
    }

    Node *fixup_node(Node *node, int k)
    {
        update_height(node);
        int bal = balance(node);
        if (bal == -2 && k < node->left->key)
            return right_rotation(node);
        if (bal == -2 && k > node->left->key)
        {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        if (bal == 2 && k > node->right->key)
            return left_rotation(node);
        if (bal == 2 && k < node->right->key)
        {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
        return node;
    }

    Node *remove_fixup_node(Node *node)
    {
        update_height(node);
        int bal = balance(node);
        if (bal < -1)
        {
            if (balance(node->left) <= 0)
                return right_rotation(node);
            else
            {
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        }
        else if (bal > 1)
        {
            if (balance(node->right) >= 0)
                return left_rotation(node);
            else
            {
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }
        return node;
    }

    Node *_insert(Node *node, int k)
    {
        if (!node)
            return new Node(k, 1, nullptr, nullptr);
        if (k < node->key)
            node->left = _insert(node->left, k);
        else if (k > node->key)
            node->right = _insert(node->right, k);
        else
            return node;

        return fixup_node(node, k);
    }

    Node *_remove(Node *node, int k)
    {
        if (!node)
            return nullptr;

        if (k < node->key)
            node->left = _remove(node->left, k);
        else if (k > node->key)
            node->right = _remove(node->right, k);
        else
        {
            Node *temp = node;
            if (!node->left)
                node = node->right;
            else if (!node->right)
                node = node->left;
            else
            {
                Node *successor = find_min(node->right);
                node->key = successor->key;
                node->right = _remove(node->right, successor->key);
                temp = nullptr;
            }
            if (temp)
                delete temp;
        }

        if (!node)
            return nullptr;
        return remove_fixup_node(node);
    }

    Node *find_min(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    Node *_contains(Node *node, int k)
    {
        if (!node || node->key == k)
            return node;
        return (k < node->key) ? _contains(node->left, k) : _contains(node->right, k);
    }

    Node *clear(Node *node)
    {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
        return nullptr;
    }

    void bshow(Node *node, std::string heranca)
    {
        if (node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right, heranca + "r");
        for (int i = 0; i < (int)heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if (heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if (node == nullptr)
        {
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if (node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    void _intersection(Node *node, const Set &Q, Set &result) const
    {
        if (node == nullptr)
            return;
        _intersection(node->left, Q, result);

        if (Q.contains_iterativo(node->key))
        {
            result.insert(node->key);
        }

        _intersection(node->right, Q, result);
    }

    void _difference(Node *node, const Set &Q, Set &result) const
    {
        if (node == nullptr)
            return;

        _difference(node->left, Q, result);
        if (!Q.contains_iterativo(node->key))
        {
            result.insert(node->key);
        }

        _difference(node->right, Q, result);
    }

    void _inorder_insert(Node *node, Set &result) const
    {
        if (node == nullptr)
            return;

        _inorder_insert(node->left, result);
        result.insert(node->key);
        _inorder_insert(node->right, result);
    }

    void _inorder_print(Node *node, bool &first) const
    {
        if (node == nullptr)
            return;

        _inorder_print(node->left, first);

        if (!first)
            std::cout << ", ";
        std::cout << node->key;
        first = false;

        _inorder_print(node->right, first);
    }
};

#endif
