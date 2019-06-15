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
enum en_tag{
	t_none,
	t_name,
	t_alias,
	t_precedence,
	t_associativity,
	t_symbol,
	t_builtinrules,
	t_attributes,
	t_source,
	t_datainc,
	t_datasrc,
	t_doc
};

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
		if(*p=='.'){*p = '_'; continue;}
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

void String_removeBlank(char *string){
	char *p,*pp,*last;
	last = strchr(string,'\0');
	for(p=string;*p;){
		if(isblank(*p)){
			for(pp=p;pp<last;pp++){
				*pp = *(pp+1);
			}
		}else{
			break;
		}
	}
	for(p=last;p>string;p--){
		if(*p=='\0'){continue;}
		else if(isblank(*p)){*p='\0';}
		else{break;}
	}
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

typedef struct st_list{
	void *content;
	struct st_list *next;
}List_Sub;
typedef List_Sub *List;

List List_create(void *content){
	List list;
	list = malloc(sizeof(List_Sub));
	list->content = content;
	list->next = NULL;
	return list;
}

void List_delete(List list, void (*delete)(void*)){
	if(delete){delete(list->content);}
	free(list);
}

void List_deleteRoot(List list,void (*delete)(void*)){
	if(list){
		List_deleteRoot(list->next,delete);
		List_delete(list,delete);
	}
}

int List_length(List list){
	int i=0;
	for(i=0;list;list=list->next){i++;}
	return i;
}

List List_append(List list, void *content){
	List root=list;
	if(!list){return List_create(content);}
	while(list->next){list = list->next;}
		list->next = List_create(content);
	return root;
}

void List_enum(List list, void (*func)(void*)){
	for(;list;list=list->next){
		func(list->content);
	}
}

typedef struct st_info{
	char *filein;
	char *name;
	char *doc;
	char *sfunc;
	char *src;
	char *datainc;
	char *datasrc;
	int sflag;
}Info_Sub;
typedef Info_Sub *Info;

Info Info_create(char *filein, char *name, char *doc, char *sfunc, char *src, char *datainc, char *datasrc, int sflag){
	Info info = malloc(sizeof(Info_Sub));
	info->filein = filein;
	info->name = name;
	info->doc = doc;
	info->sfunc = sfunc;
	info->src = src;
	info->datainc = datainc;
	info->datasrc = datasrc;
	info->sflag = sflag;
	return info;
}

void Info_delete(Info info){
	if(info){
		free(info->filein);
		free(info->doc);
		free(info->sfunc);
		free(info->src);
		free(info->datainc);
		free(info->datasrc);
		free(info);
	}
}
void Info_vdelete(void *info){Info_delete(info);}

void Info_print(Info info){
	printf("filein : %s\n",info->filein);
	printf("sfunc : %s\n",info->sfunc);
	printf("datainc : %s\n",info->datainc);
	printf("datasrc : %s\n",info->datasrc);
}

void Info_vprint(void *info){Info_print(info);}

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

char *List_concatenate(List list){
	List s;
	int wlen,i;
	char *str,*p;
	for(wlen=0,s=list;s;s=s->next){
		wlen += strlen(s->content);
	}
	p = str = malloc(wlen+1);
	for(s=list;s;s=s->next){
		strcpy(p,s->content);
		p+=strlen(s->content);
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
	List_deleteRoot(list,free);
	return p;
}

char *extract_argname(char *string){
	/*=== argname extract ===*/
	char *p,*ps,*pe;
	for(p=ps=string;*p!=')';p++){}
	for(pe = --p;p>string && !isspace(*p);p--){
		if(*p == '&'){break;}
		if(*p == '*'){break;}
	}
	ps = p+1;
	return String_ncopy(ps,pe-ps+1);
}

char *extract_funcname(char *string){
	/*=== argname extract ===*/
	char *pe;
	for(pe=string;*pe!='(';pe++){}
	return String_ncopy(string,pe-string+1);
}

char *preprocess_source(char *name,char *source, char *argname, char *funcname){
	char *p,*ps,*pe,*temp=funcname;
	int flen = strlen(funcname);
	int len;
	List list=NULL;
	//List_create(String_copy("\t"));
	//printf("%s\n",funcname);
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
			//list = List_append(list,String_copy("\t"));
			ps = p+1;
		}
		if(*p==*temp){
			temp++;
			if(*temp=='\0'){
				temp = p-flen-1;
				if(isspace(*temp) || *temp == '}'){
					pe = p-strlen(funcname);
					list = List_append(list,String_clip(ps,pe));
					len = snprintf(NULL,0,"%s::%s",name,funcname);
					temp = malloc(len+1);
					snprintf(temp,len+1,"%s::%s",name,funcname);
					temp[len] = '\0';
					list = List_append(list,temp);
					ps = p+1;
					temp = funcname;
				}
			}
		}else{
			temp=funcname;
		}
	}
	list = List_append(list,String_copy(ps));
	//List_print(list);
	p = List_concatenate(list);
	List_deleteRoot(list,free);
	free(argname);
	free(source);
	return p;
}

