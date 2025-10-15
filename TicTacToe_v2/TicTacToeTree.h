#pragma once
#include <string>
#include <vector>
#include <deque>
#include "TicTacToeBoard.h"


using namespace std;

class TicTacToeTree
{
public:
    TicTacToeTree();
    void buildFullTree();
    void breadthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
    void depthFirstSearchForOutcome(string boardSring, TicTacToeBoard::BOARD_STATE requestedState);
    
    void playGameAsX(string boardString);
    void playGameAsO(string boardString);
    
private:
    struct Node {
        TicTacToeBoard* board;
        vector < Node* > children;
        Node* parent;
        int nodeDepth = 0;
        
        ~Node() {
            delete board;
            for (Node* child : children) {
                delete child;
            }
        }
    };
    
    struct TicTacToePlay {
        int row; //0 - (board dim - 1)
        int col; //0 - (board dim - 1)
        TicTacToeBoard::PLAYER_TURN xOrO; //X or O
    };
    
    struct WinDrawStats {
        int numXWins;
        int numOWins;
        int numDraws;
    };
    
    // Stores Dimension size, used throughout the TicTacToeTree.cpp file
    int boardDim;
    int depthSearch;
    
    // Private Functions --Full Tree--
    void buildFullTreeHelper(Node* node, TicTacToeBoard::PLAYER_TURN p_turn, int& xWins, int& oWins, int& draws, int& total_g, int& total_b);
    
    // Private Functions --Search Functions--
    void searchHelper(string board, TicTacToeBoard::BOARD_STATE requestedState, string searchType);
    string getTypeGame(TicTacToeBoard::BOARD_STATE state);
    void getWinPath(Node* currentNode, deque < Node* >& nodes);
    void printWinPath(deque < Node* >& path, int boards, string searchType, string winType);
    
    // Private Function --Informed Search--
    void informedSearch(string board, string p_symbol, string ai_symbol);
    void informedSearchHelper(Node* current, TicTacToeBoard::PLAYER_TURN current_turn, TicTacToeBoard::PLAYER_TURN player_turn);
    TicTacToeTree::TicTacToePlay nextMoveHeuristic(string boardStr);
    TicTacToeTree::WinDrawStats countOutcomes(string boardString);
    void checkSpaces(Node* curr, int& r, int& c, bool isOccupied, string symbol);
    string getSymbol(TicTacToeBoard::PLAYER_TURN current_turn);
    void createDepthTree(Node* node);
    void createDepthTreeHelper(Node* node, TicTacToeBoard::PLAYER_TURN p_turn);
    
    // Private Functions --Universal Helpers--
    void createChild(Node* &currentNode, TicTacToeBoard::PLAYER_TURN p_turn, int& totalBoards);
    void deleteNodes(Node* node);

};
