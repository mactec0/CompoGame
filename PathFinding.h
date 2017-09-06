#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream> 
#include <vector>
#include <functional>
#include <set>

//credits:
//https://github.com/daancode/a-star


class cPathFinder{
    
    struct Node
    {
        sf::Vector2i Pos;
        uint32_t G, H;
        Node *p;
        
        Node(sf::Vector2i Pos, Node *p = nullptr){
            this->p = p;
            this->Pos = Pos;
            G = H = 0;
        }
        
        uint32_t F(){ return G+H; }
        
    };
    
    
    bool IsCuttingEdge(sf::Vector2i v1, sf::Vector2i v2){
        if ((v1.x!=v2.x&&v1.y!=v2.y)&&
            (bMapUnAvailable[v1.y][v2.x]||bMapUnAvailable[v2.y][v1.x])) {
            return true;
        }
        return false;
    }
    
    uint32_t Heuristic(sf::Vector2i v1, sf::Vector2i v2){
         return std::abs(v1.x-v2.x)+std::abs(v1.y-v2.y);
    }
    
    Node* GetNode(std::set<Node*>& nodes, sf::Vector2i Pos){
        for (auto node : nodes)
            if (node->Pos == Pos)
                return node;
        return nullptr;
    }
    
    void releaseNodes(std::set<Node*>& nodes_)
    {
        for (auto it = nodes_.begin(); it != nodes_.end();) {
            delete *it;
            it = nodes_.erase(it);
        }
    }
    
    bool **bMapUnAvailable;
    int Width, Height;
    
    std::vector<sf::Vector2i> path;
public:
    
    cPathFinder(int W, int H)
    :Width(W),Height(H)
    {
        bMapUnAvailable = new bool*[H];
        for(int i = 0; i < H; ++i)
            bMapUnAvailable[i] = new bool[W];
        this->Clear();
    }
    
    ~cPathFinder(){
    
    }
    
    bool isAccessible(sf::Vector2i pos){
        if(OutOfBounds(pos))
            return false;
        return !bMapUnAvailable[pos.y][pos.x];
    }
    
    bool OutOfBounds(sf::Vector2i Pos){
        if (Pos.x < 0 || Pos.x >= Width ||
            Pos.y < 0 || Pos.y >= Height) {
            return true;
        }
        return false;
    }
    
    bool bInPath(sf::Vector2i pos){
        for(auto testPath: path)
            if(testPath==pos)
                return true;
        return false;
    }
    
    void SetUnAvailable(int x, int y, bool Var){
        bMapUnAvailable[y][x]=Var;
    }
    
    void Clear(){
        for(int y=0;y<Height;y++)
            for(int x=0;x<Width;x++){
                bMapUnAvailable[y][x]=false;
            }
    }
    
    std::vector<sf::Vector2i> AStar(sf::Vector2i vecStart, sf::Vector2i vecEnd){
        std::set<Node*> OpenList, ClosedList;
        Node *pCurrentNode=nullptr;
        OpenList.insert(new Node(vecStart));
        bool bValid=false;
        
        sf::Clock TestTimer;
        TestTimer.restart();
        
        if(!OutOfBounds(vecEnd)&&isAccessible(vecEnd))
        while (!OpenList.empty()) {
            pCurrentNode = *OpenList.begin();
            
            if(TestTimer.getElapsedTime().asMilliseconds()>800){//it takes too long
                std::vector<sf::Vector2i> path;
                return path;
            }
            
            for (auto node : OpenList) {
                if (node->F() <= pCurrentNode->F()) {
                    pCurrentNode = node;
                }
            }
            
            if (pCurrentNode->Pos == vecEnd) {
                bValid=true;
                break;
            }
            
            ClosedList.insert(pCurrentNode);
            OpenList.erase(std::find(OpenList.begin(), OpenList.end(), pCurrentNode));
            
            const int directions=8;
            const sf::Vector2i dir[]={{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
                { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};
            
            for (uint32_t i = 0; i < directions; ++i) {
                sf::Vector2i newPos(pCurrentNode->Pos + dir[i]);
                if (OutOfBounds(newPos)||
                    bMapUnAvailable[newPos.y][newPos.x]||
                    GetNode(ClosedList, newPos)
                    ) {
                    continue;
                }else if(pCurrentNode->p&&
                         IsCuttingEdge(pCurrentNode->Pos,newPos)){
                    continue;
                }
                
                uint32_t totalCost = pCurrentNode->G + ((i < 4) ? 10 : 14);
                
                Node *successor = GetNode(OpenList, newPos);
                if (successor == nullptr) {
                    successor = new Node(newPos, pCurrentNode);
                    successor->G = totalCost;
                    successor->H = Heuristic(successor->Pos, vecEnd);
                    OpenList.insert(successor);
                }
                else if (totalCost < successor->G) {
                    successor->p = pCurrentNode;
                    successor->G = totalCost; 
                }
            }
        }
        
        
        std::vector<sf::Vector2i> path;
        if(!bValid)
            return path;
        
        while (pCurrentNode != nullptr){
            path.push_back(pCurrentNode->Pos);
            pCurrentNode = pCurrentNode->p;
        }
        
        releaseNodes(OpenList);
        releaseNodes(ClosedList);
        return path;
    }
    
    bool FindPath(sf::Vector2i vecStart, sf::Vector2i vecEnd){
        path = AStar(vecStart, vecEnd);
        
        while (!path.empty())
        {
            path.pop_back();
        }
    }

    
};
extern cPathFinder *Path;
