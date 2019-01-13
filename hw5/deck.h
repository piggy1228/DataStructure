#include "playing_card.h"
#include "node.h"
#include<string>

// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================

int DeckSize(const Node* deck);
Node* CopyDeck(const Node* deck);
void CutDeck(Node* deck, Node* &top, Node* &bottom,std::string method);
Node* Shuffle(Node* first,Node* second,std::string method);
bool SamePrimaryOrder(const Node* deck1, const Node* deck2);
bool ReversePrimaryOrder(const Node* deck1,const Node* deck2);
void DeleteAllCards(Node* deck);
void Deal(Node* &deck, Node* hands[],const int p,const std::string method,const int card_num);
Node* SortHand(Node* deck);
void PrintDeckSorted(const std::string &description, Node* sorted_head);
