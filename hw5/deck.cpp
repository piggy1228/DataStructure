// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include "playing_card.h"
#include "node.h"
#include "deck.h"
#include <random>

// ==================================================================================

/**
decksize get the card's size of the whole deck
 increment count each time it get to another card in the deck
 */
int DeckSize(const Node* deck){
    int counts=0;
    //if the deck is empty
    if (deck == NULL) {
        return counts;
    }
    //if the deck only has one deck
    if (deck ->after == NULL) {
        return 1;
    }
    //each time the deck get to another card, count increment
    while(deck->after!=NULL) {
        deck = deck->after;
        counts++;
    }
    counts++;//increment for the last card
    return counts;
}

/**
copy the deck into another linked list
create a new deck on the heap and copy each card into another deck
 */
Node* CopyDeck(const Node* deck){
    //if the deck is empty
    if (deck == NULL) {
        return NULL;
    }
    //create a deck on the heap
    // copy the card one by one
    Node* tmp = new Node(deck ->getCard());
    Node* deck2 = tmp;//deck2 has one card
    //when deck get to the second card, deck2 also get to the second card
    //make the card same value
    while (deck -> after!=NULL) {
        deck = deck -> after;
        Node* tmp2= new Node(deck -> getCard());
        tmp -> after = tmp2;
        tmp ->after->before = tmp;//make the double linked
        tmp = tmp ->after;
    }
    return deck2;

}


/**
 Cut the deck to two decks
 if there are odd numbers of, the first decks have one card less than the second
 deck
 */
void CutDeck(Node*deck, Node* &top, Node* &bottom, std::string method){
    if (method == "perfect") {
        // check Sanity
        assert(SanityCheckPrimary(deck));
        Node* tmp = deck;
        top = tmp;
        //find out the first deck size
        int size = DeckSize(deck)/2;
        int i =0;
        //link the first deck card
        while (i < size-1) {
            tmp = tmp -> after;
            i++;
        }
        // bottom card is after the first deck size
        bottom = tmp->after;
        //first deck card will link to end after sizer
        tmp -> after = NULL;
        bottom -> before = NULL;
        
        //check sanity
        assert(SanityCheckPrimary(top));
        assert(SanityCheckPrimary( bottom));
    }
    else{
        int size = DeckSize(deck)/2;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(size - 3,size + 3);
        int dice_roll = distribution(generator);
        Node* tmp = deck;
        top = tmp;
        int i =0;
        //link the first deck card
        while (i < dice_roll-1) {
            tmp = tmp -> after;
            i++;
        }
        // bottom card is after the first deck size
        bottom = tmp->after;
        //first deck card will link to end after sizer
        tmp -> after = NULL;
        bottom -> before = NULL;
        
    }

}

/**
 insert second one by one to the first deck.
 So that the changed linked first deck is the deck after shuttle
 there are two cases: first and second size are the same, or one is one card
 more than the other deck
 */
