#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

/*program to make sources and include files from seed files*/
/*this code prodcuce a hardcord*/

#define TABLE_SIZE 512
#define INDENT 26
enum en_tag{t_none,t_name,t_alias,t_precedence,t_associativity,t_sign,t_builtinrules,t_attributes,
t_proto,t_source,t_data,t_doc};

char *spaces;
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
	buf = malloc(size+1);
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
char *String_clip(char *s, char *e){
	char *buf;int len;
	len = e-s+2;
	//printf("len : %d\n",len );
	buf = malloc(len);
	strncpy(buf,s,len);
	buf[len-1]='\0';
	return buf;
}

char *String_ncopy(const char *str, int max){
	int len = (max>0) ? max : strlen(str);
	char *buf = NULL;
	buf = malloc(len+1);
	strncpy(buf,str,len);
	buf[len] = '\0';
	return buf;
}

char *String_copy(char *str){
	if(!str){return NULL;}
	return String_ncopy(str,-1);
}

char *String_capitalize(char *name){
	char *p,*str;
	str = String_copy(name);
	for(p=str;*p;p++){
		*p = toupper(*p);
	}
	return str;
}

void String_fwrite(FILE *fp, char *buf){
	if(buf){fwrite(buf,strlen(buf),1,fp);}
}

void String_write(char *file, char *buf){
	FILE *fp;
	fp=fopen(file,"wb");
	String_fwrite(fp,buf);
	fclose(fp);
}

void String_replace(char *buf, char *str, char c){
	char *p, *s;
	for(s=str;*s;s++){
		for(p=buf;*p;p++){
			if(*p==*s){
				*p = c;
			}
		}
	}
}

char *getFileName(char *filename){
	char *p, *tail;
	tail = strchr(filename,'\0');
	for(p=tail;p>=filename;p--){
		if('/'==*p){return p+1;} 
	}
	return filename;
}

char *getFileExtension(char *filename){
	char *p, *tail;
	
	tail = strchr(filename,'\0');
	for(p=tail;p>=filename;p--){
		if('/'==*p){return tail;}
		if('.'==*p){return p;}  
	}
	return tail;
}

char *repeatedString(char c, int len){
	char *buf;
	int i;
	if(len<=0){return NULL;}
	buf	= malloc(len+1);
	for(i=0;i<len;i++){buf[i] = c;}
	buf[len]='\0';
	return buf;
}

char *readcontent(char **ptr,char *ps, char *tag, int skipc){
	char *p,*pss,*pe,sav;
	
	for(p=*ptr;*p;p++){
		/*skip comment*/
		if(skipc){
			if(*p=='/'){
				p++;
				if(*p=='/'){
					for(;*p;p++){if(*p=='\n'){break;}}
				}else if(*p=='*'){
					for(;*p;p++){
						if(*p=='*'){
							p++;
							if(*p=='/'){break;}
						}
					}
				}
			}
		}
		pe = p;
		/*read end tag*/
		if(*p=='<'){
			p++;
			if(*p=='/'){
				p++;
				pss=p; 
				for(;*p;p++){if(*p=='>'){break;}}
				sav = *p;
				*p = '\0';
				if(strcmp(tag,pss)!=0){
					//printf("tag unmatch : tag : %s\t pss : %s\n",tag,pss); 
					*p = sav;
					*ptr = p; 
					return NULL;
				}
				*p = sav;
				/*this break end main loop*/
				break;
			}
		}
	}
	sav = *pe;
	*pe='\0';
	if(*ps == '\0'){
		//printf("no content : %s\n",tag);
		pss = NULL;
	}
	else{pss = String_copy(ps);}
	*pe = sav;
	*ptr = p;
	return pss;
}

typedef struct st_slist{
	char *filein;
	char *name;
	char *doc;
	char *sfunc;
	char *proto;
	char *src;
	char *data;
	int sflag;
	struct st_slist *next;
}SList_Sub;
typedef SList_Sub *SList;

SList SList_create(char *filein, char *name, char *doc, char *sfunc, char *proto, char *src, 
				   char *data, int sflag){
	SList s = malloc(sizeof(SList_Sub));
	s->filein = filein;
	s->name = name;
	s->doc = doc;
	s->sfunc = sfunc;
	s->proto = proto;
	s->src = src;
	s->data = data;
	s->sflag = sflag;
	s->next = NULL;
	return s;
}

void SList_delete(SList s){
	if(s){
		free(s->filein);
		free(s->name);
		free(s->doc);
		free(s->sfunc);
		free(s->proto);
		free(s->src);
		free(s->data);
		free(s);
	}
}