void vprint(void *s){puts(s);}
void parseSign(char *mark[], char *str){
	char *p,*s;
	List list=NULL,l;
	if(str){
		for(s=p=str;*p;p++){
				if(*p == ','){
					list = List_append(list,String_clip(s,p-1));
					s = p+1;
				}
			}
			list = List_append(list,String_copy(s));
			//printf("str : %s\n",str);
			//List_enum(list,vprint);
			l = list; mark[0] = l->content;
			l = list->next; mark[1] = l->content;
			//printf("mark[0] : %s\n",mark[0]);
			//printf("mark[1] : %s\n",mark[1]);
			List_deleteRoot(list,NULL);
	}else{
		mark[0] = String_copy("\"\"");
		mark[1] = String_copy("\"\"");
		/*
		l = list;
		mark[0] = l->content;
		l = list->next;
		mark[1] = l->content;
		 */
	}
}
char *removeDirectoryPath(char *str){
	char *p = strrchr(str,'/');
	if(p){
		return p+1;
	}else{
		return str;
	}
}


List learn(List list,char *filein,char *dirin){
	char tbuf[32];
	char *name=NULL,*alias=NULL,*fname=NULL,*precedence=NULL,*associativity=NULL,*sign=NULL,*builtinrules=NULL,
	*attributes=NULL,*proto=NULL,*source=NULL,*doc=NULL,*datainc=NULL,*datasrc=NULL;
	char sav;
	char *buf,*p,*ps,*sfunc=NULL,*id;
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
				if(strcmp(tbuf,"SYMBOL")==0){tag=t_symbol;break;}
				if(strcmp(tbuf,"BUILTINRULES")==0){tag=t_builtinrules;break;}
				if(strcmp(tbuf,"ATTRIBUTES")==0){tag=t_attributes;break;}
				if(strcmp(tbuf,"SOURCE")==0){tag=t_source;skipc=1;break;}
				if(strcmp(tbuf,"DOC")==0){tag=t_doc;break;}
				if(strcmp(tbuf,"DATAINC")==0){tag=t_datainc;skipc=1;break;}
				if(strcmp(tbuf,"DATASRC")==0){tag=t_datasrc;skipc=1;break;}
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
		  case t_symbol:
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
		  case t_doc:
			doc = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_datainc:
			datainc = readcontent(&p,ps,tbuf,skipc);
			tag = t_none;
			break;
		  case t_datasrc:
			datasrc = readcontent(&p,ps,tbuf,skipc);
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
	if(!builtinrules){builtinrules = String_copy("\"\"");}
	else{
		fname = malloc(sfunclen=(strlen(builtinrules)+22));
		snprintf(fname,sfunclen,"\"%s\"",builtinrules);
		free(builtinrules);
		builtinrules = fname;
	}
	if(!alias){alias = String_copy("\"\"");}
	else{
		fname = malloc(sfunclen=(strlen(alias)+22));
		snprintf(fname,sfunclen,"\"%s\"",alias);
		free(alias);
		alias = fname;
	}
	//printf("name : %s\n",name);
	//printf("data : %s\n",data);
	/*
	printf("name : %s\n",name);
	printf("attributes : %s\n",attributes);
	printf("precedence : %s\n",precedence);
	printf("associativity : %s\n",associativity);
	printf("sign : %s\n",sign);
	printf("builtinrules : %s\n",builtinrules);
	printf("doc : %s\n",doc);
	printf("sign : %s\n",sign);
	*/
	sfunclen = snprintf(NULL,0,"Symbol(\"%s\",%s,%s_%s,%s,%s,%s,%s,%s)",
		name,sign,removeDirectoryPath(dirin),name,precedence,attributes,associativity,builtinrules,alias);
	sfunc = malloc(sfunclen+1);
	snprintf(sfunc,sfunclen+1,"Symbol(\"%s\",%s,%s_%s,%s,%s,%s,%s,%s)",
		name,sign,removeDirectoryPath(dirin),name,precedence,attributes,associativity,builtinrules,alias);
	sfunc[sfunclen]='\0';
	
	free(buf);
	free(precedence);
	free(associativity);
	free(sign);
	free(builtinrules);
	free(attributes);
	free(alias);
	return List_append(list,Info_create(String_copy(filein),name,doc,sfunc,source,datainc,datasrc,sflag));
}