Node* Shuffle(Node* first, Node* second,std::string method){
    
    Node* deck_head =first;
    if (method == "perfect") {
        Node* tmp_head;
        // check sanity
        assert(SanityCheckPrimary(first));
        assert(SanityCheckPrimary(second));
        
        int firstnum = DeckSize(first);
        int secondnum = DeckSize(second);
        //if the first deck smaller than the second deck
        if (firstnum < secondnum) {
            Node* deck = first;
            Node* tmp =second;

            //tmp_head is the first card from the deck
            // so that it can go back to the head of the deck
            tmp_head = deck;
            while (first->after!=NULL) {
                second = second ->after;
                tmp ->after = deck ->after;
                deck -> after = tmp;
                //create the double linked when insert the card into first deck
                //create two double linked because two links have been changed
                deck ->after->before = deck;
                tmp -> after -> before = tmp;
                deck = tmp->after;
                tmp = second;
            }
            assert(first->after == NULL);
            //deal with the cards left in the second
            deck ->after = tmp;
            deck ->after ->before = deck;
            

        }
        else {
            Node* deck =first;
            Node* tmp =second;
            Node* tmp_head;
            tmp_head = deck;
            //deal with the size of second decks are smaller than the size of the
            //first deck, so when linked with all second decks cards, deal with
            //the left cards in first deck
            while (second->after!=NULL) {
                second = second ->after;
                tmp ->after = deck ->after;
                deck -> after = tmp;
                deck ->after->before = deck;
                tmp -> after -> before = tmp;
                deck = tmp->after;
                tmp = second;
            }
            assert(second->after == NULL);
            if (deck ->after!= NULL) {
                //if two decks are different size
                //need to linked all the left cards in the first deck
                tmp ->after = deck ->after;
                deck ->after = tmp;
                deck ->after ->before = deck;
                tmp->after ->before = tmp;
                
            }
            else{
                //two decks are the same size
                //just deal with the next card
                tmp -> after = NULL;
                deck ->after = tmp;
                deck ->after -> before = deck;
            }
            return tmp_head;
        }
    }
    else{
        std::default_random_engine generator;
        Node* deck =first;
        Node* tmp =second;
        Node* tmp2=tmp;
        Node* tmp_head;
        Node* tmp3;
        Node* lastsecondtail;
        tmp_head = deck;
        while (deck -> after != NULL && tmp->after !=NULL) {
            std::uniform_int_distribution<int> distribution(1,3);
            int dice_roll = distribution(generator);
            //std::cout<<"check2: size:"<<dice_roll<<"\n";
            int c=0;
            lastsecondtail = tmp2;
            tmp2 = tmp;
            while (c < dice_roll-1) {
                //std::cout<<"\tcheck3.1: tmp2:"<<tmp2->getCard().getCard()<<" "<<tmp2->getCard().getSuit()<<"\n";
                //std::cout<<"\tcheck3.1: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
                if (tmp2 ->after == NULL) {
                    //std::cout << "\t tmp2 after break " << std::endl;
                    break;
                }
                tmp2 = tmp2 ->after;
                //std::cout<<"check3: tmp2:"<<tmp2->getCard().getCard()<<" "<<tmp2->getCard().getSuit()<<"\n";
                c++;
            }
            //std::cout<<"check3.1: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
            int size1 = distribution(generator);
            //std::cout<<"check4: size:"<<size1<<"\n";
            if (tmp_head == NULL) {
                //std::cout << "check5.1:\tdeck null" << std::endl;

                //std::cout<<"check3.1: tmp2:"<<tmp2->getCard().getCard()<<" "<<tmp2->getCard().getSuit()<<"\n";
                deck = lastsecondtail;
                deck->after = tmp;
                deck->after->before = deck;
                /*
                if (deck != NULL && deck->after != NULL) {
                    std::cout<<"check3.1: deck after:"<<deck->after->getCard().getCard()<<" "<<deck->after->getCard().getSuit()<<"\n";
                    deck = deck->after;
                    deck->after = tmp;
                }*/
                
                if (deck->after != NULL) {
                    //std::cout<<"check3.1: deck after:"<<deck->after->getCard().getCard()<<" "<<deck->after->getCard().getSuit()<<"\n";
                    
                   /*
                if (tmp2 ->after !=NULL) {
                    tmp2 -> after = deck ->after;
                    tmp2 ->after ->before = tmp2;
                }
                    */
                    /*
                    std::cout<<"check3.1: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
                    std::cout<<"check3.1: deck:"<<deck->getCard().getCard()<<" "<<deck->getCard().getSuit()<<"\n";
                    std::cout<<"check3.1: tmp2:"<<tmp2->getCard().getCard()<<" "<<tmp2->getCard().getSuit()<<"\n";
                    std::cout<<"check3.1: deck after:"<<deck->after->getCard().getCard()<<" "<<deck->after->getCard().getSuit()<<"\n";
                     */
                    //deck = deck->after;
                }
                
                    //PrintDeckPrimary("WTF***", deck);
                
                //if (deck != NULL && deck->after != NULL) {
                
                    /*
                if (tmp != NULL)
                {
                deck ->after ->before = deck;
                }
                     */
                
                
                /*
                deck ->after = tmp;
                if (tmp !=NULL) {
                    deck ->after->before = deck;
                }
                */
        

                break;
            }
        
            deck = tmp_head;
            
            /*
            if (deck == NULL) {
                std::cout << "check5.1:\tdeck null" << std::endl;
                break;
            }
             */
            
            for (int i=0; i<size1-1; ++i) {
                if (deck->after == NULL) {
                    break;
                }
                deck = deck->after;
                //std::cout<<"check5: deck:"<<deck->getCard().getCard()<<deck->getCard().getSuit()<<"\n";
            }
           // std::cout<<"check5.1: tmp_head:"<<tmp_head->getCard().getCard()<<" "<<tmp_head->getCard().getSuit()<<"\n";
            if (tmp2 == NULL) {
                std::cout << "check:5.2 tmp2 null" << std::endl;
            }
            //if (tmp2->after != NULL) {
            //}

            if (deck != NULL) {
            //if (tmp2 ->after!=NULL && deck != NULL) {
                tmp3 = tmp2->after;

                tmp2 -> after = deck ->after;
                tmp_head = deck ->after;
                if (deck->after != NULL)
                {
                    tmp2 ->after ->before = tmp2;
                }
            }
            
            
            
            deck ->after = tmp;
            //std::cout<<"\tafter deck check3.1: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
            deck->after ->before = deck;
            tmp3->before = NULL;
            tmp = tmp3;
            //std::cout<<"\tafter tmp3 check3.1: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
            
           // std::cout<<"check6: tmp:"<<tmp->getCard().getCard()<<" "<<tmp->getCard().getSuit()<<"\n";
            //std::cout<<"check7: tmp2:"<<tmp2->getCard().getCard()<<" "<<tmp2->getCard().getSuit()<<"\n";
            
        }
        if (deck ->after == NULL) {
            std::cout<<"check6: deck:"<<deck->getCard().getCard()<<"\n";
            deck->after = tmp->after;
            if (deck->after != NULL) {
                deck->after->before =deck;
            }
        }
    }
    return deck_head;
}


