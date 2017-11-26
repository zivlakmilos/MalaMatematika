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

uint32_t Tree::calculate(void) const
{
    return calculate(m_root);
}

uint32_t Tree::calculate(const std::vector<uint32_t> &numbers) const
{
    calculate(numbers);
}

uint32_t Tree::calculateDepth(void) const
{
    return calculateDepth(m_root, 0);
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

    if(node->left)
        node->left->parent = nullptr;
    if(node->right)
        node->right->parent = nullptr;
    deleteNode(node->left);
    deleteNode(node->right);

    delete node;
}

uint32_t Tree::calculate(Node *node) const
{
    if(node->type == NodeType::NodeTypeOperand)
        return node->value;

    uint32_t operand1 = calculate(node->left);
    uint32_t operand2 = calculate(node->right);

    return doCalculation(static_cast<Operator>(node->value), operand1, operand2);
}

uint32_t Tree::calculate(Node *node, const std::vector<uint32_t> &number) const
{
    if(node->type == NodeType::NodeTypeOperand)
        return node->value;

    uint32_t operand1 = calculate(node->left, number);
    uint32_t operand2 = calculate(node->right, number);

    return doCalculation(static_cast<Operator>(node->value), number[operand1], number[operand2]);
}

uint32_t Tree::doCalculation(Operator operation, uint32_t operand1, uint32_t operand2) const
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
            return operand2 && !(operand1 % operand2) ? operand1 / operand2 : operand1;
            break;
    }

    return 0;
}

uint32_t Tree::calculateDepth(Node *node, uint32_t depth) const
{
    if(!node)
        return depth;

    uint32_t depthLeft = calculateDepth(node->left, depth + 1);
    uint32_t depthRight = calculateDepth(node->right, depth + 1);

    return depthLeft > depthRight ? depthLeft : depthRight;
}

std::ostream &operator<<(std::ostream &os, const Tree& tree)
{
    /*
    uint32_t depth = tree.calculateDepth();
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
    */

    std::cout << "Binary tree" << std::endl;

    return os;
}
