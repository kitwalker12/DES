#include "tablecheck.h"
#include "encrypt.h"
#include "encrypt3.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main (int argc, char *argv[]) {
	if(argc==3) {
		if(strcmp(argv[1],"tablecheck")==0) {	//prepare table check params
			string option,param,temp;
			temp=argv[2];
			option=temp.substr(0,3);
			if(option.compare("-t=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				FILE *f;
				f=fopen(param.c_str(),"rb");
				if(f==NULL) {fputs("Error in opening table file\n",stderr);exit(1);}
				bool res=tablecheck(f);	//call table check
				if(!res) {
					exit(1);
				}
				fclose(f);
				return 0;
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
		}
		else {
			fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
			exit(1);
		}
	}
	else if(argc==4 || argc==5) {
		if(strcmp(argv[1],"encrypt")==0) {	//prepare DES encrypt params
			string option,param,temp;
			char* key;
			FILE *f,*tf;
			temp=argv[3];
			option=temp.substr(0,3);
			if(option.compare("-t=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				tf=fopen(param.c_str(),"rb");
				if(tf==NULL) {fputs("Error in opening table file\n",stderr);exit(1);}
				bool res=tablecheck(tf);	//call tablecheck
				if(!res) {
					exit(1);
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			temp=argv[2];
			option=temp.substr(0,3);
			if(option.compare("-k=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				if(param.length()!=16){
					fputs("Invalid Key length\n",stderr);
					exit(1);
				}
				key = new char[param.length()];
				strcpy(key,param.c_str());
				for(int i=0;i<16;i++) {
					if((key[i]<'0' || key[i]>'9') && (key[i]<'A' || key[i]>'F') && (key[i]<'a' || key[i]>'f')) {
						fputs("Invalid Key\n",stderr);
						exit(1);
					}
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			if(argc==5) {
				f=fopen(argv[4],"rb");
				if(f==NULL) {fputs("Error in opening plaintext file\n",stderr);exit(1);}
			} else {
				f=stdin;
			}
			encryptDES(f,tf,key,'e');	//call encryption function
			fclose(f);
			fclose(tf);
			return 0;
		}
		if(strcmp(argv[1],"decrypt")==0) {	//prepare decryption params
			string option,param,temp;
			char* key;
			FILE *f,*tf;
			temp=argv[3];
			option=temp.substr(0,3);
			if(option.compare("-t=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				tf=fopen(param.c_str(),"rb");
				if(tf==NULL) {fputs("Error in opening table file\n",stderr);exit(1);}
				bool res=tablecheck(tf);	//verify table
				if(!res) {
					exit(1);
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			temp=argv[2];
			option=temp.substr(0,3);
			if(option.compare("-k=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				if(param.length()!=16){
					fputs("Invalid Key length\n",stderr);
					exit(1);
				}
				key = new char[param.length()];
				strcpy(key,param.c_str());
				for(int i=0;i<16;i++) {
					if((key[i]<'0' || key[i]>'9') && (key[i]<'A' || key[i]>'F') && (key[i]<'a' || key[i]>'f')) {
						fputs("Invalid Key\n",stderr);
						exit(1);
					}
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			if(argc==5) {
				f=fopen(argv[4],"rb");
				if(f==NULL) {fputs("Error in opening plaintext file\n",stderr);exit(1);}
			} else {
				f=stdin;
			}
			encryptDES(f,tf,key,'d');	//call encryption function with inverted keys
			fclose(f);
			fclose(tf);
			return 0;
		}
		if(strcmp(argv[1],"encrypt3")==0) {	//prepare 3DES params
			string option,param,temp;
			char* key;
			FILE *f,*tf;
			temp=argv[3];
			option=temp.substr(0,3);
			if(option.compare("-t=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				tf=fopen(param.c_str(),"rb");
				if(tf==NULL) {fputs("Error in opening table file\n",stderr);exit(1);}
				bool res=tablecheck(tf);	//verify table
				if(!res) {
					exit(1);
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			temp=argv[2];
			option=temp.substr(0,3);
			if(option.compare("-k=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				if(param.length()!=48){
					fputs("Invalid Key length\n",stderr);
					exit(1);
				}
				key = new char[param.length()];
				strcpy(key,param.c_str());
				for(int i=0;i<48;i++) {
					if((key[i]<'0' || key[i]>'9') && (key[i]<'A' || key[i]>'F') && (key[i]<'a' || key[i]>'f')) {
						fputs("Invalid Key\n",stderr);
						exit(1);
					}
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			if(argc==5) {
				f=fopen(argv[4],"rb");
				if(f==NULL) {fputs("Error in opening plaintext file\n",stderr);exit(1);}
			} else {
				f=stdin;
			}
			encrypt3DES(f,tf,key,'e');	//call 3DES encryption function
			fclose(f);
			fclose(tf);
			return 0;
		}
		if(strcmp(argv[1],"decrypt3")==0) {	//prepare 3DES decrypt params
			string option,param,temp;
			char* key;
			FILE *f,*tf;
			temp=argv[3];
			option=temp.substr(0,3);
			if(option.compare("-t=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				tf=fopen(param.c_str(),"rb");
				if(tf==NULL) {fputs("Error in opening table file\n",stderr);exit(1);}
				bool res=tablecheck(tf);	//verify table
				if(!res) {
					exit(1);
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			temp=argv[2];
			option=temp.substr(0,3);
			if(option.compare("-k=")==0) {
				param=temp.substr(3,temp.length());
				if(param.compare("")==0) {
					fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
					exit(1);
				}
				if(param.length()!=48){
					fputs("Invalid Key length\n",stderr);
					exit(1);
				}
				key = new char[param.length()];
				strcpy(key,param.c_str());
				for(int i=0;i<48;i++) {
					if((key[i]<'0' || key[i]>'9') && (key[i]<'A' || key[i]>'F') && (key[i]<'a' || key[i]>'f')) {
						fputs("Invalid Key\n",stderr);
						exit(1);
					}
				}
			}
			else {
				fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
				exit(1);
			}
			if(argc==5) {
				f=fopen(argv[4],"rb");
				if(f==NULL) {fputs("Error in opening plaintext file\n",stderr);exit(1);}
			} else {
				f=stdin;
			}
			encrypt3DES(f,tf,key,'d');	//call 3DES function in descrypt mode
			fclose(f);
			fclose(tf);
			return 0;
		}
		fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
		exit(1);
	}
	else {
		fputs("Error! Usage: ./hw5 [tablecheck|encrypt|decrypt|encrypt3|decrypt3] [-k=<key>] [-t=<tablefile>] [file]\n",stderr);
		exit(1);
	}
}