/**
  check each cards in two decks are all the same
 compares card one by one
 */
bool SamePrimaryOrder(const Node* deck1, const Node* deck2){
    if (DeckSize(deck1) != DeckSize(deck2)) {
        return false;
    }
    while (deck1 != NULL && deck2 != NULL) {
        //once card are different return true
        if (deck1->getCard() != deck2 -> getCard()) {
            return false;
        }
        deck1 = deck1 -> after;
        deck2 = deck2 -> after;
    }
    return true;
}


/*
 in the reveresd order, cards in two decks are different
 let first deck go to the tail, then let it come back using the before to
 compare with deck2 in the second deck
 */
bool ReversePrimaryOrder(const Node* deck1,const Node* deck2){
    //let the deck1 go to the tail
    while (deck1 ->after!= NULL) {
        deck1 = deck1 -> after;
    }
    //compare the card in two decks
    while (deck2 != NULL) {
        if (deck2->getCard() != deck1->getCard()) {
            return false;
        }
        deck1 = deck1 -> before;
        deck2 = deck2 -> after;
    }
    return true;
}


/**
 delete all the card one by one using the tmp.
 so that the link will not be cut
 */
void DeleteAllCards(Node* deck){
    while (deck != NULL) {
        Node* tmp = deck;
        deck = deck -> after;
        delete tmp;
    }
}


/**
 to send the card to each person one by one
 first give each one a card. and set the first card -> before is NULL
 */