void SList_deleteRoot(SList s){
	if(s){
		SList_delete(s);
		SList_deleteRoot(s->next);
	}
}

SList SList_append(SList s, SList s2){
	SList ss;
	if(!s){return s2;}
	for(ss=s;ss->next;ss=ss->next){}
	ss->next = s2;
	return s;
}
enum en_sflag{
	sf_init=0x0001,
	sf_finish=0x0002,
	sf_screate=0x0004,
	sf_sdelete=0x0008,
	sf_copy=0x0010,
	sf_print=0x0020,
	sf_docfunc=0x0040,
	sf_equals=0x0080
};

typedef struct st_list{
	char *name;
	int len;
	struct st_list *next;
}List_Sub;
typedef List_Sub *List;

List List_create(char *name){
	List list = malloc(sizeof(List_Sub));
	list->name = name;
	list->len = strlen(name);
	list->next = NULL;
	return list;
}

void List_delete(List list){
	free(list->name);
	if(list->next){List_delete(list->next);}
	free(list);
}

List List_append(List list, char *name){
	List s;
	if(list){
		for(s=list;s->next;s=s->next){}
		s->next = List_create(name);
	}else{
		list = List_create(name);
	}
	return list;
}

void List_print(List list){
	List s;
	char *p;
	int i;
	for(i=0,s=list;s;s=s->next,i++){
		printf("<<%d>>:\n",i);
		for(p=s->name;*p;p++){
			putchar(*p);
		}
		putchar('\n');
	}
}

char *List_concatenate(List list){
	List s;
	int wlen,i;
	char *str,*p;
	for(wlen=0,s=list;s;s=s->next){
		wlen += s->len;
	}
	p = str = malloc(wlen+1);
	for(s=list;s;s=s->next){
		strncpy(p,s->name,s->len);
		p+=s->len;
	}
	*p = '\0';
	return str;
}

/*$0 -> expr */
/*$1 -> expr->next */
/*$00 -> expr->child */
/*$01 -> expr->child->next */

char *parse(char *str,char *argname){
	char *p;
	int i,index,init=0;
	List list = List_create(String_copy("("));
	list = List_append(list,String_copy(argname));
	for(p=str;*p;p++){
		index = *p - '0';
		if(index >= 0 && index <= 9){
			if(init){
				list = List_append(list,String_copy("->child"));
			}else{
				init = 1;
			}
			for(i=0;i<index;i++){
				list = List_append(list,String_copy("->next"));
			}
		}else{
			break;
		}
	}
	list = List_append(list,String_copy(")"));
	p = List_concatenate(list);
	List_delete(list);
	return p;
}

char *preprocess_source(char *source, char *name, char *ps){
	char *argname;
	char *p,*pe,*rep;
	List list=List_create(String_copy("\t"));
;
	/*=== argname extract ===*/
	for(p=ps;*p!=')';p++){}
	for(pe = --p;p>ps && !isspace(*p);p--){
		if(*p == '&'){break;}
		if(*p == '*'){break;}
	}
	ps = p+1;
	argname = String_ncopy(ps,pe-ps+1);
	//printf("argname : %s\n",argname);
	
	/*=== argname replacement ===*/
	for(ps=p=source;*p;p++){
		if(*p=='/'){
			p++;
			if(*p=='/'){
				for(;*p;p++){if(*p=='\n'){break;}}
			}else if(*p=='*'){
				for(;*p;p++){
					if(*p=='*'){
						p++;
						if(*p=='/'){break;}
					}
				}
			}
		}
		if(*p == '$'){
			pe = p-1;
			list = List_append(list,String_clip(ps,pe));
			list = List_append(list,parse(p+1,argname));
			for(p++;(*p -'0')>=0 && (*p -'0')<=9;p++){}
			ps = p;
		}
		if(*p=='\n'){
			pe = p;
			list = List_append(list,String_clip(ps,pe));
			list = List_append(list,String_copy("\t"));
			ps = p+1;
		}
	}
	list = List_append(list,String_copy(ps));
	//List_print(list);
	p = List_concatenate(list);
	List_delete(list);
	free(argname);
	free(source);
	return p;
}