typedef struct st_context{
	List list;
	char *name;
	char *capital;
}Context_Sub;
typedef Context_Sub *Context;

Context Context_create(List list, char *name){
	Context context = malloc(sizeof(Context_Sub));
	context->list = list;
	context->name = String_copy(name);
	context->capital = String_capitalize(name);
	return context;
}

void Context_delete(Context c){
	if(c){
		List_deleteRoot(c->list,Info_vdelete);
		free(c->name);
		free(c->capital);
		free(c);
	}
}

void Context_vdelete(void *c){Context_delete(c);}

void Context_print(Context c){
	printf("name : %s\n",c->name);
	List_enum(c->list,Info_vprint);
}
void Context_vprint(void *c){Context_print(c);}

typedef struct st_finfo{
	char *rtntype;
	char *name;
	char *body;
}FuncInfo_Sub;
typedef FuncInfo_Sub *FuncInfo;

FuncInfo FuncInfo_create(char *rtntype, char *name, char *body){
	FuncInfo finfo = malloc(sizeof(FuncInfo_Sub));
	finfo->rtntype = rtntype;
	finfo->name = name;
	finfo->body = body;
	return finfo;
}

void FuncInfo_delete(FuncInfo finfo){
	if(finfo){
		free(finfo->rtntype);
		free(finfo->name);
		free(finfo->body);
		free(finfo);
	}
}

void FuncInfo_print(FuncInfo finfo){
	printf("return type : %s\n",finfo->rtntype);
	printf("name : %s\n",finfo->name);
	printf("body : %s\n",finfo->body);
}

void FuncInfo_vprint(void *finfo){FuncInfo_print(finfo);}

void readtill(char **str, char *s){
	char *p,*pp=s;
	for(p=*str;*p;p++){
		while(*p==*pp){
			p++; pp++;
		}
		if(*pp){pp=s;}
		else{*str=p; break;}
	}
}
#define KNRM  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT "\x1B[37m"

#define BNRM  "\x1B[0m"
#define BBLK  "\x1B[40m"
#define BRED  "\x1B[41m"
#define BGRN  "\x1B[42m"
#define BYEL  "\x1B[43m"
#define BBLU  "\x1B[44m"
#define BMAG  "\x1B[45m"
#define BCYN  "\x1B[46m"
#define BWHT "\x1B[47m"

#define RESET  "\x1B[0m"

