#ifndef _TREE_H_
#define _TREE_H_

#include <stdint.h>

enum NodeType
{
    NodeTypeOperator = 0,
    NodeTypeOperand
};

enum Operator
{
    OperatorPlus = 0,
    OperatorMinus,
    OperatorTimes,
    OperatorOver
};

enum ChildPosition
{
    ChildPositionLeft = 0,
    ChildPositionRight
};

struct Node
{
    NodeType type;
    uint32_t value;

    Node *parent;
    Node *left;
    Node *right;
};

class Tree
{
public:
    Tree(void);
    ~Tree(void);

    static void test(void);

    uint32_t calculate(void);

private:
    void createRoot(const Node &node);
    bool addNode(const Node &node, ChildPosition position, Node *parent);
    void deleteNode(Node *node);

    uint32_t calculate(Node *node);
    uint32_t doCalculation(Operator operation, uint32_t operand1, uint32_t operand2);

    Node *m_root;
};

#endif // _TREE_H_
