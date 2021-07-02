#include<iostream>
#include<fstream>
using namespace std;

void gridPrint(int[],int[],int,int [20][20]);    					//1
int neiArray(int[],int[],int,int[],int[],int[20][20]);				//2
int dupliRemoval(int[],int[],int);									//3
void aliveNeiofNeiArray(int[],int[],int[20][20],int[],int);			//4
void aliveNeiofSecArray(int[],int[],int[20][20],int[],int);			//5
void ruleOne_and_Three(int[],int[],int[],int,int[20][20]);			//6
int deadSecCellRemoval(int[],int[],int);							//7
int ruleTwo(int[],int[],int[],int[],int,int,int[]);					//8

int main(){															//Main Function

	
	int last,gen,neiArraySize,newLast=0;							//Variable Declration
	int inputX[100],inputY[100],secX[100],secY[100],neiX[300],neiY[300],grid[20][20]={0};

	cout<<"Enter Generations: ";
	cin>>gen;
	
	cout<<"Enter Alive Elements: ";
	cin>>last;
	
	ofstream inputFile;
	ofstream outputFile;
	
	inputFile.open("19I-0485 Input.txt");
	
	for(int i=0;i<last;i++){
		
			cout<<"X = ";
			cin>>secX[i];
			cout<<"Y = ";
			cin>>secY[i];
			inputFile<<secX[i]<<secY[i];
			cout<<endl;	
				
		}
	
	inputFile.close();
	

	
	while(gen>0){
		
		gridPrint(secX,secY,last,grid);             			 //1) to make input cells alive in the grid
		cout<<endl;
		
		cout<<"GRID"<<endl;
		cout<<endl;
		cout<<"---------------------------------------"<<endl;
		for(int i=0;i<20;i++){										//Grid Printing
		
			for(int j=0;j<20;j++){
			
				cout<<grid[i][j]<<" ";

		}	
		cout<<endl;
		outputFile<<endl;
	}
		cout<<"---------------------------------------"<<endl;
	
		cout<<endl;
	
		neiArraySize=neiArray(secX,secY,last,neiX,neiY,grid);		//2) Inputs all the neibours of cells in a sec array accept alive cells
	
		neiArraySize=dupliRemoval(neiX,neiY,neiArraySize);			//3) Removes the duplications of cells
	
		cout<<"Neibour Array without Duplication:"<<endl;			
		cout<<endl;
		
		for (int i=0;i<neiArraySize;i++) {							//Prints Neibour Array
														
    	    cout<<neiX[i]<< ","<<neiY[i]<<" ";
        
    	}
   		cout<<endl;
    
    	int aliveNei[neiArraySize]={0};								
   	
    	aliveNeiofNeiArray(neiX,neiY,grid,aliveNei,neiArraySize);		//4) Count of Alive Neibours of Neibour Array
    
   		cout<<"Alive Neibours of Neibour Array:"<<endl;
    	cout<<endl;
    	
		for(int i=0;i<neiArraySize;i++){
		
			cout<<" "<<aliveNei[i]<<"  ";

		}
		cout<<endl;
		cout<<endl;
	
		int aliNeiSec[last]={0};
	
		aliveNeiofSecArray(secX,secY,grid,aliNeiSec,last);				//5) Count of Alive Neibours of Secondary Array
	
		cout<<"Alive Neibours of Secondary Array"<<endl;
		cout<<endl;
	
		for(int i=0;i<last;i++){
		
			cout<<" "<<aliNeiSec[i]<<"  ";
		}
		cout<<endl;
	
		ruleOne_and_Three(secX,secY,aliNeiSec,last,grid);				//6) Applies Rule One and Three
	
	
		cout<<endl;
	
		newLast=deadSecCellRemoval(secX,secY,last);						//7) Removes Dead Cells from Secondary Array 
	
		int size=ruleTwo(secX,secY,neiX,neiY,neiArraySize,newLast,aliveNei);			//8) Applying Rules Two
	
		cout<<"New Secondary Array"<<endl;								
		cout<<endl;
		
		outputFile.open("19I-0485 Output.txt");
		
		for(int i=0;i<(size+newLast);i++){
		
			cout<<secX[i]<<","<<secY[i]<<" ";
			outputFile<<secX[i]<<" "<<secY[i]<<" "<<endl;
		
		}
		cout<<endl;
		outputFile.close();
	
		gen--;
	}
return 0;	
	
}
		
//1) making cells alive in the grid
		
void gridPrint(int secX[],int secY[],int alive,int grid[20][20]){			
	
	int *ptrX=secX,*ptrY=secY;												//pointers pointing secondary array
	
	for(int i=0;i<alive;i++){
			
		grid[*ptrX][*ptrY]=1;												
		ptrX++;
		ptrY++;	
			
	}
		
}

//2) Filling dead cells in neibour Array

int neiArray(int secX[],int secY[],int last,int neiX[],int neiY[],int grid[20][20]){			
	
	int neiCount=0;	
	for(int j=0;j<last;j++){
		
		int *ptrX=secX+j;				
		int *ptrY=secY+j;
		
		int x=-2,y=-1;														//applying the given alogrthm
			
		for(int i=0;i<8;i++){
				
			if(i<3||i>4){
					
				if(x>=1){
					
					x=-2;
				}
				x++;
					
				if(i>4){
				
					y=1;
				
				}
			
			}
			
			else
			if(i==3){
				
				y=0;
				x=-1;
				
			}
			else
			if(i==4){
				
				x=1;		
			}
			
			if(grid[*ptrX+x][*ptrY+y]==1){										//filling neibours cells except the alive ones
				
			}
			
			else{
				
				neiX[neiCount]=(*ptrX)+x;
				neiY[neiCount]=(*ptrY)+y;
				neiCount++;														//size of array
				
				
			}			
		}	
	}
return neiCount;																//returning the size
}