void Deal(Node* &deck, Node* hands[],const int p,const std::string method,const int card_num){
    if (method == "one-at-a-time") {
        assert(p > 0);
        assert(SanityCheckPrimary(deck));
        Node* tmp[p];
        //give each person the first hand in order
        for (int i=0; i<p; ++i) {
            hands[i] = deck;
            tmp[i] = hands[i];
            tmp[i] ->before = NULL;
            deck = deck->after;
        }
        int count =0;
        //give each one a card until all the cards are distributed
        //make each person has a double linked deck
        while ( count < card_num*p-p) {
            for (int i=0; i< p ; ++i) {
                Node* tmp_v;
                tmp_v = deck;
                tmp[i] -> after = tmp_v;
                tmp[i] ->after -> before = tmp[i];
                tmp[i] = tmp[i] ->after;
                deck = deck->after;
                count++;
            }
        }
        //make sure each person's last card -> after is NULL;
        for (int i=0;i<p;++i)
        {
            tmp[i]->after = NULL;
        }
        //make each head -> before is null
        if (deck!=NULL) {
            deck->before = NULL;
        }
        assert(SanityCheckPrimary(deck));
    }
}


/**
 sort the card using the operator <
 let there are double links in the deck
 split the decks into two decks, let the tmp2 to find a place in tmp1
 then insert it into tmp1, tmp1 will be one larger and tmp2 will be 1 smaller
 until the tmp2 is empty
 */
Node* SortHand(Node* deck) {
    //make sure there is a tmp_head so that each time it will come from the head
    Node* tmp_head = deck;
    Node* tmp2 = tmp_head->after;
    Node* tmp1 = tmp_head;
    //first insert the second card in tmp1
    //to 
    if (tmp2 -> getCard() < tmp1->getCard()) {
        tmp2 -> sorted_next = tmp1;
        tmp1 ->sorted_prev = tmp2;
        tmp2 ->sorted_prev = NULL;
        tmp_head = tmp_head ->sorted_prev;
    }
    else{
        tmp2 ->sorted_prev = tmp1;
        tmp1 ->sorted_next = tmp2;
        tmp1 ->sorted_prev =NULL;

    }
    tmp2 = tmp2 -> after;
    tmp1 = tmp_head;
    //if the first card in tmp2 is smaller than the card in tmp1,then insert
    //it at the position, otherwise, to compare it with the next sorted in
    //tmp1
    while (tmp2 != NULL) {
//if the tmp2 is smaller than the first card in tmp1, then it will be the new
//deck_head.
        if (tmp2 -> getCard() < tmp1->getCard()) {
            tmp2 -> sorted_next = tmp1;
            tmp1 ->sorted_prev = tmp2;
            tmp_head = tmp_head ->sorted_prev;
        }
        else{
            while (tmp1 != NULL ) {
                if (tmp1->sorted_next == NULL) {
                    tmp1 ->sorted_next = tmp2;
                    tmp2 ->sorted_prev = tmp1;
                    break;
                }
                if (tmp2->getCard() < tmp1 ->sorted_next->getCard()) {
                    tmp2 -> sorted_next = tmp1->sorted_next;
                    tmp2 ->sorted_next ->sorted_prev = tmp2;
                    tmp1 ->sorted_next = tmp2;
                    tmp1 -> sorted_next ->sorted_prev = tmp1;
                    break;
                }
                tmp1 = tmp1 ->sorted_next;
            }
        }
        //after tmp2 was inserted, to compare the tmp2->after with cards in tmp1
        tmp2 = tmp2->after;
        tmp1 = tmp_head;
    }
    return  tmp_head;
}


/**
 Print the deck by the sorted order
 */
void PrintDeckSorted(const std::string &description, Node* deck) {
    assert(deck != NULL);
    std::cout << description;
    Node *tmp = deck;
    assert(deck ->sorted_prev==NULL);
    while (tmp != NULL) {
        std::cout << " " << tmp->getCard().getString();
        tmp = tmp->sorted_next;//let it go as the sorted sequence
    }
    std::cout << std::endl;
}

