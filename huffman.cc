#include "huffman.hh"



Huffman::Huffman(){}

Huffman::~Huffman(){
}





//Builds a Huffman Tree from scratch
HTree::tree_ptr_t Huffman::create_tree(){
    //Initialize Freq Table
    for(int i = 0; i < ALPHABET_SIZE; i++){
        freqTable[i] = 0;
    }
    //Initialize forest of 257 HTrees 
    HForest forest;
    for(int i =0; i < ALPHABET_SIZE; i++){
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
/* void Huffman::view_tree(HTree::tree_ptr_t huff){
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
*/

//Outputs rough representation of huffman tree to console
void Huffman::view_tree(HTree::tree_ptr_t huff){
    if(huff != nullptr){
          std::cout << huff->get_key() << ":" << huff->get_value() << std::endl;
        if(huff->get_child(HTree::Direction::LEFT)){
          std::cout << "left child is " << huff->get_child(HTree::Direction::LEFT)->get_key() << std::endl;
        }
        if(huff->get_child(HTree::Direction::RIGHT)){
          std::cout << "right child is " << huff->get_child(HTree::Direction::RIGHT)->get_key() << std::endl;
        }
    }
    if(huff->get_child(HTree::Direction::LEFT)){
      view_tree(huff->get_child(HTree::Direction::LEFT));  
    }
    if(huff->get_child(HTree::Direction::RIGHT)){
      view_tree(huff->get_child(HTree::Direction::RIGHT));
    }
    return;
}

//Outputs frequency table to console followed by 
void Huffman::view_freq(std::array<int, ALPHABET_SIZE> freq){
    if(freq.size() > 0){ 
        for(unsigned long i = 0; i < freq.size(); i++){
            std::cout << "frequency of " << i << ": " << freqTable[i] << std::endl; 
        }
    }
    return;
}


//Prints the bits of a bits_t bool array, followed by a separator line of asteriks
void Huffman::view_bits(bits_t bits){
    for(unsigned long i = 0; i < bits.size(); i++){
        std::cout << bits[i];
    }
    std::cout << std::endl;
    std::cout << "****************" << std::endl;
}


//Encodes a symbol using adaptive huffman encoding, returns encoding as type bits_t (vector of booleans)
Huffman::bits_t Huffman::encode(int symbol){
    // create tree from scratch
    HTree::tree_ptr_t Huff = create_tree();                             
   
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
        else{ 
            // if direction is RIGHT append true/1
            boolList.push_back(true);        
        }
    }
    // increment the frequency of symbol in the frequency table and return encoded bits
    freqTable.at(symbol)++;
    std::cout << "Encoding of " << char(symbol) << ": ";                                        
    view_bits(boolList);
    return boolList;                                                            
}

// Decodes a symbol using adaptive huffman encoding. Decoding is done one bit at a time
// lastNode is set to nullptr at end of bit sequence, which indicates the start of a new bit sequence
// the next time decode is called
int Huffman::decode(bool bit){
    HTree::tree_ptr_t Huff;
    //If lastNode is null, then this is the first bit in the sequence
    if(lastNode == nullptr){
         Huff = create_tree();
    }
    else{
         Huff = lastNode;
    }
    //std::cout << "Freq Table at 97: " << freqTable[97] << std::endl;
    HTree::tree_ptr_t next;
    //Intrepret bits as direction inputs and navigate to child specified
    if(bit == false){
        next = Huff->get_child(HTree::Direction::LEFT);
    }
        next = Huff->get_child(HTree::Direction::RIGHT);
    
    //If child is not a leaf node (has children) save it in lastNode and return negative value
    if (next->get_child(HTree::Direction::LEFT) != nullptr || next->get_child(HTree::Direction::RIGHT) != nullptr){
        lastNode = next;
        return -1;
    }
    //Else decrement frequency table for character at leaf, reset lastNode pointer, and return the character
    int key = next->get_key();
    std::cout << "Decoded Key: " << key << std::endl;
    freqTable.at(key)++;    
    lastNode = nullptr;
    return key;
}






