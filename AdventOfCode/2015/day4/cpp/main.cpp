#include <cstdint>
#include <iostream>
#include <iomanip>
#include <limits>
#include <ostream>
#include <sstream>
#include <openssl/md5.h>
#include <string>

std::string md5(const std::string &str){
  unsigned char hash[MD5_DIGEST_LENGTH];

  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, str.c_str(), str.size());
  MD5_Final(hash, &md5);

  std::stringstream ss;

  for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
  }
  return ss.str();
}

int main()
{
    std::string input = "bgvyzdsv";

    uint32_t i;
    for(i = 0; i < std::numeric_limits<uint32_t>::max(); i++)
    {
        std::string hashInp = md5(input + std::to_string(i));
        std::cout << "It: " << i << " Input: "  << input + std::to_string(i) << " Hash: " << hashInp << std::endl;
        bool hasZero = true;
        //part 1 = 5
        //part 2 = 6
        for(int i = 0; i < 6; i++)
        {
            if(hashInp.at(i) != '0') hasZero = false;
        }
        if(hasZero) break;
    }

    std::cout << i << std::endl;
}
