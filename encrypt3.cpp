#include "tablecheck.h"
#include "encrypt.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//encryption function for single DES round (Same as one in encrypt.cpp)
unsigned int* encrypt(unsigned int* M, unsigned int* IP, unsigned int* E, unsigned int** S, unsigned int* P, unsigned int** kn, char mode, unsigned int* IP1) {
	unsigned int MIP[64];
	int i,j,t;
	//IP transformation
	for(i=0;i<64;i++) {
		MIP[i]=M[IP[i]-1];
	}
	//L0 R0
	unsigned int L[17][32],R[17][32];
	memcpy(L[0],MIP,sizeof(unsigned int)*32);
	memcpy(R[0],&MIP[32],sizeof(unsigned int)*32);
	
	for(int x=1;x<17;x++) {	//begin encryption round
		//Ln
		memcpy(L[x],R[x-1],sizeof(unsigned int)*32);
		
		//f(Rn-1,Kn)
		//E(R0)
		unsigned int ER[48];
		for(i=0;i<48;i++) {
			ER[i]=R[x-1][E[i]-1];
		}
		unsigned int B[48];
		for(i=0;i<48;i++) {
			if(mode=='e') {
				B[i]=Xor(ER[i],kn[x-1][i]);
			} else {
				B[i]=Xor(ER[i],kn[16-x][i]);
			}
		}
		//S(B)
		unsigned int SB[32];
		j=0;
		int k=0;
		for(i=0;i<48;i+=6,j++) {
			int row=(B[i]*2)+B[i+5];
			int col=(B[i+1]*8)+(B[i+2]*4)+(B[i+3]*2)+B[i+4];
			int index=col+(row*16);
			for(t=8;t>0;t/=2) {
				if(S[j][index]&t) {
					SB[k++]=1;
				} else {
					SB[k++]=0;
				}
			}
		}
		//P
		unsigned int F[32];
		for(i=0;i<32;i++) {
			F[i]=SB[P[i]-1];
		} 
		//end f() and XOR with Ln
		for(i=0;i<32;i++) {
			R[x][i]=Xor(L[x-1][i],F[i]);
		}
	}	//end round
	//reverse order
	memcpy(M,R[16],sizeof(unsigned int)*32);
	memcpy(&M[32],L[16],sizeof(unsigned int)*32);
	//inverse permutation
	unsigned int *C;
	C=new unsigned int[64];
	for(i=0;i<64;i++) {
		C[i]=M[IP1[i]-1];
	}
	return C;
}

void encrypt3DES(FILE *f, FILE *tf, char* key,char mode) {	//calls DES functions in order
	char* line;
	line=new char[200];
	unsigned int *IP,*E,*P,*V,*PC1,*PC2;
	unsigned int **S;
	S=new unsigned int *[8];
	for(int i=0;i<8;i++) {
		S[i]= new unsigned int[64];
	}
	while(fgets (line , 200 , tf) != NULL) {	//read table file
		char* value=strchr(line,'=');
		line[value-line]='\0';
		value++;
		//printf("%s=",line);
		char *token;
		token=strtok(value,",");
		if(strcmp(line,"IP")==0) {
			IP=createtable(token,64);
		}
		if(strcmp(line,"E")==0) {
			E=createtable(token,48);
		}
		if(strcmp(line,"P")==0) {
			P=createtable(token,32);
		}
		if(strcmp(line,"S1")==0) {
			S[0]=createtable(token,64);
		}
		if(strcmp(line,"S2")==0) {
			S[1]=createtable(token,64);
		}
		if(strcmp(line,"S3")==0) {
			S[2]=createtable(token,64);
		}
		if(strcmp(line,"S4")==0) {
			S[3]=createtable(token,64);
		}
		if(strcmp(line,"S5")==0) {
			S[4]=createtable(token,64);
		}
		if(strcmp(line,"S6")==0) {
			S[5]=createtable(token,64);
		}
		if(strcmp(line,"S7")==0) {
			S[6]=createtable(token,64);
		}
		if(strcmp(line,"S8")==0) {
			S[7]=createtable(token,64);
		}
		if(strcmp(line,"V")==0) {
			V=createtable(token,16);
		}
		if(strcmp(line,"PC1")==0) {
			PC1=createtable(token,56);
		}
		if(strcmp(line,"PC2")==0) {
			PC2=createtable(token,48);
		}
	}	//end table create
	
	//create IP-inverse
	unsigned int *IP1;
	IP1=new unsigned int[64];
	for(unsigned int i=0;i<64;i++) {
		for(int j=0;j<64;j++) {
			if((i+1)==IP[j]) {
				IP1[i]=j+1;
				break;
			}
		}
	}
	
	//get sub keys
	unsigned int **kn1,**kn2,**kn3;
	char *key1,*key2,*key3;
	key1=new char[16];
	key2=new char[16];
	key3=new char[16];
	memcpy(key1,key,sizeof(char)*16);
	memcpy(key2,&key[16],sizeof(char)*16);
	memcpy(key3,&key[32],sizeof(char)*16);
	kn1=subkeys(key1,PC1,PC2,V,false);
	kn2=subkeys(key2,PC1,PC2,V,false);
	kn3=subkeys(key3,PC1,PC2,V,false);
	int i,j;

	int result=0;
	unsigned char *buff=new unsigned char[8];
	FILE *of;
	of=stdout;
	unsigned char *buffer=new unsigned char;
	while(true) {	//read input file
		result=fread(buff,1,8,f);
		if(result==0) {
			break;
		}
		unsigned int* M;
		M=new unsigned int[64];
		int t;
		j=0;
		if(result<8) {
			for(i=0;i<result;i++) {
				for(t=128;t>0;t/=2) {
					if(buff[i]&t) {
						M[j++]=1;
					} else {
						M[j++]=0;
					}
				}
			}
			for(i=0;i<((8-result)*8);i++) {
				M[j++]=0;
			}
		} else {
			for(i=0;i<8;i++) {
				for(t=128;t>0;t/=2) {
					if(buff[i]&t) {
						M[j++]=1;
					} else {
						M[j++]=0;
					}
				}
			}
		}
		
		unsigned int* C;
		if(mode=='e') {	//depending on mode call encryption function in order
			C=encrypt(M,IP,E,S,P,kn1,'e',IP1);
			C=encrypt(C,IP,E,S,P,kn2,'d',IP1);
			C=encrypt(C,IP,E,S,P,kn3,'e',IP1);
		} else {
			C=encrypt(M,IP,E,S,P,kn3,'d',IP1);
			C=encrypt(C,IP,E,S,P,kn2,'e',IP1);
			C=encrypt(C,IP,E,S,P,kn1,'d',IP1);
		}
		//write to stdout
		for(i=0;i<64;i+=8) {
			unsigned int val=(C[i]*128)+(C[i+1]*64)+(C[i+2]*32)+(C[i+3]*16)+(C[i+4]*8)+(C[i+5]*4)+(C[i+6]*2)+C[i+7];
			*buffer=val;
			fwrite(buffer,1,1,of);
		}
	}//end reading plaintext file
	fclose(of);
}

