#include"graphics.h"
#include<iostream>
#include <string>
using namespace std;
class node {
public:
    int data;
    node* left, * right;
};
class BST {
public:
    node* rootBST;
    int count;
    BST() {
        rootBST = NULL;
        count = 0;
    }
    node* insertBST(int value, node* ptr)
    {
        node* newNode = new node();
        newNode->data = value;
        if (ptr == NULL) {
            ptr = newNode;
            return ptr;
        }
        else if (value < ptr->data)
            ptr->left = insertBST(value, ptr->left);
        else if (value > ptr->data)
            ptr->right = insertBST(value, ptr->right);
        return ptr;
    }

    node* searchBST(int value) {
        node* leaf = rootBST;
        while (leaf) {
            if (leaf->data == value)
                return leaf;
            else if (value < leaf->data)
                leaf = leaf->left;
            else
                leaf = leaf->right;
        }
        return NULL;
    }
};

class tree {
public:
    int data;
    tree* left, * right;
    BST objBST;
    tree() {
        data = 0;
        left = NULL;
        right = NULL;
    }
};
class AVL {
public:
    tree* rootAVL;
    AVL() {
        rootAVL = NULL;
    }

    int height(tree* temp) {
        if (temp == NULL)
            return -1;
        else {
            int lheight = height(temp->left);
            int rheight = height(temp->right);
            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }

    int getbalFactor(tree* n) {
        if (n == NULL)
            return -1;
        return height(n->left) - height(n->right);
    }

    tree* R_rotate(tree* rep) {
        tree* temp = rep->left;
        tree* temp2 = temp->right;
        temp->right = rep;
        rep->left = temp2;
        return temp;
    }

    tree* L_rotate(tree* rep) {
        tree* temp = rep->right;
        tree* temp2 = temp->left;
        temp->left = rep;
        rep->right = temp2;
        return temp;
    }

    tree* insertAVL(tree* first, int data) {
        if (first == NULL) {
            tree* newnode = new tree();
            newnode->data = data;
            first = newnode;
            return first;
        }
        if (first->data > data)
            first->left = insertAVL(first->left, data);
        else if (first->data < data)
            first->right = insertAVL(first->right, data);

        int balFactor = getbalFactor(first);
        if (balFactor > 1 && getbalFactor(first->left) >= 0)
            return R_rotate(first);

        if (balFactor < -1 && getbalFactor(first->right) <= 0)
            return L_rotate(first);

        if (balFactor > 1 && getbalFactor(first->left) < 0) {
            first->left = L_rotate(first->left);
            return R_rotate(first);
        }

        if (balFactor < -1 && getbalFactor(first->right)>0) {
            first->right = R_rotate(first->right);
            return L_rotate(first);
        }
        return first;
    }

    tree* searchAVL(tree* ptr, int data) {
        if (ptr == NULL) {
            cout << "NULL" << endl;
            return NULL;
        }
        else {
            while (ptr != NULL) {
                if (data == ptr->data)
                    return ptr;
                else if (data < ptr->data)
                    ptr = ptr->left;
                else if (data > ptr->data)
                    ptr = ptr->right;
            }
        }
        return NULL;
    }

    void mainInsertion(int val) {
        int data = val % 10;
        tree* temp = searchAVL(rootAVL, data);
        if (temp == NULL)
            rootAVL = insertAVL(rootAVL, data);
        temp = searchAVL(rootAVL, data);
        temp->objBST.rootBST = temp->objBST.insertBST(val, temp->objBST.rootBST);
        cout << " Inserted ";
    }

    bool searchNode(int val) {
        tree* temp = searchAVL(rootAVL, val % 10);
        if (temp)
            if (temp->objBST.searchBST(val))
                return 1;
        return 0;
    }

    node* getBSTroot(int data) {
        tree* temp = searchAVL(rootAVL, data % 10);
        if (temp != NULL)
            return temp->objBST.rootBST;
        else return NULL;
    }
};

void displayAVL(tree* node, int x, int y, int sep) {
    if (node == NULL)
        return;
    circle(x, y, 25);
    string str = to_string(node->data);
    char ch[5];
    int last = 0;

    for (int i = 0; i < str.length(); i++) //string to ch array
    {
        ch[i] = str[i];
        last++;
    }
    ch[last] = '\0';

    outtextxy(x - 4, y - 8, ch);
    if (node->right) {
        setcolor(10);
        line(x, y + 25, x + 30 * sep, y + 70);
        displayAVL(node->right, x + 30 * sep, y + 95, sep - 2);
    }
    if (node->left) {
        setcolor(9);
        line(x, y + 25, x - 30 * sep, y + 70);
        displayAVL(node->left, x - 30 * sep, y + 95, sep - 2);
    }
}

void displayBST(node* ptr, int x, int y, int sep) {
    if (ptr == NULL)
        return;
    circle(x, y, 25);
    string str = to_string(ptr->data);
    char ch[5];
    int i = 0;
    for (char ch2 : str)
        ch[i++] = ch2;
    ch[i] = '\0';
    outtextxy(x - 8, y - 8, ch);
    if (ptr->right) {
        setcolor(10);
        line(x + 8, y + 25, x + 30 * sep, y + 70);
        displayBST(ptr->right, x + 30 * sep, y + 95, sep - 2);
    }
    if (ptr->left) {
        setcolor(9);
        line(x - 8, y + 25, x - 30 * sep, y + 70);
        displayBST(ptr->left, x - 30 * sep, y + 95, sep - 2);
    }
}

int type(int x, int y) {
    string str; char char_input; int cursor = 0;
    while (true) {
        outtextxy(127 + cursor, y + 60, "-");
        char_input = getch();

        if (char_input == 13 && str.length() > 0) //enter 
            break;
        else if (char_input == 8 && cursor >= 8) { //backspace
            str.pop_back();
            cursor -= 11;
            outtextxy(127 + cursor, y + 60, "   ");
        }
        else if (char_input >= '0' && char_input <= '9') {
            char n[2];
            n[0] = char_input;
            n[1] = '\0';
            outtextxy(127 + cursor, y + 60, n);
            str += char_input;
            cursor += 11;
        }
    }

    //clear entered data
    cursor += 11;
    while (cursor >= 11) {
        cursor -= 11;
        outtextxy(x + 65 + cursor, 100, "  ");
    }
    return stoi(str);
}
void gui() {
    setcolor(15);
    settextstyle(4, HORIZ_DIR, 1);
    outtextxy(570, 10, "HYBRID CHAINING MODEL");
    //style,pattern,size
    setlinestyle(SOLID_LINE, 0, 3);
    line(0, 40, 1600, 40);
}
int main() {
    int x = -1, y = -1;
    AVL objA; BST objB; int num;
    initwindow(1570, 875, "Hybrid Chaining.cpp");
    readimagefile("imgg.jpg", 0, 0, 1600, 870);
    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x, y);
    cleardevice();
    while (1) {
        gui();
        setcolor(11);
        //bold direction size
        settextstyle(10, HORIZ_DIR, 1);
        outtextxy(40, 60, "INSERT: ");
        // left top right bottom
        rectangle(120, 50, 220, 75);

        outtextxy(40, 140, "SEARCH: ");
        rectangle(120, 130, 220, 155);

        outtextxy(40, 220, "BST OF: ");
        rectangle(120, 210, 220, 235);

        outtextxy(40, 805, "EXIT");
        rectangle(32, 799, 90, 825);

        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, x, y);

