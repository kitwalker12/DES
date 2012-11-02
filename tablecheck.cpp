#include "tablecheck.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

unsigned int* createtable(char* token, int size) {	//reads line from table file and creates table as array
	unsigned int *table=new unsigned int[size];
	int length=0;
	int i=0;
	while(token!=NULL) {
		unsigned int val=atoi(token);
		//printf("%d ",val);
		table[i++]=val;
		token=strtok(NULL,",");
		length++;
	}
	if(length!=size) {
		return NULL;
	}
	else {
		return table;
	}
}

bool Everify(unsigned int* table, int size, int tablesize) {	//verify E table
	unsigned int* verify = new unsigned int[size];
	for(int i=0;i<size;i++) {
		verify[i]=0;
	}
	for(int i=0;i<tablesize;i++) {
		verify[table[i]-1]++;
	}
	for(int i=0;i<size;i++) {
		if(verify[i]!=1 && verify[i]!=2) {
			free(verify);
			return false;
		}
	}
	free(verify);
	return true;
}

bool PC2verify(unsigned int* table, int size, int tablesize) {	//verify PC2 table
	unsigned int* verify = new unsigned int[size];
	for(int i=0;i<size;i++) {
		verify[i]=0;
	}
	for(int i=0;i<tablesize;i++) {
		verify[table[i]-1]++;
	}
	for(int i=0;i<size;i++) {
		if(verify[i]!=1 && verify[i]!=0) {
			free(verify);
			return false;
		}
	}
	free(verify);
	return true;
}

bool Vverify(unsigned int* table) {	//verify V table
	int ones=0,twos=0;
	for(int i=0;i<16;i++) {
		if(table[i]!=1 && table[i]!=2) {
			return false;
		}
		if(table[i]==1)
			ones++;
		if(table[i]==2)
			twos++;	
	}
	if(ones!=4 && twos!=12) {
		return false;
	}
	return true;
}

bool tablecheck(FILE *f) {	//read table file and returns false if error in table
	char* line;
	line=new char[200];
	while(fgets (line , 200 , f) != NULL) {
		char* value=strchr(line,'=');
		if(value==NULL) {
			fputs("Malformed tablefile\n",stderr);
			exit(1);
		}
		line[value-line]='\0';
		value++;
		//printf("%s=",line);
		char *token;
		token=strtok(value,",");
		unsigned int *IP,*E,*P,*S1,*S2,*S3,*S4,*S5,*S6,*S7,*S8,*V,*PC1,*PC2;
		if(strcmp(line,"IP")==0) {
			IP=createtable(token,64);
			if(IP==NULL) {
				fputs("Error in table IP:Invalid Length\n",stderr);
				return false;
			}
			int count=2080;
			for(int i=0;i<64;i++) {
				count=count-IP[i];
			}
			if(count!=0) {
				fputs("Error in table IP:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"E")==0) {
			E=createtable(token,48);
			if(E==NULL) {
				fputs("Error in table E:Invalid Length\n",stderr);
				return false;
			}
			if(!Everify(E,32,48)) {
				fputs("Error in table E:Value repeated more than twice\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"P")==0) {
			P=createtable(token,32);
			if(P==NULL) {
				fputs("Error in table P:Invalid Length\n",stderr);
				return false;
			}
			int count=528;
			for(int i=0;i<32;i++) {
				count=count-P[i];
			}
			if(count!=0) {
				fputs("Error in table P:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S1")==0) {
			S1=createtable(token,64);
			if(S1==NULL) {
				fputs("Error in table S1:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S1[i];
			}
			if(count!=0) {
				fputs("Error in table S1:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S2")==0) {
			S2=createtable(token,64);
			if(S2==NULL) {
				fputs("Error in table S2:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S2[i];
			}
			if(count!=0) {
				fputs("Error in table S2:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S3")==0) {
			S3=createtable(token,64);
			if(S3==NULL) {
				fputs("Error in table S3:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S3[i];
			}
			if(count!=0) {
				fputs("Error in table S3:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S4")==0) {
			S4=createtable(token,64);
			if(S4==NULL) {
				fputs("Error in table S4:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S4[i];
			}
			if(count!=0) {
				fputs("Error in table S4:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S5")==0) {
			S5=createtable(token,64);
			if(S5==NULL) {
				fputs("Error in table S5:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S5[i];
			}
			if(count!=0) {
				fputs("Error in table S5:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S6")==0) {
			S6=createtable(token,64);
			if(S6==NULL) {
				fputs("Error in table S6:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S6[i];
			}
			if(count!=0) {
				fputs("Error in table S6:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S7")==0) {
			S7=createtable(token,64);
			if(S7==NULL) {
				fputs("Error in table S7:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S7[i];
			}
			if(count!=0) {
				fputs("Error in table S7:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"S8")==0) {
			S8=createtable(token,64);
			if(S8==NULL) {
				fputs("Error in table S8:Invalid Length\n",stderr);
				return false;
			}
			int count=120;
			for(int i=0;i<16;i++) {
				count=count-S8[i];
			}
			if(count!=0) {
				fputs("Error in table S8:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"V")==0) {
			V=createtable(token,16);
			if(V==NULL) {
				fputs("Error in table V:Invalid Length\n",stderr);
				return false;
			}
			if(!Vverify(V)) {
				fputs("Error in table V:Invalid number of 1s or 2s\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"PC1")==0) {
			PC1=createtable(token,56);
			if(PC1==NULL) {
				fputs("Error in table PC1:Invalid Length\n",stderr);
				return false;
			}
			int count=1792;
			for(int i=0;i<56;i++) {
				count=count-PC1[i];
			}
			if(count!=0) {
				fputs("Error in table PC1:Value is invalid, missing or repeated\n",stderr);
				return false;
			}
		}
		if(strcmp(line,"PC2")==0) {
			PC2=createtable(token,48);
			if(PC2==NULL) {
				fputs("Error in table PC2:Invalid Length\n",stderr);
				return false;
			}
			if(!PC2verify(PC2,56,48)) {
				fputs("Error in table PC2:Value is repeated\n",stderr);
				return false;
			}
		}
		//cout<<endl;		
	}
	rewind(f);
	return true;
}

