#ifndef _TREE_H_
#define _TREE_H_

#include <stdint.h>
#include <vector>
#include <memory>
#include <ostream>

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

    static std::shared_ptr<Tree> generateRandomTree(int operandCount);

    inline Node *getRoot(void) { return m_root; }
    inline void setRoot(Node *root) { m_root = root; }

    uint32_t calculate(void) const;
    uint32_t calculate(const std::vector<uint32_t> &numbers) const;

    uint32_t calculateDepth(void) const;

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

private:
    void createRoot(const Node &node);
    bool addNode(const Node &node, ChildPosition position, Node *parent);
    void deleteNode(Node *node);

    uint32_t calculate(Node *node) const;
    uint32_t calculate(Node *node, const std::vector<uint32_t> &number) const;
    uint32_t doCalculation(Operator operation, uint32_t operand1, uint32_t operand2) const;
    uint32_t calculateDepth(Node *node, uint32_t depth) const;

    Node *m_root;
};

#endif // _TREE_H_
