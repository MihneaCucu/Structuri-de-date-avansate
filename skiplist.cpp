#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>

std::ifstream fin("avantajsplay_1mil.txt");

int maxNivel; 

class Node 
{
public:

    int data;
    std::vector<Node*> next;     
    Node(int data, int nivel) : data(data), next(nivel + 1, nullptr) {} 

};

class skipList 
{
private:
    Node* head; 
    int nivel;

public:
    skipList();

    void insert(int data);
    bool search(int data); 
    void remove(int data);       
    int minim();
    int maxim();

};

skipList:: skipList() 
{
    head = new Node(0, maxNivel);    

    nivel = 0;                               
}



void skipList::insert(int val) 
{
    int nivelNou = 0; 

    while (nivelNou < maxNivel && (rand() % 2) == 1) // dam cu banul
    {
        nivelNou++;
    } 

    if (nivel < nivelNou) 
    {
        head->next.resize(nivelNou+1, nullptr);
        nivel = nivelNou;
    }

    Node* current = head; 
    std::vector<Node*> update(nivel + 1, nullptr); 


    for (int i = nivel; i >= 0; i--) 
    {
        while (current->next[i] != nullptr && current->next[i]->data < val) 
        {
            current = current->next[i];
        }
        
        update[i] = current;
    }

    current = current->next[0];   

    if (current == nullptr || current->data != val) 
    {
        Node* newNode = new Node(val, nivel);

        for (int i = 0; i <= nivelNou; i++) 
        {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;  
        }

    }
    
}


void skipList::remove(int val) 
{
    
    Node* current = head; 

    std::vector<Node*> update(nivel + 1, nullptr); 


    for (int i = nivel; i >= 0; i--)         
    {
        while (current->next[i] && current->next[i]->data < val)
        {
            current = current->next[i];  
        }

        update[i] = current;         
    }

    current = current->next[0];     

    if (current != nullptr && current->data == val) 
    {
        for (int i = 0; i <= nivel; i++)      
        {      
            if (update[i]->next[i] != current)
            {
                break;
            }
            else
            {
                update[i]->next[i] = current->next[i];
            }
        }

        delete current; 

        while (nivel > 0 && head->next[nivel] == nullptr)  
        {
            nivel--;
        }

    }
    
}


bool skipList::search(int val) 
{
    Node* current = head;

    for (int i = nivel; i >= 0; i--) 
    {
        while (current->next[i] != nullptr && current->next[i]->data < val) 
        {
            current = current->next[i]; 
        }
    }

    current = current->next[0];

    if (current != nullptr && current->data == val) 
        return true;
    else 
        return false;

}


int skipList::minim()
{
    return head->next[0]->data;
}

int skipList::maxim()
{
    Node* current = head;

    for (int i = nivel; i >= 0; i--) 
    {
        while (current->next[i] != nullptr) 
        {
            current = current->next[i]; 
        }
        
    }
    return current->data;
}

int main()
{
    skipList skip;
    int k, x;
    fin >> k;
    std::string operatie;

    maxNivel = ceil(log2(k/2));

    auto start1 = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < k; i++)
    {
        fin >> operatie;
        if (operatie == "INSERT")
        {
            fin >> x;
            skip.insert(x);
        }
        else if (operatie == "DELETE")
        {
            fin >> x;
            skip.remove(x);
        }
        else if (operatie == "SEARCH")
        {
            fin >> x;
            skip.search(x);
        }
        else if (operatie == "MINIM")
        {
            skip.minim();
            //std::cout << "Minimul este " << skip.minim() << std::endl;
        }
        else if (operatie == "MAXIM")
        {
            skip.maxim();
            //std::cout << "Maximul este " << skip.maxim() << std::endl;
        }
    }

    auto finish1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = finish1 - start1;

    std::cout << "Elapsed time: " << elapsed1.count() << " s\n";
    
}