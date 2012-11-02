#include "tablecheck.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void hex(unsigned int *val,int size) {	//show L0 R0 in hex notation
	for(int i=0;i<size;i+=4) {
		unsigned int temp=(val[i]*8)+(val[i+1]*4)+(val[i+2]*2)+val[i+3];
		fprintf(stderr,"%x",(unsigned char)temp);
	}
	
}

unsigned int Xor(unsigned int a, unsigned int b) {	//perform XOR
	if(a==1 && b==1)
		return 0;
	if(a==1 || b==1)
		return 1;
	return 0;
}

unsigned int** subkeys(char* key, unsigned int* PC1, unsigned int* PC2, unsigned int* V, bool output) {	//create Subkeys
	int i,j=0;
	unsigned int **kn;
	kn=new unsigned int *[16];
	for(i=0;i<16;i++) {
		kn[i]= new unsigned int[48];
	}
	unsigned int keybits[64];
	for(i=0;i<16;i++) {
		if(key[i]>='A' && key[i]<='F') {
			key[i]-=55;
		}
		if(key[i]>='a' && key[i]<='f') {
			key[i]-=87;
		}
		int t; 
		for(t=8; t>0; t = t/2) {
			if(key[i] & t) {
				keybits[j++]=1;
				} else {
					keybits[j++]=0;
				}
			}
	}
	//hex(keybits,64);
	
	//create sub keys
	unsigned int kpc1[56];
	//PC1 transformation
	for(i=0;i<56;i++) {
		kpc1[i]=keybits[PC1[i]-1];
	}
	//split into C0 D0
	unsigned int c[17][28],d[17][28];
	memcpy(c[0],kpc1,sizeof(unsigned int)*28);
	memcpy(d[0],&kpc1[28],sizeof(unsigned int)*28);
	
	//check for weak keys
	unsigned int weak1[28]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned int weak2[28]={0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	unsigned int weak3[28]={1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
	unsigned int weak4[28]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	if(memcmp(c[0],weak1,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak1,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak4,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak4,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak2,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak2,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak2,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak3,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak2,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak1,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak2,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak4,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak1,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak2,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak4,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak2,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak3,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak3,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak3,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak2,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak3,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak1,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak3,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak4,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak1,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak3,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	if(memcmp(c[0],weak4,sizeof(unsigned int)*28)==0 && memcmp(d[0],weak3,sizeof(unsigned int)*28)==0) {
		fprintf(stderr,"Semi-Weak Key Generated\n");
		exit(1);
	}
	
	//start circular shift rounds
	unsigned int temp1,temp2,tempc[28],tempd[28];
	for(i=1;i<17;i++) {
		memcpy(tempc,c[i-1],sizeof(unsigned int)*28);
		memcpy(tempd,d[i-1],sizeof(unsigned int)*28);
		for(j=0;j<(int)V[i-1];j++) {
			temp1=tempc[0];
			temp2=tempd[0];
			for(int k=1;k<28;k++) {
				tempc[k-1]=tempc[k];
				tempd[k-1]=tempd[k];
			}
			tempc[27]=temp1;
			tempd[27]=temp2;
		}
		memcpy(c[i],tempc,sizeof(unsigned int)*28);
		memcpy(d[i],tempd,sizeof(unsigned int)*28);
	}
	//Kn
	//PC2 transformation
	for(i=0;i<16;i++) {
		for(j=0;j<48;j++) {
			if(PC2[j]<=28) {
				kn[i][j]=c[i+1][PC2[j]-1];
			}
			else {
				kn[i][j]=d[i+1][PC2[j]-29];
			} 
		}
	}
	if(output) {
		for(i=0;i<17;i++) {
			fprintf(stderr,"(C%d,D%d)=",i,i);
			hex(c[i],28);
			hex(d[i],28);
			fprintf(stderr,"\n");
			if(i==0)
				continue;
			fprintf(stderr,"k%d=",i);
			hex(kn[i-1],48);
			fprintf(stderr,"\n");
		}
	}
	return kn;	//return K1...K16
}

void encryptDES(FILE *f, FILE *tf, char* key,char mode) {	//enryption function
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
	unsigned int IP1[64];
	for(unsigned int i=0;i<64;i++) {
		for(int j=0;j<64;j++) {
			if((i+1)==IP[j]) {
				IP1[i]=j+1;
				break;
			}
		}
	}
	unsigned int **kn;
	kn=subkeys(key,PC1,PC2,V,true);	//generate subkeys
	//get sub keys
	int i,j;
	int result=0;
	unsigned char *buff=new unsigned char[8];
	bool output=true;
	FILE *of;
	of=stdout;
	unsigned char *buffer=new unsigned char;
	while(true) {	//read input file
		result=fread(buff,1,8,f);
		if(result==0) {
			break;
		}
		unsigned int M[64];
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
		unsigned int MIP[64];
		for(i=0;i<64;i++) {	//IP transformation
			MIP[i]=M[IP[i]-1];
		}
		//L0 R0 split
		unsigned int L[17][32],R[17][32];
		memcpy(L[0],MIP,sizeof(unsigned int)*32);
		memcpy(R[0],&MIP[32],sizeof(unsigned int)*32);
		if(output) {	
			fprintf(stderr,"(L0,R0)=");
			hex(L[0],32);
			hex(R[0],32);
			fprintf(stderr,"\n");
		}
		for(int x=1;x<17;x++) {	//begin encryption rounds
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
			if(output) {
				fprintf(stderr,"(L%d,R%d)=",x,x);
				hex(L[x],32);
				hex(R[x],32);
				fprintf(stderr,"\n");
			}
		}	//end round
		output=false;
		//reverse order
		memcpy(M,R[16],sizeof(unsigned int)*32);
		memcpy(&M[32],L[16],sizeof(unsigned int)*32);
		//inverse permutation
		unsigned int C[64];
		for(i=0;i<64;i++) {
			C[i]=M[IP1[i]-1];
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

