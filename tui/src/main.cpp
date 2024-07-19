#include <iostream>
#include <filesystem>
#include <cassert>
#include <defs.hpp>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

  fs::path __uiPath = "./";
  std::string commandbeta = "cmake -DPROJECT_NAME=";
  commandbeta += argv[1];
  commandbeta += " .. ";
  commandbeta += "&& cd .. && ln -s build/compile_commands.json";

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <DirectoryName>" << std::endl;
    return 1;
  }

  __uiPath /= argv[1];

  std::cout << "Creating CursesUI project in : " << __uiPath << std::endl;

  bool created = fs::create_directory(__uiPath);
  assert(created && "Directory creation failed");

  std::cout << "******************************************************" << __uiPath << std::endl;

  for(int i = 0 ; dirNames[i] != nullptr ; i++){

   __uiPath /= dirNames[i];

   if(!fs::create_directory(__uiPath)){
    std::cerr << "Error creating directory: " << __uiPath << std::endl;
    return 1;
   }
   std::cout << "Successfully Created : " << __uiPath << std::endl;
    __uiPath.clear();
    __uiPath /= argv[1];
  }

  std::cout << "******************************************************" << __uiPath << std::endl;

  std::fstream fileTouch;

  for(int j = 0 ; dirfiles[j] != nullptr ; j++){

	__uiPath /= dirfiles[j];
  	fileTouch.open(__uiPath,std::ios::out);

  	if(!fileTouch.is_open()){
         std::cerr << "Error creating/opening file : " << __uiPath << std::endl;
         return 1;
  	}

    	 switch(j){
	       case 0:
	       fileTouch << HomeContent;
               break;
	       case 1:
	       fileTouch<<CMakeFileHeader;
	       break;
	       case 2:
	       fileTouch<<maincpp;
	       break;
	       default:
	       break;
    	 }
    std::cout << "Successfully Written to : " << __uiPath << std::endl;
    fileTouch.close();
    __uiPath.clear();
    __uiPath /= argv[1];
  }
   __uiPath /= dirNames[2];
   fs::current_path(__uiPath);
   std::system(commandbeta.c_str());
  return 0;
}