List FList_extract(char *src){
	char *p,*s,*e=NULL;
	char *name,*rtntype;
	int level;
	List t,list=NULL;
	FuncInfo finfo;
	if(!src){return NULL;}
	for(level=0,s=p=src;*p;p++){
		switch(*p){
		case '/' :
			switch(*++p){
				case '*':
					readtill(&p,"*/"); break;
				case '/':
					readtill(&p,"\n"); break;
				case '\0':
					goto end;
				default:
					break;
			}
			break;
		case '{':
			if(level==0){e=p-1;}
			level++;
			break;
		case '}':
			level--;
			if(level==0){
				finfo = FuncInfo_create(String_clip(s,e),NULL,String_clip(e+1,p));
				list = List_append(list,finfo);
				for(p++;*p == '\n' || isblank(*p);p++){}
				if(*p){
					s = p;
				}else{
					goto end;
				}
			}
			break;
		default:
			break;
		}
	}
	end:

	for(t=list;t;t=t->next){
		finfo = t->content;
		if(finfo->body){
			/*
				rtntype : "type func(...)"
				name : NULL
			->
				rtntype : "type"
				name : "func"
			*/
			p = strchr(finfo->rtntype,'(');
			if(p==NULL){
				/*
				printf("rtntype : %s\n",finfo->rtntype);
				printf("body : %s\n",finfo->body);
				printf("NULL POINTER\n");exit(1);
				*/
			}
			for(;p!=finfo->rtntype;p--){
				if(isblank(*p) || *p == '*' || *p == '&'){
					p++;
					finfo->name = String_copy(p);
					*p='\0';
					goto loopend;
				}
			}
			loopend:;
		}
	}
	return list;
}

void incwrite(char *incfile, List ss, List ff){
	FILE *fp = fopen(incfile,"w");
	Info info = ss->content;
	FuncInfo finfo;
	List f;
	fprintf(fp,"#include <Expr.h>\n");
	fprintf(fp,"#include <Symbol.h>\n");
	fprintf(fp,"class %s : public Symbol{\n",info->name);
	fprintf(fp,"public :\n");
	fprintf(fp,"\t%s();\n",info->name);
	for(f=ff;f;f=f->next){
		finfo = f->content;
		fprintf(fp,"\t%s%s;",finfo->rtntype,finfo->name);
		if(f->next){fprintf(fp,"\n");}
	}
	if(info->datainc){fprintf(fp,"\nData* createData() override;\n");}
	fprintf(fp,"\n};\n");
	if(info->datainc){
		fprintf(fp,"%s\n",info->datainc);
	}
	fclose(fp);
}

char *remove_static(char *str){
	char *p = strstr(str,"static");
	if(p){
		p += 6;
		for(;isspace(*p);p++){}
		return p;
	}else{
		return str;
	}
}

char *remove_virt(char *str){
	char *pe;
	for(pe=str;*pe!=')';pe++){}
	return String_ncopy(str,pe-str+1);
}

char *extract_struct(char *str){
	char *ps,*pe;
	ps = strstr(str,"struct");
	ps += 6;
	for(;isblank(*ps);ps++){}
	for(pe=ps;!isblank(*pe);pe++){}
	return String_clip(ps,pe);
}

void srcwrite(char *srcfile, List ss, List ff){
	FILE *fp = fopen(srcfile,"w");
	List f;
	Info info = ss->content;
	FuncInfo finfo;
	fprintf(fp,"#include <SymbolList.h>\n");
	fprintf(fp,"#include <SymbolTable.h>\n");
	fprintf(fp,"%s::%s() : %s{}\n",info->name,info->name,info->sfunc);
	for(f=ff;f;f=f->next){
		finfo = f->content;
		//printf("%s\n",finfo->name);
		fprintf(fp,"%s%s::%s%s\n",
			remove_static(finfo->rtntype),
			info->name,
			remove_virt(finfo->name),
			preprocess_source(
				info->name,finfo->body,
				extract_argname(finfo->name),
				extract_funcname(finfo->name)
			)
		);
	}
	if(info->datasrc){
		fprintf(fp,"Data* %s::createData(){return new %s();}\n",info->name,extract_struct(info->datainc));
		fprintf(fp,"%s\n",info->datasrc);
	}
	fclose(fp);
}

