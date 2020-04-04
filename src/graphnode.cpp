#include "graphedge.h"
#include "graphnode.h"

#include "chatlogic.h"
#include <iostream>
#include <memory>

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //std::cout<< "Deleting chatBot instance in GraphNode Destructor" << std::endl;
    //delete _chatBot; 
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{
    _childEdges.push_back(std::unique_ptr<GraphEdge>(edge));
}

// passign an r-value reference as an argument
void GraphNode::MoveChatbotHere(ChatBot &&chatbot)
{
    _chatBot = std::move(chatbot);
    //update Chatlogic._chatBot handle that points to ChatBot
    _chatBot.GetChatLogicHandle()->SetChatbotHandle(&_chatBot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    return (_childEdges[index]).get();
}