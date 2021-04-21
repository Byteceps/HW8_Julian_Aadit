# Homework 8: Adaptive Huffman Encoding
## The Exercise
* This program can be compiled through the makefile. 

    * ```make test_huffman``` will compile just the huffman tree part of this exercise
    * ```make test_bitio``` will compile just the bitIO section of this exercise

## Design Choices
In the huffman class, we needed to add several privata data members and functions.
* To store the huffman tree's frquency table, we initially used a ```std::map```, but during Sundays drop in tutoring we ended up changing it to an ```std::array``` so that we could set the array's size, and initialize all it's values to 0. We ran into an issue where our constructor was using an uninitalized frequency table, thus creating trees with garbage frequency data and rendering them undeterministic. 
* We also included an ```HTree::tree_ptr_t lastNode``` to keep track of the last node trasversed within the ```decode``` function. When ```lastNode``` is a ```nullptr``` this signals to ```decode``` to create a huffman tree from scratch for the first bit of an encoding.
* ```create_tree()``` is our constructor function to create a huffman tree from scratch, using the algorithm provided.
* ```view_tree()```, ```view_bits()```, and ```view_freq()``` are all helper functions we created to aid the debugging process. It was essential to see what our tree, bit encodings, and frequency tables looked like when debugging ```encode()``` and ```decode()```
#### BitIO 
* For the implementation of Bit_IO, we added two private data members ```std::ostream* output``` and ``` std::istream* input``` for use in the constructor
The bitio object works with one stream at a time, either input or output but never both. If two non nullptr streams, or two nullptr streams are passed to the BitIO constructor, then both streams in the BitIO object are set to null. 
* When input bit has read all the bits in the stream, i.e when EOF is reached, then the input is set to false

## Design Difficulties
We were able to get BitIO to compile cleanly and pass all of the tests provided, however we were not able to find more edge cases to test with. Our main difficulties were with getting Huffman to pass all the necessary tests. 
* We spent a lot of time debugging ```create_tree()```, ```encode()```, and ```decode()```, but we were not able to get ```test_encode``` and ```test_decode``` to pass. For a time ```test_encode``` was passing all tests, and ```encode()``` seemed to be correctly returning shorter encodings for more frequent characters, but drop in tutoring revealed bugs in our ```encode()``` and ```HForest::compare_trees()``` functions
 that when fixed caused ```test_encode``` to fail because the initial encodings were no longer long enough, and more frequent encodings were no longer short enough. 
    * We initally had ```compare_trees```returning ```t1->get_value() >= t2->get_value()```, but drop in tutors pointed out that when ```t1``` and ```t2``` were equal, we would need to compare them by height, so we added a necessary ```get_height``` method to the ```Htree``` class.
    * Our ```encode()``` method was wrongly appending true's to ```boolList``` due to a missing else statement.


* Our biggest roadblock was getting ```decode()``` to return the correct symbol for the given bit encoding. We spent days trying to figure out why encode seemed to be functioning properly, but decode would return a wrong key for the given input. The issue was coming from the decoder huffman object not having access to the same frequency table as the encoder object, so ```decode()``` was creating a different tree than ```encode()``` had used to produce the encoding. We tried figuring this out in Sunday's drop in tutoring, but that is where the bug fixes in ```encode()``` and ```compare_trees()``` set up back because encode was no longer able to pass it's tests, and the rest of the tutoring session was spent trying to debug the ```encode()``` aspect

### Encoder.cc and Decoder.cc
We started working on Encoder.cc during the period where we thought that ```encode()``` was functioning properly. We had been struggling for days trying to get decode to function properly, and thought it would be wise to divert our efforts to getting Encoder.cc working. We spent a while discussing what ```Encoder.cc``` would look like, outlining necessary helper functions and writing pseudo code to describe them step by step, but we did not have enough time to finish these parts by the deadline as we had to spend the last tutoring session figuring out what we could in ```huffman.cc```. 




