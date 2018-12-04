//
//  Edges.cpp
//  AirHockey
//
//  Created by Artur on 17/11/2018.
//

#include "Edges.hpp"

USING_NS_CC;


Node* Edges::create() {
//    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1, 0), 3);
//    auto edgeNode = Node::create();
//
//    Vec2* points = new Vec2[2];
//
//    PhysicsBody::createPolygon(points, 2);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeNode = Node::create();
    
    float wallWidth = 2;
    float goalsHeight = visibleSize.height / 3;
    float verticalWallHeight = visibleSize.height / 2 - goalsHeight / 2;
    
    auto material = PhysicsMaterial(1, 1, 0);
    
    
    // creating top wall
    auto topWall = Node::create();
    topWall->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y);
    auto topWallPhysics = PhysicsBody::createEdgeBox(Size(visibleSize.width, wallWidth), material);
    topWall->setPhysicsBody(topWallPhysics);
    edgeNode->addChild(topWall);
    
    
    // creating bottom wall
    auto bottomWall = Node::create();
    bottomWall->setPosition(visibleSize.width / 2 + origin.x, origin.y);
    auto bottomWallPhysics = PhysicsBody::createEdgeBox(Size(visibleSize.width, wallWidth), material);
    bottomWall->setPhysicsBody(bottomWallPhysics);
    edgeNode->addChild(bottomWall);
    
    
    // creating left wall (two parts: upper and lower. goals are between them)
    auto upperLeftWall = Node::create();
    auto upperLeftWallPhysics = PhysicsBody::createEdgeBox(Size(wallWidth, verticalWallHeight), material);
    upperLeftWall->setPhysicsBody(upperLeftWallPhysics);
    upperLeftWall->setPosition(origin.x, origin.y + visibleSize.height - verticalWallHeight / 2);
    edgeNode->addChild(upperLeftWall);
    
    auto lowerLeftWall = Node::create();
    auto lowerLeftWallPhysics = PhysicsBody::createEdgeBox(Size(wallWidth, verticalWallHeight), material);
    lowerLeftWall->setPhysicsBody(lowerLeftWallPhysics);
    lowerLeftWall->setPosition(origin.x, origin.y + verticalWallHeight / 2);
    edgeNode->addChild(lowerLeftWall);
    
    
    // creating right wall (two parts: upper and lower. goals are between them)
    auto upperRightWall = Node::create();
    auto upperRightWallPhysics = PhysicsBody::createEdgeBox(Size(wallWidth, verticalWallHeight), material);
    upperRightWall->setPhysicsBody(upperRightWallPhysics);
    upperRightWall->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height - verticalWallHeight / 2);
    edgeNode->addChild(upperRightWall);
    
    auto lowerRightWall = Node::create();
    auto lowerRightWallPhysics = PhysicsBody::createEdgeBox(Size(wallWidth, verticalWallHeight), material);
    lowerRightWall->setPhysicsBody(lowerRightWallPhysics);
    lowerRightWall->setPosition(origin.x + visibleSize.width, origin.y + verticalWallHeight / 2);
    edgeNode->addChild(lowerRightWall);
    
    
    return edgeNode;
}
