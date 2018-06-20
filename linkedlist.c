#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>

typedef struct node{
	int data;
	struct node*next;
} Node;

Node* makeNewNode (int data, Node* next){
	Node* newNode=(Node*)malloc(sizeof(Node));
	if (newNode==NULL){
		printf("ERROR\n");
	}
	newNode->data=data;
	newNode->next=next;
	return newNode;
}
Node *insert(Node* head, int newData){

	if (head==NULL){
		Node* newNode=makeNewNode(newData, head);
		head=newNode;
		return head;
	}
	Node* nextNode=head->next;
	Node* current = head;
	Node* temp=head;
	if (head->data==newData){
		return head;
	}
	if (head->data>newData){
		temp=head;
		head=makeNewNode(newData, temp);
		return head;
	}
	if (nextNode==NULL){
		current->next=makeNewNode(newData, NULL);
		return head;
	}
	
		while(nextNode->data<newData&&nextNode->next!=NULL){
			current=current->next;
			nextNode=current->next;
		}
		if (nextNode->data==newData){
			return head;
		}	
		else if (nextNode->next==NULL){
			if(nextNode->data<newData){
				nextNode->next=makeNewNode(newData, NULL);
				return head;
			}
			else{
				current->next=makeNewNode(newData, nextNode);
				return head;
			}
		}
		else{		
			current->next=makeNewNode(newData, nextNode);	
			return head;			
		}
		
}
Node* search (Node* head, int data){
	Node* current = head;
	while(current!=NULL){
		if (current->data==data)
			return current;
		current=current->next;
	}
	return NULL;
}
int countNodes(Node*head){
	Node*current=head;
	int count=0;
	while(current!=NULL){
		++count;
		current=current->next;
	}
	return count;
}
Node* delete(Node* head, int num){
	Node* target= search(head, num);
	if (target==NULL){
		return head;
	}
	Node* current=head;
	Node* nextNode=current->next;
	Node* prevNode=NULL;
	while(current!=target){
		prevNode=current;
		current=current->next;
		nextNode=current->next;
	}
	if (prevNode==NULL){
		return nextNode;
	}
	else{
		prevNode->next=current->next;
		current=prevNode;
		return head;
	}
}

int main (int argc, char * argv[]){
	
	Node *head=NULL;
	int count=0;
	int fd =open (argv[1], O_RDONLY);
	if (fd==-1){
		return -1;
	}
	int i=0;
	int numBytes=500;
	int numRead=0;
	char*buffer=(char*) malloc(sizeof(char)*numBytes);
	for (i=0; i<numBytes-1; ++i){
		buffer[i]='\0';
	}
	while ((numRead =read(fd, buffer, numBytes))!=0){
		if (numRead==-1){
			return -1;
		}
	
		int a=0;
		int b=0;
		char*line=(char*) malloc(sizeof(char)*(numRead));

		while (b<numRead){
			
			while(b<numRead && buffer[b]!='\n'){
				line[a]=buffer[b];
				++a;
				++b;
			}
			
			if (b>=numRead-1&& buffer[b]!='\n'){
			}
			line[a]='\0';
	
			char op= line[0];
			char*num=(char*) malloc(sizeof(char)*(b));
			int k=0;
			for (i=2; i<b; ++i){
				if (!(isdigit(line[i]))){
					printf("error\n");
				}
				num[k]=line[i];
				++k;
			}
			int target = atoi(num);
			free(num);
			switch(op){
				case 'i': 
					head=insert(head, target);
					++count;
					break;
				case 'd':
					head=delete(head, target);
					break;
				default:
					printf("error\n");
					return 0;
			}
			
			for (k=0; k<a;++k){
				line[k]='\0'; 
			}
			a=0;
			++b;;
		}
		free(line);
	}
	free(buffer);
	close(fd);
	Node*current=head;
	printf("%d\n",countNodes(head));
	while(current!=NULL){
		printf("%d\t", current->data);
		current=current->next;
	}
	return 0;
}
