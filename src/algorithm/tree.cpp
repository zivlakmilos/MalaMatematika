#include "algorithm/tree.h"

#include <iomanip>
#include <stack>

#include "core/random.h"

#include <iostream>

Tree::Tree(void)
    : m_root(nullptr)
{
}

Tree::~Tree(void)
{
    deleteNode(m_root);
}

void Tree::test(void)
{
    Tree tree;
    Node node;

    std::vector<int32_t> numbers = { 0, 1, 2, 3, 50, 100 };

    node.type = NodeTypeOperator;
    node.value = OperatorMinus;
    tree.createRoot(node);

    node.type = NodeTypeOperator;
    node.value = OperatorPlus;
    tree.addNode(node, ChildPositionLeft, tree.m_root);

    node.type = NodeTypeOperand;
    node.value = 1;
    tree.addNode(node, ChildPositionRight, tree.m_root);

    node.type = NodeTypeOperand;
    node.value = 0;
    tree.addNode(node, ChildPositionLeft, tree.m_root->left);

    node.type = NodeTypeOperand;
    node.value = 2;
    tree.addNode(node, ChildPositionRight, tree.m_root->left);

    tree.reduce(numbers);

    std::cout << tree << std::endl;
              //<< tree.calculate(numbers) << std::endl;
}

std::shared_ptr<Tree> Tree::generateRandomTree(int operandCount)
{
    Random random;
    std::vector<uint8_t> operandi;
    for(int i = 0; i < 6; i++)
        operandi.push_back(i);

    std::vector<Node> nodes;

    Node node;
    int operandCount2;
    while(operandCount > 0)
    {
        if(operandCount2 >= 2)
        {
            if(random.nextInt(2))
            {
                node.type = NodeTypeOperator;
                node.value = random.nextInt(4);
                operandCount2--;
            } else
            {
                uint8_t index = random.nextInt(operandi.size());
                node.type = NodeTypeOperand;
                node.value = operandi[index];
                operandi.erase(operandi.begin() + index);
                operandCount2++;
                operandCount--;
            }
        } else
        {
            uint8_t index = random.nextInt(operandi.size());
            node.type = NodeTypeOperand;
            node.value = operandi[index];
            operandi.erase(operandi.begin() + index);
            operandCount2++;
            operandCount--;
        }

        nodes.push_back(node);
    }

    while(operandCount2-- > 1)
    {
        node.type = NodeTypeOperator;
        node.value = random.nextInt(4);
        nodes.push_back(node);
    }

    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if(it->type == NodeTypeOperator)
        {
            switch(it->value)
            {
                case OperatorPlus:
                    std::cout << '+';
                    break;
                case OperatorMinus:
                    std::cout << '-';
                    break;
                case OperatorTimes:
                    std::cout << '*';
                    break;
                case OperatorOver:
                    std::cout << '/';
                    break;
            }
        } else
        {
            std::cout << it->value;
        }
    }
    std::cout << std::endl;

    auto it = nodes.rbegin();

    std::shared_ptr<Tree> tree = std::make_shared<Tree>();
    tree->createRoot(*it);
    it++;

    std::stack<Node*> stack;
    stack.push(tree->m_root);

    for(; it != nodes.rend(); it++)
    {
        if(it->type == NodeTypeOperator)
        {
            Node *node = stack.top();
            if(!node->left)
            {
                if(tree->addNode(*it, ChildPositionLeft, node))
                    stack.push(node->left);
            } else
            {
                if(tree->addNode(*it, ChildPositionRight, node))
                {
                    stack.pop();
                    stack.push(node->right);
                }
            }
        } else
        {
            Node *node = stack.top();
            if(!node->left)
            {
                tree->addNode(*it, ChildPositionLeft, node);
            } else
            {
                if(tree->addNode(*it, ChildPositionRight, node))
                    stack.pop();
            }
        }
    }

    return tree;
}

int32_t Tree::calculate(void) const
{
    return calculate(m_root);
}

int32_t Tree::calculate(const std::vector<int32_t> &numbers) const
{
    return calculate(m_root, numbers);
}

int32_t Tree::calculateDepth(void) const
{
    return calculateDepth(m_root, 0);
}

void Tree::reduce(const std::vector<int32_t> &numbers)
{
    std::vector<NodeValue> buffer;
    Node *node = reduce(m_root, numbers, buffer);
    if(node)
    {
        Node newNode;
        newNode.type = node->type;
        newNode.value = node->value;
        createRoot(newNode);
    }
}

void Tree::createRoot(const Node &node)
{
    if(m_root)
        deleteNode(m_root);

    m_root = new Node;
    m_root->parent = nullptr;
    m_root->left = nullptr;
    m_root->right = nullptr;

    m_root->type = node.type;
    m_root->value = node.value;
}

