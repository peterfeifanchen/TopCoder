// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.
#include <iostream>
#include <vector>
#include <string>
#include <regex>

bool checkResult( std::vector<int>& res, std::vector<int>& ans ) {
   if ( res.size() != ans.size() ) return false;
   for( int i = 0; i < ans.size(); i++ ) {
      if ( res[i] != ans[i] ) return false;
   }
   return true;
}

void printResult( std::vector<int>& res, std::vector<int>& ans ) {
   std::cout << "Got: ";
   for( int i = 0; i < res.size(); i++ ) {
      std::cout << res[i] << ",";
   }
   std::cout << std::endl;
   std::cout << "Expected: ";
   for( int i = 0; i < ans.size(); i++ ) {
      std::cout << ans[i] <<  ",";
   }
   std::cout << std::endl;
}

class CheatCode {
 public:
    std::vector<int> matches( std::string keyPresses, std::vector<std::string>& codes ) {
       std::vector<int> result;

       for( int i = 0; i < codes.size(); i++ ) {
         
         std::string pattern = ".*";
         int j = 0;
         while( j < codes[i].size() ) { 
            int k = 1;
            while( j+k < codes[i].size() && codes[i][j] == codes[i][j+k] ) k++; 
            pattern += codes[i][j]; 
            pattern += "{" + std::to_string(k) + ",}"; 
            j += k;
         }
         pattern += ".*";

         // std::cout << "code[" << i << "]:" << codes[i] << std::endl;
         // std::cout << "pattern:" << pattern << std::endl;
         // std::cout << "keyPresses: " << keyPresses << std::endl;

         std::regex match_regex(pattern);
         // std::cout << regex_search(keyPresses, match_regex) << std::endl;;
         if (regex_search(keyPresses, match_regex)) {
            // std::cout << i << " matched" << std::endl;
            result.push_back(i);  
         }
       }
       return result; 
    }
};

