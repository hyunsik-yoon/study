#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

// 1628_Design_an_Expression_Tree_With_Evaluate_Function

// https://leetcode.com/problems/design-an-expression-tree-with-evaluate-function/description/

/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node () {};
    virtual int evaluate() const = 0;
};

class OpNode : public Node {
protected:
    OpNode(Node *l, Node *r): left{l}, right{r} { }
    // define your fields here
    Node *left;
    Node *right;
};

class Add : public OpNode {
public:
    Add(Node *l, Node *r): OpNode{l, r} { }
    virtual ~Add () {};
    virtual int evaluate() const
    {
        return left->evaluate() + right->evaluate();
    }
};

class Sub : public OpNode {
public:
    Sub(Node *l, Node *r): OpNode{l, r} { }
    virtual ~Sub () {};
    virtual int evaluate() const
    {
        return left->evaluate() - right->evaluate();
    }
};

class Mul : public OpNode {
public:
    Mul(Node *l, Node *r): OpNode{l, r} { }
    virtual ~Mul () {};
    virtual int evaluate() const
    {
        return left->evaluate() * right->evaluate();
    }
};

class Div : public OpNode {
public:
    Div(Node *l, Node *r): OpNode{l, r} { }
    virtual ~Div () {};
    virtual int evaluate() const
    {
        return left->evaluate() / right->evaluate();
    }
};

class NumNode: public Node {
public:
    virtual ~NumNode () {};
    NumNode (int val): _val{val} { }
    virtual int evaluate() const
    {
        return _val;
    }

private:
    int _val;
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input
 * and returns the expression tree represnting it as a Node.
 */

bool is_op(const string &ch)
{
    return ch.length() == 1 && (ch == "+" || ch == "-" || ch == "*" || ch == "/");
}

class OpNodeFactory
{
public:
    static OpNode *get(const string &token, Node *first, Node *second)
    {
        if (token == "+")
            return new Add(first, second);
        else if (token == "-")
            return new Sub(first, second);
        else if (token == "*")
            return new Mul(first, second);
        else if (token == "/")
            return new Div(first, second);
        else
            throw runtime_error("not supported op");
    }
};

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix)
    {
        /* TC
        ["1"], ["6", "2", "*", "12", "/"]
        */
        stack<Node *> st;

        for (auto &token: postfix)
        {
            if (is_op(token))
            {
                Node *second = st.top(); st.pop();
                Node *first = st.top(); st.pop();

                st.push(OpNodeFactory::get(token, first, second));
            }
            else
            {
                st.push(new NumNode(stoi(token)));
            }
        }

        return st.top();
    }
};

/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */
