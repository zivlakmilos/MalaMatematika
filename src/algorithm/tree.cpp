#include "algorithm/tree.h"

#include <iostream>

Tree::Tree(void)
    : m_root(nullptr)
{
}

Tree::~Tree(void)
{
    deleteNode(m_root);
}

uint32_t Tree::calculate(void)
{
    return calculate(m_root);
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
    } else if(position == ChildPositionRight && !parent->right)
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

    if(!node->parent)
    {
        if(node->left)
            node->left->parent = nullptr;
        if(node->right)
            node->right->parent = nullptr;
        deleteNode(node->left);
        deleteNode(node->right);
        return;
    }

    Node tmp;
    tmp.type = node->type;
    tmp.value = node->value;
    tmp.parent = node->parent;
    tmp.left = node->left;
    tmp.right = node->right;

    ChildPosition nodePosition;
    if(node->parent)
    {
        nodePosition = node->parent->left == node ? ChildPosition::ChildPositionLeft
                                                  : ChildPosition::ChildPositionRight;
    }

    delete node;

    if(node->type == NodeType::NodeTypeOperator)
    {
        if(nodePosition == ChildPosition::ChildPositionLeft)
        {
        } else
        {
        }
    } else
    {
    }
}

uint32_t Tree::calculate(Node *node)
{
    if(node->type == NodeType::NodeTypeOperand)
        return node->value;

    uint32_t operand1 = calculate(node->left);
    uint32_t operand2 = calculate(node->right);
    return doCalculation(static_cast<Operator>(node->value), operand1, operand2);
}

uint32_t Tree::doCalculation(Operator operation, uint32_t operand1, uint32_t operand2)
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