SList learn(SList list,char *filein){
	char tbuf[32];
	char *name=NULL,*alias=NULL,*fname=NULL,*precedence=NULL,*associativity=NULL,*sign=NULL,*builtinrules=NULL,
	*attributes=NULL,*proto=NULL,*source=NULL,*doc=NULL,*data=NULL;
	char sav;
	char *buf,*p,*ps,*sfunc,*id;
	enum en_tag tag=t_none;
	int sfunclen,namelen,sflag=0,skipc=0;
	
	//printf("filein : %s\n",filein);
	buf = String_read(filein);
	for(p=buf;*p;p++){
		skipc=0;
		switch(tag){
		  case t_none:
			if(*p=='<'){
				ps = ++p;
				for(;*p;p++){if(*p=='>'){break;}}
				sav = *p;
				*p='\0';
				snprintf(tbuf,32,"%s",ps);
				*p=sav;
				ps=p+1;
				if(*ps=='\n'){ps++;}
				if(strcmp(tbuf,"NAME")==0){tag=t_name;break;}
				if(strcmp(tbuf,"ALIAS")==0){tag=t_alias;break;}
				if(strcmp(tbuf,"PRECEDENCE")==0){tag=t_precedence;break;}
				if(strcmp(tbuf,"ASSOCIATIVITY")==0){tag=t_associativity;break;}
				if(strcmp(tbuf,"SIGN")==0){tag=t_sign;break;}
				if(strcmp(tbuf,"BUILTINRULES")==0){tag=t_builtinrules;break;}
				if(strcmp(tbuf,"ATTRIBUTES")==0){tag=t_attributes;break;}
				if(strcmp(tbuf,"PROTO")==0){tag=t_proto;skipc=1;break;}
				if(strcmp(tbuf,"SOURCE")==0){tag=t_source;skipc=1;break;}
				if(strcmp(tbuf,"DOC")==0){tag=t_doc;break;}
				if(strcmp(tbuf,"DATA")==0){tag=t_data;skipc=1;break;}
				fprintf(stderr,"undefined tag %s is found\n",tbuf);
			}
			break;
		  case t_name:
			name = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_precedence:
			precedence = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_associativity:
			associativity = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_sign:
			sign = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_builtinrules:
			builtinrules = readcontent(&p,ps,tbuf,skipc);
			String_replace(builtinrules,"\t\r\n\\",' ');
			tag = t_none;
			break;
		  case t_alias:
			alias = readcontent(&p,ps,tbuf,skipc);
			String_replace(alias,"\t\r\n\\",' ');
			tag = t_none;
			break;
		  case t_attributes:
			attributes = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_source:
			source = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_proto:
			proto = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_doc:
			doc = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_data:
			data = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  default:
			break;
		}
	}
	if(!attributes){attributes = String_copy("0");}
	if(!precedence){precedence = String_copy("0");}
	if(!associativity){associativity = String_copy("0");}
	if(!sign){sign = String_copy("\"\"");}
	if(!builtinrules){builtinrules = String_copy("nullptr");}
	else{
		fname = malloc(sfunclen=(strlen(builtinrules)+22));
		snprintf(fname,sfunclen,"Expr_createString(\"%s\")",builtinrules);
		free(builtinrules);
		builtinrules = fname;
	}
	if(!alias){alias = String_copy("nullptr");}
	else{
		fname = malloc(sfunclen=(strlen(alias)+22));
		snprintf(fname,sfunclen,"Expr_createString(\"%s\")",alias);
		free(alias);
		alias = fname;
	}
	
	/*
	printf("name : %s\n",name);
	printf("attributes : %s\n",attributes);
	printf("precedence : %s\n",precedence);
	printf("associativity : %s\n",associativity);
	printf("sign : %s\n",sign);
	printf("builtinrules : %s\n",builtinrules);
	printf("doc : %s\n",doc);
	*/
	//printf("name : %s\n",name);
	//printf("data : %s\n",data);
	if(source){
		/*check if "function()" function is exist in source*/
		namelen = strlen(name);
		fname = malloc(11);
		snprintf(fname,11," function(");
		if((p=strstr(source,fname))!=NULL){
			source = preprocess_source(source,name,p+10);
		}
		free(fname);
		sfunc = malloc(sfunclen = (7 + strlen(name) + 2 + 1 
									 + strlen(sign) + 1
									 + strlen(name) + 3 + 1
									 + strlen(precedence) + 1 
									 + strlen(attributes) + 1
									 + strlen(associativity) + 1 
									 + strlen(builtinrules) + 1
									 + strlen(alias) + 1 + 1));
		snprintf(sfunc,sfunclen,"Symbol(\"%s\",%s,id_%s,%s,%s,%s,%s,%s)",
				 name,sign,name,precedence,attributes,associativity,builtinrules,alias);
	}
	
	free(buf);
	free(precedence);
	free(associativity);
	free(sign);
	free(builtinrules);
	free(attributes);
	free(alias);
	return SList_append(list,SList_create(String_copy(filein),name,doc,sfunc,proto,source,data,sflag));
}

