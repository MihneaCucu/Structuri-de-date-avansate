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
    void remove(int data);
    bool search(int data);
    void display();         
    int minim();
    int maxim();
};

skipList:: skipList() 
{
    head = new Node(0, maxNivel);    

    nivel = 0;                               
}



void skipList::insert(int data) 
{
    int newnivel = 0; 

    while (newnivel < maxNivel and (rand() % 2) == 1) // ca si cum am da cu banul
    {
        newnivel++;
    } 

    if (nivel < newnivel) 
    {
        head->next.resize(newnivel + 1, nullptr);
        
        nivel = newnivel;
    }

    Node* current = head; 

    std::vector<Node*> update(nivel + 1, nullptr); 


    for (int i = nivel; i >= 0; i--) 
    {

        while (current->next[i] != nullptr && current->next[i]->data < data) 
        {
            current = current->next[i];
        }
        

        update[i] = current;

    }

    current = current->next[0];   

    if (current == nullptr || current->data != data) 
    {
        Node* newNode = new Node(data, nivel);

        for (int i = 0; i <= newnivel; i++) 
        {
            newNode->next[i] = update[i]->next[i];

            update[i]->next[i] = newNode;  

        }

        //std::cout << "Element " << data << " inserted successfully.\n";
    }
    else
    {
        //std::cout << "Element " << data << " already exists.\n";  
    }
    
}


void skipList::remove(int data) 
{
    
    Node* current = head; 

    std::vector<Node*> update(nivel + 1, nullptr); 


    for (int i = nivel; i >= 0; i--)         
    {
        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];  
        }

        update[i] = current;         
    }

    current = current->next[0];     

    if (current != nullptr && current->data == data) 
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

        while (nivel > 0 and head->next[nivel] == nullptr)  
        {
            nivel--;
        }

        //std::cout << "Element " << data << " deleted successfully.\n";
    }
    else
    {
        //std::cout << "Element " << data << " not found.\n";
    }
    
}


bool skipList::search(int data) 
{
    Node* current = head;          


    for (int i = nivel; i >= 0; i--) 
    {
        while (current->next[i] and current->next[i]->data < data) 
        {
            current = current->next[i]; 
        }
    }

    current = current->next[0];

    if (current != nullptr && current->data == data) 
    {
        //std::cout << "Element " << data << " found.\n";
        return true;
    }
    else 
    {
        //std::cout << "Element " << data << " not found.\n";
        return false;
    }
}


int skipList::minim()
{
    Node* current = head->next[0]; 

    while (current->data == 0)
    {
        current = current->next[0];
    }

    return current->data;
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


void skipList::display() 
{

    std::cout << "Skip list:"<< std::endl;

    for (int i = nivel; i >= 0; i--) 
    {
        Node* current = head->next[i]; 

        std::cout << "Nivelul " << i << ": "; 

        while (current != nullptr)       
        {
            std::cout << current->data << " ";
            current = current->next[i]; 
        }
        std::cout << std::endl;
    }
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