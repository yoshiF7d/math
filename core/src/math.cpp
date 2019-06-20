#include <stdio.h>
#include <pwd.h>
#include <SymbolTable.h>
#include <Expr.h>
#include <parser.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <linenoise.hpp>
#define Function readline_Function
#include <readline/readline.h>
#undef Function

//class Evaluate;

char *stripQuotes(char *str);

int main(int argc, char *argv[]){
	char*com=nullptr,historyfile[256];
	const char *prompt="math>";
	Expr *expr=nullptr;
	int opt,oneline=0;
	std::string buf;
	struct passwd *pw = getpwuid(getuid());
	while((opt= getopt(argc,argv,"c:h"))!=-1){
		switch(opt){
		  case 'c':
			com = stripQuotes(optarg); break;
		  case 'h':
			printf("options\n");
			printf("-c <command> : input command\n");
			return 0;
		}
	}
	snprintf(historyfile,256,"%s/.math_histoy",pw->pw_dir);
	read_history(historyfile);
	SymbolTable::init();
	/*fprintf(stderr,"size of data : %ld byte\n",sizeof(union un_data));
	fprintf(stderr,"size of Expr : %ld byte\n",sizeof(Expr));
	fprintf(stderr,"size of Expr_Sub : %ld byte\n",sizeof(Expr_Sub));
	fprintf(stderr,"size of int : %ld byte\n",sizeof(int));*/
	if(com){
		SymbolTable::parser->set(std::string(com));
		expr=SymbolTable::parser->parse();
		if(!expr){
			printf("parse error\n");
		}else{
			//expr = Evaluate::function(expr);
			if(expr){
				 FullForm::mod(expr);
				expr->deleteRoot();
			}
		}
	}else{
		for(;;){
			char *line = readline(prompt);
			/*
			auto quit = linenoise::Readline(prompt,buf);
			if(quit){break;}
			*/
			buf = std::string(line);
			if(!buf.empty()){
				SymbolTable::parser->set(buf);
				expr=SymbolTable::parser->parse();
				if(!expr){
					std::cout << "parse error\n";
					continue;
				}
				TreeForm::mod(expr);
				std::cout << std::endl;
				add_history(buf.c_str());
				expr = SymbolTable::get(global_Evaluate)->evaluate(expr);
				if(!expr){break;}
				TreeForm::mod(expr);
				expr->deleteRoot();
				free(line);
			}
		}
	}
	SymbolTable::finish();
	write_history(historyfile);
	return 0;
}

char *strtail(char *str){return strchr(str ,'\0');}
char *stripQuotes(char *str){
	int len = strlen(str);
	char *p;
	if(str[0] == '\"' && strtail(str)[-1] =='\"'){
		for(p=str;*p;p++){*p = p[1];}
		p[-2]='\0';
	}
	return str;
}
