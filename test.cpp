#include <linenoise.hpp>
#include <iostream>

int main(){
	while (true) {
	  // Read line
	  std::string line;
	  auto quit = linenoise::Readline("hello> ", line);
	  if (quit) {
	  	break;
		}
	std::cout <<  "echo: '" << line << "'" << std::endl;	
	// Add text to history
	linenoise::AddHistory(line.c_str());
	}

}
