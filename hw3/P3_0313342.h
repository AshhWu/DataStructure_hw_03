#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class TreeNode
{
    friend class BT;
    TreeNode()  //construtor
    {
        this->data=-1;
        this->right=NULL;
        this->left=NULL;
        this->parent=NULL;
    }
private:
    int data;
    TreeNode* right;    //right-child
    TreeNode* left;     //left-child
    TreeNode* parent;   //parent
};
class BT
{
public:
    BT(){ root=nullptr; }   //constructor
    BT(const char* s)            //constructor
    {
        TreeNode *Tree;       //Data裝data (tree 先用array表示法)
        int i=0;
        stringstream in;    //做字串分割
        in<<s;              //將字串s寫入stringstream
        if(in.good())
        {
            in>>height;     //第一個數字為height
            NodeNum=pow(2,height)-1;                //tree的node數量
            if(height==0)
                cout<<"empty tree!"<<endl;          //空的
            else
                Tree=new TreeNode[NodeNum+1];    //arr裝data (tree 先用array表示法)
        }
        i++;
        while(in.good())
        {
            in>>Tree[i].data;       //將數字輸出到arr的data
            //cout<<"arr["<<i<<"]="<<Tree[i].data<<' ';
            i++;
        }
        if(height)                  //若非empty
        {
            root=&Tree[1];
            //cout<<"root data:"<<root->data<<" / ";
            if(NodeNum==1)          //若只有1個Node則出
                return;
            else
            {
                TreeNode* current;
                i=1;
                while(i<=NodeNum)
                {
                    
                    current=&Tree[i];
                    if(Tree[i].data==-1||!(Tree[i].data)) ;   //若為-1則繼續下一個，或沒有輸入了
                    else
                    {
                        if(2*i<=NodeNum)         //若left-child的node存在，設定
                            current->left=&Tree[2*i];
                        if(2*i+1<=NodeNum)       //若right-child的node存在，設定
                            current->right=&Tree[2*i+1];
                        if(2*i<=NodeNum&&current->right!=NULL&&current->left!=NULL)               //若parent存在，設parent
                        {
                            current->right->parent=&Tree[i];
                            current->left->parent=&Tree[i];
                        }
                        
                    }
                    i++;
                    //cout<<"##data:"<<current->data;if(current->parent!=NULL)cout<<" / parrent:"<<current->parent->data;//<<" / right:"<<current->right->data;
                }
                current=root;
                current=current->right;
            }
        }
    }
    void inorder()
    {
        TreeNode* current;
        current=root;
        while(current->left!=NULL)
        {
            current=current->left;
        }
        //cout<<"data:"<<current->data<<endl;
        while(current!=NULL)
        {
            //cout<<"#data:"<<current->data<<endl;
            if(current->data!=-1)
                cout<<current->data<<' ';
            current=InorderSuccessor(current);
        }
        cout<<endl;
    }
    TreeNode* InorderSuccessor(TreeNode* current)
    {
        if(current->right!=NULL)
        {
            current=current->right;
            //cout<<"****data:"<<current->data<<endl;
            while(current->left!=NULL)
            {
                current=current->left;
            }
            //cout<<"****data:"<<current->data<<endl;
            
            return current;
        }
        TreeNode* p=current->parent;
        while(p!=NULL&&current==p->right)
        {
            current=p;
            p=current->parent;
        }
        return p;
        
    }
    
private:
    TreeNode* root;
    int height;
    int NodeNum;
};