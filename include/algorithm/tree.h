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
    int32_t value;

    Node *parent;
    Node *left;
    Node *right;
};

struct NodeValue
{
    int32_t value;
    Node *node;
};

class Tree
{
public:
    Tree(void);
    ~Tree(void);

    static void test(void);

    static std::shared_ptr<Tree> generateRandomTree(int operandCount);

    static std::shared_ptr<Tree> crossover(const std::shared_ptr<Tree> &parent1,
                                           const std::shared_ptr<Tree> &parent2);

    inline Node *getRoot(void) { return m_root; }
    inline void setRoot(Node *root) { m_root = root; }

    int32_t calculate(void) const;
    int32_t calculate(const std::vector<int32_t> &numbers) const;

    void reduce(const std::vector<int32_t> &numbers);
    void reduceDuplicated(void);

    uint32_t calculateDepth(void) const;
    uint32_t calculateSize(void) const;

    std::shared_ptr<Tree> duplicate(void);

    void mutation(void);

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

private:
    void createRoot(const Node &node);
    bool addNode(const Node &node, ChildPosition position, Node *parent);
    bool addNode(Node *node, ChildPosition position, Node *parent);
    void deleteNode(Node *node);
    bool swapNodes(Node *node1, Node *node2);
    Node *copyNode(Node *node);
    Node *getRandomNode(void);
    bool isAncestor(Node *node1, Node *node2);

    int32_t calculate(Node *node) const;
    int32_t calculate(Node *node, const std::vector<int32_t> &numbers) const;
    int32_t doCalculation(Operator operation, int32_t operand1, int32_t operand2) const;
    uint32_t calculateDepth(Node *node, int32_t depth) const;
    uint32_t calculateSize(Node *node) const;

    void reduce(Node *node, const std::vector<int32_t> &numbers, std::vector<NodeValue> &buffer);
    void findDuplicatedNodes(Node *node, std::vector<Node*> &nodeBuffer, std::vector<int32_t> &intBuffer);

    Node *m_root;
};

#endif // _TREE_H_