int main( int argc, char** argv) {
   std::string tc1 = "UUDDLRRLLRBASS";
   std::vector<std::string> cc1 = {
      "UUDDLRLRBA",
      "UUDUDLRLRABABSS",
      "DDUURLRLAB",
      "UUDDLRLRBASS",
      "UDLRRLLRBASS"
   };
   std::vector<int> ans1 = { 0, 3, 4 };

   std::string tc2 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
   std::vector<std::string> cc2 = {
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
   };
   std::vector<int> ans2 = { 0 };

   std::string tc3 = "IDDQDDTSFHHALL";
   std::vector<std::string> cc3 = {
      "FHHALL", "FHSHH", "IDBEHOLDA", "IDBEHOLDI", 
      "IDBEHOLDL", "IDBEHOLDR", "IDBEHOLDS", "IDBEHOLDV", 
      "IDCHOPPERS", "IDCLEV", "IDCLIP", "IDDQD", 
      "IDDT", "IDFA", "IDKFA", "IDMYPOS", "IDMUS"
   };
   std::vector<int> ans3 = { 0, 11 };

   std::string tc4 = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYY";
   std::vector<std::string> cc4 = {
      "ABCDE", "BCDEF", "CDEFG", "DEFGH", "EFGHI",
      "FGHIJ", "GHIJK", "HIJKL", "IJKLM", "JKLMN",
      "KLMNO", "LMNOP", "MNOPQ", "NOPQR", "OPQRS",
      "PQRST", "QRSTU", "RSTUV", "STUVW", "TUVWX",
      "UVWXY", "VWXYZ", "WXYZA", "XYZAB", "YZABC",
      "ZABCD"
   };
   std::vector<int> ans4 = { 
      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  
      11,  12,  13,  14,  15,  16,  17,  18,  19,  20 
   };

   std::string tc5 = "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ";
   std::vector<std::string> cc5 = {
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSS", 
      "LAKJDGSJKGLSDKHFKDFHDGHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDHHSDKKSJDHFHJGKDKLSLSLJKASSJ",  
      "AKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKHHSJ",  
      "LAKDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDFHJGKDKLSLSLJKAHS",   
      "KJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDHHSDKKSJDHFHJGKDKLLSLJKAHS",    
      "LAKGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGJKGLSDKHFKDFHDGHHDKKSJDHFHJGKDKLSLSLJKAHS",    
      "LAKJDGJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHGHHSDKKSJDHFHJGKDKLSLSLJKAHS",   
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSL",
      "LAKJDGSJKGLSDKHFDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHS",   
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLJKAHSJ",
      "LAKJDGSJKGLSDHFKDFHDGHHSDKKSJDHFHJGKDKLSLSJKAHS",    
      "KGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSL",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJHFHJGKDKLSLSLJKAHS",   
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKSJHFHJGKDKLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHS",   
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKSJHFHJGKDKLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJKDKLSLSLJKAHSJ",
      "LKJDGSJKGLSDKHFKDFHDGHHSDKKJDHFHJGKDKLSLSLJKAHS",    
      "AKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDKLSLSLJKAHS",
      "LAJDGSJKGLSDKHFKDFHDGHHSDKKSJDFHJGKDKLSLSLKAHS",     
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFGKDKLSLSLJKAHSJ",
      "LKJDGSJKLSDKHFKDFHDGHHSDKSJDHFHJGKDKLSLSLJKAHS",     
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHHJGKDKLSLSLJKAHSJ",
      "AKJDGSJKGLSDKFKDFHDGHHSSJDHFJGKDKLSLSLJKAHS",        
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJDHFJGKDKLSLSLJKAHS",   
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSJHFHJGKDKLSLSLJKAHSJ",
      "LAKJDSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKSDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDSJKGLSDKHFKDFHDGHHSDKKSJDHFHJGKDLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKKJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDHHSDKKSJDHFHJGKDKLSLSLJKAHS",   
      "LAKDGSJKGLSDKHFKDFHDGHHSDKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSDKHFKDFHDGHHSDKSJDHFHJGKDKLSLSLJKAS",    
      "KJDGSJKGLSDKHFKDFHDGHSDKKSJDHFHJGKDKLSLSLJKAH",
      "LAKJDGSJKGLSDKHFKDFHDGHHDKKSJDHFHJGKDKLSLSLJKAHS",   
      "LAKDGSJKGLSDKFHDGHHSDKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJKGLSKHFKDFHDHHSDKKSJDHFHJGKDKLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHSKKSJDHFHJGKDKLSLSLJKAHSJ",
      "LAKJDGSJGLSDKHFKDFHDGHHSDKKSJDFHJGKDKLSLSLJKAHS",    
      "LAKJDGSJKGLSDKHFKDFHDGHHDKKSJDHFHJGKDKLSLSLJKAHSJ"
   };
   std::vector<int> ans5 = { 1, 3, 7, 13, 17, 27, 43 };

   CheatCode test;
   std::vector<int> result;
   bool fail = false;

   result = std::move(test.matches( tc1, cc1 ));
   if( !checkResult( result, ans1 ) ) {
      printResult( result, ans1 );	
      fail = true;
   }

   result = std::move(test.matches( tc2, cc2 ));
   if( !checkResult( result, ans2 ) ) {
      printResult( result, ans2 );	
      fail = true;
   }
   
   result = std::move(test.matches( tc3, cc3 ));
   if( !checkResult( result, ans3 ) ) {
      printResult( result, ans3 );	
      fail = true;
   }

   result = std::move(test.matches( tc4, cc4 ));
   if( !checkResult( result, ans4 ) ) {
      printResult( result, ans4 );	
      fail = true;
   }

   result = std::move(test.matches( tc5, cc5 ));
   if( !checkResult( result, ans5 ) ) {
      printResult( result, ans5 );	
      fail = true;
   }
   
   if( !fail ) {
      std::cout << "PASS" << std::endl;
   }

   return 0;
}
