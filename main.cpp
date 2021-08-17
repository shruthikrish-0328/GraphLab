#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include <algorithm>
using namespace std;

struct Node{
    int toNode;
    int weight;
    Node* next;
};

class Graph{
   private:
      // Graph data structure here
    vector<int> fromNode;
    map<int, Node*> graphmap;
    public:
      void insertEdge(int from, int to, int weight);
      int getWeight(int from, int to);
      vector<int> getAdjacent(int vertex);
      void printSums();
};
void Graph::insertEdge(int from, int to, int weight){
    Node* temp = new Node;

        temp->toNode = to;
        temp->weight = weight;
        temp->next = NULL;

        // for the from vertex
        if (graphmap.find(from) == graphmap.end()){
            fromNode.push_back(from);
            graphmap[from] = temp;
        }
        else{
            //entry in map exists...so take the head node and add additional link
            Node* rnode = graphmap[from]->next;
            Node* prev = NULL;
            if (rnode != NULL){
                while (rnode != NULL){
                    //cout << " From Rnode: " << rnode << "\n";
                    prev = rnode;
                    rnode = rnode->next;
                }
                prev->next = temp;
            }
            else {
                graphmap[from]->next = temp;
            }
        }

        //for to vertex
        temp = new Node;
        temp->toNode = from;
        temp->weight = weight;
        temp->next = NULL;

        if (graphmap.find(to) == graphmap.end()){
            //cout << " To not found \n";
            fromNode.push_back(to);
            graphmap[to] = temp;
        }
        else {
            //cout << " To found \n";
            //entry in map exists...so take the head node and add additional link
            Node* rnode = graphmap[to]->next;
            Node* prev = NULL;
            if (rnode != NULL) {
                while (rnode != NULL){
                    //cout << "To Rnode: " << rnode << "\n";
                    prev = rnode;
                    rnode = rnode->next;
                }
                prev->next = temp;
            }
            else {
                graphmap[to]->next = temp;
            }
        }
}
int Graph::getWeight(int from, int to){
    if (graphmap.find(from) != graphmap.end())
        {
            Node* rnode = graphmap[from]->next;
            Node* prev = NULL;
            if ( graphmap[from]->toNode == to )
            {
                return graphmap[from]->weight;
            }

            if (rnode != NULL) {
                while (rnode != NULL)
                {
                    if (rnode->toNode == to)
                    {
                        return rnode->weight;
                    }
                    else {
                        rnode = rnode->next;
                    }
                }
            }
        }
        return 0; // return zero if not found
}
vector<int> Graph::getAdjacent(int vertex){
    vector<int> adjacent;
        if (graphmap.find(vertex) != graphmap.end())
        {
            //cout << "For vertex " << vertex << " : "  << graphmap[vertex]->next << "\n";
            adjacent.push_back(graphmap[vertex]->toNode);
            Node* rnode = graphmap[vertex]->next;
            while (rnode != NULL)
            {
                adjacent.push_back(rnode->toNode);
                rnode = rnode->next;
            }
        }
        //sort(adjacent.begin(), adjacent.end());
        return adjacent;
}
void Graph::printSums(){
        vector <int> rvec;
        sort(fromNode.begin(), fromNode.end());
        for (int i = 0; i < fromNode.size(); i++){
            int weight = 0;
            cout << fromNode[i] << " ";
            rvec = Graph::getAdjacent(fromNode[i]);
            for (int j = 0; j < rvec.size(); j++)
            {
                weight = weight + Graph::getWeight(fromNode[i], rvec[j]);
            }
            cout << weight << "\n";
        }
    }

int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK

    int noOfLines, operation, vertex, to, fro, weight, source, j;
    vector<int> arr;
    int arrSize;
    Graph g;
    cin>>noOfLines;
    for(int i=0;i<noOfLines;i++)
    {
        cin>>operation;
        switch(operation)
        {
            case 1:
                cin>>fro;
                cin>>to;
                cin>>weight;
                g.insertEdge(fro,to,weight);
                break;
            case 2:
                cin>>fro;
                cin>>to;
                cout<<g.getWeight(fro,to)<<"\n";
                break;
            case 3:
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                arrSize = arr.size();
                j=0;
                while(j<arrSize)
                {
                    cout<<arr[j]<<" ";
                    j++;
                }
                cout<<"\n";
                break;
            case 4:
                g.printSums();
                cout<<"\n";
                break;
        }
    }
}