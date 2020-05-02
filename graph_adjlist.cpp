#include <iostream>
using namespace std;

struct node
{
    int e; // end
    int wt;
    struct node *next;
};

struct list
{
    struct node *head;
};

class graph
{
private:
    int v; // vertices
    struct list *arr;

public:
    graph(int vert)
    {
        this->v = vert;
        arr = new list[vert];
        for (int i = 0; i < vert; i++)
        {
            arr[i].head = NULL;
        }
    }

    node *new_node(int E, int W)
    {
        struct node *temp = new (node);
        temp->e = E;
        temp->wt = W;
        temp->next = NULL;
        return temp;
    }

    void add_edge(int s, int e, int w) // start and end
    {
        struct node *ptr1 = new_node(e, w);
        ptr1->next = arr[s].head;
        arr[s].head = ptr1;

        struct node *ptr2 = new_node(s, w);
        ptr2->next = arr[e].head;
        arr[e].head = ptr2;
    }

    void display()
    {
        int i;
        cout << "\nAdjacency List \n";
        for (i = 0; i < v; i++)
        {
            struct node *ptr = arr[i].head;
            cout << "\nVertex " << i << " - ";
            while (ptr)
            {
                cout << ptr->e << "  wt :" << ptr->wt << ", ";
                ptr = ptr->next;
            }
            cout << "\n";
        }
    }
};

int main()
{
    graph g(5);

    g.add_edge(0, 1, 10);

    g.add_edge(0, 4, 20);

    g.add_edge(1, 2, 30);

    g.add_edge(1, 3, 40);

    g.add_edge(1, 4, 50);

    g.add_edge(2, 3, 60);

    g.display();
    return 0;
}