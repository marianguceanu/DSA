#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r)
{
    // TODO - Implementation
    relation = r;
    length = 0;
    tree = nullptr;
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
void SortedBag::add(TComp e)
{
    // TODO - Implementation
    if (tree == nullptr)
        tree = createNode(e);
    else
        addValueToTree(tree, e);
    length++;
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: Theta(log length)
 */
bool SortedBag::remove(TComp e)
{
    // TODO - Implementation
    auto nodeToRemove = findNode(tree, e);
    if (nodeToRemove == nullptr)
        return false;
    auto parent = findParent(tree, e);
    if (length == 1)
        removeNode(tree);
    else if (parent == nullptr && (nodeToRemove->left == nullptr || nodeToRemove->right == nullptr))
    {
        if (nodeToRemove->left == nullptr)
        {
            auto node = nodeToRemove->right;
            removeNode(tree);
            tree = node;
        }
        else
        {
            auto node = nodeToRemove->left;
            removeNode(tree);
            tree = node;
        }
    }
    else if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
    {
        if (relation(nodeToRemove->value, parent->value))
            removeNode(parent->left);
        else
            removeNode(parent->right);
    }
    else if (nodeToRemove->left == nullptr && nodeToRemove->right != nullptr)
    {
        if (relation(nodeToRemove->value, parent->value))
            parent->left = nodeToRemove->right;
        else
            parent->right = nodeToRemove->right;
        removeNode(nodeToRemove);
    }
    else if (nodeToRemove->left != nullptr && nodeToRemove->right == nullptr)
    {
        if (relation(nodeToRemove->value, parent->value))
            parent->left = nodeToRemove->left;
        else
            parent->right = nodeToRemove->left;
        removeNode(nodeToRemove);
    }
    else
    {
        auto maxNode = nodeToRemove->left;
        if (maxNode->right == nullptr)
        {
            nodeToRemove->left = maxNode->left;
            removeNode(maxNode);
        }
        else
        {
            Node *previousMaxNode = nullptr;
            while (maxNode->right != nullptr)
            {
                previousMaxNode = maxNode;
                maxNode = maxNode->right;
            }
            nodeToRemove->value = maxNode->value;
            removeNode(previousMaxNode->right);
        }
    }
    length--;
    return true;
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
bool SortedBag::search(TComp elem) const
{
    // TODO - Implementation
    return doesContain(tree, elem);
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
int SortedBag::nrOccurrences(TComp elem) const
{
    // TODO - Implementation
    auto count = 0;
    countValue(findNode(tree, elem), elem, count);
    return count;
}

// O(1)
int SortedBag::size() const
{
    // TODO - Implementation
    return length;
}

// O(1)
bool SortedBag::isEmpty() const
{
    // TODO - Implementation
    return length < 1;
}

SortedBagIterator SortedBag::iterator() const
{
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag()
{
    // TODO - Implementation
    destroyTree(tree);
}

// O(1)
Node *SortedBag::createNode(int value, Node *left, Node *right)
{
    auto node = new Node;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}
/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
void SortedBag::addValueToTree(Node *root, TComp value)
{
    if (relation(value, root->value))
    {
        if (root->left == nullptr)
        {
            root->left = createNode(value);
        }
        else
        {
            addValueToTree(root->left, value);
        }
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = createNode(value);
        }
        else
        {
            addValueToTree(root->right, value);
        }
    }
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
bool SortedBag::doesContain(Node *root, TComp value) const
{
    if (root == nullptr)
        return false;
    if (root->value == value)
        return true;
    if (relation(value, root->value))
        return doesContain(root->left, value);
    return doesContain(root->right, value);
}

/*
 * Best case: Theta(1)
 * Worst case: Theta (log length)
 * Overall: O(log length)
 */
Node *SortedBag::findParent(Node *root, TComp value) const
{
    if (root->value == value)
        return nullptr;
    if (relation(value, root->value))
    {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->value == value)
            return root;
        return findParent(root->left, value);
    }
    if (root->right == nullptr)
        return nullptr;
    if (root->right->value == value)
        return root;
    return findParent(root->right, value);
}

void SortedBag::filter(Condition cond)
{
    int iterated;
    auto stop = false;
    TComp current;
    iterator().iterateTree(
        tree, [&](Node *node)
        {
        current = node->value;
        if(!cond(current))
            remove(current);
        iterated++;
        if(iterated == length)
            stop = true; },
        stop);
}
/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
Node *SortedBag::findNode(Node *root, TComp value) const
{
    if (root == nullptr)
        return nullptr;
    if (root->value == value)
        return root;
    if (relation(value, root->value))
        return findNode(root->left, value);
    return findNode(root->right, value);
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
Node *SortedBag::findMin(Node *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->left == nullptr)
        return root;
    return findMin(root->left);
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
void SortedBag::countValue(Node *root, TComp value, int &count) const
{
    if (root == nullptr)
        return;
    if (root->value == value)
        count++;
    if (relation(value, root->value))
        countValue(root->left, value, count);
    countValue(root->right, value, count);
}
// O(1)
void SortedBag::removeNode(Node *&node)
{
    delete node;
    node = nullptr;
}

/*
 * Best case: Theta(1)
 * Worst case: Theta(log length)
 * Overall: O(log length)
 */
void SortedBag::destroyTree(Node *root)
{
    if (root == nullptr)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}