//3) Removing duplications

int dupliRemoval(int neiX[],int neiY[],int neiCount){							
		
	int sizeX=0;
	int sizeY=0;
	
	for (int i=0;i<neiCount;i++){
		
        for (int j=0;j<neiCount;j++) {
        	
            if (i!=j) {
            	
                if (neiX[i]==neiX[j]&&neiY[i]==neiY[j]){						//if found the same value again fill the adress with -1
                	
                    neiX[j]=-1;
                    neiY[j]=-1;
                }
            }
        }
    }
    

    for (int i = 0; i < neiCount; i++) {										
    	
        if (neiX[i] != -1) {												//calculating size except -1 values
        		
            sizeX += 1;
            
        }
        if (neiY[i] != -1) {
        	
            sizeY += 1;
            
        }
    }
	
	 int t = 0;
	 
    for (int i = 0; i < neiCount; i++) {
    	
        if (neiX[i] != -1) {
        	
            neiX[t] = neiX[i];							//filling neibour arrays except -1 values
            t++;
        }
        
    }
    t = 0;
    for (int i = 0; i < neiCount; i++) {
    	
        if (neiY[i] != -1) {
            neiY[t] = neiY[i];
            t++;
        }
	}

return sizeX;													//returning new size of the neibour array
}

//4) Alive Neibours of Neibour Array

void aliveNeiofNeiArray(int neiX[],int neiY[],int grid[20][20],int aliveNei[],int size){     
	
	int*ptrNeiX,*ptrNeiY;
	int count;
	
	for(int j=0;j<size;j++){
		
		count=0;
		ptrNeiX=neiX+j;
		ptrNeiY=neiY+j; 
		int x=-2,y=-1;
		
		for(int i=0;i<8;i++){								//applying the given lograthm
			
			if(i<3||i>4){
					
				if(x>=1){
					
					x=-2;
				}
				x++;
					
				if(i>4){
				
					y=1;
				
				}
			
			}
			
			else
			if(i==3){
				
				y=0;
				x=-1;
				
			}
			else
			if(i==4){
				
				x=1;		
			}
			
			if(grid[*ptrNeiX+x][*ptrNeiY+y]==1){						//if adress value is 1 incriment count
				
				count++;
			
			}

		}
	aliveNei[j]=count;													//filing the Alive Neibour Array with counts
		
	}
	cout<<endl;
	
}

//5) Alive Neibours of Secondary 

void aliveNeiofSecArray(int secX[],int secY[],int grid[20][20],int aliNeiSec[],int last){

	int *ptrX,*ptrY,count;
	for(int j=0;j<last;j++){
		
		count=0;
		ptrX=secX+j;
		ptrY=secY+j; 
		int x=-2,y=-1;
		
		for(int i=0;i<8;i++){					//applying alogrthm
			
			if(i<3||i>4){
					
				if(x>=1){
					
					x=-2;
				}
				x++;
					
				if(i>4){
				
					y=1;
				
				}
			
			}
			
			else
			if(i==3){
				
				y=0;
				x=-1;
				
			}
			else
			if(i==4){
				
				x=1;		
			}
			
			if(grid[*ptrX+x][*ptrY+y]==1){						//if value is 1 incriment count
				
				count++;
			
			}

		}
	 aliNeiSec[j]=count;										//filling alive nei count 
		
	}
}

//6) Applying Rule One and Two

void ruleOne_and_Three(int secX[],int secY[],int aliNeiSec[],int last,int grid[20][20]){
	
	int *ptrX=secX,*ptrY=secY;
	
	for(int i=0;i<last;i++){
		
		if(aliNeiSec[i]<2||aliNeiSec[i]>3){					//if alive neibour count is less than two then cells dies by loneliness
															// and if more than three then it dies by over crowdiness
			
			grid[*ptrX][*ptrY]=0;
			*ptrX=0;
			*ptrY=0;			
		}
		ptrX++;
		ptrY++;
	}
}

//7) Removing the deadcells from secondry array and returning a new last

int deadSecCellRemoval(int secX[], int secY[],int last){

	int t=0;
	
	for(int i=0;i<last;i++){
		
		if(secX[i]&&secY[i]!=0){
			
			secX[t]=secX[i];
			secY[t]=secY[i];
			t++;
			
		}
		
	}
return t;						//returning a new last
}

//8) Applying Rule Two

int ruleTwo(int secX[],int secY[],int neiX[],int neiY[],int neiArraySize,int newLast,int aliveNei[]){

	int t=0;
	int z=0;
	
	for(int i=0;i<neiArraySize;i++){
		
		if(aliveNei[i]==3){								//if a neibour cell has more than three alive neibours it becomes alive in next gen
			
			secX[newLast+t]=neiX[i];
			secY[newLast+t]=neiY[i];
			
			t++;
			z++;
			
		}
		
	}
											
return z;
}