typedef struct st_clist{
	SList s;
	char *name;
	char *capital;
	struct st_clist *next;
}CList_Sub;
typedef CList_Sub *CList;

CList CList_create(SList s, char *name){
	CList c = malloc(sizeof(CList_Sub));
	c->s = s;
	c->name = String_copy(name);
	c->capital = String_capitalize(name);
	c->next = NULL;
	return c;
}

void CList_delete(CList c){
	if(c){
		SList_deleteRoot(c->s);
		free(c->name);
		free(c->capital);
		free(c);
	}
}

void CList_deleteRoot(CList c){
	if(c){
		CList_delete(c);
		CList_deleteRoot(c->next);
	}
}

CList CList_append(CList c, CList c2){
	CList cc;
	if(!c){return c2;}
	for(cc=c;cc->next;cc=cc->next){}
	cc->next = c2;
	return c;
}

CList master(CList list, char *dirin, char *fileout){
	SList ss,s=NULL;
	DIR *dp=NULL;
	FILE *fp=NULL;
	struct dirent *entry;
	struct stat stfi,stfo;
	char seeddir[256],srcdir[256],filein[256],srcfile[256];
	char *buf,*p;

	//fprintf(stderr,"%s\n",getFileName(dirin));
	snprintf(seeddir,256,"%s/xml",dirin);
	snprintf(srcdir,256,"%s/src",dirin);
	if((dp = opendir(seeddir))==NULL){perror("master"); return NULL;}
	while((entry=readdir(dp))!=NULL){
		if(entry->d_name[0]=='.'){continue;}
		if(strcmp(getFileExtension(entry->d_name),".xml")==0){
			snprintf(filein,256,"%s/%s",seeddir,entry->d_name);
			//fprintf(stderr,"%s\n",filein);
			s=learn(s,filein);
		}
	}
	closedir(dp);
	/*if source file info is written in seed file, make source file*/
	for(ss=s;ss;ss=ss->next){
		snprintf(srcfile,256,"%s/%s.cpp",srcdir,ss->name);
		if(stat(srcfile,&stfo) != -1){
			if(stat(ss->filein,&stfi) != -1){
				if(stfi.st_mtime <= stfo.st_mtime){continue;}
			}
		}
		fprintf(stdout,"making %s\n",srcfile);
		fp = fopen(srcfile,"w");
		fprintf(fp,"class %s : public Symbol{\n",ss->name);
		fprintf(fp,"  public:\n");
		fprintf(fp,"\t%s() : \n\t",ss->name);
		String_fwrite(fp,ss->sfunc);
		fprintf(fp,"\n\t{}\n",ss->name);
		String_fwrite(fp,ss->src);
		if(!(ss->sflag & sf_docfunc ) && (s->doc)){
			fprintf(fp,"\tvirtual void printdoc() override{\n");
			buf = strtok(s->doc,"\n");
			/* " -> /"  % -> %%*/
			while(buf){
				fprintf(fp,"\t\tcout << \"%s",spaces);
				for(p=buf;*p;p++){
					if(*p == '\"'){fputc('\\',fp);}
					if(*p == '%'){fputc('%',fp);}
					fputc(*p,fp);
				}
				fprintf(fp,"\\n\"\n");
				buf = strtok(NULL,"\n");
			}
			fprintf(fp,"\t}\n");
		}
		fprintf(fp,"}\n");
		fclose(fp);
	}
	return CList_append(list,CList_create(s,getFileName(dirin)));
}

