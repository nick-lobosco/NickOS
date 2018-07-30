typedef struct gdtentry GDTE;
 struct gdtentry{
	short limit1;
	short base1;
	char base2;
	char access;
	char flags;
	char base3;
}__attribute__((packed));


struct gdtDescriptor{
	short size;
	unsigned int gdtPtr;
}__attribute__((packed));
typedef struct gdtDescriptor GDTD;

typedef struct idtd{
	short size;
	int address;
}IDTD;

typedef struct idtEntry{
	uint16_t offset1;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset2;
}IDTE;

void printGdtEntry(GDTE *gdte){
	printf("%d %d %d %d %d %d\n", gdte->limit1, gdte->base1, gdte->base1, gdte->access, gdte->flags, gdte->base3);
}

void printGDT(GDTD *gdtd){
	printf("%d\n%d\n",gdtd->size, gdtd->gdtPtr);
	int i;
	for(i=0;i<(gdtd->size);i+=8){
		printGdtEntry((GDTE*)(gdtd->gdtPtr+i));
	}
}

