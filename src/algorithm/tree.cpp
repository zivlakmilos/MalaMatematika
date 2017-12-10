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

    std::shared_ptr<Tree> tree2 = tree.duplicate();
    tree2->reduce(numbers);

    //std::cout << tree << std::endl;
    //std::cout << *tree2 << std::endl;

    std::shared_ptr<Tree> tmp1 = tree.duplicate();
    std::shared_ptr<Tree> tmp2 = Tree::generateRandomTree(6);

    //std::shared_ptr<Tree> child = Tree::crossover(tmp1, tmp2);
    //child->reduceDuplicated();
    //std::cout << *tmp2 << std::endl;
    //std::cout << *child << std::endl;;

    std::cout << *tmp2 << std::endl;
    tmp2->mutation();
    std::cout << *tmp2 << std::endl;
}

std::shared_ptr<Tree> Tree::generateRandomTree(int operandCount)
{
    Random random;
    std::vector<uint8_t> operandi;
    for(int i = 0; i < 6; i++)
        operandi.push_back(i);

    std::vector<Node> nodes;

    Node node;
    int operandCount2 = 0;
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

std::shared_ptr<Tree> Tree::crossover(const std::shared_ptr<Tree> &parent1,
                                      const std::shared_ptr<Tree> &parent2)
{
    std::shared_ptr<Tree> result = parent1->duplicate();

    Node *node1;
    Node *node2;

    do
    {
        node1 = result->getRandomNode();
        node2 = parent2->getRandomNode();
    } while((result->calculateSize(node1) + 1) / 2 < (result->calculateSize(node2) + 1) / 2);

    Node *parent = node1->parent;
    if(parent)
    {
        ChildPosition position = parent->left == node1 ? ChildPositionLeft : ChildPositionRight;
        result->deleteNode(node1);
        result->addNode(node2, position, parent);
    } else
    {
        result->deleteNode(node1);
        result->createRoot(*node2);
        result->addNode(node2->left, ChildPositionLeft, result->m_root);
        result->addNode(node2->right, ChildPositionRight, result->m_root);
    }

    return result;
}

int32_t Tree::calculate(void) const
{
    return calculate(m_root);
}

int32_t Tree::calculate(const std::vector<int32_t> &numbers) const
{
    return calculate(m_root, numbers);
}

uint32_t Tree::calculateDepth(void) const
{
    return calculateDepth(m_root, 0);
}

uint32_t Tree::calculateSize(void) const
{
    return calculateSize(m_root);
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

void Tree::reduceDuplicated(void)
{
    Random random;
    std::vector<Node*> duplicateNodes;
    std::vector<int32_t> ussedIntegers;
    std::vector<int32_t> freeIntegers;

    findDuplicatedNodes(m_root, duplicateNodes, ussedIntegers);

    if(duplicateNodes.empty())
        return;

    for(int i = 0; i < 6; i++)
    {
        bool duplicated = false;
        for(auto it = ussedIntegers.begin(); it != ussedIntegers.end(); it++)
        {
            if(i == *it)
            {
                duplicated = true;
                break;
            }
        }

        if(!duplicated)
            freeIntegers.push_back(i);
    }

    for(auto it = duplicateNodes.begin(); it != duplicateNodes.end(); it++)
    {
        int32_t rand = random.nextInt(freeIntegers.size());
        (*it)->value = freeIntegers[rand];
        freeIntegers.erase(freeIntegers.begin() + rand);
    }
}

std::shared_ptr<Tree> Tree::duplicate(void)
{
    std::shared_ptr<Tree> result = std::make_shared<Tree>();

    result->createRoot(*m_root);
    result->m_root->left = copyNode(m_root->left);
    result->m_root->right = copyNode(m_root->right);

    if(result->m_root->left)
        result->m_root->left->parent = result->m_root;
    if(result->m_root->right)
        result->m_root->right->parent = result->m_root;

    return result;
}

void Tree::mutation(void)
{
    Random random;

    if(random.nextFloat() > 0.5f)
    {
        Node *node1;
        Node *node2;

        do
        {
            node1 = getRandomNode();
            node2 = getRandomNode();
        } while(isAncestor(node1, node2));

        swapNodes(node1, node2);
    } else
    {
        Node *node;
        do
        {
            node = getRandomNode();
        } while(node->type != NodeTypeOperand);

        std::vector<Node*> duplicateNodes;
        std::vector<int32_t> ussendNumbers;
        std::vector<int32_t> freeNumbers;
        findDuplicatedNodes(m_root, duplicateNodes, ussendNumbers);

        for(int i = 0; i < 6; i++)
        {
            bool duplicate = false;
            for(auto it = ussendNumbers.begin(); it != ussendNumbers.end(); it++)
            {
                if(i == *it)
                {
                    duplicate = true;
                    break;
                }
            }
            if(!duplicate)
                freeNumbers.push_back(i);
        }

        if(!freeNumbers.empty())
        {
            int32_t rand = random.nextInt(freeNumbers.size());
            node->value = freeNumbers[rand];
        }
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

bool Tree::addNode(Node *node, ChildPosition position, Node *parent)
{
    if(!parent || !node)
        return false;

    Node *tmp = copyNode(node);
    node->parent = nullptr;

    if(position == ChildPositionLeft && !parent->left)
    {
        parent->left = tmp;
        tmp->parent = parent;
    } else if(position == ChildPositionRight && !parent->right)
    {
        parent->right = tmp;
        tmp->parent = parent;
    } else
    {
        deleteNode(node);
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
    } else
    {
        m_root = nullptr;
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

Node *Tree::copyNode(Node *node)
{
    if(!node)
        return nullptr;

    Node *result = new Node;
    result->type = node->type;
    result->value = node->value;

    result->left = copyNode(node->left);
    result->right = copyNode(node->right);

    if(result->left)
        result->left->parent = result;
    if(result->right)
        result->right->parent = result;

    return result;
}

Node *Tree::getRandomNode(void)
{
    uint32_t size = calculateSize();
    if(size == 0)
        return nullptr;

    Random random;
    uint32_t rand = random.nextInt(size);

    if(rand == 0)
        return m_root;

    std::vector<Node*> buffer;
    std::vector<Node*> tmp;
    buffer.push_back(m_root);

    uint32_t i = 0;
    while(!buffer.empty())
    {
        for(auto it = buffer.begin(); it != buffer.end(); it++)
        {
            if((*it)->left)
            {
                if(++i == rand)
                    return (*it)->left;
                tmp.push_back((*it)->left);
            }

            if((*it)->right)
            {
                if(++i == rand)
                    return (*it)->right;
                tmp.push_back((*it)->right);
            }
        }

        buffer.swap(tmp);
        tmp.clear();
    }

    return nullptr;
}

bool Tree::isAncestor(Node *node1, Node *node2)
{
    Node *tmp = node1;
    while(tmp)
    {
        if(tmp == node2)
            return true;
        tmp = tmp->parent;
    }

    tmp = node2;
    while(tmp)
    {
        if(tmp == node1)
            return true;
        tmp = tmp->parent;
    }

    return false;
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

uint32_t Tree::calculateDepth(Node *node, int32_t depth) const
{
    if(!node)
        return depth;

    int32_t depthLeft = calculateDepth(node->left, depth + 1);
    int32_t depthRight = calculateDepth(node->right, depth + 1);

    return depthLeft > depthRight ? depthLeft : depthRight;
}

uint32_t Tree::calculateSize(Node *node) const
{
    if(!node)
        return 0;

    uint32_t left = calculateSize(node->left);
    uint32_t right = calculateSize(node->right);

    return left + right + 1;
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

void Tree::findDuplicatedNodes(Node *node, std::vector<Node*> &nodeBuffer, std::vector<int32_t> &intBuffer)
{
    if(!node)
        return;

    std::vector<Node*> currentBuffer;
    std::vector<Node*> nextBuffer;
    currentBuffer.push_back(node);

    while(!currentBuffer.empty())
    {
        for(auto it = currentBuffer.begin(); it != currentBuffer.end(); it++)
        {
            if((*it)->type == NodeTypeOperator)
            {
                nextBuffer.push_back((*it)->left);
                nextBuffer.push_back((*it)->right);
            } else
            {
                bool duplicated = false;
                for(auto it2 = intBuffer.begin(); it2 != intBuffer.end(); it2++)
                {
                    if((*it)->value == *it2)
                    {
                        duplicated = true;
                        nodeBuffer.push_back(*it);
                        break;
                    }
                }
                if(!duplicated)
                {
                    intBuffer.push_back((*it)->value);
                }
            }
        }

        currentBuffer.swap(nextBuffer);
        nextBuffer.clear();
    }
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