int main(int argc, char *argv[]){
	FILE *fp=stdout,*fp3=stdout;
	CList c,list=NULL;
	SList s=NULL;
	DIR *dp=NULL;
	struct dirent *entry;
	char dirin[256],*buf,*p;
	
	if(argc<4){fprintf(stderr,"usage : %s symboldir SymbolList.h Data.h\n",argv[0]); return -1;}
	/*fp : header file*/
	/*fp3 : header file 2*/
	if((fp = fopen(argv[2],"w"))==NULL){perror("prec"); return -1;}
	if((fp3 = fopen(argv[3],"w"))==NULL){perror("prec"); return -1;}
	if((dp = opendir(argv[1]))==NULL){perror("prec"); return -1;}
	spaces = repeatedString(' ',INDENT);
	while((entry=readdir(dp))!=NULL){
		if(entry->d_name[0]=='.'){continue;}
		snprintf(dirin,256,"%s/%s",argv[1],entry->d_name);
		list = master(list,dirin,argv[3]);
	}
	closedir(dp);
	/*for(c=list;c;c=c->next){fprintf(stderr,"%s\n",c->name);}*/
	fprintf(fp,"#ifndef ");
	for(p=getFileName(argv[2]);*p;p++){
		if(*p=='.'){break;}
		fputc(toupper(*p),fp);
	}
	fprintf(fp,"_H\n");
	fprintf(fp,"#define ");
	for(p=getFileName(argv[2]);*p;p++){
		if(*p=='.'){break;}
		fputc(toupper(*p),fp);
	}
	fprintf(fp,"_H\n");
	fprintf(fp,"#define TABLE_SIZE %d\n",TABLE_SIZE);

	/*write symbol name list*/
	fprintf(fp,"/*====== symbol table ======*/\n");
	for(c=list;c;c=c->next){
		fprintf(fp,"#define CONTEXT_%s(UNFOLD,TABLE) ",c->capital);
		for(s=c->s;s;s=s->next){
			fprintf(fp,"\\\nUNFOLD(%s,TABLE,%s)",s->name,c->name);
		}
		fprintf(fp,"\n\n");
	}
	
	/*write enum*/
	fprintf(fp,"/*====== symbol id ======*/\n");
	fprintf(fp,"#define UNFOLD(SYMBOL,TABLE,NAME) NAME##_##SYMBOL,\n");	
	fprintf(fp,"enum symbol_id{\n");
	for(c=list;c;c=c->next){
		fprintf(fp,"\tCONTEXT_%s(UNFOLD,TABLE)\n",c->capital);
	}
	fprintf(fp,"id_end,\n");
	fprintf(fp,"};\n");
	fprintf(fp,"#undef UNFOLD\n\n");
	
	/*write make context*/
	fprintf(fp,"/*====== make context ======*/\n");
	fprintf(fp,"#define SET_TABLE(SYMBOL,TABLE,NAME) TABLE[NAME##_##SYMBOL]=new SYMBOL();\n");
	fprintf(fp,"#define SET_MAP(SYMBOL,TABLE,NAME) {#SYMBOL,TABLE[NAME##_##SYMBOL]},\n");
	for(c=list;c;c=c->next){
		fprintf(fp,"#define MAKE_CONTEXT_%s(LIST,TABLE) \\\n"
		"CONTEXT_%s(SET_TABLE,TABLE) LIST.push_back(make_pair(\"%s\",SymbolMap{CONTEXT_%s(SET_MAP,TABLE)}));\n",
		c->capital,c->capital,c->name,c->capital);
	}
	
	fprintf(fp,"#define MAKE_CONTEXT(LIST,TABLE) \\\n");
	for(c=list;c;c=c->next){
		fprintf(fp,"MAKE_CONTEXT_%s(LIST,TABLE)\n",c->capital);
	}
	fprintf(fp,"\n#endif\n");
	
	/*write data types*/
	fprintf(fp3,"#ifndef ");
	for(p=getFileName(argv[3]);*p;p++){
		if(*p=='.'){break;}
		fputc(toupper(*p),fp3);
	}
	fprintf(fp3,"_H\n");
	fprintf(fp3,"#define ");
	for(p=getFileName(argv[3]);*p;p++){
		if(*p=='.'){break;}
		fputc(toupper(*p),fp3);
	}
	fprintf(fp3,"_H\n");
	fprintf(fp3,"#define R64_LIMIT 52\n");
	fprintf(fp3,"#define I32_LIMIT 31\n");
	fprintf(fp3,"#define I64_LIMIT 63\n");
	fprintf(fp3,"#include <gmp.h>\n");
	fprintf(fp3,"#include <mpfr.h>\n");
	fprintf(fp3,"union Data{\n\t");
	for(c=list;c;c=c->next){
		for(s=c->s;s;s=s->next){
			if(s->data){
				for(p=s->data;*p;p++){
					fputc(*p,fp3);
					if(*p=='\n'){fputc('\t',fp3);}
				}
			}
		}
	}
	fputc('\n',fp3);
	fprintf(fp3,"};\n");
	fprintf(fp3,"#endif\n");
	CList_deleteRoot(list);
	fclose(fp);
	fclose(fp3);
	return 0;
}