List master(List list, char *dirin, char *fileout){
	List ss,s=NULL;
	List flist=NULL,dlist=NULL;
	Info info;
	FuncInfo finfo;
	DIR *dp=NULL;
	FILE *fp=NULL;
	struct dirent *entry;
	struct stat stfi,stfo;
	char seeddir[256],srcdir[256],incdir[256],filein[256],srcfile[256],incfile[256];
	char *buf,*p;

	//fprintf(stderr,"%s\n",getFileName(dirin));
	snprintf(seeddir,256,"%s/xml",dirin);
	snprintf(srcdir,256,"%s/src",dirin);
	snprintf(incdir,256,"%s/inc",dirin);
	if((dp = opendir(seeddir))==NULL){perror("master"); return NULL;}
	while((entry=readdir(dp))!=NULL){
		if(entry->d_name[0]=='.'){continue;}
		if(!strcmp(getFileExtension(entry->d_name),".xml")){
			snprintf(filein,256,"%s/%s",seeddir,entry->d_name);
			//fprintf(stdout,"%s\n",filein);
			s=learn(s,filein,dirin);
		}
	}
	closedir(dp);
	//List_enum(s,Info_vprint);
	/*if source file info is written in seed file, make source file*/
	for(ss=s;ss;ss=ss->next){
		info = ss->content;
		snprintf(incfile,256,"%s/%s.h",incdir,info->name);
		snprintf(srcfile,256,"%s/%s.cpp",srcdir,info->name);
		if(stat(srcfile,&stfo) != -1){
			if(stat(info->filein,&stfi) != -1){
				if(stfi.st_mtime <= stfo.st_mtime){continue;}
			}
		}
		//printf("%s\n",info->name);
		flist = FList_extract(info->src);
		fprintf(stdout,"making %s\n",incfile);
		incwrite(incfile,ss,flist);
		fprintf(stdout,"making %s\n",srcfile);
		srcwrite(srcfile,ss,flist);
	}
	//return list;
	return List_append(list,Context_create(s,getFileName(dirin)));
}

typedef struct st_dtype{
	char *type;
	char *name;
}DataType_Sub;
typedef DataType_Sub *DataType;

DataType DataType_create(char *type, char *name){
	DataType dtype = malloc(sizeof(DataType_Sub));
	dtype->type = type;
	dtype->name = name;
	return dtype;
}

DataType DataType_parse(char *string){
	char *type=NULL, *name=NULL,*p,sav;
	char *last;
	if(!(last = strchr(string,'{'))){
		last = strchr(string,'\0');
	}
	for(p=last-1;p>string;p--){
		if(isblank(*p) || *p=='*' || *p =='&'){
			name = String_copy(p+1);
			*(p+1) ='\0';
			type = String_copy(string);
			break;
		}
	}
	String_removeBlank(type);
	return DataType_create(type,name);
}

void DataType_delete(DataType dtype){
	if(dtype){
		free(dtype->type);
		free(dtype->name);
	}
}
void DataType_vdelete(void *dtype){DataType_delete(dtype);}