bool Tree::addNode(const Node &node, ChildPosition position, Node *parent)
{
    if(!parent)
        return false;

    Node *tmp = new Node;
    tmp->type = node.type;
    tmp->value = node.value;
    tmp->parent = parent;
    tmp->left = nullptr;
    tmp->right = nullptr;

    if(position == ChildPosition::ChildPositionLeft && !parent->left)
    {
        parent->left = tmp;
    } else if(position == ChildPosition::ChildPositionRight && !parent->right)
    {
        parent->right = tmp;
    } else
    {
        delete tmp;
        return false;
    }

    return true;
}

void Tree::deleteNode(Node *node)
{
    if(!node)
        return;

    if(node->parent)
    {
        if(node->parent->left == node)
            node->parent->left = nullptr;
        if(node->parent->right == node)
            node->parent->right = nullptr;
    }
    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

bool Tree::swapNodes(Node *node1, Node *node2)
{
    if(!node1 || !node2 || node1 == m_root || node2 == m_root)
        return false;
    if(node1 == node2)
        return true;

    Node *parent1 = node1->parent;
    Node *parent2 = node2->parent;

    if(parent1 == parent2)
    {
        Node *tmp = parent1->left;
        parent1->left = parent1->right;
        parent1->right = tmp;
    } else
    {
        node1->parent = parent2;
        node2->parent = parent1;

        if(parent1)
        {
            if(parent1->left == node1)
                parent1->left = node2;
            else if(parent1->right == node1)
                parent1->right = node2;
        }
        if(parent2)
        {
            if(parent2->left == node2)
                parent2->left = node1;
            else if(parent2->right == node2)
                parent2->right = node1;
        }
    }

    return true;
}

int32_t Tree::calculate(Node *node) const
{
    if(node->type == NodeType::NodeTypeOperand)
        return node->value;

    int32_t operand1 = calculate(node->left);
    int32_t operand2 = calculate(node->right);

    return doCalculation(static_cast<Operator>(node->value), operand1, operand2);
}

int32_t Tree::calculate(Node *node, const std::vector<int32_t> &numbers) const
{
    if(node->type == NodeType::NodeTypeOperand)
        return numbers[node->value];

    int32_t operand1 = calculate(node->left, numbers);
    int32_t operand2 = calculate(node->right, numbers);

    return doCalculation(static_cast<Operator>(node->value), operand1, operand2);
}

int32_t Tree::doCalculation(Operator operation, int32_t operand1, int32_t operand2) const
{
    switch(operation)
    {
        case Operator::OperatorPlus:
            return operand1 + operand2;
            break;
        case Operator::OperatorMinus:
            return operand1 - operand2;
            break;
        case Operator::OperatorTimes:
            return operand1 * operand2;
            break;
        case Operator::OperatorOver:
            return !operand2 || (operand1 % operand2) ? operand1 : operand1 / operand2;
            break;
    }

    return 0;
}

int32_t Tree::calculateDepth(Node *node, int32_t depth) const
{
    if(!node)
        return depth;

    int32_t depthLeft = calculateDepth(node->left, depth + 1);
    int32_t depthRight = calculateDepth(node->right, depth + 1);

    return depthLeft > depthRight ? depthLeft : depthRight;
}

Node *Tree::reduce(Node *node, const std::vector<int32_t> &numbers, std::vector<NodeValue> &buffer)
{
    if(!node)
        return nullptr;

    if(node->type == NodeTypeOperand)
    {
        NodeValue nodeValue;
        nodeValue.node = node;
        nodeValue.value = numbers[node->value];
        buffer.push_back(nodeValue);
        return nullptr;
    }

    Node *left = reduce(node->left, numbers, buffer);
    if(left)
    {
        Node newNode;
        newNode.type = left->type;
        newNode.value = left->value;
        deleteNode(node->left);
        addNode(newNode, ChildPositionLeft, node);
    }

    Node *right = reduce(node->right, numbers, buffer);
    if(right)
    {
        Node newNode;
        newNode.type = right->type;
        newNode.value = right->value;
        deleteNode(node->right);
        addNode(newNode, ChildPositionRight, node);
    }

    int32_t result = calculate(node, numbers);
    for(auto it = buffer.begin(); it != buffer.end(); it++)
    {
        if(it->value == result)
        {
            return it->node;
        }
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Tree& tree)
{
    int32_t depth = tree.calculateDepth();
    std::vector<Node*> tmp;
    std::vector<Node*> nodes;
    nodes.push_back(tree.m_root);
    for(int i = 0; i < depth; i++)
    {
        for(auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if((*it)->type == NodeTypeOperator)
            {
                switch((*it)->value)
                {
                    case OperatorPlus:
                        os << '+';
                        break;
                    case OperatorMinus:
                        os << '-';
                        break;
                    case OperatorTimes:
                        os << '*';
                        break;
                    case OperatorOver:
                        os << '/';
                        break;
                }
            } else
            {
                os << (*it)->value;
            }

            if((*it)->left)
                tmp.push_back((*it)->left);
            if((*it)->right)
                tmp.push_back((*it)->right);
        }
        os << std::endl;

        nodes = tmp;
        tmp.clear();
    }

    return os;
}
