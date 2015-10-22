#include "bt.h"

BT::BT()
{
    m_id = 0;
    m_root = new Node;
    m_id++;
}

BT::~BT()
{
    clear();
}

void BT::construct(const QString& str)
{
    foreach(QChar c, str) {
        if (c == 'I')
            insert(Term::I);
        else if (c == 'K')
            insert(Term::K);
        else if (c == 'S')
            insert(Term::S);
        else
            qDebug() << "error constructing tree!";
    }
}

void BT::insert(const Term& term)
{
    m_root = insert(term, m_root);
}

Node* BT::insert(const Term& term, Node* root)
{
    Node* node = root;
    bool rootLeft = root->left;
    bool rootRight = root->right;

    if (rootLeft && !rootRight) {
        // Make a new right for existing root
        node = new Node;
        node->id = m_id++;
        root->right = node;
        node->parent = root;
    } else {
        // Make a new root and set current root to left
        root = new Node;
        root->id = m_id++;
        root->left = node;
        node->parent = root;
    }

    if (rootLeft && rootRight) {
        // Make a new right for existing root
        node = new Node;
        node->id = m_id++;
        root->right = node;
        node->parent = node;
    }

    node->term = term;
    return root;
}

void BT::walk(QTextStream* stream, const Node* node) const
{
    if (!node)
        return;

    *stream << "\t" << node->id << " [label=\""
        << node->toString() << "\", shape=\"circle\"]" << endl;

    if (node->left) {
        *stream << "\t" << node->id << " -- " << node->left->id << ";" << endl;
        walk(stream, node->left);
    }

    if (node->right) {
        *stream << "\t" << node->id << " -- " << node->right->id << ";" << endl;
        walk(stream, node->right);
    }
}

QByteArray BT::graph() const
{
    QByteArray bytes;
    QTextStream stream(&bytes, QIODevice::ReadWrite);
    stream << "graph {" << endl;
    walk(&stream, const_cast<const Node*>(m_root));
    stream << "}" << endl;
    stream.flush();
    return bytes;
}

void BT::clear()
{
    clear(m_root);
    m_root = 0;
    m_id = 0;
}

void BT::clear(Node* node)
{
    if (!node)
        return;

    clear(node->left);
    clear(node->right);
    node->left = 0;
    node->right = 0;
    delete node;
}
