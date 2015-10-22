#ifndef bt_h
#define bt_h

#include <QtCore>

enum Term {
    I = 1,
    K = 2,
    S = 3
};

struct Node {
    Node()
        : left(0)
        , right(0)
        , parent(0)
        , term(Term(0))
        , id(0)
    { }

    Node* left;
    Node* right;
    Node* parent;
    Term term;
    uint id;

    QString toString() const
    {
        switch (term) {
        case I:
            return "I";
        case K:
            return "K";
        case S:
            return "S";
        default:
            return "";
        }
    }
};

class BT {
public:
    BT();
    ~BT();

    void construct(const QString&);
    void insert(const Term&);
    void clear();
    QByteArray graph() const;

private:
    Node* insert(const Term& term, Node* root);
    void clear(Node* node);
    void walk(QTextStream* stream, const Node* node) const;

    Node* m_root;
    uint m_id;
};

#endif // bt_h