void listwrite(char *file,List list){
	FILE *fp = fopen(file,"w");
	char *p,*buf;
	List s;
	List c;
	Context context;
	Info info;

	buf = String_capitalize(getFileName(file));
	fprintf(fp,"#ifndef %s\n",buf);
	fprintf(fp,"#define %s\n",buf);
	fprintf(fp,"#define TABLE_SIZE %d\n",TABLE_SIZE);
	for(c=list;c;c=c->next){
		context = c->content;
		for(s=context->list;s;s=s->next){
			info = s->content;
			fprintf(fp,"#include \"../../symbols/%s/inc/%s.h\"\n",context->name,info->name);
		}
	}

	for(c=list;c;c=c->next){
		context = c->content;
		fprintf(fp,"#define CONTEXT_%s(UNFOLD,TABLE) ",context->capital);
		for(s=context->list;s;s=s->next){
			info = s->content;
			fprintf(fp,"\\\nUNFOLD(%s,TABLE,%s)",info->name,context->name);
		}
		fprintf(fp,"\n\n");
	}
	fprintf(fp,"#define UNFOLD(SYMBOL,TABLE,NAME) NAME##_##SYMBOL,\n");
	fprintf(fp,"enum ID{\n");
	for(c=list;c;c=c->next){
		context = c->content;
		fprintf(fp,"\tCONTEXT_%s(UNFOLD,TABLE)\n",context->capital);
	}
	fprintf(fp,"end,\n");
	fprintf(fp,"};\n");
	fprintf(fp,"#undef UNFOLD\n\n");
	/*write make context*/
	fprintf(fp,"#define SET_TABLE(SYMBOL,TABLE,NAME) TABLE[NAME##_##SYMBOL]=new SYMBOL();\n");
	fprintf(fp,"#define SET_MAP(SYMBOL,TABLE,NAME) {#SYMBOL,TABLE[NAME##_##SYMBOL]},\n");
	for(c=list;c;c=c->next){
		context = c->content;
		fprintf(fp,"#define MAKE_CONTEXT_%s(LIST,TABLE) \\\n"
		"CONTEXT_%s(SET_TABLE,TABLE) LIST.push_back(make_pair(\"%s\",SymbolMap{CONTEXT_%s(SET_MAP,TABLE)}));\n",
		context->capital,context->capital,context->name,context->capital);
	}
	fprintf(fp,"#define MAKE_CONTEXT(LIST,TABLE) \\\n");
	for(c=list;c;c=c->next){
		context = c->content;
		fprintf(fp,"MAKE_CONTEXT_%s(LIST,TABLE)",context->capital);
		if(c->next){fprintf(fp,"\\");}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n#endif\n");
	free(buf);
	fclose(fp);
}

void fprintIndent(FILE *fp, char *string, int indent){
	char *p;
	int i;
	for(i=0;i<indent;i++){fputc('\t',fp);}
	for(p=string;*p;p++){
		fputc(*p,fp);
		if(*p == '\n'){
			for(i=0;i<indent;i++){fputc('\t',fp);}
		}
	}
}

/*
void datawrite(char *file, List list){
	FILE *fp = fopen(file,"w");
	char *p,*buf;
	List c;
	List s;
	List dlist=NULL,d,dd,prev;
	Context context;
	Info info;
	DataType dt,dt2;

	buf = String_capitalize(getFileName(file));
	fprintf(fp,"#ifndef %s\n",buf);
	fprintf(fp,"#define %s\n",buf);

	fprintf(fp,"#define R64_LIMIT 52\n");
	fprintf(fp,"#define I32_LIMIT 31\n");
	fprintf(fp,"#define I64_LIMIT 63\n");
	fprintf(fp,"class Expr;\n");
	fprintf(fp,"union Data{\n");
	fprintf(fp,"\tData(){};\n");
	fprintf(fp,"\t~Data(){};\n");
	for(c=list;c;c=c->next){
		context = c->content;
		for(s=context->list;s;s=s->next){
			info = s->content;
			if(info->data){
				//fprintf(fp,"\t%s\t",info->data);
				fprintIndent(fp,info->data,1);
				//dlist = List_append(dlist,DataType_parse(info->data));
			}
		}
	}
	fprintf(fp,"};\n");
	fprintf(fp,"#endif\n");
	free(buf);
	fclose(fp);
}
*/

int main(int argc, char *argv[]){
	FILE *fp=stdout,*fp2=stdout;
	List c,list=NULL;
	List s=NULL;
	DIR *dp=NULL;
	struct dirent *entry;
	char dirin[256],*buf,*p;
	if(argc<3){fprintf(stderr,"usage : %s symboldir SymbolList.h\n",argv[0]); return -1;}
	/*fp : header file*/
	/*fp2 : header file 2*/
	if((fp = fopen(argv[2],"w"))==NULL){perror(argv[0]); return -1;}
	//if((fp2 = fopen(argv[3],"w"))==NULL){perror(argv[0]); return -1;}
	if((dp = opendir(argv[1]))==NULL){perror(argv[0]); return -1;}
	spaces = repeatedString(' ',INDENT);
	while((entry=readdir(dp))!=NULL){
		if(entry->d_name[0]=='.'){continue;}
		snprintf(dirin,256,"%s/%s",argv[1],entry->d_name);
		list = master(list,dirin,argv[3]);
	}
	closedir(dp);
	//List_enum(list,Context_vprint);
	listwrite(argv[2],list);
	//datawrite(argv[3],list);

	List_deleteRoot(list,Context_vdelete);
	fclose(fp);
	//fclose(fp2);
	return 0;
}
