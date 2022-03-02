int PList_check(PList list, void *pointer, int *index, size_t *size, char **funcname){
	*index=-1; *size = 0;
	if(!pointer){return *index;}
	for(;list;list=list->next){
		if(list->pointer == pointer){
			list->deallocated=1;
			*index = list->index;
			*size = list->size;
			*funcname = (char*)(list->funcname);
			list->pointer = NULL;
			break;
		}
	}
	return *index;
}
