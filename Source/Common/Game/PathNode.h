//
//  PathNode.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-11-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__PathNode__
#define __GAM_1514_OSX_Game__PathNode__

#include "../OpenGL/OpenGL.h"


class Tile;

class PathNode
{
public:
    PathNode(Tile* tile);
    ~PathNode();
    
    void paintScore(OpenGLColor color);
    
    Tile* getTile();
    
    float getScoreG();
    float getScoreH();
    float getScoreF();
    
    PathNode* getParentNode();
    
    void setScoreG(float scoreG);
    void setScoreH(float scoreH);
    
    void setParentNode(PathNode* parentNode);
    
    static bool compareNodes(PathNode* nodeA, PathNode* nodeB);
    
private:
    Tile* m_Tile;
    float m_ScoreG;
    float m_ScoreH;
    PathNode* m_ParentNode;
};

#endif /* defined(__GAM_1514_OSX_Game__PathNode__) */







