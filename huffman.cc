#include "huffman.hh"



Huffman::Huffman(){};

Huffman::~Huffman(){};



//Builds a Huffman Tree from scratch
HTree::tree_ptr_t Huffman::create_tree(){
    //Initialize forest of 257 HTrees 
    HForest forest = HForest(); 
    for(int i =97; i < 100; i++){
        HTree::tree_ptr_t tree = std::make_shared<HTree>(i, freqTable[i]);
        forest.HForest::add_tree(tree);
    }   
    //Iterate over forest
    while(forest.size() > 1){
        HTree::tree_ptr_t firstTree = forest.HForest::pop_top();
        HTree::tree_ptr_t secondTree = forest.HForest::pop_top();
        HTree::tree_ptr_t newTree;

        if(firstTree->get_key() >= 0){
                            newTree = std::make_shared<HTree>(firstTree->get_key() * -1, 
                                                              firstTree->get_value() + secondTree->get_value(),
                                                              firstTree,
                                                              secondTree);
        }

                            newTree = std::make_shared<HTree>(firstTree->get_key(), 
                                                              firstTree->get_value() + secondTree->get_value(),
                                                              firstTree,
                                                              secondTree);

        forest.HForest::add_tree(newTree);
    }
    //return one remaining tree q
return forest.pop_top();
}


//Outputs the keys of an HTree to the console
void Huffman::view_tree(HTree::tree_ptr_t huff){
    if(huff != nullptr){
      std::cout << huff->get_key() << ":" << huff->get_value() << std::endl;
    }
    if(huff->get_child(HTree::Direction::LEFT)){
      view_tree(huff->get_child(HTree::Direction::LEFT));  
    }
    if(huff->get_child(HTree::Direction::RIGHT)){
      view_tree(huff->get_child(HTree::Direction::RIGHT));
    }
    return;
}

void Huffman::view_freq(std::map<int, int> freq){
    if(freq.size() > 0){
        for(unsigned long i = 0; i < freq.size(); i++){
            std::cout << "frequency of " << i << ": " << freq[i] << std::endl;
        }
    }
    return;
}


//Prints the bits of a bits_t bool array
void Huffman::view_bits(bits_t bits){
    for(unsigned long i = 0; i < bits.size(); i++){
        std::cout << bits[i];
    }
    std::cout <<std::endl;
}


//Encodes a symbol using adaptive huffman encoding
Huffman::bits_t Huffman::encode(int symbol){
    // create tree from scratch
    HTree::tree_ptr_t Huff = Huffman::create_tree();                             
    view_tree(Huff);

    HTree::possible_path_t directionList = Huff->HTree::path_to(symbol);               
    Huffman::bits_t boolList;          

    //Iterate over direction list                                          
    std::list<HTree::Direction>::iterator iter;
    assert(directionList != nullptr && "Direction list nullptr");
    for (iter = directionList->begin(); iter != directionList->end(); iter++) {  
        // if direction is LEFT append false/0
        if (*iter == HTree::Direction::LEFT) { 
            boolList.push_back(false);                                           
        } 
        // if direction is RIGHT append true/1
        boolList.push_back(true);                                            
        
    }
    // increment the frequency of symbol in the frequency table and returns encoded bits
    Huffman::freqTable.at(symbol)++; 
    //view_freq(freqTable);                                            
    view_bits(boolList);
    return boolList;                                                            
}

int Huffman::decode(bool bit){
    HTree::tree_ptr_t Huff;
    //If lastNode is null, then this is the first bit in the sequence
    if(!lastNode){
         Huff = create_tree();
    }
    else{
         Huff = lastNode;
    }
    HTree::tree_ptr_t next;
    //Intrepret bits as direction inputs and navigate to child specified
    if(bit == false){
        next = Huff->get_child(HTree::Direction::LEFT);
    }
    next = Huff->get_child(HTree::Direction::RIGHT);
    //If child is not a leaf node (has no children) save it in lastNode and return negative value
    if (!Huff->get_child(HTree::Direction::LEFT) && !Huff->get_child(HTree::Direction::RIGHT)){
        lastNode = next;
        return -1;
    }
    //Else decrement frequency table for character at leaf, reset lastNode pointer, and return the character
    int key = next->get_key();
    freqTable.at(key)--;    
    lastNode = nullptr;
    return key;
}