        //insert
        if (x >= 120 && x <= 220 && y >= 55 && y <= 75) {
            num = type(x, -5);
            objA.mainInsertion(num);
            cleardevice();
            displayAVL(objA.rootAVL, 900, 100, 8);
        }
        //search
        if (x >= 120 && x <= 220 && y >= 130 && y <= 155) {
            num = type(60, 75);
            if (objA.searchNode(num)) {
                cleardevice();
                gui();
                setcolor(11);
                string str;
                settextstyle(10, HORIZ_DIR, 4);
                outtextxy(640, 300, "NUMBER FOUND");
                setlinestyle(DOTTED_LINE, 0, 3);
                line(560, 350, 950, 350);
                str = to_string(num);
                int last = 0;
                char ch[5];
                for (int i = 0; i < str.length(); i++) //string to ch array
                {
                    ch[i] = str[i];
                    last++;
                }
                ch[last] = '\0';
                setlinestyle(SOLID_LINE, 0, 3);
                circle(750, 417, 35);
                outtextxy(735, 400, ch);
            }
            else {
                cleardevice();
                gui();
                setcolor(11);
                settextstyle(10, HORIZ_DIR, 4);
                outtextxy(550, 300, "NUMBER NOT ENTERED YET");
                setlinestyle(DOTTED_LINE, 0, 3);
                line(500, 350, 1000, 350);
            }
            settextstyle(10, HORIZ_DIR, 2);
            setcolor(15);
            outtextxy(600, 800, ".click anywhere to continue");
            while (!ismouseclick(WM_LBUTTONDOWN)) {}
            getmouseclick(WM_LBUTTONDOWN, x, y);
            cleardevice();
        }
        //bst
        if (x >= 120 && x <= 220 && y >= 210 && y <= 235) {
            num = type(60, 155);
            cleardevice();
            if (objA.getBSTroot(num) == NULL) {
                gui();
                setcolor(11);
                settextstyle(10, HORIZ_DIR, 4);
                outtextxy(550, 300, "NUMBER NOT ENTERED YET");
                setlinestyle(DOTTED_LINE, 0, 3);
                line(500, 350, 1000, 350);
                settextstyle(10, HORIZ_DIR, 2);
                setcolor(15);
                outtextxy(600, 800, ".click anywhere to continue");
                while (!ismouseclick(WM_LBUTTONDOWN)) {}
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cleardevice();
            }
            else {
                displayBST(objA.getBSTroot(num), 750, 100, 8);
                gui();
                settextstyle(10, HORIZ_DIR, 2);
                outtextxy(10, 100, "BST OF : ");
                circle(145, 110, 25);
                string str = to_string(num);
                int last = 0;
                char ch[5];
                for (int i = 0; i < str.length(); i++) //string to ch array
                {
                    ch[i] = str[i];
                    last++;
                }
                ch[last] = '\0';
                setcolor(11);
                outtextxy(140, 100, ch);
                setcolor(15);
                outtextxy(600, 800, ".click anywhere to continue");
                while (!ismouseclick(WM_LBUTTONDOWN)) {}
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cleardevice();
            }
        }
        //exit
        if (x >= 32 && x <= 90 && y >= 799 && y <= 825)
            return 0;
    }
    system("pause");
    return 0;
}
