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
    Node* root = m_root;
    QStack<Node*> stack;

    foreach(QChar c, str) {
        if (c == 'I') {
            root = insert(Term::I, root);
        } else if (c == 'K') {
            root = insert(Term::K, root);
        } else if (c == 'S') {
            root = insert(Term::S, root);
        } else if (c == '(') {
            stack.push(root); // push the current root
            root = new Node;
            root->id = m_id++;
        } else if (c == ')') {
            Node* oldRoot = stack.pop();
            if (!oldRoot->right) {
                oldRoot->right = root;
                root->parent = oldRoot;
                root = oldRoot;
            } else {
                Node* newRoot = new Node;
                newRoot->id = m_id++;
                newRoot->left = oldRoot;
                newRoot->right = root;
                oldRoot->parent = newRoot;
                root->parent = newRoot;
                root = newRoot;
            }
        } else {
            qDebug() << "error constructing tree!";
        }
    }

    m_root = root;
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
