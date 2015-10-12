#ifndef CTREE_H
#define CTREE_H

#include <iostream>
#include <utility>

template<class T> class CTree
{
public:
    CTree() {m_root = 0;}
    ~CTree() {

        
        delete m_root;
    }


    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;}
        Node(const T &t) {m_number = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_number;}
        const T &Data() const {return m_number;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_number;

    };
    void Insert(const T &t,  Node * &root)

    {
        if (root == nullptr)
            root= new Node (t);
        else if (t<root->m_number)
            Insert(t, root->m_ll);
        else if (t>root->m_number)
            Insert(t, root->m_rl);
    }

    void Insert(const T &t) {
        Insert(t, m_root); //overload
    }

// root preorder(left) preorder(right)
    void Preorder(std::ostream &out, Node * &root) {
        if (root==nullptr)
            return;
        out<<root->m_number<<"     ";
        Preorder(out, root->m_ll);
        Preorder(out, root->m_rl);   
    }


    // root preorder(left) preorder(right)
    void Preorder(std::ostream &p_str) {
        Preorder(p_str, m_root);
       
    }
    int Depth(Node * &t) {
        if (t==nullptr)
            return -1;
        else 
            return 1 + std::max(Depth(t->m_ll), Depth(t->m_rl));
        
    }
    int Depth() {
        return Depth(m_root);
    }
    Node *Find(const T &t, Node * &root) {
        if (t== nullptr)
            return (nullptr);
        else if(t < root->m_number)
            return Find(t, root->m_ll);
        else if( t > root->m_number)
            return Find(t, root->m_rl);
        else return root; 

    }


    


    const Node *Find(const T &t) const {}
    Node *Find(const T &t) {
        Node * result= Find(t, m_root);

    }
    std::pair<Node *, Node*> findMin(Node *root) const{
        Node *parent= nullptr;
        Node *cp =root;
        while (cp->m_ll != nullptr){
             parent=cp;
             cp=cp->m_ll;

        }
        return {parent, cp};
      
    }
    std::pair<Node *, Node*> findMax(Node *root) const{
        Node *parent= nullptr;
        Node *cp =root;
        while (cp->m_rl != nullptr){
             parent=cp;
             cp=cp->m_rl;

        }
        return {parent, cp};
      
    }

           


   /* Node * findMin(Node *t) const{
        if (t==nullptr)
            return nullptr;
        if (t->m_ll == nullptr)
            return t;
        return findMin( t-> m_ll);

    }*/
     void Delete(const T &t, Node * &root, Node *&child)
    {
        if (child == nullptr)
            return;
        //found node we want to delete
        if (child->m_number == t){
            //case 1 children are nullptr
            if (child->m_ll == nullptr && child->m_rl==nullptr){
                if (child == root->m_ll)
                    root->m_ll=nullptr; //break link
                if (child == root->m_rl)
                    root->m_rl=nullptr; //break link
                delete child;
                return;
            }
            //case 2 left child is nulptr
            if (child->m_ll == nullptr){
                auto minPair=findMin(child->m_rl);
                minPair.first = minPair.first==nullptr ? child :minPair.first;
                auto tmp= minPair.second->m_number;
                Delete(tmp, child, child->m_rl);
                child->m_number= tmp;
                return;

            }
            //case 3 child right is nullptr
            if (child->m_rl == nullptr){
                auto maxPair = findMax(child->m_ll);
                maxPair.first = maxPair.first == nullptr ? child : maxPair.first;
                auto tmp = maxPair.second->m_number;
                Delete(tmp, child, child->m_ll);
                child->m_number = tmp;
                return;


            }
            //case 4 two children are present
            else{
                auto minPair=findMin(child->m_rl);
                minPair.first = minPair.first==nullptr ? child :minPair.first;
                auto tmp= minPair.second->m_number;
                Delete(tmp, child, child->m_rl);
                child->m_number= tmp;
                return;


            }
          


            


        }
        else{
            if (t > child->m_number)
                Delete(t, child, child->m_rl);
            else
                Delete(t, child, child->m_ll);
        }

    }



   /* void Delete(const T &t, Node * &root)
    {
       
        if (root== nullptr)
            return;


        



        if (t < root->m_number)
            Delete(t, root->m_ll);
        else if (t > root->m_number)
            Delete(t, root->m_rl);
        else if ( root ->m_ll != nullptr && root-> m_rl != nullptr ) //two children
        {
            root->m_number = findMin(root->m_rl)->m_number;
            Delete(root->m_number, root->m_rl);
        }
        else
        {
            if ( root ->m_ll == nullptr && root-> m_rl == nullptr ){
                delete root;
                return;
            }
                



            Node *oldNode = root;
            root = (root->m_ll != nullptr) ? root->m_ll : root->m_rl;
            
            std::cout<<"where did we seg?"<<std::endl;
        
            delete oldNode;
            std::cout<<"where did we seg2?"<<std::endl;

        }





    }*/

    void Delete(const T &t)
    {
        if (m_root==nullptr)
            return;
        if (t > m_root->m_number)
            Delete(t, m_root, m_root->m_rl);
        else
            Delete(t, m_root, m_root->m_ll);


    }


private:
    Node *m_root;


};


#endif
