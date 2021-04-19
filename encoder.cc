#include "bitio.hh"
#include "huffman.hh"



std::vector<char> char_to_vec(char* filename) {
    std::vector<char> v;
    if (FILE *fp = fopen(filename, "r"))  {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            v.insert(v.end(), buf, buf + len);
        fclose(fp);
    }
    return v;
}
void encode_characters(std::vector<char> vec){
    Huffman encoder;
    //Encode each char from the vector
    for(char c : vec){
        encoder.encode(c);
    }

    for(char c : vec){
        auto path = encoder.get_huffman()->path_to(c);

        }
    }







}


int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Need Exactly 1 filename as input";
        return -1;
    }
    std::ifstream input(argv[1]);

    if(!input.is_open()){
        std::cerr << "Cant open input file " << argv[1] << "!" << std::endl;
        return -2;
    }







}