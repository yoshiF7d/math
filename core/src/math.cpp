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
#include <readline/history.h>
#undef Function

//class Evaluate;

char *String_copy(const char *str);
char *String_read(char *file);
char *stripQuotes(char *str);

int main(int argc, char *argv[]){
	char*com=nullptr,historyfile[256];
	const char *prompt="math>";
	Expr *expr=nullptr;
	int opt,oneline=0;
	std::string buf;
	struct passwd *pw = getpwuid(getuid());
	while((opt= getopt(argc,argv,"f:c:h"))!=-1){
		switch(opt){
		  case 'f':
		  	com = String_read(optarg); break;
		  case 'c':
			com = String_copy(stripQuotes(optarg)); break;
		  case 'h':
			printf("options\n");
			printf("-c <command> : input command\n");
			printf("-f <file> : input source file\n");
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
				TreeForm::mod(expr);
				expr->deleteRoot();
			}
		}
		free(com);
	}else{
		for(;;){
			char *line = readline(prompt);
			/*
			auto quit = linenoise::Readline(prompt,buf);
			if(quit){break;}
			*/
			buf = std::string(line);
			free(line);
			if(!buf.empty()){
				SymbolTable::parser->set(buf);
				expr=SymbolTable::parser->parse();
				if(!expr){
					std::cout << "parse error\n";
					continue;
				}
				/*
				std::cout << KYEL << "after pre-eval" << KNRM << "\n";
				TreeForm::mod(expr);
				std::cout << std::endl;
				*/
				add_history(buf.c_str());
				expr = SymbolTable::get(global_Evaluate)->evaluate(expr);
				if(!expr){break;}
				
				std::cout << KYEL << "after eval" << KNRM << "\n";
				
				TreeForm::mod(expr);
				std::cout << std::endl;
				expr->deleteRoot();
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

char *String_ncopy(const char *str, int max){
	int len = (max >0) ? max : strlen(str);
	char *buf=NULL;
	buf = (char*)malloc(len+1);
	strncpy(buf,str,len);
	buf[len]='\0';
	return buf;
}

char *String_copy(const char *str){
	if(!str){return NULL;}
	return String_ncopy(str,-1);
}

unsigned long getFileSize(FILE *fp){	
	unsigned long fsize = ftell(fp);
	fpos_t p; 
	fgetpos(fp,&p);
	fseek(fp,0,SEEK_END);
	fsize = ftell(fp) - fsize;
	fsetpos(fp,&p);
	return (unsigned long)fsize;
} 

char *String_fread(FILE *fp){
	char *buf;
	char c; unsigned long size;
	size = getFileSize(fp);
	buf = (char*)malloc(size+1);
	fread(buf,1,size,fp); buf[size] = '\0';
	return buf;
}

char *String_read(char *file){
	char *buf;	
	FILE *fp = fopen(file,"r");
	if(fp==NULL){
		printf("%s\n",file);
		perror("String_read");return NULL;
	}
	buf = String_fread(fp);
	fclose(fp);
	return buf;
}

