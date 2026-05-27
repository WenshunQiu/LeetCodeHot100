#include <iostream>
#include <stack>

using namespace std;

struct BTNode {
    char data;
    BTNode *lchild; // first child
    BTNode *rchild; // next sibling
};

BTNode *newNode(char c) {
    BTNode *p = new BTNode;
    p->data = c;
    p->lchild = nullptr;
    p->rchild = nullptr;
    return p;
}

void makeTree(BTNode *&root) {
    // According to the sample in the statement.
    BTNode *A = newNode('A');
    BTNode *B = newNode('B');
    BTNode *C = newNode('C');
    BTNode *D = newNode('D');
    BTNode *E = newNode('E');
    BTNode *F = newNode('F');
    BTNode *G = newNode('G');
    BTNode *H = newNode('H');
    BTNode *I = newNode('I');
    BTNode *J = newNode('J');
    BTNode *K = newNode('K');

    // A -> B, C, D
    A->lchild = B;
    B->rchild = C;
    C->rchild = D;

    // B -> E, F
    B->lchild = E;
    E->rchild = F;

    // C -> I
    C->lchild = I;

    // D -> G
    D->lchild = G;

    // G -> H, J, K
    G->lchild = H;
    H->rchild = J;
    J->rchild = K;

    root = A;
}

enum FrameKind { TREE_FRAME, FOREST_FRAME };

struct StackElem {
    BTNode *node;     // TREE: current tree root; FOREST: current sibling root
    BTNode *parent;   // parent in child-sibling tree
    bool isLeftChild; // relationship to parent
    FrameKind kind;
    int stage;        // state machine stage
};

static void printNode(BTNode *p) {
    if (p != nullptr) {
        cout << p->data;
    }
}

void HTravserse(BTNode *root) {
    if (root == nullptr) {
        return;
    }

    // Non-recursive simulation of:
    // HTree(T): HTree(firstChild); visit(root); HForest(remainingChildren)
    // HForest(F): visit each tree in sibling order.
    stack<StackElem> st;
    st.push({root, nullptr, false, TREE_FRAME, 0});

    while (!st.empty()) {
        StackElem &cur = st.top();

        if (cur.kind == TREE_FRAME) {
            BTNode *x = cur.node;

            if (cur.stage == 0) {
                cur.stage = 1;
                if (x->lchild != nullptr) {
                    st.push({x->lchild, x, true, TREE_FRAME, 0});
                }
                continue;
            }

            if (cur.stage == 1) {
                // Root visit point.
                printNode(x);
                cur.stage = 2;
                continue;
            }

            if (cur.stage == 2) {
                cur.stage = 3;
                if (x->lchild != nullptr && x->lchild->rchild != nullptr) {
                    st.push({x->lchild->rchild, x, false, FOREST_FRAME, 0});
                }
                continue;
            }

            st.pop();
            continue;
        }

        // FOREST_FRAME: process sibling trees one by one.
        BTNode *s = cur.node;
        if (s == nullptr) {
            st.pop();
            continue;
        }

        if (cur.stage == 0) {
            cur.stage = 1;
            st.push({s, cur.parent, false, TREE_FRAME, 0});
            continue;
        }

        // Move to next sibling tree.
        cur.node = s->rchild;
        cur.stage = 0;
    }

    cout << '\n';
}

void freeTree(BTNode *root) {
    if (root == nullptr) {
        return;
    }
    stack<BTNode *> st;
    st.push(root);
    while (!st.empty()) {
        BTNode *p = st.top();
        st.pop();
        if (p->lchild != nullptr) {
            st.push(p->lchild);
        }
        if (p->rchild != nullptr) {
            st.push(p->rchild);
        }
        delete p;
    }
}

int main() {
    BTNode *root;
    makeTree(root);
    HTravserse(root);
    freeTree(root);
    return 0;
}
